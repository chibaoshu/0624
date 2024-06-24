
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

//
#include <fcntl.h>
//
#include <sys/reboot.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/un.h>
#include <netdb.h>
//
#include <libgen.h>
#include <getopt.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <linux/can.h>
#include <linux/can/raw.h>
//
#define GSM_TX //

#include <GB_BWT.h>
#include <cmd_queue.h>
#include <AES.h>

//
#include <sqlite3.h>
#include "sqlite.h"
//
#include <strings.h>
#include <time.h>
//
#include <linux/watchdog.h>
//
#define GB_BWT_TBOX 			0
#define G4_TBOX 				0 

//////////////////////////////////////////////////////////////////////////////////////////
int 			cell_data_time = 0;

//////////////////////////////////////////////////////////////////////////////////////////
extern volatile uint32_t timer_tick_count_[100];
extern volatile uint8 buttonFlag;

//////////////////////////////////////////////////////////////////////////////////////////
int 			datasave = 0;

//
extern struct FifoQueue ATCmdQueue;

//
typedef struct 
{
	int 			counter;
	pthread_mutex_t counter_mutex;
} COUNTER;


COUNTER 		worker;

//
void time_func()
{
	static uint32_t count = 0;

	printf("count is %d\n", count++);

	//
	Reg_car_in_time++;

	Reg_car_out_time++;

	Platform_in_time++;

	Platform_out_time++;

	new_autodata_time++;

	new_Heartbeat_time++;

	new_time_time++;

	set_comm_time++;

	upline_time++;

	Alarm__time++;

	//-----------------------------------------------
	++timer_tick_count_[0];
	timer_tick_count_[1] ++;
	timer_tick_count_[2] ++;
	timer_tick_count_[3] ++;
	timer_tick_count_[4] ++;
	timer_tick_count_[5] ++;
	timer_tick_count_[6] ++;
	timer_tick_count_[7] ++;
	timer_tick_count_[8] ++;
	timer_tick_count_[9] ++;
	timer_tick_count_[10] ++;
	timer_tick_count_[11] ++;

	//-----------------------------------------------
}


void init_sigaction()
{
	struct sigaction act;
	act.sa_handler		= time_func;				//$)Ao?=g?o?=o?=f2$o?=o?=i?o?=o?=f=??=g"??=f=??o?=e?
	act.sa_flags		= 0;

	sigemptyset(&act.sa_mask);
	sigaction(SIGPROF, &act, NULL); 				//$)Ao?=e?o?=g?g"??=h7??o?=o?=SIGROFo?=o?=f=??=
}


void init_time()
{
	struct itimerval val;
	val.it_value.tv_sec = 1;						// //1$)Ao?=f?f=?48o?=d?o?=o?=?2f?o?=e?o?=f?
	val.it_value.tv_usec = 0;

	val.it_interval 	= val.it_value; 			//?$)A2f?o?=e?o?=f?o?=g????o?=i?1s

	setitimer(ITIMER_PROF, &val, NULL);
}


//////////////
extern int main_DO4_L();
extern int main_DO3_L();
extern int gpio_con(int id, int out);
extern int scoker_main(char * ip, char * ip_port, char ip_url);
extern void rev_gb_socket(char * ip, char * ip_port, char ip_url);

////////////////////////////////////////////////////
extern int can_ini();
extern int can0_run();
extern int can1_run();
extern int can_send(char can, struct can_frame frame1, unsigned char id);
extern int can_tast();
extern int can_send0();
extern int can_send1();



///////////////////////////////////////////////////////////////////////////////////////////
extern void gb_datasave(int on);
extern void gb_data_set(int cmd);

///////////////////////////////////////////////////////////////////////////////////////////
void ftp_gb()
{
	printf("-------------------------------Now ftp sockte----------------------------\n");

	//if (system("./ftp 36.7.87.115 30001") == -1)
	//	;
	//perror("ftp error");
	//pthread_exit(NULL);
	return;
}


///////////////////////////////////////////////////////////////////////////////////////////
void sockte_gb()
{
	printf("-------------------------------Now start sockte----------------------------\n");
	scoker_main("3694x4500s.qicp.vip", "30303", 1);

	/*
		while (1) //ÎÞ·¨Ö´ÐÐ ¶þ´ÎÖ´ÐÐ
			{
			sleep(1);
			datasave++;

			if (datasave >= 30)
				{
				datasave			= 0;

				scoker_main("3694x4500s.qicp.vip", "30303", 1);
				pthread_exit(NULL);
				return;

				}
			}
			*/
	//pthread_exit(NULL);
	return;
}


///////////////////////////////////////////////////////////////////////////////////////////
void can0_main()
{
	printf("-------------------------------Now start CAN0----------------------------\n");
	can0_run();
	printf("\nCAN0 down.\n");
	pthread_exit(NULL);
	return;
}


///////////////////////////////////////////////////////////////////////////////////////////
void can1_main()
{
	printf("-------------------------------Now start CAN1----------------------------\n");
	can1_run();
	printf("\nCAN1 down.\n");
	pthread_exit(NULL);
	return;
}


