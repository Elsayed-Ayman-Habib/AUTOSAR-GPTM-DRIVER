/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCtrl.c
 *        \brief  Nested Vector Interrupt Driver
 *
 *      \details  Source file for Nested Vector Interrupt Driver 
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IntCtrl.h"
#include "IntCtrl_Regs.h"
#include "IntCtrl_Cfg.h"
#include "tm4c123gh6pm_registers.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
STATIC const IntCtrl_ConfigChannel * IntCtrl_Configuration = NULL_PTR;
STATIC uint8 IntCtrl_Status = INTCTRL_NOT_INITIALIZED ;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void IntCtrl_init(void)        
* \Description     : Function to Init the Nested Vector Interrupt driver                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void IntCtrl_init(const IntCtrl_ConfigType* ConfigPtr)
{
  IntCtrl_InterruptType IntCtl_Number;
  uint32 EnableRegOffset,OffsetBit;
  IntCtrl_Status        = INTCTRL_INITIALIZED;
  IntCtrl_Configuration = ConfigPtr->Interrupt;
  volatile uint32 * IntCtrl_Interrupt_Ptr = (volatile uint32 *)INTCTRL_BASE_ADDRESS;
  
  for(uint8 i = 0; i < INTCTRL_CONFIGURED_INTERRUPT ; i++)
  {
    /* 
    *enable the corresponding interrupt 
    */
    
    IntCtl_Number = IntCtrl_Configuration[i].IntCtrl_Interrupt_Number;
    EnableRegOffset=(IntCtl_Number/REG_LENGTH_BIT)*REG_LENGTH_BYTE;
    OffsetBit=IntCtl_Number%REG_LENGTH_BIT;
    switch(EnableRegOffset/REG_LENGTH_BYTE)
    {
    case 0: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_EN0_BASE_OFFSET),OffsetBit); 
    break;
    case 1: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_EN1_BASE_OFFSET),OffsetBit); 
    break;
    case 2: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_EN2_BASE_OFFSET),OffsetBit); 
    break;
    case 3: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_EN3_BASE_OFFSET),OffsetBit); 
    break;			
    }
    
    /*
    *The APINT register provides priority grouping control for the exception model , This field determines the split of group priority from subpriority 
    */	
    
    if ( (IntCtrl_Configuration[i].group == INTCTRL_GROUP0) && (IntCtrl_Configuration[i].sub_group == INTCTRL_SUBGROUP0) )
    {
      *(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_APINT_BASE_OFFSET) = ((((INTCTRL_VALUE_TO_WRITE_NUMBER) << (APINT_VECTKEY_NUM))&((INTCTRL_APINT_VECTKEY_MASK)))+((NVIC_PRIORITY_GROUPS_7_SUB_0) << (APINT_PRIGROUP_NUM))); 
    }
    
    /* 
    *set the priority 
    */
    
    switch(((IntCtrl_Configuration[i].IntCtrl_Interrupt_Number))%(4))
    {
    case 0 : *(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_PRI5_BASE_OFFSET) = ((( INTCTRL_PRIX_BASE_ADDRESS + INTCTRL_PRI5_BASE_OFFSET )&(INTCTRL_PRIX_INTA_MASK))|((IntCtrl_Configuration[i].group) << (PRIX_INTA_NUM)));
    break;
    case 1 : *(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_PRI5_BASE_OFFSET) = ((( INTCTRL_PRIX_BASE_ADDRESS + INTCTRL_PRI5_BASE_OFFSET )&(INTCTRL_PRIX_INTB_MASK))|((IntCtrl_Configuration[i].group) << (PRIX_INTB_NUM)));
    break;
    case 2 : *(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_PRI5_BASE_OFFSET) = ((( INTCTRL_PRIX_BASE_ADDRESS + INTCTRL_PRI5_BASE_OFFSET )&(INTCTRL_PRIX_INTC_MASK))|((IntCtrl_Configuration[i].group) << (PRIX_INTC_NUM)));
    break;
    case 3 : *(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_PRI5_BASE_OFFSET) = ((( INTCTRL_PRIX_BASE_ADDRESS + INTCTRL_PRI5_BASE_OFFSET )&(INTCTRL_PRIX_INTD_MASK))|((IntCtrl_Configuration[i].group) << (PRIX_INTD_NUM)));
    break;
    }
  }
}

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl.c
 *********************************************************************************************************************/
