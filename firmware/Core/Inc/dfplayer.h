/*
 * dfplayer.h
 *
 *  Created on: Nov 1, 2024
 *      Author: ChristianNolte
 */

#ifndef INC_DFPLAYER_H_
#define INC_DFPLAYER_H_

extern UART_HandleTypeDef huart1;

void dfplayer_send_command_next();
void dfplayer_send_command_previous();
void dfplayer_send_command_increase_volume();
void dfplayer_send_command_decrease_volume();
void dfplayer_send_command_standby();
void dfplayer_send_command_normal_working();
void dfplayer_send_command_reset_module();
void dfplayer_send_command_playback();
void dfplayer_send_command_pause();

void dfplayer_send_command_specify_track(uint16_t tracknumber);
void dfplayer_send_command_specify_volume(uint8_t volume);
void dfplayer_send_command_specify_playback_mode(uint8_t playback_mode);
void dfplayer_send_command_specify_playback_source(uint8_t playback_source);
void dfplayer_send_command_specify_folder(uint8_t folder);
void dfplayer_send_command_volume_adjust(uint8_t volume_adjust, uint8_t volume_gain);




#endif /* INC_DFPLAYER_H_ */
