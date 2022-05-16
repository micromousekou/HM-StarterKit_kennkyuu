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
				
				BEEP();
				//モータの回転
				MOT_OUT_R=120; //最大値は240?
				MOT_OUT_L=120; //最大値は240
				
				MOT_POWER_ON; //
				
				while(timer<2000);
				MOT_OUT_R=0; //最大値は240
				MOT_OUT_L=0; //最大値は240
				MOT_POWER_OFF;
				BEEP();
				
				
				
				break;
				
			case 3:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	O	X	X	*
				*					*
				*****************************************/
			
				
				break;
				
			case 4:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	X	O	X	*
				*					*
				*****************************************/
			
				
				
				break;
				
			case 5:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	X	O	X	*
				*					*
				*****************************************/
			
						
				
				
				break;
				
			case 6:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	X	O	O	X	*
				*					*
				*****************************************/
			
				
				break;
				
			case 7:
				/****************************************
				*MODE LED STATE				*
				*					*
				*	D3	D4	D5	D6	*
				*	O	O	O	X	*
				*					*
				*****************************************/
			
				
				
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
