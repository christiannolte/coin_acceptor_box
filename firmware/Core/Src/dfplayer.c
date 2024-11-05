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
#define CMD_SET_FOLDER	0x0F
#define CMD_SET_VOL_ADJ	0x10
#define CMD_SET_REPEAT	0x11

#define PARAMETER_1_NA	0x00
#define PARAMETER_2_NA	0x00


void dfplayer_send_command_tx(uint8_t *buf, uint8_t len)
{
	uint16_t mycrc;
	uint8_t sndbuf[len+4];
	uint8_t i;

	sndbuf[0]=0x7F;             //START
	for(i=0;i<len;i++)
	{
		sndbuf[i+1]=buf[i];
	}
	mycrc=0;
	for(i=0;i<len;i++)
	{
		mycrc-=buf[i];
	}
	sndbuf[len+1]=mycrc>>8;      //crc high byte
	sndbuf[len+2]=mycrc&0xff;    //crc low byte
	sndbuf[len+3]=0xEF;          //END
	HAL_UART_Transmit(&huart1,sndbuf,len+4,10);// Sending in normal mode
}

void dfplayer_send_command(uint8_t command, uint8_t highparameter, uint8_t lowparameter)
{
	// FF 06 01 00 crc1 crc2
	uint8_t mybuf[4];
	mybuf[0]=0xFF;   //version
    mybuf[1]=6;      //6 byte length
    mybuf[2]=command;      //cmd 1 next
    mybuf[3]=0;      //no feedback
    dfplayer_send_command_tx(mybuf, 4);
}

//NEXT
void dfplayer_send_command_next()
{
	dfplayer_send_command(CMD_NEXT,PARAMETER_1_NA,PARAMETER_2_NA);
}

//PREVIOUS
void dfplayer_send_command_previous()
{
	dfplayer_send_command(CMD_PREV,PARAMETER_1_NA,PARAMETER_2_NA);
}

//SPECIFY TRACK
void dfplayer_send_command_specify_track(uint16_t tracknumber)
{
	dfplayer_send_command(CMD_SET_TRACK ,tracknumber>>8,tracknumber&0xff);
}

//INCREASE VOLUME
void dfplayer_send_command_increase_volume()
{
	dfplayer_send_command(CMD_INC_VOL,PARAMETER_1_NA,PARAMETER_2_NA);
}

//DECREASE VOLUME
void dfplayer_send_command_decrease_volume()
{
	dfplayer_send_command(CMD_DEC_VOL, PARAMETER_1_NA, PARAMETER_2_NA);
}

//SPECIFY VOLUME
void dfplayer_send_command_specify_volume(uint8_t volume)
{
	dfplayer_send_command(CMD_SET_VOL, PARAMETER_1_NA, volume);
}

//SPECIFY EQ
void dfplayer_send_command_specify_eq(uint8_t eq)
{
	dfplayer_send_command(CMD_SET_EQ, PARAMETER_1_NA, eq);
}

//SPECIFY PLAYBACK MODE
void dfplayer_send_command_specify_playback_mode(uint8_t playback_mode)
{
	dfplayer_send_command(CMD_SET_PB_MODE, PARAMETER_1_NA, playback_mode);
}

//SPECIFY PLAYBACK SOURCE
void dfplayer_send_command_specify_playback_source(uint8_t playback_source)
{
	dfplayer_send_command(CMD_SET_PB_SRC, PARAMETER_1_NA, playback_source);
}

//ENTER STANDBY MODE
void dfplayer_send_command_standby()
{
	dfplayer_send_command(CMD_STANDBY, PARAMETER_1_NA, PARAMETER_2_NA);
}

//NORMAL WORKING
void dfplayer_send_command_normal_working()
{
	dfplayer_send_command(CMD_NORMAL, PARAMETER_1_NA, PARAMETER_2_NA);
}

//RESET MODULE
void dfplayer_send_command_reset_module()
{
	dfplayer_send_command(CMD_RESET, PARAMETER_1_NA, PARAMETER_2_NA);
}

//PLAYBACK
void dfplayer_send_command_playback()
{
	dfplayer_send_command(CMD_PLAYBACK, PARAMETER_1_NA, PARAMETER_2_NA);
}

//PAUSE
void dfplayer_send_command_pause()
{
	dfplayer_send_command(CMD_PAUSE, PARAMETER_1_NA, PARAMETER_2_NA);
}

//SPECIFY FOLDER
void dfplayer_send_command_specify_folder(uint8_t folder)
{
	dfplayer_send_command(CMD_SET_FOLDER, PARAMETER_1_NA, folder);
}

//VOLUME ADJUST SET
void dfplayer_send_command_volume_adjust(uint8_t volume_adjust, uint8_t volume_gain)
{
	dfplayer_send_command(CMD_SET_VOL_ADJ, volume_adjust, volume_gain);
}

//REPEAT play
void dfplayer_send_command_set_repeat(uint8_t repeat)
{
	dfplayer_send_command(CMD_SET_REPEAT, PARAMETER_1_NA, repeat);
}
