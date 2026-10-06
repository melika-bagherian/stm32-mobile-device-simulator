/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LiquidCrystal.h"
#include "string.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "note.h"
#include "contact.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CHAR_HUMAN 1
#define CHAR_Plant   2
#define CHAR_Contact  3
#define BLOCK_ROWS 4
#define BLOCK_COLS 6
#define CHAR_Notes 5
#define CHAR_Music 7
#define CHAR_Settings 8
#define CHAR_Info 6
#define CHAR_P1 4
#define CHAR_P2 6
#define CHAR_S 3
#define CHAR_HEART 5


#define CHAR_pervious 1
#define CHAR_next 2
#define CHAR_song 3
#define MELODY_DURATION_MS 30000


#define MAX_ZOMBIES 10
#define MAP_HEIGHT 4
#define MAP_WIDTH 17
#define MAX_PLANTS 15
#define MAX_BULLETS 20
#define BULLET_INVALID_ROW 255
#define SHOOT_DELAY 3
#define SONG_LENGTH(song) (sizeof(song) / sizeof(song[0]))



/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

PCD_HandleTypeDef hpcd_USB_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM3_Init(void);
static void MX_ADC3_Init(void);
static void MX_ADC2_Init(void);
/* USER CODE BEGIN PFP */
typedef unsigned char byte;
RTC_TimeTypeDef nowTime;
RTC_DateTypeDef nowDate;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */




void off() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, RESET);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);

}

void show_0() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);

}
void show_1() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_2() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_3() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);

}
void show_4() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_5() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_6() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_7() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void show_8() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, SET);
}
void show_9() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, SET);
}
void reset() {
	off();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);
	show_0();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
	show_0();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);
	show_0();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, RESET);
	show_0();
}

typedef void (*func_ptr)();
func_ptr functionArray[10] = { show_0, show_1, show_2, show_3, show_4, show_5,
		show_6, show_7, show_8, show_9 };


typedef unsigned char byte;
RTC_TimeTypeDef nowTime;
RTC_DateTypeDef nowDate;
typedef enum {
    APP_STATE_NOTE,
    APP_STATE_CONTACT
} AppState_t;

AppState_t currentAppState = APP_STATE_CONTACT;

//byte circle[] = { 0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E };
//byte heart[] = { 0x0C, 0x1E, 0x1F, 0x0F, 0x1F, 0x1F, 0x1E, 0x0C };
//byte square[] = { 0x00, 0x00, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x00 };
//byte padle[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
byte Human[8] = { 0x0E,0x0A, 0x0E, 0x04, 0x1F, 0x04,0x0A, 0x11};
byte P_Z[8] = {0x1C, 0x14, 0x1C, 0x10, 0x17, 0x02, 0x04, 0x07};
byte Contact[8] = {0x0E, 0x1F, 0x1F, 0x0E, 0x0E, 0x0E, 0x1F, 0x1F};
byte Notes[8] = {0x1F, 0x11, 0x11, 0x11, 0x11, 0x12, 0x14, 0x18};
byte Music[8] = {0x07, 0x04, 0x04, 0x04, 0x04, 0x1C, 0x1C, 0x1C};
byte Settings[8] = {0x0E, 0x0A, 0x11, 0x15, 0x11, 0x0A, 0x0E, 0x00};
byte Info[8] = {0x1F, 0x11, 0x15, 0x11, 0x15, 0x15, 0x11, 0x1F};
byte Plant_1 [8] = { 0x00, 0x00, 0x1D, 0x1F, 0x1D, 0x08, 0x08, 0x08 };
byte Plant_2 [8] = { 0x00, 0x00, 0x0C, 0x1F, 0x1E, 0x0C, 0x0C, 0x0C };
byte Shield [8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F  };
byte Heart[8] = { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 };



//typedef struct {
//	uint16_t freq;
//	uint16_t dur;
//} Note;

// super mario

Note melody2[] = { { 660, 100 }, { 660, 100 }, { 0, 100 }, { 660, 100 }, { 0,
		100 }, { 523, 100 }, { 660, 100 }, { 0, 100 }, { 784, 100 }, { 0, 300 },
		{ 392, 100 }, { 0, 300 }, { 523, 100 }, { 0, 100 }, { 392, 100 }, { 0,
				100 }, { 330, 100 }, { 0, 200 }, { 440, 100 }, { 0, 100 }, {
				494, 100 }, { 466, 100 }, { 440, 100 }, { 392, 100 },
		{ 660, 100 }, { 784, 100 }, { 880, 100 }, { 698, 100 }, { 784, 100 }, {
				660, 100 }, { 523, 100 }, { 587, 100 }, { 494, 100 } };


typedef struct
{
    const Note *song;

    uint16_t length;
    uint16_t currentNote;

    uint32_t noteStartTime;

    uint8_t playing;

} MusicPlayer;

MusicPlayer music;

typedef struct
{
    uint8_t row;
    uint8_t col;
    uint8_t hp;
    uint8_t alive;

}Zombie;

Zombie zombies[MAX_ZOMBIES];

typedef enum
{
    PLANT_DAY,
    PLANT_NIGHT

} PlantType;

typedef struct
{
    uint8_t row;
    uint8_t col;
    uint8_t hp;
    uint8_t alive;
    uint8_t reload;

    PlantType type;

}Plant;
Plant plants[MAX_PLANTS];




typedef struct
{
    uint8_t row;
    uint8_t col;

} Bullet;
Bullet bullets[MAX_BULLETS];

typedef enum
{
    EMPTY,
    PLANT,
    ZOMBIE,
    BULLET,
	HEART,
	BLOCK ,
	NUMBER,
	PLUS
}ObjectType;

