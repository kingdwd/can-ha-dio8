﻿/**
 * @file    can-ha-protocol.h
 * @author  Felix Horn
 * @version 0.1
 * @date    25-Oct-2015
 * @brief   This file contains all the defines and functions prototypes for the
 *          CAN HomeAutomation Protocol.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#ifndef CAN_HA_PROTOCOL_H_
#define CAN_HA_PROTOCOL_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <string.h>
#include "can-ha-protocol-conf.h"

/* Exported constants --------------------------------------------------------*/
#define CAN_BUFFER_SIZE           10

/* CAN communication */
#define DATA_FRAME 0
#define REMOTE_FRAME 1
#define STANDARD_FRAME 0
#define EXTENDED_FRAME 1

/* Exported variables --------------------------------------------------------*/
extern volatile uint32_t UnixTimestamp;

/* Exported types ------------------------------------------------------------*/
#ifndef BOOL
    #define BOOL
    typedef enum { FALSE, TRUE }bool;
#endif

/* Functionpointer */
typedef void (*SingleCommand_Function) (uint_least8_t);
typedef void (*DoubleCommand_Function) (uint_least8_t);
typedef void (*SetPoint16_Function) (int16_t);
typedef void (*SetPoint32_Function) (int32_t);

/* Structs for message types */
/**
  * @brief  Single Indication
  *
  * Test
  */
typedef struct {
    const uint_least32_t    Identifier;
    uint32_t                Timestamp;
    uint8_t                 State;
    uint_least8_t           padding[3];
}SingleIndication_TypeDef;

/**
  * @brief  Double Indication
  *
  * Test
  */
typedef struct {
    const uint_least32_t    Identifier;
    uint32_t                Timestamp;
    uint_least8_t           State;
    uint_least8_t           padding[3];
}DoubleIndication_TypeDef;

/**
  * @brief  Measured Value 16bit
  *
  * Fix point value
  * e.g. 21,53°C = 2153
  */
typedef struct {
    const uint_least32_t    Identifier;
    uint32_t                Timestamp;
    int_least16_t           Value;
    uint_least8_t           padding[2];
}MeasuredValue16_TypeDef;

/**
  * @brief  Measured Value 32bit
  *
  * Floating Point Value
  */
typedef struct {
    const uint_least32_t    Identifier;
    uint32_t                Timestamp;
    int_least32_t           Value;
}MeasuredValue32_TypeDef;

/**
  * @brief  Single Command
  *
  * Test
  */
typedef struct {
    const uint_least32_t    Identifier;
    SingleCommand_Function  Function;
    int_least8_t            State;
    uint_least8_t           padding[3];
}SingleCommand_TypeDef;

/**
  * @brief  Double Command
  *
  * Test
  */
typedef struct {
    const uint_least32_t    Identifier;
    DoubleCommand_Function  Function;
    int_least8_t            State;
    uint_least8_t           padding[3];
}DoubleCommand_TypeDef;

/**
  * @brief  Set Point 16bit
  *
  * Fix point value
  * e.g. 21,53°C = 2153
  */
typedef struct {
    const uint_least32_t    Identifier;
    SetPoint16_Function     Function;
    int_least16_t           Value;
    uint_least8_t           padding[2];
}SetPoint16_TypeDef;

/**
  * @brief  Set Point 32bit
  *
  * Floating point value
  */
typedef struct {
    const uint_least32_t    Identifier;
    SetPoint32_Function     Function;
    int_least32_t           Value;
}SetPoint32_TypeDef;

/**
  * @brief  CAN home automation message struct
  *
  * Test
  */
typedef struct {
  uint_least16_t            MessageType;
  uint_least32_t            Identifier;
  uint_least8_t             DataLength;
  uint_least8_t             Data[8];
}CanHA_MsgTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void CAN_HA_Refresh(void);
void Single_Indication_Write(uint_least32_t ObjectNumber, bool NewState);
void Measured_Value_16_Write(uint_least32_t ObjectNumber, int16_t NewValue);
void Measured_Value_32_Write(uint_least32_t ObjectNumber, int32_t NewValue);
void CAN_HA_GetMessage(CanHA_MsgTypeDef *GetMessage); /* Insert in Can rx interrupt */
void CAN_HA_ReadBuffer();
void CAN_HA_WriteBuffer(uint_least16_t MessageType, uint_least32_t Identifier, uint_least8_t DataLength, uint_least8_t *Data);
bool CANHA_GetMsgFromBuf(CanHA_MsgTypeDef *GetMessage);
void CANHA_MsgSent(void);

#endif /* CAN_HA_PROTOCOL_H_ */
