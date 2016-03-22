/*
 * File name:
     NRF905_DRIVER.c
 * Copyright:
     HAZEM ELSAYED.
     hazem.elsayed@telia.com
 * Revision History:
     20150822:
       - Rev.1
*/
#include "nrf905_driver.h"
/************************************************************************
* Digital input control, power up, tx, rx
************************************************************************/
extern sfr sbit PWR_UP_NRF_bit;
extern sfr sbit TX_EN_NRF_bit;
extern sfr sbit TRX_CE_NRF_bit;
/************************************************************************
* Digital output indicators, carrier detect, address match, data ready
************************************************************************/
extern sfr sbit DR_NRF_bit;
/************************************************************************
* SPI - interface (chip select)
************************************************************************/
extern sfr sbit CS_NRF_bit;
/************************************************************************
* Nrf905 macro configuration registers
************************************************************************/
#define ASSIGN_TX_ADDR_REG      0x22 // ASSIGN TX ADDRESS REGISTER
#define TX_PAYLOAD_REG          0x20 // TX PAYLOAD WIDTH REGISTER
#define RX_PAYLOAD_REG          0x24 // TX PAYLOAD WIDTH REGISTER
#define RX_PAYLOAD_WEDTH_REG    0x03 // RX PAYLOAD WIDTH REGISTER
#define RX_PAYLOAD_WEDTH        0x01 // RX PAYLOAD WIDTH 1-32 BYTE (CAN BE CHANGED)
#define TX_PAYLOAD_WEDTH_REG    0x04 // TX PAYLOAD WIDTH REGISTER
#define TX_PAYLOAD_WEDTH        0x01 // TX PAYLOAD WIDTH 1-32 BYTE (CAN BE CHANGED)
#define CHANNEL_REG             0x00 // CHANNELS RANGE REGISTER 1-170
#define CHANNEL                 0x6C // CHANNEL NO 108  (CAN BE CHANGED)
#define XTAL_REG                0x09 // XTAL SETTING REGISTER
#define _16MHZ                  0xD8 // XTAL 16 MHZ
#define TXRX_ADDR_WIDTH_REG     0x02 // TX/RX ADDRESS WIDTH REGISTER
#define _4BYTE                  0x44 // 4 BYTE ADDRESS WIDTH
#define NRF_PWR_REG             0x01 // NRF905 POWER REGISTER
#define NRF_PWR_10DBM           0x0C // +10 dBm
#define START_SPI               0x00 // ENTER SPI MODE
#define EXIT_SPI                0x01 // EXIT SPI MODE
#define SPI_RECOVER_TIME        0x32 // EXIT SPI MODE
#define POWER_UP_REC_TIME       0x05 //POWER UP RECOVER TIME
#define RX_REG_LOC              0x05 // RX REGISTER LOCATION
#define _4_BYTE                 0x04 // 4 BYTES
#define INIT                    0x00 // INITIAL VALUE
#define STAT_ACTIVE             0x01 // ACTIVE STATUSE
#define STAT_INACTIVE           0x00 // INACTIVE STATUSE
#define FLUSH_RX_PAYLOAD        0x00 //FLUSH RX PAYLOAD
#define END_TX                  0x00 //END_TX
/************************************************************************
* Nrf905 Variables
************************************************************************/
const unsigned short txAddr[_4_BYTE ]={0x14,0xD7,0x6B,0x21};    // TX ADDRESS
const unsigned short rxAddr[_4_BYTE ]={0x14,0xD7,0x6B,0x21};    // RX ADDRESS
int cntTx, cntRx;                         // TX/RX COUNTER CONTROL
unsigned short receive=INIT;             // RECIEVED DATA
/************************************************************************
* Functions
************************************************************************/
void Nrf905RegCom (unsigned short RegCom, unsigned short RegValue)
{
    CS_NRF_bit=START_SPI;
    SPI1_Write(RegCom);
    SPI1_Write(RegValue);
    CS_NRF_bit=EXIT_SPI;
    Delay_us(SPI_RECOVER_TIME);
}
void PowerDownMode(void)
  {
    PWR_UP_NRF_bit=STAT_ACTIVE;
    Delay_ms(POWER_UP_REC_TIME);
  }
void PowerUpMode(void)
  {
    PWR_UP_NRF_bit=STAT_ACTIVE;
    Delay_ms(POWER_UP_REC_TIME);
  }
void  TransmitMode(void)
  {
    TX_EN_NRF_bit=STAT_ACTIVE;
    TRX_CE_NRF_bit=STAT_ACTIVE;
    Delay_us(SPI_RECOVER_TIME);
  }
void ReceiveMode(void)
  {
    TX_EN_NRF_bit=STAT_INACTIVE;
    TRX_CE_NRF_bit=STAT_ACTIVE;
    Delay_us(SPI_RECOVER_TIME);
  }
void TransmitPacket(unsigned short dByte)
  {
     TransmitMode();
     Nrf905RegCom(TX_PAYLOAD_REG,dByte);  // Transmit payload
     TRX_CE_NRF_bit=END_TX;           // end trasmit mode
  }
void Nrf905Init(void)
{
    PowerDownMode();                                    //enable spi write mode
    Nrf905RegCom(CHANNEL_REG, CHANNEL);                //CHANNELS 1 TO 170
    Nrf905RegCom(XTAL_REG, _16MHZ);                      //XTAL
    Nrf905RegCom(TXRX_ADDR_WIDTH_REG, _4BYTE);           //TX/RX address width
    Nrf905RegCom(TX_PAYLOAD_WEDTH_REG, TX_PAYLOAD_WEDTH);  //Tx payload width
    Nrf905RegCom(RX_PAYLOAD_WEDTH_REG, RX_PAYLOAD_WEDTH);  //Rx payload width
    Nrf905RegCom(NRF_PWR_REG,NRF_PWR_10DBM);         // Output power = +10dBm
    CS_NRF_bit=START_SPI;
    SPI1_Write(ASSIGN_TX_ADDR_REG);                  //tx address  4 byte
    for (cntTx=INIT;cntTx<_4_BYTE;cntTx++)
    SPI1_Write(txAddr[cntTx]);
    CS_NRF_bit=EXIT_SPI;
    Delay_us(SPI_RECOVER_TIME);
    for (cntRx=INIT;cntRx<_4_BYTE;cntRx++)
    Nrf905RegCom((cntRx+RX_REG_LOC),rxAddr[cntRx]);  //RX address 4 bytes
    PowerUpMode();              // Exit programing mode & power up nrf905 unit
  }
unsigned short ReceivePacket(void)
 {
    ReceiveMode();
    if(DR_NRF_bit= STAT_ACTIVE)
    {
    TRX_CE_NRF_bit=FLUSH_RX_PAYLOAD;
    CS_NRF_bit=START_SPI;
    SPI1_Read(RX_PAYLOAD_REG);
    receive=SPI1_Read(INIT);
    CS_NRF_bit=EXIT_SPI;
    return(receive);     // Return recieved data
    }
}