typedef struct
{
    ObjectType type;
    uint8_t timer;
    int8_t index;

}Cell;

Cell map[4][17];
Cell map_2[4][3];

typedef struct
{
    uint8_t plantDamage;

    uint32_t zombieSpeed;

    uint32_t zombieSpawnRate;

    uint8_t plantCount;

    uint8_t dayPlantCount;

    uint8_t nightPlantCount;

}GameSetting;

GameSetting gameSetting;
uint16_t nextPlantRewardScore = 10;
PlantType selectedPlantType = PLANT_DAY;

void Game_BackgroundMusic_Update(void);

typedef enum
{
    DAY,
    NIGHT

} GameTime;

typedef struct
{
    uint16_t score;

    uint8_t life;

    uint8_t cursorRow;

    uint8_t cursorCol;

    uint32_t tick;

    uint8_t gameOver;

    uint8_t plantsPlaced;

    GameTime time;

}GameItems ;

GameItems game;


volatile KeyType pressedKey = KEY_NONE;

volatile ContactKeyType contactPressedKey = CT_KEY_NONE;
typedef enum
{
    STATE_MENU,
    STATE_GAME,
    STATE_SETTING,
	STATE_GAMEOVER

}GameState;
GameState gameState = STATE_MENU;

typedef enum
{
    APP_LOGO,
    APP_MENU,
    APP_GAME,
    APP_CONTACT,
    APP_NOTE,
    APP_MUSIC_PLAYER,
    APP_SETTING,
    APP_INFO

} AppState;

AppState appState = APP_MENU;



int music_once = 0;
//int BLOCK_ROWS =  4 ;
//int BLOCK_COLS = 6 ;
int blocks[BLOCK_ROWS][BLOCK_COLS];
int elements_num = 1 ;

int paddle_x = 0;
int paddle_flag = 3;
int PADDLE_WIDTH = 1;
int change_paddle = 1 ; // 1 = keypad  2 = potensiometr

int ballX = 12;
int ballY = 2;
int ballDX = 1;
int ballDY = 1;
int ball_num = 1 ;

int menu_flag = 3;
int ok_flag = 3;
int setting_flag = 3;
int stop_flag = 3 ;
int end_flag = 3 ;
int end_key = 1 ;


char gameMap[4][20];
int menu_mode = 0;
int mode = 0;

int clear_menu = 0;

char menuItems[5][10] = { "Plant", "Contact", "Notes", "Music", "Info" };

struct Ball {
	int x, y;
	int dx, dy;
};

struct Ball ball;


void Logo(){
	setCursor(6, 1);
	print("NOKIA");
	switch(pressedKey)
	case KEY_SELECT:
		appState = APP_MENU;
}





uint8_t menuIndex = 0;
int show_menu = 0 ;
void Main_Menu() {
	const uint8_t menuCol[] = {2, 5, 8, 11, 14, 17};
	const uint8_t menuIcons[] = {2, 3, 5, 7, 8, 9};


	if (!show_menu) {
		clear();
		show_menu = 1 ;
	}
	for(uint8_t i = 0; i < 6; i++)
	{
	    setCursor(menuCol[i], 1);
	    write(menuIcons[i]);
	}
	switch(pressedKey)
	{
	case KEY_LEFT:

	    if(menuIndex > 0)
	        menuIndex--;

	    break;

	case KEY_RIGHT:

	    if(menuIndex < 5)
	        menuIndex++;

	    break;

//	 case KEY_7:
//		    	appState = APP_MENU;
//		 break ;

	case KEY_SELECT:

	    switch(menuIndex)
	    {
	        case 0:
	        	appState = APP_GAME;

	            break;

	        case 1:
	        	appState = APP_CONTACT;

	            break;

	        case 2:
	        	  appState = APP_NOTE;

	            break;

	        case 3:
	        	 appState = APP_MUSIC_PLAYER;
	        	 music_once = 1;
	            break;

	        case 4:
	            appState = APP_SETTING;
	            break;
	        case 5:
	            appState = APP_INFO;
	            break;
	    }



	    break;
	}
	setCursor(menuCol[menuIndex], 1);
	cursor();
//	blink();
	HAL_Delay(500);



}



int Info_once = 0 ;
void User_Info(void) {
	if (!Info_once){
    clear();
	Info_once = 1 ;
	}
    setCursor(0, 0);
    print("1: Frazaneh Haasnzade");
    setCursor(0, 1);
    print("ID: 4011262554");

    setCursor(0, 2);
    print("2: Marziye esfahani");

    setCursor(0, 3);
    print("ID: 4011262049");
}



int showC_once = 0 ;
void Contact_all(){
	if(!showC_once){
	  Contact_DrawList();
		showC_once = 1 ;
	}
	 Contact_Task();
}
int showN_once = 0 ;

void Note_all(){
	if(!showN_once){
		Note_DrawList();
		showN_once = 1 ;
	}
	 Note_Task();
}




