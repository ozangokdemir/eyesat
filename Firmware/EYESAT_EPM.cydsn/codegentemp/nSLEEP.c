/*******************************************************************************
* File Name: nSLEEP.c  
* Version 2.5
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "nSLEEP.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        nSLEEP_PC =   (nSLEEP_PC & \
                                (uint32)(~(uint32)(nSLEEP_DRIVE_MODE_IND_MASK << (nSLEEP_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (nSLEEP_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: nSLEEP_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void nSLEEP_Write(uint8 value) 
{
    uint8 drVal = (uint8)(nSLEEP_DR & (uint8)(~nSLEEP_MASK));
    drVal = (drVal | ((uint8)(value << nSLEEP_SHIFT) & nSLEEP_MASK));
    nSLEEP_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: nSLEEP_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  nSLEEP_DM_STRONG     Strong Drive 
*  nSLEEP_DM_OD_HI      Open Drain, Drives High 
*  nSLEEP_DM_OD_LO      Open Drain, Drives Low 
*  nSLEEP_DM_RES_UP     Resistive Pull Up 
*  nSLEEP_DM_RES_DWN    Resistive Pull Down 
*  nSLEEP_DM_RES_UPDWN  Resistive Pull Up/Down 
*  nSLEEP_DM_DIG_HIZ    High Impedance Digital 
*  nSLEEP_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void nSLEEP_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(nSLEEP__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: nSLEEP_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro nSLEEP_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 nSLEEP_Read(void) 
{
    return (uint8)((nSLEEP_PS & nSLEEP_MASK) >> nSLEEP_SHIFT);
}


/*******************************************************************************
* Function Name: nSLEEP_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 nSLEEP_ReadDataReg(void) 
{
    return (uint8)((nSLEEP_DR & nSLEEP_MASK) >> nSLEEP_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(nSLEEP_INTSTAT) 

    /*******************************************************************************
    * Function Name: nSLEEP_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 nSLEEP_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(nSLEEP_INTSTAT & nSLEEP_MASK);
		nSLEEP_INTSTAT = maskedStatus;
        return maskedStatus >> nSLEEP_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