///////////////////////////////////////////////////////////////////////////////////////////
void cantast()
{
	printf("-------------------------------Now start CANTAST----------------------------\n");
	can_tast();
	printf("\nCANTAST down.\n");
	pthread_exit(NULL);
	return;
}


///////////////////////////////////////////////////////////////////////////////////////////
void cansend0()
{
	printf("-------------------------------Now start CANSEND0----------------------------\n");
	can_send0();
	printf("\nCANSEND0 down.\n");
	pthread_exit(NULL);
	return;
}


///////////////////////////////////////////////////////////////////////////////////////////
void cansend1()
{
	printf("-------------------------------Now start CANSEND1----------------------------\n");
	can_send1();
	printf("\nCANSEND1 down.\n");
	pthread_exit(NULL);
	return;
}


///////////////////////////////////////////////////////////////////////////////////////////
///
int 			fd_wat;

//./wdt settimeout 10 #SEC
//.wdt keepalive 10 #SEC
int 			system_sec = 0;

//
void led_main()
{
	FILE *			fp1, *fp2;

	printf("-------------------------------Now start led(ems-tcu-all)----------------------------\n");

	//
	//init_time();
	//init_sigaction();
	//
	//struct can_frame sendfra;
	//	  sendfra.can_id=0x18fffff4;
	//	 sendfra.can_dlc = 8;
	//
	//
	//sleep(5);
	//
	//fd_wat= open("/dev/watchdog",O_RDWR);
	//
	//			if(ioctl(fd_wat,WDIOC_SETTIMEOUT,&sec) < 0){
	//									perror("ioctl set timeout");
	//							}
	//
	QueueInit(&ATCmdQueue);

	//
	while (1)
		{
		//
		//if(ioctl(fd_wat,WDIOC_KEEPALIVE) < 0){
		//								perror("ioctl keep alive");
		//						}
		//
		gpio_con(0, 0);
		usleep(500000);
		gpio_con(0, 1);
		usleep(500000);
		time_func();

		//
		//
		//
		if (ATCmdQueue.count > 0)
			{
			printf("ATCmdQueue.count  is %d\n", ATCmdQueue.count);

			//pthread_mutex_lock(&worker.counter_mutex);
			while (ATCmdQueue.count > 0)
				{
				gb_commod(&ATCmdQueue);
				}

			//pthread_mutex_unlock(&worker.counter_mutex);
			}

		else 
			{
			//
			//
			system_sec++;

			if (system_sec >= 10)
				{
#if (											G4_TBOX 								== 1)
				fp1 				= popen("ifconfig eth0 up", "r");
				pclose(fp1);

				//
				fp2 				= popen("ifconfig eth1 up", "r");
				pclose(fp2);
#endif

				system_sec			= 0;
				}
			}

		}

	printf("\nled down.\n");

	pthread_exit(NULL);
	return;
}


///////////////////////////////////////////////////////////////////////////////////////////
extern int gb_system(uint8 cmd, uint8 name);

//
extern int gbtbox_data(int cmd, int upflg, struct TCP_SEND data);
extern void gb_new_autodata(uint16 newflag, uint8 * time);

extern struct TCP_SEND tcp_send;

//
const char * get_local_time(char * time_str);