char dayPlant_num;
void First(){
	char ch;
	uint8_t sum = 0;
	char buf[20];
	sprintf(buf, "ch=%d\r\n", ch);


	do {
		HAL_UART_Transmit(&huart1, (uint8_t*)"choose plantCount:\r\n", strlen("choose plantCount:\r\n"), HAL_MAX_DELAY);
		HAL_UART_Receive(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", strlen("\r\n"), HAL_MAX_DELAY);
		gameSetting.plantCount = ch - '0' ;


		HAL_UART_Transmit(&huart1, (uint8_t*)"choose 4 plants\r\n", strlen("choose 4 plants\r\n"), HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)"Day Plant: ", strlen("Day Plant: "), HAL_MAX_DELAY);

		HAL_UART_Receive(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", strlen("\r\n"), HAL_MAX_DELAY);
		gameSetting.dayPlantCount = (ch >= '0' && ch <= '4') ? (ch - '0') : 0;

		HAL_UART_Transmit(&huart1, (uint8_t*)"Night Plant: ", strlen("Night Plant: "), HAL_MAX_DELAY);
		HAL_UART_Receive(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);

		HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", strlen("\r\n"), HAL_MAX_DELAY);
		gameSetting.nightPlantCount = (ch >= '0' && ch <= '4') ? (ch - '0') : 0;

		sum = gameSetting.dayPlantCount + gameSetting.nightPlantCount;
		if(sum != gameSetting.plantCount  ) {
			HAL_UART_Transmit(&huart1, (uint8_t*)"choose again\r\n", strlen("choose again\r\n"), HAL_MAX_DELAY);
		}
	} while(sum != gameSetting.plantCount );

	selectedPlantType = (gameSetting.dayPlantCount > 0) ? PLANT_DAY : PLANT_NIGHT;
	HAL_UART_Transmit(&huart1, (uint8_t*)"ok\r\n", strlen("ok\r\n"), HAL_MAX_DELAY);
}

void Game_Init(void){
    uint8_t row, col;

    for(row = 0; row < 4 ; row++)
    {
        for(col = 0; col < MAP_WIDTH ; col++)
        {
            map[row][col].type  = EMPTY;
            map[row][col].timer = 0;
            map[row][col].index = -1;
        }
    }

    for(int i = 0; i < MAX_ZOMBIES; i++)
    {
        zombies[i].alive = 0;
        zombies[i].hp = 0;
        zombies[i].row = 0;
        zombies[i].col = 0;
    }
    for(uint8_t i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].row = BULLET_INVALID_ROW;
        bullets[i].col = 0;
    }
    for(uint8_t i = 0; i < MAX_PLANTS; i++)
    {
        plants[i].alive = 0;
        plants[i].hp = 0;
        plants[i].row = 0;
        plants[i].col = 0;
        plants[i].reload = 0;
        plants[i].type = PLANT_DAY;
    }
    for (row = 0 ; row < 4 ; row ++){
    	for (col = 0 ; col < 2 ; col ++){
    		switch (row){
    		case 0 :
    			map_2[row][col].type = HEART ;
    			break ;
    		case 1 :
    			map_2[row][col].type = NUMBER ;
    			break ;
    		case 2 :
    			map_2[row][col].type = PLANT ;
    			break ;
    		case 3 :
    			map_2[row][col].type = PLUS ;
    			break ;
    		}

    	}
    	map_2[row][2].type = BLOCK ;
    }

    game.score = 0;

    game.life = 2;

    game.cursorRow = 0;
    game.cursorCol = 0;

    game.tick = 0;

    game.gameOver = 0;
    game.plantsPlaced = 0;
    nextPlantRewardScore = 10;
}

void DrawHUD(void)
{
    uint8_t row, col;

      for(row = 0; row < 4 ; row++)
      {
          setCursor(0, row);

          for(col = 0; col < 3 ; col++)
          {
          	setCursor(col, row);
              switch(map_2[row][col].type)
              {
                  case EMPTY:
                      print(" ");
                      break;

                  case HEART :
                      write(5);
                      break;

                  case BLOCK:
                      write(CHAR_S);
                      break;
                  case PLANT:

                	  if (col == 0) {
                      		write(4);
                	  }
                	  else {
                	     	write(6);}
                      break;

                  case PLUS:
                      print("+");
                      break;

                  case NUMBER:
                	  if(col == 0){
                		  write(gameSetting.dayPlantCount + '0');
                	  }
                	  else {
                		  write(gameSetting.nightPlantCount + '0');
                	  }
                      break;

                  default:
                      print("?");
                      break;
              }
          }
      }


}
int updateHub = 0 ;
void Game_Draw(void){
    uint8_t row, col;

    for(row = 0; row < 4 ; row++)
    {
        setCursor(0, row);

        for(col = 0; col < 17 ; col++)
        {
        	uint8_t idx = map[row][col].index;
        	setCursor(col+3, row);
            switch(map[row][col].type)
            {
                case EMPTY:
                    print(" ");
                    break;

                case PLANT:

                	if (plants[idx].type == PLANT_DAY) {
                		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
                		write(4);
                	}
                	if(plants[idx].type == PLANT_NIGHT) {
                		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
                		write(6);

                	}
                    break;

                case ZOMBIE:
                    write(CHAR_HUMAN);
                    break;

                case BULLET:
                    print(".");
                    break;

                default:
                    print("?");
                    break;
            }
        }
    }
    if(updateHub){
    	map_2[0][1].type = EMPTY ;
    	DrawHUD();
    	updateHub = 0 ;
    }
}


static uint8_t Plant_Type_Available(PlantType type)
{
    if(type == PLANT_DAY)
        return gameSetting.dayPlantCount > 0;

    return gameSetting.nightPlantCount > 0;
}

static void Plant_Select_Available_Type(void)
{
    if(!Plant_Type_Available(selectedPlantType))
    {
        if(gameSetting.dayPlantCount > 0)
            selectedPlantType = PLANT_DAY;
        else if(gameSetting.nightPlantCount > 0)
            selectedPlantType = PLANT_NIGHT;
    }
}

static void Plant_Draw_Selected_Type(void)
{
    setCursor(0, 3);
    print("S:");
    write(selectedPlantType == PLANT_DAY ? CHAR_P1 : CHAR_P2);
}

static void Plant_Decrease_Selected_Count(void)
{
    if(selectedPlantType == PLANT_DAY && gameSetting.dayPlantCount > 0)
        gameSetting.dayPlantCount--;
    else if(selectedPlantType == PLANT_NIGHT && gameSetting.nightPlantCount > 0)
        gameSetting.nightPlantCount--;
}

