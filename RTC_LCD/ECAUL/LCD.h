/*
 * LCD.h
 *
 *  Created on: Jul 8, 2024
 *      Author: PurplE
 */

#ifndef LCD_H_
#define LCD_H_

#include "main.h"


void lcd_init(void);
void lcd_send_command(uint8_t cmd);
void lcd_send_char(uint8_t data);
void lcd_display_clear(void);
void lcd_display_return_home(void);
void lcd_print_string(char* message);
void lcd_set_cursor(uint8_t row,uint8_t column);
char* time_to_string(RTC_TimeTypeDef *RTC_time);
char* date_to_string(RTC_DateTypeDef *RTC_date);
void number_to_string(uint8_t num,char* buf);
void lcd_createChar(uint8_t location, uint8_t charc[]);
//define commands
#define LCD_CMD_4DL_2N_5X8F			0x28
#define LCD_CMD_DON_CURON			0x0E
#define LCD_CMD_INCADD				0x06
#define LCD_CMD_DIS_CLEAR			0x01
#define LCD_CMD_DIS_RETURN_HOME		0x02
#define LCD_SETCGRAMADDR 			0x40
//Application configurable items
#define LCD_GPIO_PORT	GPIOD
#define LCD_GPIO_RS		GPIO_PIN_0
#define LCD_GPIO_RW		GPIO_PIN_1
#define LCD_GPIO_EN		GPIO_PIN_2
#define LCD_GPIO_D4		GPIO_PIN_3
#define LCD_GPIO_D5		GPIO_PIN_4
#define LCD_GPIO_D6		GPIO_PIN_7
#define LCD_GPIO_D7		GPIO_PIN_6





#endif /* LCD_H_ */
