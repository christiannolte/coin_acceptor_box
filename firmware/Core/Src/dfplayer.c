/*
 * dfplayer.c
 *
 *  Created on: Nov 1, 2024
 *      Author: ChristianNolte
 */
#include "stm32f1xx_hal.h"
#include "dfplayer.h"

#define CMD_NEXT		0x01
#define CMD_PREV		0x02
#define CMD_SET_TRACK   0x03
#define CMD_INC_VOL		0x04
#define CMD_DEC_VOL		0x05
#define CMD_SET_VOL     0x06
#define CMD_SET_EQ      0x07
#define CMD_SET_PB_MODE 0x08
#define CMD_SET_PB_SRC  0x09
#define CMD_STANDBY		0x0A
#define CMD_NORMAL		0x0B
#define CMD_RESET		0x0C
#define CMD_PLAYBACK	0x0D
#define CMD_PAUSE		0x0E
#define CMD_FILE_FOLDER	0x0F
#define CMD_SET_VOL_ADJ	0x10
#define CMD_SET_REPEAT	0x11
#define CMD_PLAY_FROM_MP3_FOLDER 0x12
#define CMD_INSERT_ADVERTISEMENT 0x13

#define CMD_STOP_ADVERTISEMENT   0x15
#define CMD_STOP_ALL             0x16
#define CMD_PLAY_COMPLETE_FOLDER 0x17

#define CMD_GET_VOLUME   0x43

#define CMD_GET_VERSION  0x46


#define CMD_SET_DAC		0x1A

#define PARAMETER_1_NA	0x00
#define PARAMETER_2_NA	0x00

#define DAC_ON			0x00
#define DAC_OFF			0x01

#define NO_RESPONSE		0x00
#define RESPONSE		0x01

extern UART_HandleTypeDef huart3;
uint8_t rxbuffer[10];

uint16_t get_rxcrc()
{
	uint8_t i;
	uint16_t crc;

	crc=0;
	for(i=1;i<7;i++)
	{
		crc-=rxbuffer[i];
	}
	return(crc);
}

uint16_t get_crc(uint8_t *ptr)
{
	uint8_t i;
	uint16_t crc;

	crc=0;
	for(i=1;i<7;i++)
	{
		crc-=ptr[i];
	}
	return(crc);
}


uint8_t dfplayer_receive_packet()
{
	if(HAL_UART_Receive(&huart3, rxbuffer, 10, 100)==HAL_OK) //if transfer is successful
	  {
		//10 Byte received 1st step ok
		//lets check crc
		uint16_t read_crc;
		read_crc=rxbuffer[7]<<8;
		read_crc|=rxbuffer[8];
		if(get_rxcrc()==read_crc){
			return(0);
		}
		else
		{
			//maybe out of sync, lets see what we can do
			if(HAL_UART_Receive(&huart3, rxbuffer, 1, 100)==HAL_OK) //if transfer is successful
			{
				// one caracter sussesshul read
				return(-1);
			}
			else
			{
				//reading not possible
				return(-1);
			}
			return(-1);
		}
		return(0);
	  } else {
	    return(-1);
	  }
}

void dfplayer_send_command(uint8_t response, uint8_t command, uint8_t highparameter, uint8_t lowparameter)
{
	uint8_t sndbuf[10];
	uint16_t mycrc;

	sndbuf[0]=0x7F;             //START
	sndbuf[1]=0xFF;   //version
	sndbuf[2]=6;      //6 byte length
	sndbuf[3]=command;      //cmd 1 next
	sndbuf[4]=response;
	sndbuf[5]=highparameter;
	sndbuf[6]=lowparameter;
	sndbuf[7]=0;      //crc high byte dummy
	sndbuf[8]=0;      //crc low byte dummy
	sndbuf[9]=0xEF;          //END
	mycrc=get_crc(sndbuf);
	sndbuf[7]=mycrc>>8;      //crc high byte
	sndbuf[8]=mycrc&0xff;      //crc low byte dummy
	HAL_UART_Transmit(&huart3,sndbuf,10,10);// Sending in normal mode
}


void dfplayer_send_command_with_response(uint8_t command, uint8_t highparameter, uint8_t lowparameter)
{
	dfplayer_send_command(RESPONSE, command, highparameter, lowparameter);
}

void dfplayer_send_command_no_response(uint8_t command, uint8_t highparameter, uint8_t lowparameter)
{
	dfplayer_send_command(NO_RESPONSE, command, highparameter, lowparameter);
}


void dfplayer_sync()
{
	uint8_t cnt=0;
	dfplayer_send_command_with_response(CMD_GET_VERSION, PARAMETER_1_NA, PARAMETER_2_NA);
	HAL_Delay(100);
	do
	{
		__NOP();
		cnt++;
		HAL_Delay(1);
	}
	while(HAL_UART_Receive(&huart3, rxbuffer, 1, 100)==HAL_OK);
}



//NEXT
void dfplayer_send_command_next()
{
	dfplayer_send_command_no_response(CMD_NEXT,PARAMETER_1_NA,PARAMETER_2_NA);
}

//PREVIOUS
void dfplayer_send_command_previous()
{
	dfplayer_send_command_no_response(CMD_PREV,PARAMETER_1_NA,PARAMETER_2_NA);
}

