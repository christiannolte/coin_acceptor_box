/*
 * dfplayer.h
 *
 *  Created on: Nov 1, 2024
 *      Author: ChristianNolte
 */

#ifndef INC_DFPLAYER_H_
#define INC_DFPLAYER_H_

#define EQ_NORMAL	0x00
#define EQ_POP		0x01
#define EQ_ROCK		0x02
#define EQ_JAZZ		0x03
#define EQ_CLASSIC	0x04
#define EQ_BASE		0x05

#define PB_MODE_REPEAT			0x00
#define PB_MODE_FOLDER_REPEAT	0x01
#define PB_MODE_SINGLE_REPEAT	0x02
#define PB_MODE_RANDOM			0x03

#define PB_SOURCE_U				0x00
#define PB_SOURCE_TF			0x01
#define PB_SOURCE_AUX			0x02
#define PB_SOURCE_SLEEP			0x03
#define PB_SOURCE_FLASH			0x04

void dfplayer_sync(void);

void dfplayer_send_command_next(void);
void dfplayer_send_command_previous(void);
void dfplayer_send_command_increase_volume(void);
void dfplayer_send_command_decrease_volume(void);
void dfplayer_send_command_standby(void);
void dfplayer_send_command_normal_working(void);
void dfplayer_send_command_reset_module(void);
void dfplayer_send_command_playback(void);
void dfplayer_send_command_pause(void);

void dfplayer_enable_dac(void);
void dfplayer_disable_dac(void);
void dfplayer_stop_advertisement(void);
void dfplayer_stop_all(void);
void dfplayer_play_complete_folder(uint8_t folder);

void dfplayer_send_command_play_track_in_root_directory(uint16_t tracknumber);
void dfplayer_send_command_specify_volume(uint8_t volume);
void dfplayer_send_command_specify_playback_mode(uint8_t playback_mode);
void dfplayer_send_command_specify_playback_source(uint8_t playback_source);
void dfplayer_send_command_play_file_in_folder(uint8_t foldernumber, uint8_t filenumber);
void dfplayer_send_command_volume_adjust(uint8_t volume_adjust, uint8_t volume_gain);
void dfplayer_play_track_from_mp3_folder(uint16_t filenumber);

uint8_t dfplayer_get_volume(void);

#endif /* INC_DFPLAYER_H_ */
