// including the required header files
#include "radio_interface.h"
// =====================================================================================
// variable defitions

/** RF driver variables and params */
static RF_Object rf_obj;
static RF_Handle rf_handle;
static RF_CmdHandle rf_cmd_handle;

/** reception data buffer variables and parameters */
static uint8_t
rx_buffer[RF_QUEUE_DATA_ENTRY_BUFFER_SIZE(NUM_DATA_ENTRIES,
                                                  MAX_LENGTH,
                                                  NUM_APPENDED_BYTES)]
                                                  __attribute__((aligned(4)));

static dataQueue_t dataQueue;
static rfc_dataEntryGeneral_t* currentDataEntry;
static uint8_t packetLength;
static uint8_t* packetDataPointer;
static uint8_t packet[MAX_LENGTH + NUM_APPENDED_BYTES - 1];

/** transmitting packet varaibles and parameters */
static uint8_t tx_packet[PAYLOAD_LENGTH];
// ====================================================================================
// helper functions

/* Callback function called when data is received via RF */
void rx_callback(RF_Handle h, RF_CmdHandle ch, RF_EventMask e)
{
    if (e & RF_EventRxEntryDone)
    {

        /* Get current unhandled data entry */
        currentDataEntry = RFQueue_getDataEntry(); //loads data from entry

        /* Handle the packet data, located at &currentDataEntry->data:
        packetLength      = *(uint8_t*)(&currentDataEntry->data); //gets the packet length (send over with packet)
        packetDataPointer = (uint8_t*)(&currentDataEntry->data + 1); //data starts from 2nd byte

        /* Copy the payload + the status byte to the packet variable */
        memcpy(packet, packetDataPointer, (packetLength + 1));

        /* Move read entry pointer to next entry */
        RFQueue_nextEntry();
    }
}



// =====================================================================================
// functions

int radio_init(void){

    RF_Params rfParams;
    RF_Params_init(&rfParams);

    if(RFQueue_defineQueue(&dataQueue,
                                rx_buffer,
                                sizeof(rx_buffer),
                                NUM_DATA_ENTRIES,
                                MAX_LENGTH + NUM_APPENDED_BYTES)){
        return -1;
     }


    /** updating the rf_command for the rx mode */
    RF_cmdPropRx.pQueue = &dataQueue;
    RF_cmdPropRx.rxConf.bAutoFlushIgnored = 1;
    RF_cmdPropRx.rxConf.bAutoFlushCrcErr = 1;
    RF_cmdPropRx.maxPktLen = MAX_LENGTH;
    RF_cmdPropRx.pktConf.bRepeatOk = 1;
    RF_cmdPropRx.pktConf.bRepeatNok = 1;
    RF_cmdPropTx.pPkt = packet;
    RF_cmdPropTx.startTrigger.triggerType = TRIG_NOW;


    /** updating the rf_command for the tx mode */
    RF_cmdPropTx.pktLen = AIR_PAYLOAD_LENGTH;
    RF_cmdPropTx.pPkt = tx_packet;
    RF_cmdPropTx.startTrigger.triggerType = TRIG_NOW;


    rf_handle = RF_open(&rf_obj, &RF_prop, (RF_RadioSetup*)&RF_cmdPropRadioDivSetup, &rfParams);
    RF_postCmd(rf_handle, (RF_Op*)&RF_cmdFs, RF_PriorityNormal, NULL, 0);

     return 0;
 }



 int radio_send(uint8_t *data, uint16_t data_len){
    if (!data) return -1;

    uint32_t safe_size = 0;
    if (data_len < AIR_PAYLOAD_LENGTH){
        safe_size = data_len;
    } else {
        safe_size = AIR_PAYLOAD_LENGTH;
    }
    // updating the tx ari packet
    memcpy(tx_packet, data, safe_size);

    RF_EventMask RF_ret = RF_runCmd(rfHandle, (RF_Op*)&RF_cmdPropTx,
                                          RF_PriorityNormal, NULL, 0);
    
    return 0;
 }


 int radio_receive(void){

    rf_handle = RF_postCmd(rfHandle, (RF_Op*)&RF_cmdPropRx, RF_PriorityNormal, rx_callback, RF_EventRxEntryDone);

    return 0;
 }