void Plant_Select(void)
{

    game.cursorRow = 0;
    game.cursorCol = 0;

    Plant_Select_Available_Type();
    Game_Draw();
    DrawHUD();
    Plant_Draw_Selected_Type();
    cursor();
    blink();

    setCursor(game.cursorCol +3, game.cursorRow);

    while(game.plantsPlaced < gameSetting.plantCount)
    {
        Game_BackgroundMusic_Update();

        switch(pressedKey)
        {
            case KEY_UP:

                if(game.cursorRow > 0)
                    game.cursorRow--;

                pressedKey = KEY_NONE;
                break;

            case KEY_DOWN:

                if(game.cursorRow < 4 - 1)
                    game.cursorRow++;

                pressedKey = KEY_NONE;
                break;

            case KEY_LEFT:

                if(game.cursorCol > 0)
                    game.cursorCol--;

                pressedKey = KEY_NONE;
                break;

            case KEY_RIGHT:

                if(game.cursorCol < MAP_WIDTH - 1)
                    game.cursorCol++;

                pressedKey = KEY_NONE;
                break;

            case KEY_7:

                if(gameSetting.dayPlantCount > 0)
                    selectedPlantType = PLANT_DAY;

                Plant_Draw_Selected_Type();
                pressedKey = KEY_NONE;
                break;

            case KEY_8:

                if(gameSetting.nightPlantCount > 0)
                    selectedPlantType = PLANT_NIGHT;

                Plant_Draw_Selected_Type();
                pressedKey = KEY_NONE;
                break;

            case KEY_SELECT:

                if(map[game.cursorRow][game.cursorCol].type == EMPTY &&
                   game.plantsPlaced < MAX_PLANTS &&
                   Plant_Type_Available(selectedPlantType))
                {
                    map[game.cursorRow][game.cursorCol].type = PLANT;
                    map[game.cursorRow][game.cursorCol].timer = 0;

                	plants[game.plantsPlaced].alive = 1;
                	plants[game.plantsPlaced].row = game.cursorRow;
                	plants[game.plantsPlaced].col = game.cursorCol;
                	plants[game.plantsPlaced].hp = 3;
                	plants[game.plantsPlaced].reload = 1;
                	map[game.cursorRow][game.cursorCol].index = game.plantsPlaced;

                	plants[game.plantsPlaced].type = selectedPlantType;
                	Plant_Decrease_Selected_Count();
                    Game_Draw();
                    DrawHUD();
                    game.plantsPlaced++;
                    Plant_Select_Available_Type();
                    Plant_Draw_Selected_Type();
                }

                pressedKey = KEY_NONE;
                break;

            default:
                break;
        }

        setCursor(game.cursorCol+3, game.cursorRow);
    }

    noBlink();
    noCursor();
}

void Zombie_Spawn(void)
{
    static uint32_t lastSpawnTime = 0;

    if(HAL_GetTick() - lastSpawnTime < gameSetting.zombieSpawnRate)
        return;

    lastSpawnTime = HAL_GetTick();

    uint8_t startRow;
    uint8_t row;
    uint8_t slot = MAX_ZOMBIES;

    for(uint8_t i = 0; i < MAX_ZOMBIES; i++)
    {
        if(zombies[i].alive == 0)
        {
            slot = i;
            break;
        }
    }

    if(slot == MAX_ZOMBIES)
        return;

    startRow = rand() % MAP_HEIGHT;

    for(uint8_t i = 0; i < MAP_HEIGHT; i++)
    {
        row = (startRow + i) % MAP_HEIGHT;

        if(map[row][MAP_WIDTH - 1].type == EMPTY)
        {
            zombies[slot].alive = 1;
            zombies[slot].row = row;
            zombies[slot].col = MAP_WIDTH - 1;
            zombies[slot].hp = 1;

            map[row][MAP_WIDTH - 1].type = ZOMBIE;

            return;
        }
    }
}

void MoveSingleZombie(uint8_t index)
{
    uint8_t row = zombies[index].row;
    uint8_t col = zombies[index].col;
    uint8_t maxPlant = gameSetting.plantCount;
    if(maxPlant > MAX_PLANTS)
        maxPlant = MAX_PLANTS;

    if(col == 0)
    {
    	if(game.life > 0)
    	        game.life--;
//    			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
    			updateHub = 1 ;


    	    zombies[index].alive = 0;
    	    map[row][col].type = EMPTY;

    	    if(game.life == 0)
    	    {
    	        game.gameOver = 1;
//    	        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
    	    }
    	    return;
    }

    switch(map[row][col - 1].type)
    {
        case EMPTY:
            map[row][col].type = EMPTY;

            zombies[index].col--;

            map[row][zombies[index].col].type = ZOMBIE;


            break;

        case PLANT:

            for(uint8_t i = 0; i < maxPlant; i++)
            {
                if(plants[i].alive &&
                   plants[i].row == row &&
                   plants[i].col == (col - 1))
                {
                    if(plants[i].hp > 0)
                        plants[i].hp--;
//                        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);

                    if(plants[i].hp == 0)
	                    {
	                        plants[i].alive = 0;
	                        map[row][col - 1].type = EMPTY;
	                        map[row][col - 1].index = -1;
//                        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
	                    }

                    break;

                }

            break;
            }

        default:

            break;
     }

}

void Zombie_Move(void)
{
    static uint32_t lastMoveTime = 0;

    if(HAL_GetTick() - lastMoveTime < gameSetting.zombieSpeed)
        return;

    lastMoveTime = HAL_GetTick();

    for(uint8_t i = 0; i < MAX_ZOMBIES; i++)
    {
        if(zombies[i].alive)
        {
            MoveSingleZombie(i);
        }
    }
}

