/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gptm.h
 *       Module:  General-Purpose Timer Module (GPTM)
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef GPTM.H
#define GPTM.H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Common_Macros.h"

/* Id for the company in the AUTOSAR
 * for example Elsayed Ayman's ID = 1000 ;) */
#define GPT_VENDOR_ID    (1000U)

/* Gptm Module Id */
#define GPT_MODULE_ID    (100U)

/* Gptm Instance Id */
#define GPT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define GPTM_SW_MAJOR_VERSION           (1U)
#define GPTM_SW_MINOR_VERSION           (0U)
#define GPTM_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPTM_AR_RELEASE_MAJOR_VERSION   (4U)
#define GPTM_AR_RELEASE_MINOR_VERSION   (0U)
#define GPTM_AR_RELEASE_PATCH_VERSION   (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Gptm Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != GPTM_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != GPTM_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != GPTM_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Gptm Pre-Compile Configuration Header file */
#include "Gptm_Cfg.h"

/* AUTOSAR Version checking between Gptm_Cfg.h and Gptm.h files */
#if ((GPTM_CFG_AR_RELEASE_MAJOR_VERSION != GPTM_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPTM_CFG_AR_RELEASE_MINOR_VERSION != GPTM_AR_RELEASE_MINOR_VERSION)\
 ||  (GPTM_CFG_AR_RELEASE_PATCH_VERSION != GPTM_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gptm_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Gptm_Cfg.h and Gptm.h files */
#if ((GPTM_CFG_SW_MAJOR_VERSION != GPTM_SW_MAJOR_VERSION)\
 ||  (GPTM_CFG_SW_MINOR_VERSION != GPTM_SW_MINOR_VERSION)\
 ||  (GPTM_CFG_SW_PATCH_VERSION != GPTM_SW_PATCH_VERSION))
  #error "The SW version of Gptm_Cfg.h does not match the expected version"
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define GPTM_INITIALIZED                (1U)
#define GPTM_NOT_INITIALIZED            (0U)

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for getting version of the GPT Driver. */
#define Gpt_GetVersionInfo_SID          (uint8)0x00 

/* Service ID for Initializes the GPT Driver. */
#define Gpt_Init_SID                    (uint8)0x01

/* Service ID for Initializes the GPT Driver.  */
#define Gpt_DeInit_SID                  (uint8)0x02

/* Service ID for getting the elapsed time. */
#define Gpt_GetTimeElapsed_SID          (uint8)0x03

/* Service ID for getting the remaining time. */
#define Gpt_GetTimeRemaining_SID        (uint8)0x04

/* Service ID for starting the timer. */
#define Gpt_StartTimer_SID              (uint8)0x05

/* Service ID for stopping the timer. */
#define Gpt_StopTimer_SID               (uint8)0x06

/* Service ID for enabling notification for the timer channel. */
#define Gpt_EnableNotification_SID      (uint8)0x07

/* Service ID for disabling notification for the timer channel. */
#define Gpt_DisableNotification_SID     (uint8)0x08

/* Service ID for setting the mode of the GPT driver. */
#define Gpt_SetMode_SID                 (uint8)0x09

/* Service ID for disabling wakeup for a channel. */
#define Gpt_DisableWakeup_SID           (uint8)0x0A

/* Service ID for enabling wakeup for a channel. */
#define Gpt_EnableWakeup_SID            (uint8)0x0B

/* Service ID for checking wakeup for a channel. */
#define Gpt_CheckWakeup_SID            (uint8)0x0C

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* API service called without module initialization */
#define GPT_E_UNINIT                  (uint8)0x0A

/* API service called when timer channel is still busy (running) */
#define GPT_E_BUSY                    (uint8)0x0B

/* API service for initialization called when already initialized */
#define GPT_E_ALREADY_INITIALIZED     (uint8)0x0D

/* API parameter checking: invalid channel */
#define GPT_E_PARAM_CHANNEL           (uint8)0x14

/* API parameter checking: invalid value */
#define GPT_E_PARAM_VALUE             (uint8)0x15

/* API parameter checking: invalid pointer */
#define GPT_E_PARAM_POINTER           (uint8)0x16

/* API parameter checking: invalid mode */
#define GPT_E_PARAM_MODE              (uint8)0x1F

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint8 Gpt_ChannelType;

typedef uint32 Gpt_ValueType;

typedef enum{
  GPT_MODE_NORMAL,GPT_MODE_SLEEP
}Gpt_ModeType;

typedef enum
{
  INITIALIZED, RUNNING, STOPPED, EXPIRED
} Gpt_StateType;

typedef enum
{
  GPT_CONTINUOUS,GPT_ONE_SHOTT,GPT_CAPTURE
} Gpt_RunningMode;

typedef enum
{
  INTERRUPT_OFF, INTERRUPT_ON
} Gpt_InterruptOption;


typedef struct{ 
  Gpt_ChannelType      GptChannelId;
  Gpt_ModeType         Gpt_ChannelMode;
  Gpt_StateType        Gpt_ChannelState;
  Gpt_ValueType        GptChannelTickFrequency;
  Gpt_ValueType        GptChannelTickValueMax;
  Gpt_InterruptOption  Gpt_EnableChannelNotification;
  Gpt_RunningMode      ChannelMode;
  void 		       (*GptNotifcation)(void);
}Gpt_ConfigChannel;

typedef struct{
  Gpt_ConfigChannel Gpt_Channels[GPT_CONFIGURED_CHANNLES];
}Gpt_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const Gpt_ConfigType Gpt_ConfigPtr;
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* The function Gpt_Init shall initialize the hardware timer module */
void Gpt_init (const Gpt_ConfigType* ConfigPtr);

/* The function Gpt_DisableNotification shall disable the interrupt notification */
#if (GptEnableDisableNotificationApi == STD_ON)
void Gpt_DisableNotification (Gpt_ChannelType Channel);
#endif

/* The function Gpt_EnableNotification shall enable the interrupt notification */
#if (GptEnableDisableNotificationApi == STD_ON)
void Gpt_EnableNotification (Gpt_ChannelType Channel);
#endif

/* The function Gpt_StartTimer shall start the selected timer channel */
void Gpt_StartTimer (Gpt_ChannelType Channel,Gpt_ValueType Value);

/* The function Gpt_StopTimer shall stop the selected timer channel */
void Gpt_StopTimer (Gpt_ChannelType Channel);

/* The function Gpt_GetTimeElapsed shall return the time already elapsed. */
#if (GptTimeElapsedApi == STD_ON)
Gpt_ValueType Gpt_GetTimerElapsed (Gpt_ChannelType Channel);
#endif

/* The function Gpt_GetTimeRemaining shall return the timer value remaining */
#if (GptTimeRemainingApi == STD_ON)
Gpt_ValueType Gpt_TimerRemaining (Gpt_ChannelType Channel);
#endif

#endif  /* GPTM.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
