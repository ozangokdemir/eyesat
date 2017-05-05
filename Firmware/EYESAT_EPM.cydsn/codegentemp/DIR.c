/*******************************************************************************
* File Name: DIR.c  
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
#include "DIR.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        DIR_PC =   (DIR_PC & \
                                (uint32)(~(uint32)(DIR_DRIVE_MODE_IND_MASK << (DIR_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (DIR_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: DIR_Write
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
void DIR_Write(uint8 value) 
{
    uint8 drVal = (uint8)(DIR_DR & (uint8)(~DIR_MASK));
    drVal = (drVal | ((uint8)(value << DIR_SHIFT) & DIR_MASK));
    DIR_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: DIR_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DIR_DM_STRONG     Strong Drive 
*  DIR_DM_OD_HI      Open Drain, Drives High 
*  DIR_DM_OD_LO      Open Drain, Drives Low 
*  DIR_DM_RES_UP     Resistive Pull Up 
*  DIR_DM_RES_DWN    Resistive Pull Down 
*  DIR_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DIR_DM_DIG_HIZ    High Impedance Digital 
*  DIR_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DIR_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(DIR__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: DIR_Read
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
*  Macro DIR_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DIR_Read(void) 
{
    return (uint8)((DIR_PS & DIR_MASK) >> DIR_SHIFT);
}


/*******************************************************************************
* Function Name: DIR_ReadDataReg
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
uint8 DIR_ReadDataReg(void) 
{
    return (uint8)((DIR_DR & DIR_MASK) >> DIR_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DIR_INTSTAT) 

    /*******************************************************************************
    * Function Name: DIR_ClearInterrupt
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
    uint8 DIR_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(DIR_INTSTAT & DIR_MASK);
		DIR_INTSTAT = maskedStatus;
        return maskedStatus >> DIR_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