//
void gb_tbox()
{
	char buf[128];

	struct tm loc_t;

	//
	printf("-------------------------------Now start tbox---------------------------\n");

	//
	//sleep(10);
	//gb_data_set(0);
	sleep(10);
	system_data();
	sleep(100);

	//
	while (1)
		{

		if (gb_system(1, 1) == 0)
			{ //
			gb_time_int();

			//rev_gb_socket();
			//
			//sprintf(buf,"date -s '%4d-%02d-%02d %02d:%02d:%02d'",loc_t.tm_year+1900,loc_t.tm_mon+1,loc_t.tm_mday,loc_t.tm_hour,loc_t.tm_min,loc_t.tm_sec);
			//system(buf);
			//system("hwclock -w");
			//
			//QueueInit(&ATCmdQueue);
			//
			//
			while (1)
				{
				//gb_data_set(3);
				//get_local_time(buf);
				//
				//printf("hear\n");
				if (new_Heartbeat_time >= heatup_time)
					{
					gb_Heartbeat();

					//rev_gb_socket();
					//
					new_Heartbeat_time	= 0;
					printf("hear is %d\n", new_Heartbeat_falg);

					//
					if (new_Heartbeat_falg >= 8)
						{
						datasave			= 3000;
						new_Heartbeat_falg	= 0;
						printf("sys_rset\n");

						//reboot(RB_AUTOBOOT);
						}

					}

				//
				//usleep(5000);
				//
				if ((Platform_in_time * 1000) >= safe_time)
					{
					Platform_in_time	= 0;

					/*gb_new_autodata(0x3ff,&unTime.strTime[0]);
					if(datasave == 0){
									gbtbox_data(1,1,tcp_send);
									 }else {
									 gbtbox_data(1,0,tcp_send);
									 datasave++;
									 if(datasave>=512) reboot(RB_AUTOBOOT);
									 }*/
					}

				//
				//usleep(5000);
				//
				if (new_autodata_time >= newup_time)
					{
					//pthread_mutex_lock(&worker.counter_mutex);
					//gb_PDAS_new_autodata((0x0001 | 0x0020 | 0x0040));
					gb_PDAS_new_autodata(0x3ff);
                    //
                    usleep(500000);
					//gb_PDAS_new_autodata(0x0080);
					//usleep(500000);
					//gb_PDAS_new_autodata(0x0100);
					//usleep(500000);
                    //gb_PDAS_cell();
					//rev_gb_socket();
					if (datasave <= 300)
						{ //

						//if (cell_data_time <= 60)
						//	{
							//usleep(100000);
						//	gb_new_autodata(0x27f, &unTime.strTime[0]);
						//	}
						//else 
						//	{
						//	cell_data_time		= 0;
						//	}

						//
						gbtbox_data(1, 1, tcp_send);

						cell_data_time++;

						}

					new_autodata_time	= 0;

					//pthread_mutex_unlock(&worker.counter_mutex);
					}

				//
				//usleep(5000);
				if (gb_bwc__flag)
					{
					usleep(100000);
					gb_bwc_();

					//
					gb_bwc__flag		= 0;

					}

				//
				//usleep(5000);
				if (gb_alarm_flag)
					{
					usleep(100000);
					gb_PDAS_Alarm();

					//
					gb_alarm_flag		= 0;

					}

				//
				if (new_time_time >= time_time)
					{
					//printf("time is %d\n", new_time_falg);
					usleep(100000);
					gb_time();
					//
					//gb_PDAS_cell();

					//rev_gb_socket();
					new_time_time		= 0;
					}

				//

				/*if(ATCmdQueue.count > 0){
					printf("ATCmdQueue.count  is %d\n", ATCmdQueue.count);
					//pthread_mutex_lock(&worker.counter_mutex);
					while(ATCmdQueue.count > 0){
						gb_commod(&ATCmdQueue);
					}
					//pthread_mutex_unlock(&worker.counter_mutex);
				}*/
				//
				usleep(100000);

				//
				}
			}
		else 
			gb_system(0, 1);

		sleep(10);
		}

	//reboot(RB_AUTOBOOT);
	printf("\ntbox down.\n");

	//pthread_exit(NULL);
	return;
}


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
int kill_pth()
{

	system("bash /ZY_TBOX/killpth_gyp4.sh");
	return 0;
}


//////
int led_int()
{
	system("bash /ZY_TBOX/sys-green.sh");			//
	system("bash /ZY_TBOX/sys-red.sh");
	return 0;
} //

////////
///


extern uint8 g_car_vin[17];
const unsigned int MODENDABLECAS[4] =
{
	172, 0, 0, 0, 
		};


const unsigned int MODENDABLECAS_T[4] =
{
	168, 0, 0, 0
};