void Plant_Attack(void)
{
//	gameSetting.plantCount = 2;
    uint8_t maxPlant = gameSetting.plantCount ;

    if(maxPlant > MAX_PLANTS)
        maxPlant = MAX_PLANTS;

    for(uint8_t i = 0; i < maxPlant; i++)
    {
//        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
//    	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14,SET);
        if(!plants[i].alive)
            continue;

        if(game.time == DAY && plants[i].type != PLANT_DAY)
               continue;

           if(game.time == NIGHT && plants[i].type != PLANT_NIGHT)
               continue;

        if(plants[i].reload > 0)
        {
//        	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9,SET);
            plants[i].reload--;
            continue;
        }

        uint8_t zombieFound = 0;

        for(uint8_t j = 0; j < MAX_ZOMBIES; j++)
        {

            if(zombies[j].alive==1 &&
               zombies[j].row == plants[i].row
              )
            {
                zombieFound = 1;
//                HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13,SET);
                break;
            }
        }

	        if(!zombieFound)
	            continue;

	        if(plants[i].col >= MAP_WIDTH - 1)
	            continue;

	        for(uint8_t j = 0; j < MAX_BULLETS; j++)
        {
//             HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_15);
             HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15,SET);
            if(bullets[j].row == BULLET_INVALID_ROW)
            {
                bullets[j].row = plants[i].row;
                bullets[j].col = plants[i].col + 1;

                plants[i].reload = SHOOT_DELAY;
                map[bullets[j].row][bullets[j].col].type = BULLET;
                break;
            }
        }
    }
}

void Bullet_Move(void)
{
    for(uint8_t i = 0; i < MAX_BULLETS; i++)
    {
        if(bullets[i].row == BULLET_INVALID_ROW)
            continue;

        uint8_t row = bullets[i].row;
        uint8_t col = bullets[i].col;

	        if(col >= MAP_WIDTH - 1)
	        {
            map[row][col].type = EMPTY;

            bullets[i].row = BULLET_INVALID_ROW;
            bullets[i].col = 0;

            continue;
        }

        switch(map[row][col + 1].type)
        {
            case EMPTY:

                map[row][col].type = EMPTY;

                bullets[i].col++;

                map[row][bullets[i].col].type = BULLET;

                break;

            case ZOMBIE:

                for(uint8_t j = 0; j < MAX_ZOMBIES; j++)
                {
                    if(zombies[j].alive &&
                       zombies[j].row == row &&
                       zombies[j].col == col + 1)
                    {
                        if(zombies[j].hp > 0)
                            zombies[j].hp--;

                        if(zombies[j].hp == 0)
                        {
                            zombies[j].alive = 0;
                            map[row][col + 1].type = EMPTY;
                            game.score++;
                        }

                        break;
                    }
                }

                map[row][col].type = EMPTY;

                bullets[i].row = BULLET_INVALID_ROW;
                bullets[i].col = 0;

                break;

            default:
                break;
        }
    }
}

uint32_t last_ldr = 0;
uint32_t ldr_value;
void Read_LDR() {
	char ldr_buffer[10];
	if (HAL_GetTick() - last_ldr > 1000) {
		HAL_ADC_Start(&hadc2);
		HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
		ldr_value = HAL_ADC_GetValue(&hadc2);
		if (ldr_value > 2000) {
			game.time = DAY ;
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);

		} else {
			game.time = NIGHT ;
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
		}
//		sprintf(ldr_buffer, "%d", ldr_value);
		last_ldr = HAL_GetTick();
	}
}

static void Game_BackgroundMusic_SetTone(uint16_t freq)
{
    uint32_t arr;

    if(freq == 0)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
        return;
    }

    arr = (1000000U / freq) - 1U;
    __HAL_TIM_SET_AUTORELOAD(&htim3, arr);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, (arr + 1U) / 2U);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

void Game_BackgroundMusic_Start(const Note *song, uint16_t length)
{
    if(song == NULL || length == 0)
        return;

    music.song = song;
    music.length = length;
    music.currentNote = 0;
    music.noteStartTime = HAL_GetTick();
    music.playing = 1;

    Game_BackgroundMusic_SetTone(song[0].freq);
}

void Game_BackgroundMusic_Update(void)
{
    uint32_t now;
    const Note *currentNote;

    if(!music.playing || music.song == NULL || music.length == 0)
        return;

    now = HAL_GetTick();
    currentNote = &music.song[music.currentNote];

    if(now - music.noteStartTime < currentNote->dur)
        return;

    music.currentNote++;
    if(music.currentNote >= music.length)
        music.currentNote = 0;

    music.noteStartTime = now;
    Game_BackgroundMusic_SetTone(music.song[music.currentNote].freq);
}

void Game_BackgroundMusic_Stop(void)
{
    music.playing = 0;
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
}

static void Game_CheckPlantReward(void)
{
    while(game.score >= nextPlantRewardScore && gameSetting.plantCount < MAX_PLANTS)
    {
        gameSetting.plantCount++;

        if(game.time == DAY)
            gameSetting.dayPlantCount++;
        else
            gameSetting.nightPlantCount++;

        nextPlantRewardScore += 10;
        DrawHUD();
        Plant_Select();
    }
}


