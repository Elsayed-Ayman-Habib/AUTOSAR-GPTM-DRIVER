/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Gpt_Lcfg.c
 *        \brief  Gpt_Lcfg
 *
 *      \details  General-Purpose Timer Link Configuration Source File
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Gptm.h"
#include "App.h"

/*
 * Module Version 1.0.0
 */
#define GPTM_LCFG_SW_MAJOR_VERSION              (1U)
#define GPTM_LCFG_SW_MINOR_VERSION              (0U)
#define GPTM_LCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPTM_LCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPTM_LCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define GPTM_LCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Gpt_Lcfg.c and Gptm.h files */
#if ((GPTM_LCFG_AR_RELEASE_MAJOR_VERSION != GPTM_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPTM_LCFG_AR_RELEASE_MINOR_VERSION != GPTM_AR_RELEASE_MINOR_VERSION)\
 ||  (GPTM_LCFG_AR_RELEASE_PATCH_VERSION != GPTM_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of LCFG.c does not match the expected version"
#endif

/* Software Version checking between Gpt_Lcfg.c and Gptm.h files */
#if ((GPTM_LCFG_SW_MAJOR_VERSION != GPTM_SW_MAJOR_VERSION)\
 ||  (GPTM_LCFG_SW_MINOR_VERSION != GPTM_SW_MINOR_VERSION)\
 ||  (GPTM_LCFG_SW_PATCH_VERSION != GPTM_SW_PATCH_VERSION))
  #error "The SW version of LCFG.c does not match the expected version"
#endif


/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
extern void Timer0A_ISR(void);

const Gpt_ConfigType Gpt_ConfigPtr = {
			 TIMER0_A       ,GPT_MODE_NORMAL,INITIALIZED,TickFrequency,TickValueMax,INTERRUPT_ON ,GPT_CONTINUOUS,Timer0A_ISR
};
	
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
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
