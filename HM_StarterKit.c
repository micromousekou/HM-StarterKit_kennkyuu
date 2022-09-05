/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :2017/6/27	                                       */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :RX631 48P                                             */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#include "iodefine.h"
#include "mathf.h"
#include "sci.h"
#include "init.h"
#include "spi.h"
#include "i2c.h"
#include "parameters.h"
#include "glob_var.h"
#include "run.h"
#include "interface.h"
#include "DataFlash.h"
#include "portdef.h"
#include "fast.h"
#include "search.h"

extern long	log2[1000];
extern long	log3[1000];
extern long	log4[1000];
extern long	log5[1000];

#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif


extern void wait_ms(int wtime);
extern void adjust(void);

void main(void)
{

	init_all();
	unsigned long i = 0;
	

	
	//ブザー
	BEEP();
	//最初は0しておく
	speed_r=0;
	speed_l=0;
	
	//起動時のログはとらない
	log_flag = 0;
	short mode = 1;
	while(1){
		I_tar_ang_vel = 0;
		I_ang_vel = 0;
		I_tar_speed = 0;
		I_speed = 0;

		switch(mode){
			
			case 1:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	X	X	X	*
				*					*
				*****************************************/
				//センサーの前に手をかざしてスタート
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					//壁制御を有効にする
					con_wall.enable = true;
					while(1){
						//A/D sensor
						SCI_printf("sen_r.value: %d\n\r",sen_r.value);
						SCI_printf("sen_l.value: %d\n\r",sen_l.value);
						SCI_printf("sen_fr.value: %d\n\r",sen_fr.value);
						SCI_printf("sen_fl.value: %d\n\r",sen_fl.value);
						SCI_printf("V_bat: %d\n\r",(int)(V_bat*1000));
						SCI_printf("sen_r.th_wall: %d\n\r",sen_r.th_wall);
						SCI_printf("sen_l.th_wall: %d\n\r",sen_l.th_wall);
						SCI_printf("sen_fr.th_wall: %d\n\r",sen_fr.th_wall);
						SCI_printf("sen_fl.th_wall: %d\n\r",sen_fl.th_wall);
						SCI_printf("con_wall.omega: %d\n\r",(int)(con_wall.omega*1000));
						SCI_printf("speed_r: %d\n\r", (int)(speed_r*100));
						SCI_printf("speed_l: %d\n\r", (int)(speed_l*100));
						//gyro
						SCI_printf("degree: %d\n\r",(int)degree*10);;			
						SCI_printf("gyro: %d\n\r", (int)(ang_vel*1000) );
						//encoder
						SCI_printf("locate_r: %d\n\r",locate_r);
						SCI_printf("locate_l: %d\n\r",locate_l);	
					
						//switch
						SCI_printf("switchC: %d\n\r",SW_C);
						SCI_printf("switchU: %d\n\r",SW_U);
						SCI_printf("switchD: %d\n\r",SW_D);
						wait_ms(100);
						//画面クリアシーケンス
						SCI_printf("\x1b[2J");				//クリアスクリーン[CLS]
						SCI_printf("\x1b[0;0H");			//カーソルを0,0に移動
						
						//プッシュスイッチ用処理
						push_switch = IOex_SWITCH();
			
						if(SW_C == 1){
							BEEP();
							break;	
						}
					}
				}
				
				
				
				break;
				
			case 2:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	O	X	X	*
				*					*
				*****************************************/
				
				/****************************************
				*      モータデータ取得用プログラム     *
				*****************************************/
				
				
				//センサーの前に手をかざしてスタート
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					
					//MOT_OUT_R=0; 
					//MOT_OUT_L=0;
									
					//MOT_POWER_ON;
					PID_ON=1;
					timer=0;
					
					while(timer<1000);
									
					//モータ停止
					MOT_OUT_R=0; 
					MOT_OUT_L=0; 
					MOT_POWER_OFF;
					//SCI_printf("logcount: %d\n\r",log_cmt);
				
					timer=0;
					while(timer<1000);
					BEEP();
						
				}
				PID_ON=0;
				break;
				
			case 3:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	O	X	X	*
				*					*
				*****************************************/
				
				/****************************************
				*      モータデータ出力用プログラム     *
				*****************************************/
				
				
				//センサーの前に手をかざしてスタート
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					//SCI_printf("logcount: %d\n\r",log_cmt);
					SCI_printf("time[msec],speed_l[m/s],speed_r[m/s]\n\r");
					
					for(i = 0; i <1000; i++){
						
						SCI_printf("%d,",i);            //time[msec]
						SCI_printf("%d,",log2[i]);	//speed_L/100[m/s]
						SCI_printf("%d,",log3[i]);
						SCI_printf("%d,",log4[i]);
						SCI_printf("%d\n\r",log5[i]);	//speed_R/100[m/s]
			
					}
					
				
				}
				break;
				
			case 4:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	X	O	X	*
				*					*
				*****************************************/
				
				//センサーの前に手をかざしてスタート
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					
					//壁制御を有効にする
					con_wall.enable = true;
					
					timer=0;
					while(timer<3000){
					BEEP();}
					SCI_printf("timer=0:%d\n\r",timer);
				
				}
				
				break;
				
			case 5:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	X	O	X	*
				*					*
				*****************************************/
				
				
				/*****************************************************
				*    モータ回転数取得用プログラム(非接触計を用いて)  *
				*****************************************************/
				
				/*
				//センサーの前に手をかざしてスタート
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					
					/*
					//電圧確認-------------------------------------
					int V;
					V=S12AD.ADDR9*3.3*2/4.096;
					SCI_printf("V = %d[mV]\n\r",V);
					
					//---------------------------------------------
				
					//モータの速度(出力)設定
					int motorsp;
					motorsp=239;//モータ速度

					MOT_OUT_R=motorsp*0.55; //最大値は239
					MOT_OUT_L=motorsp*0.55; //最大値は239
					
					MOT_CWCCW_R = MOT_R_FORWARD;
					
					
					timer=0; //timerリセット
					
					
					
					MOT_POWER_ON; //モータ回転開始＆回転時のデータ取得開始（非接触計）
					while(timer<2000);//回転開始後2秒間待機
					timer=0;
					i=0;
					//モータ速度計測---------------------------------------
					while(1){//n秒間回転
						
						short SL = (short)(speed_l*1000*60/(TIRE_DIAMETER*PI));//単位は[rpm]
						short SR = (short)(speed_r*1000*60/(TIRE_DIAMETER*PI));
						
						while(timer<10000);//5秒おきに測定
						BEEP();
						//SCI_printf("L[rpm]=%d   :",SL);
						SCI_printf("%d,",i);
						SCI_printf("%d\n\r",SL);
						timer=0;
						i++;
						
					}
					
					//モータ停止
					MOT_OUT_R=0; 
					MOT_OUT_L=0; 
					MOT_POWER_OFF;
					timer=0;
					while(timer<1000);
					BEEP();
				
		}*/
				break;		
				
			case 6:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	O	O	X	*
				*					*
				*****************************************/
			
				/*************************
				*   比例制御プログラム   *
				*************************/
				//------------------------------------------------------
				/*memo
					
				------------------------------------------------------*/
				/******************************************
				ブロック図
				
				  ref  +         duty
				------>○--->[Kp]--->[Motor]---●------>ω
				     - ↑			|
				       |			|
				       --------------------------
				*******************************************/
				
				
				//センサーの前に手をかざしてスタート
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					
					//各パラメータ設定---------------------------------------------------------------------------------
					float output_R, output_L, trim_R, trim_L, targetV, Perr_R, Perr_L, Ierr_L, Ierr_R, Derr_L, Derr_R; //関数設定
					short NR , NL;
					Perr_R = Perr_L = 0; //誤差
					//output_L = speed_l*100; //出力値左
					//output_R = speed_r*100; //出力値右
					MSP = 239; //最大モータ出力
					
					//MOT_CWCCW_R = MOT_R_FORWARD; //右モータ回転方向設定
					//MOT_CWCCW_L = MOT_L_FORWARD; //左モータ回転方向設定
										
					//変更する必要のあるパラメータ左モータ-----------------------
					KP_L = 0.02;//	0.02; 	//比例ゲイン左設定
					KI_L = 0.0008/1000;	//積分ゲイン左設定
					KD_L = 0;//1*1000; 	//微分ゲイン左設定
					trim_L = 0.4;//0.379; 	//左モータトリム設定
					
					Perr_L = Ierr_L = Derr_L = 0;
					//変更する必要のあるパラメータ右モータ-----------------------
					KP_R = 0.02;//0.01; 	//比例ゲイン右設定
					KI_R = 0.0008/1000;	//積分ゲイン右設定
					KD_R = 0;//1*1000; 	//微分ゲイン右設定
					trim_R = 0.4;//0.379; 	//右モータトリム設定
					
					
					Perr_R = Ierr_R = Derr_R = 0;
					targetV = 3000;//2000; //目標値[rpm]
					
					// ---------------------------------------------------------------------------------------------------
					
					//モータ制御---------------------------------------
					for (timer=0; timer<1000; timer){
					
						if(timer<101){    //100ms待機時間
						
							while(timer<100);
							
							NL = (short)(speed_l*1000*60/(TIRE_DIAMETER*PI));//単位は[rpm]
							NR = (short)(speed_r*1000*60/(TIRE_DIAMETER*PI));
							
							log[12][timer] = NL;
							log[13][timer] = MOT_OUT_L;
							log[3][timer] = NR;
							log[4][timer] = MOT_OUT_R;
							
								}
						
						MOT_POWER_ON; //モータ回転開始＆回転時のデータ取得開始
														
						output_L = NL;
						output_R = NR;
						
						//比例要素-----(目標値 - 出力)
						Perr_L = targetV-output_L;
						Perr_R = targetV+output_R;
						
						//積分要素-----(今までのエラー + 現在のエラー)
						Ierr_L = Ierr_L+Perr_L;
						Ierr_R = Ierr_R+Perr_R;
						
						//微分要素-----(現在のエラー - ひとつ前のエラー)
						Derr_L = Perr_L-Derr_L;
						Derr_R = Perr_R-Derr_R;
						
						//PID制御を用いた計算----------------------------------------
						MOT_OUT_L = MSP*trim_L+KP_L*Perr_L+KI_L*Ierr_L+KD_L*Derr_L; 					
						MOT_OUT_R = MSP*trim_R+KP_R*Perr_R+KI_R*Ierr_R+KD_R*Derr_R;
						
						//リミッター設定---------------------------------------------
						if (MOT_OUT_L >239){
							MOT_OUT_L =239;
						}
						if (MOT_OUT_L <0){
							MOT_OUT_L =0;
						}
						
						if (MOT_OUT_R >239){
							MOT_OUT_R =239;
						}
						if (MOT_OUT_R <0){
							MOT_OUT_R =0;
						}
						//-----------------------------------------------------------
						
						NL = (short)(speed_l*1000*60/(TIRE_DIAMETER*PI));//単位は[rpm]
						NR = (short)(speed_r*1000*60/(TIRE_DIAMETER*PI));
						
						log[12][timer] = NL;
						log[13][timer] = MOT_OUT_L;
						log[3][timer] = NR;
						log[4][timer] = MOT_OUT_R;	
					}
					
					//モータ停止
					MOT_OUT_R=0; 
					MOT_OUT_L=0; 
					MOT_POWER_OFF;
					timer=0;
					while(timer<1000);
					BEEP();
					
				}
				break;
				
			case 7:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	O	O	X	*
				*					*
				*****************************************/
				
				//センサーの前に手をかざしてスタート
				if(sen_fr.value + sen_fl.value + sen_r.value + sen_l.value > SEN_DECISION * 4){
					BEEP();
					
				
				
					}
				
				
				break;
				
			case 8:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	X	X	O	*
				*					*
				*****************************************/
			
				
				
				break;
				
			case 9:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	X	X	O	*
				*					*
				*****************************************/
			
				
				
				break;
				
			case 10:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	O	X	O	*
				*					*
				*****************************************/
			

				break;
				
			case 11:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	O	X	O	*
				*					*
				*****************************************/
			
				
				break;
				
			case 12:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	X	O	O	*
				*					*
				*****************************************/
			
				
				
				break;
				
				
			case 13:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	X	O	O	*
				*					*
				*****************************************/
			
				
				
				break;
				
			case 14:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	O	O	O	*
				*					*
				*****************************************/
			
				
				
				break;
				
			case 15:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	O	O	O	*
				*					*
				*****************************************/
				
				break;
				
			//mode0~15以外の場合。何もしない。
			default:
				break;
			
		}
		
		//モード切り替え用処理
		if(speed > 0.1){
			if(mode == 15){
				mode = 1;
			}else{
				mode ++;
			}
			for(i = 0; i < 100*1000*10; i++);
			BEEP();
		}
		
		if(speed < -0.1){
			if(mode == 1){
				mode = 15;
			}else{
				mode --;
		}
			for(i = 0; i < 100*1000*10; i++);
			BEEP(); 
		}
		LED(mode);
		
		//プッシュスイッチ用処理
		push_switch = IOex_SWITCH();
		MOT_POWER_OFF;
	
	}
	

}

#ifdef __cplusplus
void abort(void)
{

}
#endif