void Game_Run(void)
{
	if(game.gameOver)
	{
		Game_BackgroundMusic_Stop();
	    gameState = STATE_GAMEOVER;
	    return;
	}

	Game_BackgroundMusic_Update();
	Read_LDR();
	Game_CheckPlantReward();

	if (gameSetting.plantCount == game.plantsPlaced){


				Zombie_Spawn();

				Zombie_Move();

				Plant_Attack();

				Bullet_Move();

//				Read_LDR();

				Show_health();

				Game_Draw();

				Game_BackgroundMusic_Update();



				}

}
int clear_page = 0 ;
void GameOver(void)
{
	if (!clear_page){
		clear();
		clear_page = 1 ;
	}


    setCursor(5,1);
    print("GAME OVER");

    setCursor(4,2);
    print("Score:");
    char str[10];

    sprintf(str, "%d", game.score);

    print(str);



    if(pressedKey == KEY_SELECT)
    {
        gameState = STATE_MENU;

        pressedKey = KEY_NONE;
    }

}

void Game_Setting(void){
	char ch;
	uint8_t sum = 0;
	char buf[20];
	sprintf(buf, "ch=%d\r\n", ch);

		HAL_UART_Transmit(&huart1, (uint8_t*)"plantDamage: 1/2/3\r\n", strlen("plantDamage: 1/2/3\r\n"), HAL_MAX_DELAY);
		HAL_UART_Receive(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", strlen("\r\n"), HAL_MAX_DELAY);
		gameSetting.plantDamage =  (ch - '0') ;

		HAL_UART_Transmit(&huart1, (uint8_t*)"zombieSpeed: 1/2", strlen("zombieSpeed: 1/2"), HAL_MAX_DELAY);
		HAL_UART_Receive(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);

		HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", strlen("\r\n"), HAL_MAX_DELAY);
		gameSetting.zombieSpeed = ch - '0';

		HAL_UART_Transmit(&huart1, (uint8_t*)"plantCount: ", strlen("plantCount: "), HAL_MAX_DELAY);
		HAL_UART_Receive(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);

		HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 2, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", strlen("\r\n"), HAL_MAX_DELAY);
		gameSetting.plantCount = ch - '0';

}

uint8_t menuInitialized = 0;
int first_menu = 0 ;
void Game_Menu(void)
{
    static uint8_t menuIndex = 0;


    if (!first_menu){
    	clear();
    	first_menu = 1 ;
    }
    if (!show_menu){
    	clear();
    	show_menu = 1 ;
    }


    setCursor(0,0);
    print("New Game");

    setCursor(0,1);
    print("Continue");

    setCursor(0,2);
    print("Setting");

    setCursor(9, menuIndex);
    print("<");


//
//    }

    switch(pressedKey)
    {
        case KEY_UP:
            if(menuIndex > 0)

                menuIndex--;

            break;

        case KEY_DOWN:
            if(menuIndex < 3)
//
                menuIndex++;

            break;

        case KEY_SELECT:
            switch(menuIndex)
            {
                case 0:
                	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
//
                	  gameState = STATE_GAME;
                    break;

                case 1:
                    // Continue
                	gameState = STATE_GAME;
                	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_15);
                    break;

                case 2:

                    // Setting
                	gameState = STATE_SETTING ;
                	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
                    break;
            }
            break;

        default:
            break;
    }

}


uint32_t read_pot() {
    HAL_ADC_Start(&hadc3);
    HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(&hadc3);
}

int map_adc_to_paddle(uint32_t adc_value) {
    return (adc_value * 4) / 4096;
}

void update_potansiometr() {
    static int last_paddle_x = -1;

    uint32_t adc_val = read_pot();
    int new_paddle_x = map_adc_to_paddle(adc_val);

    if (new_paddle_x != last_paddle_x) {

        if (last_paddle_x >= 0 && last_paddle_x <= 3) {
            setCursor(17, last_paddle_x);
            print(" ");
        }


        paddle_x = new_paddle_x;
        setCursor(17, paddle_x);
//        write(CHAR_PADDLE);

        last_paddle_x = new_paddle_x;
    }
}




void Show_health() {
	off();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);
	functionArray[0]();
	HAL_Delay(2);

	off();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);
	functionArray[game.time]();
	HAL_Delay(2);

	off();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);
	functionArray[game.score / 10]();
	HAL_Delay(2);

	off();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, SET);
	functionArray[game.score % 10]();
	HAL_Delay(2);
//		off();

}



// Note melody_zombie_ambient[] = {{185, 1200}, {0, 400}, {165, 1400}, {0, 300}, {175, 1000}, {0, 500}, {155, 1600}, {0, 600}, {196, 800}, {0, 350}, {185, 1100}, {0, 450}, {165, 1500}, {0, 500}, {175, 900}, {0, 400}, {0, 0}};
//*******************************************************************************************
byte next_song[8] = {0x11, 0x19, 0x1D, 0x1F, 0x1F, 0x1D, 0x19, 0x11};
byte previous_song[8] = {0x11, 0x13, 0x17, 0x1F, 0x1F, 0x17, 0x13, 0x11};
byte song[8] = {0x18, 0x1C, 0x1E, 0x1F, 0x1E, 0x1C, 0x18, 0x10};
byte Speaker[8] = {0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01};

typedef enum {
    SPRITE_HUMAN = 0,
    SPRITE_PLANT = 1,
    SPRITE_CONTACT = 2,
    SPRITE_P1 = 3,
    SPRITE_NOTES = 4,
    SPRITE_INFO = 5,
    SPRITE_MUSIC = 6,
    SPRITE_SETTINGS = 7,
    SPRITE_PREVIOUS = 8,
    SPRITE_NEXT = 9,
    SPRITE_SONG = 10,
    SPRITE_SHIELD = 11,
    SPRITE_SPEAKER = 12
} SpriteID_t;


uint16_t volumeValue = 0;


