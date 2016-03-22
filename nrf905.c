/*
 * Project name:
     NRF905
 * Copyright:
     HAZEM ELSAYED.
     hazem.elsayed@telia.com
 * Revision History:
     20150822:
       - Rev.1
 * Description:
     This is a simple 'NRF905 transmitter/receiver' project. It sends 1 byte and increment it every 300ms, reciever display it on port B.
     data being transmitted are also shown on port B in the transmitter side.
 * Test configuration:
     MCU:             PIC18F45K22
     dev.board:       easypic pro v7
     Oscillator:      HS-PLL 32.0000 MHz, 8.0000 MHz Crystal
     Software:        mikroC PRO for PIC
*/
#include "nrf905_driver.h"
#define  CLR_LATCH               0X00    //CLEAR THE ENTIRE LATCHS BANK
#define  DIGITAL                 0X00    // CHOOSE DIGITAL MUX
#define  PLL_STABLE_TIME         0X96    // WHAIT FOR PLL TO STABLIZE
#define  PLL_ENABLE              0X01    // WHAIT FOR PLL TO STABLIZE
#define  DIRECTION_OUTPUT        0X00    // PORT DIRECTION
#define  DIRECTION_INPUT         0X01    // PORT DIRECTION
#define  LOOP                    0X01    // LOOP FOREVER
/************************************************************************
* Digital input
************************************************************************/
sfr sbit TRX_CE_NRF_bit at LATA0_bit;  // Enables chip for receive and transmit
sfr sbit TRX_CE_NRF_Direction_bit at TRISA0_bit;
sfr sbit PWR_UP_NRF_bit at LATA1_bit;  // Power up chip
sfr sbit PWR_UP_NRF_Direction_bit at TRISA1_bit;
sfr sbit TX_EN_NRF_bit at LATA2_bit;  //TX/RX mode
sfr sbit TX_EN_NRF_Direction_bit at TRISA2_bit;
/************************************************************************
* Digital   output
************************************************************************/
sfr sbit DR_NRF_bit at RD0_bit;  // Receive and transmit Data Ready
sfr sbit DR_NRF_Direction_bit at TRISD0_bit;
/************************************************************************
* SPI - interface
************************************************************************/
sfr sbit CS_NRF_bit  at LATE0_bit;  //  SPI CS
sfr sbit CS_NRF_Direction_bit  at  TRISE0_bit;

unsigned short counter;
void main()
{
  PLLEN_bit = PLL_ENABLE;        // Enable PLL
  Delay_ms(PLL_STABLE_TIME);
  ANSELA=DIGITAL;                // Set pins as digital
  ANSELB=DIGITAL;
  ANSELC=DIGITAL;
  ANSELE=DIGITAL;
  ANSELD=DIGITAL;
  TRISB=DIGITAL;
  LATB=CLR_LATCH;
 //DIGITAL PIN DIRECTION
DR_NRF_Direction_bit=DIRECTION_INPUT;
TRX_CE_NRF_Direction_bit=DIRECTION_OUTPUT;
PWR_UP_NRF_Direction_bit=DIRECTION_OUTPUT;
TX_EN_NRF_Direction_bit=DIRECTION_OUTPUT;
CS_NRF_Direction_bit=DIRECTION_OUTPUT;
SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV16, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);
SPI_Set_Active(&SPI1_Read, &SPI1_Write);          //  initializes SPI1
Nrf905Init() ;                                    //  initializes NRF905
while(LOOP)
   { 
   for (counter=0;counter<256;counter++)
     {
      TransmitPacket(counter);
      Delay_ms(300);
      LATB=counter;    // display transmitted data on port B
     }
   }
   
}