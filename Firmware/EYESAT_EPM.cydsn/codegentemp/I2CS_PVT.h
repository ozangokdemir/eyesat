/*******************************************************************************
* File Name: .h
* Version 1.20
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_I2CS_H)
#define CY_SCB_PVT_I2CS_H

#include "I2CS.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define I2CS_SetI2CExtClkInterruptMode(interruptMask) I2CS_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define I2CS_ClearI2CExtClkInterruptSource(interruptMask) I2CS_CLEAR_INTR_I2C_EC(interruptMask)
#define I2CS_GetI2CExtClkInterruptSource()                (I2CS_INTR_I2C_EC_REG)
#define I2CS_GetI2CExtClkInterruptMode()                  (I2CS_INTR_I2C_EC_MASK_REG)
#define I2CS_GetI2CExtClkInterruptSourceMasked()          (I2CS_INTR_I2C_EC_MASKED_REG)

#if(!I2CS_CY_SCBIP_V1_I2C_ONLY)
/* APIs to service INTR_SPI_EC register */
#define I2CS_SetSpiExtClkInterruptMode(interruptMask) I2CS_WRITE_INTR_SPI_EC_MASK(interruptMask)
#define I2CS_ClearSpiExtClkInterruptSource(interruptMask) I2CS_CLEAR_INTR_SPI_EC(interruptMask)
#define I2CS_GetExtSpiClkInterruptSource()                 (I2CS_INTR_SPI_EC_REG)
#define I2CS_GetExtSpiClkInterruptMode()                   (I2CS_INTR_SPI_EC_MASK_REG)
#define I2CS_GetExtSpiClkInterruptSourceMasked()           (I2CS_INTR_SPI_EC_MASKED_REG)
#endif /* (!I2CS_CY_SCBIP_V1_I2C_ONLY) */

#if(I2CS_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void I2CS_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx);
#endif /* (I2CS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_I2CS_CUSTOM_INTR_HANDLER)
    extern cyisraddress I2CS_customIntrHandler;
#endif /* !defined (CY_REMOVE_I2CS_CUSTOM_INTR_HANDLER) */

extern I2CS_BACKUP_STRUCT I2CS_backup;

#if(I2CS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    extern uint8 I2CS_scbMode;
    extern uint8 I2CS_scbEnableWake;
    extern uint8 I2CS_scbEnableIntr;

    /* I2C config vars */
    extern uint8 I2CS_mode;
    extern uint8 I2CS_acceptAddr;

    /* SPI/UART config vars */
    extern volatile uint8 * I2CS_rxBuffer;
    extern uint8   I2CS_rxDataBits;
    extern uint32  I2CS_rxBufferSize;

    extern volatile uint8 * I2CS_txBuffer;
    extern uint8   I2CS_txDataBits;
    extern uint32  I2CS_txBufferSize;

    /* EZI2C config vars */
    extern uint8 I2CS_numberOfAddr;
    extern uint8 I2CS_subAddrSize;
#endif /* (I2CS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*  Conditional Macro
****************************************/

#if(I2CS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Define run time operation mode */
    #define I2CS_SCB_MODE_I2C_RUNTM_CFG     (I2CS_SCB_MODE_I2C      == I2CS_scbMode)
    #define I2CS_SCB_MODE_SPI_RUNTM_CFG     (I2CS_SCB_MODE_SPI      == I2CS_scbMode)
    #define I2CS_SCB_MODE_UART_RUNTM_CFG    (I2CS_SCB_MODE_UART     == I2CS_scbMode)
    #define I2CS_SCB_MODE_EZI2C_RUNTM_CFG   (I2CS_SCB_MODE_EZI2C    == I2CS_scbMode)
    #define I2CS_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (I2CS_SCB_MODE_UNCONFIG == I2CS_scbMode)

    /* Define wakeup enable */
    #define I2CS_SCB_WAKE_ENABLE_CHECK        (0u != I2CS_scbEnableWake)
#endif /* (I2CS_SCB_MODE_UNCONFIG_CONST_CFG) */

#endif /* (CY_SCB_PVT_I2CS_H) */


/* [] END OF FILE */