void change_volum(){
	 setCursor(0, 3);
		 write(SPRITE_PLANT);

	if (pressedKey == KEY_UP)
	{
		setCursor(1, 3);
		 write(CHAR_S);
		 setCursor(2, 3);
		 print(" ");
		 if (volumeValue == 0){
			 volumeValue =250;

				setCursor(1, 3);
				print(" ");
				setCursor(2, 3);
				print(" ");
					 }
				 else if (volumeValue ==250)
					 {
					 volumeValue =500;
					 setCursor(1, 3);
					 write(CHAR_S);
					 setCursor(2, 3);
					 print(" ");

					 }

}
	else if (pressedKey == KEY_DOWN )

		 if (volumeValue == 500)
			 {
			 volumeValue =250;
             setCursor(1, 3);
            write(CHAR_S);
            setCursor(2, 3);
            print(" ");			 }
		 else if (volumeValue ==250)
			 {
			 volumeValue =0;
			 setCursor(1, 3);
			 print(" ");
			 setCursor(2, 3);
			 print(" ");
			 }


}
void buzzer_play_tone(uint16_t freq, uint16_t duration_ms) {
    uint32_t ccr_value = (volumeValue * freq) / 1000;

    if (volumeValue == 0) {
        HAL_Delay(duration_ms);
        return;
    }

    __HAL_TIM_SET_AUTORELOAD(&htim3, (1000000 / freq) - 1);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, ccr_value);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_Delay(duration_ms);
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
}


void LoadSprite(SpriteID_t id, const uint8_t *data) {
    if (id <= 7) {
        createChar(id, (uint8_t*)data);
    }
}

void DrawSprite(SpriteID_t id) {
    if (id <= 7) {
        write(id);
    }
}

// آ1: (Like a lullaby)
Note melody_simple[] = {
    { 262, 300 }, { 0, 50 }, { 294, 300 }, { 0, 50 }, { 330, 300 }, { 0, 50 },
    { 349, 300 }, { 0, 50 }, { 392, 300 }, { 0, 50 }, { 440, 300 }, { 0, 50 },
    { 494, 300 }, { 0, 50 }, { 523, 400 }, { 0, 100 }
};

//2:  (Happy tune)
Note melody_upbeat[] = {
    { 523, 150 }, { 0, 30 }, { 587, 150 }, { 0, 30 }, { 659, 150 }, { 0, 30 },
    { 784, 150 }, { 0, 30 }, { 659, 150 }, { 0, 30 }, { 587, 150 }, { 0, 30 },
    { 523, 150 }, { 0, 30 }, { 494, 150 }, { 0, 30 }, { 440, 150 }, { 0, 30 },
    { 494, 150 }, { 0, 30 }, { 523, 200 }, { 0, 50 }
};

// 3 : (Sad melody)
Note melody_error[] = {
    { 392, 400 }, { 0, 50 }, { 349, 400 }, { 0, 50 }, { 330, 400 }, { 0, 50 },
    { 294, 400 }, { 0, 50 }, { 330, 400 }, { 0, 50 }, { 349, 400 }, { 0, 50 },
    { 392, 400 }, { 0, 50 }, { 440, 400 }, { 0, 50 }, { 392, 300 }, { 0, 100 }
};

//4 : (Fast melody)
Note melody_message[] = {
    { 659, 100 }, { 0, 20 }, { 784, 100 }, { 0, 20 }, { 880, 100 }, { 0, 20 },
    { 988, 100 }, { 0, 20 }, { 880, 100 }, { 0, 20 }, { 784, 100 }, { 0, 20 },
    { 659, 100 }, { 0, 20 }, { 587, 100 }, { 0, 20 }, { 523, 100 }, { 0, 20 },
    { 587, 100 }, { 0, 20 }, { 659, 100 }, { 0, 20 }, { 784, 100 }, { 0, 20 },
    { 880, 100 }, { 0, 20 }, { 988, 150 }, { 0, 50 }
};

void Music_Player(void) {
    clear();


    LoadSprite(SPRITE_HUMAN, previous_song);
    LoadSprite(SPRITE_PLANT, next_song);
    LoadSprite(SPRITE_CONTACT, song);
    LoadSprite(SPRITE_SPEAKER, Speaker);
    const char *song_names[4] = {
        "Simple",      // 1
        "Upbeat",      // 2
        "Error",       // 3
        "Message"      // 4
    };


    Note *melodies[4] = { melody_simple, melody_upbeat, melody_error, melody_message };
    uint16_t melody_lengths[4] = {
        SONG_LENGTH(melody_simple),
        SONG_LENGTH(melody_upbeat),
        SONG_LENGTH(melody_error),
        SONG_LENGTH(melody_message)
    };

    uint32_t start_time;
    uint32_t last_progress_update;

    for (uint8_t i = 0; i < 4; i++) {
        char display[20];
        sprintf(display, "Song %d:", i+1);
        setCursor(0, 0);
        print(display);
        setCursor(8, 0);
        print(song_names[i]);

        setCursor(5, 1);
        write(SPRITE_HUMAN);
        setCursor(8, 1);
        write(SPRITE_CONTACT);
        setCursor(12, 1);
        write(SPRITE_PLANT);

        setCursor(6, 2);
        print("        ");
        setCursor(6, 2);
        write(CHAR_S);




        start_time = HAL_GetTick();
        last_progress_update = start_time;
        uint8_t progress_count = 1;
        uint16_t note_index = 0;

        while ((HAL_GetTick() - start_time) < 10000) {

            if (melodies[i][note_index].freq == 0) {
                HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
                HAL_Delay(melodies[i][note_index].dur);
            } else {
                buzzer_play_tone(melodies[i][note_index].freq, melodies[i][note_index].dur);
            }

            note_index++;
            if (note_index >= melody_lengths[i]) {
                note_index = 0;
            }

            if ((HAL_GetTick() - last_progress_update) >= 5000 && progress_count < 8) {
                last_progress_update = HAL_GetTick();
                setCursor(6 + progress_count, 2);
                write(CHAR_S);
                progress_count++;
            }
        }
        HAL_Delay(300);
    }

    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
    setCursor(0, 0);
    print("Finished!     ");
    setCursor(6, 2);
    print("        ");
}