//SPECIFY TRACK
void dfplayer_send_command_play_track_in_root_directory(uint16_t tracknumber)
{
	dfplayer_send_command_no_response(CMD_SET_TRACK ,tracknumber>>8,tracknumber&0xff);
}

//INCREASE VOLUME
void dfplayer_send_command_increase_volume()
{
	dfplayer_send_command_no_response(CMD_INC_VOL,PARAMETER_1_NA,PARAMETER_2_NA);
}

//DECREASE VOLUME
void dfplayer_send_command_decrease_volume()
{
	dfplayer_send_command_no_response(CMD_DEC_VOL, PARAMETER_1_NA, PARAMETER_2_NA);
}

//SPECIFY VOLUME
void dfplayer_send_command_specify_volume(uint8_t volume)
{
	dfplayer_send_command_no_response(CMD_SET_VOL, PARAMETER_1_NA, volume);
}

//SPECIFY EQ
void dfplayer_send_command_specify_eq(uint8_t eq)
{
	dfplayer_send_command_no_response(CMD_SET_EQ, PARAMETER_1_NA, eq);
}

//SPECIFY PLAYBACK MODE
void dfplayer_send_command_specify_playback_mode(uint8_t playback_mode)
{
	dfplayer_send_command_no_response(CMD_SET_PB_MODE, PARAMETER_1_NA, playback_mode);
}

//SPECIFY PLAYBACK SOURCE
void dfplayer_send_command_specify_playback_source(uint8_t playback_source)
{
	dfplayer_send_command_no_response(CMD_SET_PB_SRC, PARAMETER_1_NA, playback_source);
}

//ENTER STANDBY MODE
void dfplayer_send_command_standby()
{
	dfplayer_send_command_no_response(CMD_STANDBY, PARAMETER_1_NA, PARAMETER_2_NA);
}

//NORMAL WORKING
void dfplayer_send_command_normal_working()
{
	dfplayer_send_command_no_response(CMD_NORMAL, PARAMETER_1_NA, PARAMETER_2_NA);
}

//RESET MODULE
void dfplayer_send_command_reset_module()
{
	dfplayer_send_command_no_response(CMD_RESET, PARAMETER_1_NA, PARAMETER_2_NA);
}

//PLAYBACK
void dfplayer_send_command_playback()
{
	dfplayer_send_command_no_response(CMD_PLAYBACK, PARAMETER_1_NA, PARAMETER_2_NA);
}

//PAUSE
void dfplayer_send_command_pause()
{
	dfplayer_send_command_no_response(CMD_PAUSE, PARAMETER_1_NA, PARAMETER_2_NA);
}

//SPECIFY FOLDER
void dfplayer_send_command_play_file_in_folder(uint8_t foldernumber, uint8_t filenumber)
{
	dfplayer_send_command_no_response(CMD_FILE_FOLDER, foldernumber, filenumber);
}

//VOLUME ADJUST SET
void dfplayer_send_command_volume_adjust(uint8_t volume_adjust, uint8_t volume_gain)
{
	dfplayer_send_command_no_response(CMD_SET_VOL_ADJ, volume_adjust, volume_gain);
}

//REPEAT play
void dfplayer_send_command_set_repeat(uint8_t repeat)
{
	dfplayer_send_command_no_response(CMD_SET_REPEAT, PARAMETER_1_NA, repeat);
}

//Play file from MP3 folder
void dfplayer_play_track_from_mp3_folder(uint16_t filenumber)
{
	dfplayer_send_command_no_response(CMD_PLAY_FROM_MP3_FOLDER, filenumber>>8, filenumber&0xff);
}

//insert advertisement
void dfplayer_insert_advertisement(uint16_t filenumber)
{
	dfplayer_send_command_no_response(CMD_INSERT_ADVERTISEMENT, filenumber>>8, filenumber&0xff);
}

//ENABLE DAC
void dfplayer_enable_dac()
{
	dfplayer_send_command_no_response(CMD_SET_DAC, PARAMETER_1_NA, DAC_ON);
}

//DISABLE DAC
void dfplayer_disable_dac()
{
	dfplayer_send_command_no_response(CMD_SET_DAC, PARAMETER_1_NA, DAC_OFF);
}

//STOP ADVERTISEMENT
void dfplayer_stop_advertisement()
{
	dfplayer_send_command_no_response(CMD_STOP_ADVERTISEMENT, PARAMETER_1_NA, PARAMETER_2_NA);
}

//STOP ALL
void dfplayer_stop_all()
{
	dfplayer_send_command_no_response(CMD_STOP_ALL, PARAMETER_1_NA, PARAMETER_2_NA);
}

//PLAY COMPLETE FOLDER
void dfplayer_play_complete_folder(uint8_t folder)
{
	dfplayer_send_command_no_response(CMD_PLAY_COMPLETE_FOLDER, PARAMETER_1_NA, folder);
}


//query volume
uint8_t dfplayer_get_volume()
{

	dfplayer_send_command_with_response(CMD_GET_VOLUME, PARAMETER_1_NA, PARAMETER_2_NA);
//	dfplayer_receive_packet();
//	return(rxbuffer[6]);
}

//query vversion
uint8_t dfplayer_get_version()
{
	dfplayer_send_command_with_response(CMD_GET_VERSION, PARAMETER_1_NA, PARAMETER_2_NA);
//	dfplayer_receive_packet();
//	return(rxbuffer[6]);
}
