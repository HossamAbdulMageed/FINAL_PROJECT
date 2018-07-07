#include <stdint.h>
#include "CAN_Trial.h"
#include "BTN.h"
#include "BTN_Cfg.h"
#include "GPIO.h"
#include "PiMngr.h"
#include "PiMngr_Cfg.h"
#include"app.h"
#include "HMIManager.h"
#include "HMIManager_Cfg.h"
#include "HMI.h"
#include "HMI_Cfg.h"
#include "BT.h"
#include "BT_Cfg.h"
#include "GPS.h"
#include "GPS_Cfg.h"
#include "Alarm.h"
#include "led.h"
 uint8_t Switch;

extern uint32_t pp;
//state = 0;
//counter = 0;
uint8_t StateX,x=0;
uint32_t counter=0,state=0;
void app(void)
{

    if(StateX == BTN_ON)
    {
        state=1;
        StateX = BTN_OFF;
        HMI_RecognitionState(0,1);
    }
    if(state==1)
    {
        counter++;
        if(counter==1)
        {
            PiMngr_GetStatus();
        }
        PiMngr_StartRecognition();
        PiMngr_RequestData();
    }

    if(state==2)
    {
        HMI_RecognitionState(0,0);
        CAN0_Transmit_Data(1, 0xff);
        x^=1;
        Engine_Status_Display(0,x);
        state =0;
        Alarm_var =0;
    }
    if(state==3)
    {
        /**/
        HMI_RecognitionState(0,0);
        pp=0;
        GPS_Request();
        Alarm_var =0;
        state =0;
    }
    if(state==4)
     {
         /**/
        HMI_RecognitionState(0,0);
         Incoming_Call_Display(0, "01065233286");
         SendCmd(BT_Call,"01065233286");
         Alarm_var =0;
       // SendCmd(BT_Call,"01111709622");
        //  Music_Status_Display(0 , Stop);
         state =0;
     }
    if(state == 5)
    {
        HMI_RecognitionState(0,0);
        state =0;
        Music_Status_Display(0 , Play);
        SendCmd(PlayMusic,"");
        Alarm_var =0;
        //state =0;

    }
    if(state == 6)
    {
        HMI_RecognitionState(0,0);
        state =0;
        Music_Status_Display(0 , Stop);
        SendCmd(PauseMusic,"");


    }
    if(state == 7)
      {
          HMI_RecognitionState(0,0);
          state =18;
          Music_Status_Display(0 , Next);
         // HMI_MusicName_Display(0  ,MusicTitle);
          SendCmd(ForwardMusic,"");
          Alarm_var =0;


      }
    if(state == 8)
      {
          HMI_RecognitionState(0,0);
          state =0;
          Music_Status_Display(0 , Previous);

          SendCmd(BackwardMusic,"");


      }
    if(state == 9)
      {
          HMI_RecognitionState(0,0);
          state =0;
          HMI_CallDecision (0 , Answer);
          SendCmd(BT_Answer,"");
          Alarm_var =0;


      }

    if(state == 18)
        {
        HMI_RecognitionState(0,0);
        state =0;
        Alarm_var =1;



        }



    }