volatile uint32_t keyPressTime = 0;
volatile uint32_t lastKeyTime = 0;
volatile uint8_t selectPressed = 0;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//	 HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);


	 if (GPIO_Pin == GPIO_PIN_0) {
	 			if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0) == GPIO_PIN_SET) {
//	 				HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
	 				pressedKey = KEY_RIGHT;
	 				contactPressedKey = CT_KEY_RIGHT;
	 				 					}
	 			}
	 if (GPIO_Pin == GPIO_PIN_1) {
			if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == GPIO_PIN_SET) {
				pressedKey = KEY_LEFT;
				contactPressedKey = CT_KEY_LEFT;
					 				}
	 	 	 }



	 if (GPIO_Pin == GPIO_PIN_2) {
	 			if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == GPIO_PIN_SET) {
//	 				HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
	 				 pressedKey = KEY_UP;
	 				contactPressedKey = CT_KEY_UP;
	 				}
	 			}
	 if (GPIO_Pin == GPIO_PIN_3) {
	 			if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == GPIO_PIN_SET) {
//	 				HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
	 				pressedKey = KEY_DOWN;
	 				contactPressedKey = CT_KEY_DOWN;
	 				}
	 			}
	 if (GPIO_Pin == GPIO_PIN_4) {
	 			if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == GPIO_PIN_SET) {
	 				HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
	 				pressedKey = KEY_SELECT ;
	 			   contactPressedKey = CT_KEY_SELECT;

	 			    if (appState == APP_GAME && gameState == STATE_MENU){
	 			 	        		 	show_menu = 0 ;
	 			 	        	 }
	 				}
	 			}
	 else if (GPIO_Pin == GPIO_PIN_5) {
	         if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == GPIO_PIN_SET) {
	        	 pressedKey = KEY_7;
	        	 if (appState != APP_GAME){
	        		 	appState = APP_MENU;
	        		 	show_menu = 0 ;
	        	 }
	        	 if (appState == APP_GAME && gameState == STATE_MENU){
	        		 	appState = APP_MENU;
	        		 	show_menu = 0 ;
	        	 }
	        	 HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
	         }
	     }
	     else if (GPIO_Pin == GPIO_PIN_6) {
	         if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6) == GPIO_PIN_SET) {
	        	 pressedKey = KEY_8;
	        	 HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
	         }
	     }

	}








/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();
  MX_TIM3_Init();
  MX_ADC3_Init();
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */

	LiquidCrystal(GPIOD, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10,
	GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);

	HAL_Delay(50);
	begin(20, 4);

	createChar(CHAR_HUMAN, Human);
	createChar(CHAR_Plant, P_Z);
	createChar(CHAR_Contact, Contact );
	createChar(CHAR_Notes,Notes);
	createChar(CHAR_Music,Music );
	createChar(CHAR_Settings ,Settings );
	createChar(CHAR_Info,Info);
	createChar(CHAR_P1,Plant_1);
	createChar(CHAR_P2,Plant_2);
	createChar(CHAR_S,Shield);
	createChar(CHAR_HEART,Heart);


	  Contact_Init();
	  Note_Init();

	Game_Init();

	game.score = 0 ;
	gameSetting.plantDamage = 1;
	gameSetting.zombieSpeed = 1000 ;
	gameSetting.zombieSpawnRate = 5000;
	game.time = DAY ;
	game.plantsPlaced = 0;

	int start = 0 ;
	int music_once = 0 ;



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {

		switch(appState)
		    {
		        case APP_LOGO:
		            Logo();
		            break;
		        case APP_MENU:
		            Main_Menu();
		            break;

		        case APP_GAME:
		   		 switch(gameState)
		   		    {
		   		        case STATE_MENU:
		   		            Game_Menu();
		   		            break;

		   		        case STATE_GAME:
		   		        	if (start == 0 ){
		   		        		First();
		   		        		DrawHUD();
		   		        		Plant_Select();
		   		        		Game_Draw();
		   		        		start = 1 ;
		   		        	}
		   		        	else {
		   		            Game_Run();
		   		        	}
		   		            break;

		   		        case STATE_SETTING:
		   		            Game_Setting();
		   		            break;
		   		        case STATE_GAMEOVER:
		   		            GameOver();
		   		            break;

		   		    }

		            break;

		        case APP_CONTACT:
		            Contact_all();
		            break;

		        case APP_NOTE:
		            Note_all();
		            break;

		        case APP_MUSIC_PLAYER:
//		        	if(music_once){
		        		Music_Player();
//		        		music_once = 0 ;

//		        	}
		            break;

		        case APP_SETTING:
//		            Setting_Run();
		            break;
		        case APP_INFO:
		            User_Info();
		            break;

		    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_RTC
                              |RCC_PERIPHCLK_ADC12|RCC_PERIPHCLK_ADC34;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Common config
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc3.Init.LowPowerAutoWait = DISABLE;
  hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc3, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 71;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_I2C_SPI_Pin LD4_Pin LD3_Pin LD5_Pin
                           LD7_Pin LD9_Pin LD10_Pin LD8_Pin
                           LD6_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 PD10 PD11
                           PD12 PD13 PD14 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6 PC7 PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD2 PD3
                           PD4 PD5 PD6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
