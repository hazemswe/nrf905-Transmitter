/*
 * File name:
     NRF905_DRIVER.c
 * Copyright:
     HAZEM ELSAYED.
     hazem.elsayed@telia.com
 * Revision History:
     20150822:
       - initial release.
*/
#ifndef _NRF905_DRIVER_H_
#define _NRF905_DRIVER_H_
/************************************************************************
* Function Nrf905Init()
* -----------------------------------------------------------------------
* Overview: initializes NRF905
* Input: none
* Output: none
************************************************************************/
void Nrf905Init(void);

/************************************************************************
* Function PowerDownMode()
* -----------------------------------------------------------------------
* Overview: SPI PROGRAMMING mode
* Input: none
* Output: none
************************************************************************/
void PowerDownMode(void);

/************************************************************************
* Function PowerUpMode()
* -----------------------------------------------------------------------
* Overview: SWICH ON NRF905 AND EXIT PROGRAMMING mode
* Input: none
* Output: none
************************************************************************/
void PowerUpMode(void);

/************************************************************************
* Function TransmitMode()
* -----------------------------------------------------------------------
* Overview: Transmit mode
* Input: none
* Output: none
************************************************************************/
void TransmitMode(void);

/************************************************************************
* Function ReceiveMode()
* -----------------------------------------------------------------------
* Overview: Receive mode
* Input: none
* Output: none
************************************************************************/
void ReceiveMode(void);

/************************************************************************
* Function TransmitPacket()
* -----------------------------------------------------------------------
* Overview: TransmitPacket 1-32 BYTE
* Input: unsigned short
* Output: none
* When accessing succeeding bytes, you read or write the MSB of the
* byte with the smallest byte number first.
************************************************************************/
void TransmitPacket(unsigned short dByte);

/************************************************************************
* Function ReceivePacket()
* -----------------------------------------------------------------------
* Overview:  Receive Packet 1-32 BYTE
* Input: none
* Output: unsigned short
* When accessing succeeding bytes, you read or write the MSB of the
* byte with the smallest byte number first.
************************************************************************/
unsigned short ReceivePacket(void);

/************************************************************************
* Function Nrf905RegCom()
* -----------------------------------------------------------------------
* Overview: Access nrf905 registers
* Input1: unsigned short
* Input2: unsigned short
* Output: none
************************************************************************/
void Nrf905RegCom (unsigned short RegCom, unsigned short RegValue);

#endif