void car_int()
{
	uint32_t i, j, temp, ki, g_temp;

	//unsigned long g_temp = 0;
	/////////////////////////////////////////////////////////////$)Ai2??o?=i8%g"??=o?=f?
	//$)Ai)4o?=i2??g"??o?=e?g"??i2??=o?=o?=o?=g?o?=i????o?=e?cellsystem_num
	gb_carDATA.gb_stReg_carDATA.energy_st_subsystem = 0;

	//$)Ai)4o?=i2??g"??o?=e?g"??i2??=o?=o?=o?=g?o?=i??$o?=o?=f?i2??=o?=g?o??llsystem_num
	gb_carDATA.gb_stReg_carDATA.Subsystem_code_num = 0;
	temp				=
		 gb_carDATA.gb_stReg_carDATA.energy_st_subsystem * gb_carDATA.gb_stReg_carDATA.Subsystem_code_num;

	for (i = 0; i < (temp); i++)
		{
		gb_carDATA.gb_stReg_carDATA.Subsystem_code[i] = 0x00;
		}

	//////////////////////////////////////////////////////////////$)Ao?=f2!i2??o?=e?i8%o?=
	gb_vehicle_DATA.gb_Vehicle_DATA.car_sta = Flameout; //$)Ai2??o?=i8%o?=f2$o?=e?
	gb_vehicle_DATA.gb_Vehicle_DATA.charge_sta = Charge_over; //$)Ai2??g"??o?=f2$o?=e?

	//
	gb_vehicle_DATA.gb_Vehicle_DATA.run = Pure_electric; //$)Ao?=o?=o?=o?=o?=f?o?=o?=

	//
	gb_vehicle_DATA.gb_Vehicle_DATA.speed[0] = 0x00; //$)Ai2??o?=o?=
	gb_vehicle_DATA.gb_Vehicle_DATA.speed[1] = 0x01; //$)Ai2??o?=o?=

	//
	gb_vehicle_DATA.gb_Vehicle_DATA.mileage[0] = 0x00; //$)Ao?=h?i2??=
	gb_vehicle_DATA.gb_Vehicle_DATA.mileage[1] = 0x00; //$)Ao?=h?i2??=
	gb_vehicle_DATA.gb_Vehicle_DATA.mileage[2] = 0x00; //$)Ao?=h?i2??=
	gb_vehicle_DATA.gb_Vehicle_DATA.mileage[3] = 0x00; //$)Ao?=h?i2??=

	//
	//usr_data_bwc_un.stusr_data_bwc.bwc_mileage[0] = gb_vehicle_DATA.gb_Vehicle_DATA.mileage[0];
	//usr_data_bwc_un.stusr_data_bwc.bwc_mileage[1] = gb_vehicle_DATA.gb_Vehicle_DATA.mileage[1];
	//usr_data_bwc_un.stusr_data_bwc.bwc_mileage[2] = gb_vehicle_DATA.gb_Vehicle_DATA.mileage[2];
	//usr_data_bwc_un.stusr_data_bwc.bwc_mileage[3] = gb_vehicle_DATA.gb_Vehicle_DATA.mileage[3];
	//
	gb_vehicle_DATA.gb_Vehicle_DATA.All_v[0] = 0x11; //$)Ao?=o?=g"??o?=i9?
	gb_vehicle_DATA.gb_Vehicle_DATA.All_v[1] = 0x22; //$)Ao?=o?=g"??o?=i9?

	//
	gb_vehicle_DATA.gb_Vehicle_DATA.All_i[0] = 0x11; //$)Ao?=o?=g"??o?=f?
	gb_vehicle_DATA.gb_Vehicle_DATA.All_i[1] = 0x22; //$)Ao?=o?=g"??o?=f?

	//
	gb_vehicle_DATA.gb_Vehicle_DATA.soc = 0x33; 	//soc

	//
	gb_vehicle_DATA.gb_Vehicle_DATA.DC_sta = 0xff;	//dc$)Ao?=f2$o?=e?

	//
	gb_vehicle_DATA.gb_Vehicle_DATA.Stall = 0xff;	//$)Ag"??o?=g?

	//
	gb_vehicle_DATA.gb_Vehicle_DATA.nsulation_res[0] = 0x11; //$)Ai8%i?o?=g?g"??o?=g?
	gb_vehicle_DATA.gb_Vehicle_DATA.nsulation_res[1] = 0x22; //$)Ai8%i?o?=g?g"??o?=g?

	//
	gb_vehicle_DATA.gb_Vehicle_DATA.usr[0] = 0xff;	//usr[0]:taban;usr[0]:tabanzhuangtai
	gb_vehicle_DATA.gb_Vehicle_DATA.usr[1] = 0xff;	//usr[0]:taban;usr[0]:tabanzhuangtai

	//
	//////////////////////////////////////////////////////////////$)Ao?=e??2g?g"??g&??o?=e?i8%o?=
	//
	driving_motor.cell_num = 1; 					//$)Ag&??o?=o?=o?=g?o?=o?=o?=e??2g?g"??g&??h7??o?=o?=???o?=e?

	//
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.Serial_number = 0x1; //$)Ao?=h?f=??=
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.state = 0xff; //$)Ao?=f2$o?=e?
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.contr_T = 0x01; //$)Ai)4o?=o?=o?=o?=o?=?2o?=
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.speed[0] = 0x00; //$)Ao?=i?o?=o?=
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.speed[1] = 0x00; //$)Ao?=i?o?=o?=
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.torque[0] = 0x00; //$)Ao?=i?i8%o?=
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.torque[1] = 0x00; //$)Ao?=i?i8%o?=
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.T = 0xff; //$)Ao?=o?=?2o?=
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.contr_V[0] = 0xff; //$)Ai)4o?=o?=o?=g"??o?=i9?
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.contr_V[1] = 0xff; //$)Ai)4o?=o?=o?=g"??o?=i9?
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.contr_I[0] = 0x00; //$)Ai)4o?=o?=o?=g"??o?=f?
	driving_motor.gb_Driving_motor_data[0].stDriving_motor_str.contr_I[1] = 0x00; //$)Ai)4o?=o?=o?=g"??o?=f?

	//////////////////////////////////////////////////////////////$)Ao?=o?=o?=o?=g"??i2??=o?=e?i8%o?=
	gb_power_batt_pack.gb_stP_b_pack.fuel_cell_V[0] = 0xff; //$)Ao?=o?=g"??o?=i9?
	gb_power_batt_pack.gb_stP_b_pack.fuel_cell_I[0] = 0xff; //$)Ao?=o?=g"??o?=f?
	gb_power_batt_pack.gb_stP_b_pack.fuel_cell_usr[0] = 0xff; //$)Ao?=f2!f=??=o?=i)4
	temp				= gb_power_batt_pack.gb_stP_b_pack.fuel_cell_num[0]; //$)Ao?=o?=?2o?=???o?=e?

	for (i = 0; i < temp; i++)
		gb_power_batt_pack.gb_stP_b_pack.fuel_cell_t[i] = 0xff; //$)Ao?=o?=?2o?=o?=g?

	gb_power_batt_pack.gb_stP_b_pack.fuel_cell_maxt[0] = 0xff; //$)Ao?=e????=o?=o?=?2o?=
	gb_power_batt_pack.gb_stP_b_pack.maxt_add = 0xff; //$)Ao?=g?o?=o?=
	gb_power_batt_pack.gb_stP_b_pack.fuel_cell_maxcc[0] = 0xff; //$)Ao?=e????=o?=f??2o?=
	gb_power_batt_pack.gb_stP_b_pack.maxcc_num = 0xff; //$)Ao?=g?o?=o?=
	gb_power_batt_pack.gb_stP_b_pack.fuel_cell_maxPa[0] = 0xff; //$)Ao?=e????=o?=i9?o?=o?=
	gb_power_batt_pack.gb_stP_b_pack.maxPa_num = 0xff; //$)Ao?=g?o?=o?=
	gb_power_batt_pack.gb_stP_b_pack.high_dc_sta = 0xff; //??$)A?=o?=i9?dco?=f2$o?=e?

	//////////////////////////////////////////////////////////////$)Ah7???2g?g&??o?=e?i8%o?=
	gb_engine_un.gb_stEngine.Engine_sta = 0xff; 	//$)Ah7???2g?g&??o?=f2$o?=e?

	for (i = 0; i < 4; i++)
		{
		gb_engine_un.gb_stEngine.speed[i] = 0x00;	//$)Ao?=i?o?=o?=
		gb_engine_un.gb_stEngine.Engine_usr[i] = 0x01; //$)Ao?=f2!f=??=o?=i)4
		}

	//////////////////////////////////////////////////////////////?$)A2f?o?=g?o?=e?i8%o?=
	gb_Add_sta.gb_Add_sta_bit.Add = 0;				//$)Ao?=o?=o?=f?
	gb_Add_sta.gb_Add_sta_bit.E_W = 0;				//?$)A2h?
	gb_Add_sta.gb_Add_sta_bit.N_S = 0;				//?$)A$e?
	gb_car_add_un.gb_stcar_add.car_add_sta = gb_Add_sta.add_sta_char; //$)Ao?=f2$o?=e?

	//
	gb_Add_sta.gb_Add_sta_bit.N_S = 0;
	gb_Add_sta.gb_Add_sta_bit.E_W = 0;

	g_temp				= 1040764;
	gb_car_add_un.gb_stcar_add.longitude[0] = (unsigned char) (g_temp >> 24);
	gb_car_add_un.gb_stcar_add.longitude[1] = (unsigned char) (g_temp >> 16);
	gb_car_add_un.gb_stcar_add.longitude[2] = (unsigned char) (g_temp >> 8);
	gb_car_add_un.gb_stcar_add.longitude[3] = (unsigned char) (g_temp);

	g_temp				= 386518;
	gb_car_add_un.gb_stcar_add.latitude[0] = (unsigned char) (g_temp >> 24);
	gb_car_add_un.gb_stcar_add.latitude[1] = (unsigned char) (g_temp >> 16);
	gb_car_add_un.gb_stcar_add.latitude[2] = (unsigned char) (g_temp >> 8);
	gb_car_add_un.gb_stcar_add.latitude[3] = (unsigned char) (g_temp);

	//
	//////////////////////////////////////////////////////////////$)Ao?=h?o?=g?o?=e?i8%o?=
	gb_extremum_un.gb_stextremum.extremum_maxv_box = 0x01; //$)Ao?=e????=o?=o?=o?=g?o?=i?f=??=
	gb_extremum_un.gb_stextremum.extremum_maxv_num = 0x02; //$)Ao?=e????=g"?%<o?=f?o?=g?o?=o?=
	gb_extremum_un.gb_stextremum.extremum_maxv[0] = 0x0c; //$)Ao?=e????=g"?%<o?=f?o?=g?
	gb_extremum_un.gb_stextremum.extremum_maxv[1] = 0x33;

	//
	gb_extremum_un.gb_stextremum.extremum_minv_box = 0x02; //$)Ao?=e?g"??=o?=o?=o?=g?o?=i?f=??=
	gb_extremum_un.gb_stextremum.extremum_minv_num = 0x03; //$)Ao?=e?g"??=g"?%<o?=f?o?=g?o?=o?=
	gb_extremum_un.gb_stextremum.extremum_minv[0] = 0x0c; //$)Ao?=e?g"??=g"?%<o?=f?o?=g?
	gb_extremum_un.gb_stextremum.extremum_minv[1] = 0x0c;

	//
	gb_extremum_un.gb_stextremum.extremum_maxt_box = 0x01; //$)Ao?=e????=o?=o?=o?=g?o?=i?f=??=
	gb_extremum_un.gb_stextremum.extremum_maxt_num = 0x02; //$)Ao?=e????=g"?%<o?=f?o?=g?o?=o?=
	gb_extremum_un.gb_stextremum.extremum_maxt = 0x33; //$)Ao?=e????=g"?%<o?=f?o?=g?

	//
	gb_extremum_un.gb_stextremum.extremum_mint_box = 0x03; //$)Ao?=e?g"??=o?=o?=o?=g?o?=i?f=??=
	gb_extremum_un.gb_stextremum.extremum_mint_num = 0x04; //$)Ao?=e?g"??=g"?%<o?=f?o?=g?o?=o?=
	gb_extremum_un.gb_stextremum.extremum_mint = 0x33; //$)Ao?=e?g"??=g"?%<o?=f?o?=g?

	//////////////////////////////////////////////////////////////$)Ag"?%<o?=f?g"??o?=i9?o?=e?i8%o?=
	power_cell_v.cell_num = CELL_NUM;				//?$)A2g?o?=o?=o?=e?g"??i2??=?3g?o?=o?=o?=e?N

	for (i = 0; i < CELL_NUM; i++)
		{
		power_cell_v.power_ce_data_V[i].stP_b_pack_V.P_b_pack_num = i + 1; //?$)A2g?o?=o?=o?=e?g"??i2??=?3g?o?=h?f=??=
		power_cell_v.power_ce_data_V[i].stP_b_pack_V.vol[0] = 0x11; //$)Ao?=o?=g"??o?=i9?
		power_cell_v.power_ce_data_V[i].stP_b_pack_V.vol[1] = 0x22; //$)Ao?=o?=g"??o?=i9?
		power_cell_v.power_ce_data_V[i].stP_b_pack_V.current[0] = 0x33; //$)Ao?=o?=g"??o?=f?
		power_cell_v.power_ce_data_V[i].stP_b_pack_V.current[1] = 0x44; //$)Ao?=o?=g"??o?=f?
		power_cell_v.power_ce_data_V[i].stP_b_pack_V.all_cell_num[0] =
			 (unsigned char) ((MODENDABLECAS[i] &0xff00) >> 8); //$)Ao?=o?=o?=e?
		power_cell_v.power_ce_data_V[i].stP_b_pack_V.all_cell_num[1] = (unsigned char) (MODENDABLECAS[i]); //$)Ao?=o?=o?=e?
		power_cell_v.power_ce_data_V[i].stP_b_pack_V.Serial[0] = 0x00; //?$)A$i8%o?=i?o?=e?o?=o?=o?=e?
		power_cell_v.power_ce_data_V[i].stP_b_pack_V.Serial[1] = 0x00; //?$)A$i8%o?=i?o?=e?o?=o?=o?=e?

		//
		if (MODENDABLECAS[i] <= 200) //$)Ah7??=o?=i?
			{
			power_cell_v.power_ce_data_V[i].stP_b_pack_V.cell_num = MODENDABLECAS[i];
			power_batt_pack_V[i].stP_b_pack_V.P_b_pack_num = 0xff;
			}
		else 
			{
			power_cell_v.power_ce_data_V[i].stP_b_pack_V.cell_num = 0xc8;
			}

		for (j = 0; j < power_cell_v.power_ce_data_V[i].stP_b_pack_V.cell_num; j++)
			{
			power_cell_v.power_ce_data_V[i].stP_b_pack_V.cell_voll[j * 2] = 0x0c;
			power_cell_v.power_ce_data_V[i].stP_b_pack_V.cell_voll[j * 2 + 1] = 0x33;
			}

		if (MODENDABLECAS[i] > 200) //$)Ah7??=o?=i?
			{
			power_batt_pack_V[i].stP_b_pack_V.P_b_pack_num = i + 1;
			power_batt_pack_V[i].stP_b_pack_V.vol[0] = 0x11; //$)Ao?=o?=g"??o?=i9?
			power_batt_pack_V[i].stP_b_pack_V.vol[1] = 0x22; //$)Ao?=o?=g"??o?=i9?
			power_batt_pack_V[i].stP_b_pack_V.current[0] = 0x33; //$)Ao?=o?=g"??o?=f?
			power_batt_pack_V[i].stP_b_pack_V.current[1] = 0x44; //$)Ao?=o?=g"??o?=f?
			power_batt_pack_V[i].stP_b_pack_V.all_cell_num[0] = (unsigned char) ((MODENDABLECAS[i] &0xff00) >> 8); //$)Ao?=o?=o?=e?
			power_batt_pack_V[i].stP_b_pack_V.all_cell_num[1] = (unsigned char) (MODENDABLECAS[i]); //$)Ao?=o?=o?=e?
			power_batt_pack_V[i].stP_b_pack_V.Serial[0] = 0x00; //?$)A$i8%o?=i?o?=e?o?=o?=o?=e?
			power_batt_pack_V[i].stP_b_pack_V.Serial[1] = 0xc8; //?$)A$i8%o?=i?o?=e?o?=o?=o?=e?
			power_batt_pack_V[i].stP_b_pack_V.cell_num = MODENDABLECAS[i] -200;

			for (j = 0; j < power_batt_pack_V[i].stP_b_pack_V.cell_num; j++)
				{
				power_batt_pack_V[i].stP_b_pack_V.cell_voll[j * 2] = 0x0c;
				power_batt_pack_V[i].stP_b_pack_V.cell_voll[j * 2 + 1] = 0x33;
				}
			}
		}

	//////////////////////////////////////////////////////////////$)Ag"?%<o?=f?o?=o?=?2o?=o?=e?i8%o?=
	power_cell_t.cell_num = CELL_NUM;				//?$)A2g?o?=o?=o?=e?g"??i2??=?3g?o?=o?=o?=e?N

	for (i = 0; i < CELL_NUM; i++)
		{
		power_cell_t.power_ce_data_T[i].stP_b_pack_T.P_b_pack_num = i + 1; //?$)A2g?o?=o?=o?=e?g"??i2??=?3g?o?=h?f=??=
		power_cell_t.power_ce_data_T[i].stP_b_pack_T.all_t_num[0] =
			 (unsigned char) ((MODENDABLECAS_T[i] &0xff00) >> 8); //$)Ao?=o?=o?=e?
		power_cell_t.power_ce_data_T[i].stP_b_pack_T.all_t_num[1] = (unsigned char) (MODENDABLECAS_T[i]); //$)Ao?=o?=o?=e?

		for (j = 0; j < MODENDABLECAS_T[i]; j++)
			{
			power_cell_t.power_ce_data_T[i].stP_b_pack_T.cell_voll[j] = 0x28;
			}
		}

	//////////////////////////////////////////////////////////////$)Ao?=o?=?2f?o?=f?o?=e?i8%o?=
}


