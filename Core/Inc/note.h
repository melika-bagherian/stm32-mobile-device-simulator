#ifndef __NOTE_H

#define __NOTE_H



#include "main.h"



#define MAX_NOTES      10

#define NOTE_TITLE_LEN 20

#define NOTE_TEXT_LEN  200


typedef struct {

    uint32_t freq;

    uint32_t dur;

} Note;


typedef struct

{

    char title[NOTE_TITLE_LEN];

    char text[NOTE_TEXT_LEN];

} Note_t;



typedef enum

{

    NOTE_LIST,

    NOTE_VIEW,

    NOTE_EDIT

} NoteState_t;



void Note_Init(void);

void Note_Task(void);

void Note_DrawList(void);




//typedef enum
//
//{
//
//    KEY_NONE,
//
//    KEY_LEFT,
//
//    KEY_RIGHT,
//
//    KEY_UP,
//
//    KEY_DOWN,
//
//    KEY_7,
//
//    KEY_8,
//
//    KEY_SELECT
//
//} KeyType;
//
//
//
//extern volatile KeyType pressedKey;



#endif
