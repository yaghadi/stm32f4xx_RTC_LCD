/*
 * LCD.c
 *
 *  Created on: Jul 8, 2024
 *      Author: PurplE
 */


#include "LCD.h"
static void write_4_bits(uint8_t value);
static void lcd_enable(void);
static void udelay(uint32_t cnt);

void lcd_send_command(uint8_t cmd){
	//RS=0 for command
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_RS, GPIO_PIN_RESET);
	//R/W 0 for command
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_RW, GPIO_PIN_RESET);
	//send the higher nibble of the command
	write_4_bits(cmd >> 4);
	//send the lower nibble of the command
	write_4_bits(cmd & 0x0F);
}
void lcd_send_char(uint8_t data){
	//RS=1 for user data
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_RS, GPIO_PIN_SET);
	//R/W 0 for command
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_RW, GPIO_PIN_RESET);
	//send the higher nibble of the user data
	write_4_bits(data >> 4);
	//send the lower nibble of the user data
	write_4_bits(data & 0x0F);
}
void lcd_print_string(char* message){
	do{
		lcd_send_char((uint8_t)*message++);
	}while(*message != '\0');
}
void lcd_set_cursor(uint8_t row,uint8_t column){
	column--;
	switch(row){
	case 1:
		lcd_send_command((column |= 0x80));
		break;
	case 2:
		lcd_send_command((column |= 0xC0));
		break;
	default:
		break;
	}
}
void lcd_init(void){


	GPIO_InitTypeDef LCD_signal;

	/*Configure GPIO pins : LCD_GPIO_RS LCD_GPIO_RW LCD_GPIO_EN
	 * 						LCD_GPIO_D4 LCD_GPIO_D5 LCD_GPIO_D6 LCD_GPIO_D7
	 */
	LCD_signal.Pin = LCD_GPIO_RS|LCD_GPIO_RW|LCD_GPIO_EN|LCD_GPIO_D4
	                          |LCD_GPIO_D5|LCD_GPIO_D6|LCD_GPIO_D7;
	LCD_signal.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_signal.Pull = GPIO_NOPULL;
	LCD_signal.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &LCD_signal);


	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_RS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_RW, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_EN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_D4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_D5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_D6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_D7, GPIO_PIN_RESET);

	//initialization sequence
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_RS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_RW, GPIO_PIN_RESET);
	HAL_Delay(40);

	write_4_bits(0x03);

	HAL_Delay(5);

	write_4_bits(0x03);

	udelay(150);

	write_4_bits(0x03);
	write_4_bits(0x02);

	//function set Command
	lcd_send_command(LCD_CMD_4DL_2N_5X8F);

	//Display ON and cursor ON
	lcd_send_command(LCD_CMD_DON_CURON);

	//display clear
	lcd_display_clear();

	//entry mode set
	lcd_send_command(LCD_CMD_INCADD);


}
void lcd_display_clear(void){
	lcd_send_command(LCD_CMD_DIS_CLEAR);
	HAL_Delay(2);
}
void lcd_display_return_home(void){
	lcd_send_command(LCD_CMD_DIS_RETURN_HOME);
	HAL_Delay(2);
}
static void write_4_bits(uint8_t value){
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_D4, ((value >> 0) & 0x01));
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_D5, ((value >> 1) & 0x01));
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_D6, ((value >> 2) & 0x01));
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_D7, ((value >> 3) & 0x01));

	lcd_enable();
}
static void lcd_enable(void){
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_EN, GPIO_PIN_SET);
	udelay(100);
	HAL_GPIO_WritePin(GPIOD, LCD_GPIO_EN, GPIO_PIN_RESET);
	udelay(100);
}
char* date_to_string(RTC_DateTypeDef *RTC_date){
	static char buf[11];

	buf[2]='/';
	buf[5]='/';

	number_to_string(RTC_date->Date,&buf[0]);
	number_to_string(RTC_date->Month,&buf[3]);
	number_to_string(RTC_date->Year,&buf[6]);

	buf[10]='\0';
	return buf;
}
char* time_to_string(RTC_TimeTypeDef *RTC_time){
	static char buf[9];

	buf[2]=':';
	buf[5]=':';

	number_to_string(RTC_time->Hours,&buf[0]);
	number_to_string(RTC_time->Minutes,&buf[3]);
	number_to_string(RTC_time->Seconds,&buf[6]);

	buf[8]='\0';
	return buf;
}
void number_to_string(uint8_t num,char* buf){
	if(num<10){
		buf[0]='0';
		buf[1]=num+48;
	}else if(num >=10 && num <99){
		buf[0]=(num/10)+48;
		buf[1]=(num%10)+48;
	}
}
void lcd_createChar(uint8_t location, uint8_t charc[]){
	location &=0x07;
	lcd_send_command(LCD_SETCGRAMADDR | (location << 3));
	  for (int i=0; i<8; i++) {
		  lcd_send_char(charc[i]);
	  }
}
static void udelay(uint32_t cnt){
	for(uint32_t i=0;i<cnt;i++);
}