//////////////////////////////////////////
//
int system_data()
{
	int i;

	//
	if (1)
		{
		g_car_vin[0]		= 'L';
		g_car_vin[1]		= 'E';
		g_car_vin[2]		= '3';
		g_car_vin[3]		= 'L';
		g_car_vin[4]		= 'G';
		g_car_vin[5]		= '5';
		g_car_vin[6]		= 'J';
		g_car_vin[7]		= 'U';
		g_car_vin[8]		= '7';
		g_car_vin[9]		= 'J';
		g_car_vin[10]		= 'R';
		g_car_vin[11]		= '1';
		g_car_vin[12]		= '8';
		g_car_vin[13]		= '3';
		g_car_vin[14]		= '3';
		g_car_vin[15]		= '6';
		g_car_vin[16]		= '6';

		//
		for (i = 0; i < 20; i++)
			{
			gb_carDATA.gb_stReg_carDATA.ICCID[i] = 0x01;
			}

		//
		comm_int();
		gb_data_set(0);

		//
		car_int();

		//
		safe_time			= 1000;
		newup_time			= 2;
		almup_time			= 1000;
		heatup_time 		= 10;
		time_time			= 60;

		//
		//
		usr_data_bwc_un.stusr_data_bwc.bwc_door1 = 0x01;

		//
		usr_data_bwc_un.stusr_data_bwc.bwc_door2 = 0x01;

		//
		usr_data_bwc_un.stusr_data_bwc.bwc_door3 = 0x01;

		//
		usr_data_bwc_un.stusr_data_bwc.bwc_door4 = 0x01;

		//
		usr_data_bwc_un.stusr_data_bwc.bwc_door5 = 0x01;

		//
		usr_data_bwc_un.stusr_data_bwc.bwc_lock = 0x01;

		//
		usr_data_bwc_un.stusr_data_bwc.bwc_lamp = 0x01;

		//
		usr_data_bwc_un.stusr_data_bwc.bwc_window = 0x01;

		//
		usr_data_bwc_un.stusr_data_bwc.bwc_charge = 0x01;

		//
		usr_data_bwc_un.stusr_data_bwc.bwc_addmileage[0] = 0x32;

		//
		usr_data_bwc_un.stusr_data_bwc.bwc_mileage[2] = 0x20;
		usr_data_bwc_un.stusr_data_bwc.bwc_mileage[3] = 0x4E;

		//
		//
		}
	else 
		{

		}

	//
	//
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////
extern int serial_main_HMI(void);
extern int modbusRTUMaste_AMP(void);
extern int modbusRTUMaste_PCS(void);
extern int SmartEnergy_tast(void);
extern int IO_main(void);


//////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	pthread_t id_hmi, id_sqlite3, id_can0, id_can1, id_cantast, id_cansend0, id_cansend1, id_bt, id_wifi, 
		id_gps, id_sockte, id_ftp, 
		id_datasafe, id_led, id_gb_tbox;			//pthread_t
	pthread_t id_AMP, id_PCS;
	pthread_t id_SE, id_IO;

	//
	int ret_hmi, ret_sqlite3, ret_can0, ret_can1, ret_cantast, ret_cansend0, ret_cansend1, ret_bt, 
		ret_wifi, ret_gps, ret_sockte, 
		ret_ftp, ret_datasafe, ret_led, ret_gb_tbox; //pthread_ID
	int ret_AMP, ret_PCS;
	int ret_SE, ret_IO;
	int ret_return;

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//execlp("login","login","-f","root",0);
	//killpth
	kill_pth();

	led_int();

	//
	can_ini();

	//
	worker.counter		= 0;
	pthread_mutex_init(&worker.counter_mutex, NULL);

	//
	ret_hmi 			= pthread_create(&id_hmi, NULL, (void * (*) (void *)) serial_main_HMI, NULL);

	//
	ret_sqlite3 		= pthread_create(&id_sqlite3, NULL, (void * (*) (void *)) sqlite3_DB, NULL); //$)Ao?=e?i8%o?=i2??o?=o?=g&??

	//
	ret_can0			= pthread_create(&id_can0, NULL, (void * (*) (void *)) can0_main, NULL); //can$)Ai2??o?=o?=g&??

	//
	ret_can1			= pthread_create(&id_can1, NULL, (void * (*) (void *)) can1_main, NULL); //can$)Ai2??o?=o?=g&??

	//
	//ret_cantast		= pthread_create(&id_cantast, NULL, (void * (*) (void *)) cantast, NULL); //can$)Ai2??o?=o?=g&??
	ret_cansend0		= pthread_create(&id_cansend0, NULL, (void * (*) (void *)) cansend0, NULL);
	ret_cansend1		= pthread_create(&id_cansend1, NULL, (void * (*) (void *)) cansend1, NULL);

	//
	//ret_bt = pthread_create(&id_bt,NULL,(void*(*)(void*)) bt_ini,NULL);//bt$)Ai2??o?=o?=g&??
	//
	//ret_gps = pthread_create(&id_gps,NULL,(void*(*)(void*)) gps_main(),NULL);//gps$)Ai2??o?=o?=g&??
	//
#if (								G4_TBOX 						== 1)
	ret_sockte			= pthread_create(&id_sockte, NULL, (void * (*) (void *)) sockte_gb, NULL); //$)Ao?=f?o?=e?o?=e?o?=o?=i2??o?=o?=g&??
#endif

	//
	//ret_ftp= pthread_create(&id_ftp,NULL,(void*(*)(void*)) ftp_gb,NULL);//$)Ao?=i?i2??=o?=e?o?=i?i2??o?=o?=g&??
	//
	//ret_datasfae= pthread_create(&id_datasfae,NULL,(void*(*)(void*)) datasafe_ini,NULL);//$)Ao?=e?i8%o?=?3h?o?=h?i2??o?=o?=g&??
	//
#if (								GB_BWT_TBOX 					== 1)
	ret_gb_tbox 		= pthread_create(&id_gb_tbox, NULL, (void * (*) (void *)) gb_tbox, NULL);
#endif

	//
	ret_led 			= pthread_create(&id_led, NULL, (void * (*) (void *)) led_main, NULL);

	//
	ret_AMP 			= pthread_create(&id_AMP, NULL, (void * (*) (void *)) modbusRTUMaste_AMP, NULL);

	//
	ret_PCS 			= pthread_create(&id_PCS, NULL, (void * (*) (void *)) modbusRTUMaste_PCS, NULL);

	//
	ret_SE				= pthread_create(&id_SE, NULL, (void * (*) (void *)) SmartEnergy_tast, NULL);

	//
	ret_IO				= pthread_create(&id_IO, NULL, (void * (*) (void *)) IO_main, NULL);

	//////////////////////////////////////////////////////////////////////
	pthread_mutex_destroy(&worker.counter_mutex);

	//////////////////////////////////////////////////////////////////////
	//
	ret_return			= pthread_join(id_sqlite3, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_sqlite3 down:%d.\n", ret_return);
		}

	//
	ret_return			= pthread_join(id_can0, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_can0 down:%d.\n", ret_return);
		}

	//
	ret_return			= pthread_join(id_can1, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_can1 down:%d.\n", ret_return);
		}

	//
#if (								G4_TBOX 						== 1)
	ret_return			= pthread_join(id_sockte, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_sockte down:%d.\n", ret_return);
		}

#endif

	//
	ret_return			= pthread_join(id_led, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_led down:%d.\n", ret_return);
		}

	//
	//pthread_join(id_cantast, NULL);
	ret_return			= pthread_join(id_cansend0, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_cansend0 down:%d.\n", ret_return);
		}

	ret_return			= pthread_join(id_cansend1, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_cansend1 down:%d.\n", ret_return);
		}

	//
#if (								GB_BWT_TBOX 					== 1)
	ret_return			= pthread_join(id_gb_tbox, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_gb_tbox down:%d.\n", ret_return);
		}

#endif

	//
	ret_return			= pthread_join(id_hmi, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_hmi down:%d.\n", ret_return);
		}

	//
	ret_return			= pthread_join(id_SE, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_SE down:%d.\n", ret_return);
		}

	//
	ret_return			= pthread_join(id_AMP, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_AMP down:%d.\n", ret_return);
		}

	//
	ret_return			= pthread_join(id_IO, NULL);

	//if (ret_return == 0)
		{
		printf("\nid_IO down:%d.\n", ret_return);
		}

	//
	//gb_datasave(0);
	//
	//
	//pthread_mutex_destroy(&worker.counter_mutex);
	//
	printf("\nEMS down.................................\n");
	reboot(RB_AUTOBOOT);

	//
	return 1;
}











