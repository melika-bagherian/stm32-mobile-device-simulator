#include "main.h"
#include "note.h"
#include <string.h>
#include <stdio.h>
#include "LiquidCrystal.h"




typedef enum {

    MODE_NAVIGATION,

    MODE_TYPING

} KeyboardMode_t;


static KeyboardMode_t keyboardMode = MODE_NAVIGATION;

static uint8_t textCursorPos = 0;




static uint32_t lastKeyPressTime = 0;

static uint8_t awaitingLock = 0;

#define MULTI_PRESS_TIMEOUT 1500




Note_t notes[MAX_NOTES] =

{

    {"Note 1", "Milk Egg Bread"},

    {"Note 2", "Finish LCD Driver"},

    {"Note 3", "Music Player"},

    {"Note 4", "Finish Final Project"},

    {"Note 5", "Embedded Systems"}

};



uint8_t noteCount = 5;

uint8_t selectedNote = 0;

uint8_t listOffset = 0;

NoteState_t noteState = NOTE_LIST;




static void Notes_CycleCharacter(int direction);

//static void Note_HandleKeyPress(KeyType key);
//volatile KeyType pressedKey = KEY_NONE;

static void Note_ListTask(void);

static void Note_EditTask(void);



void Note_Init(void)

{

    noteState = NOTE_LIST;

    selectedNote = 0;

    listOffset = 0;

    keyboardMode = MODE_NAVIGATION;

}




void Note_DrawList(void)

{

    clear();

    noCursor();

    noBlink();



    if(selectedNote < listOffset)

        listOffset = selectedNote;



    if(selectedNote >= listOffset + 4)

        listOffset = selectedNote - 3;



    for(uint8_t i = 0; i < 4; i++)

    {

        uint8_t index = listOffset + i;



        setCursor(0, i);

        if(index == selectedNote && index < noteCount) {

            print("> ");

        } else {

            print("  ");

        }



        if(index < noteCount) {

            print(notes[index].title);

        }



        if(i == 3) {

            setCursor(19, 3);

            if(selectedNote == noteCount) {

                print(">");

            } else {

                print("+");

            }

        }

    }

}

void Note_DrawEdit(void)

{


    setCursor(0, 0);

    print("T: ");

    print(notes[selectedNote].title);

    for(int fill = strlen(notes[selectedNote].title) + 3; fill < 20; fill++) {

        print(" ");

    }



    int len = strlen(notes[selectedNote].text);

    int start_line_idx = 0;





    int current_line = textCursorPos / 20;


    if (current_line >= 2) {

        start_line_idx = (current_line - 1) * 20;

    }



    setCursor(0, 2);

    char line1_buffer[21];

    for(int i = 0; i < 20; i++) {

        int idx = start_line_idx + i;

        if(idx < len) line1_buffer[i] = notes[selectedNote].text[idx];

        else line1_buffer[i] = ' ';

    }

    line1_buffer[20] = '\0';

    print(line1_buffer);



    setCursor(0, 3);

    char line2_buffer[21];

    for(int i = 0; i < 20; i++) {

        int idx = start_line_idx + 20 + i;

        if(idx < len) line2_buffer[i] = notes[selectedNote].text[idx];

        else line2_buffer[i] = ' ';

    }

    line2_buffer[20] = '\0';

    print(line2_buffer);



    if(keyboardMode == MODE_TYPING) {

        int relative_pos = textCursorPos - start_line_idx;

        int lcd_x = relative_pos % 20;

        int lcd_y = 2 + (relative_pos / 20);



        if(lcd_y > 3) { lcd_y = 3; lcd_x = 19; }



        setCursor(lcd_x, lcd_y);

        cursor();

        blink();

    } else {

        noCursor();

        noBlink();

    }

}



static void Note_ListTask(void)

{

    uint8_t oldSelectedNote = selectedNote;

    uint8_t oldListOffset = listOffset;



    switch(pressedKey)

    {

        case KEY_UP:

            if(selectedNote > 0) selectedNote--;

            break;



        case KEY_DOWN:

            if(selectedNote <= noteCount) selectedNote++;

            break;



        case KEY_SELECT:

            if(selectedNote == noteCount)

            {

                if(noteCount < MAX_NOTES)

                {

                    sprintf(notes[noteCount].title, "Note %d", noteCount + 1);

                    strcpy(notes[noteCount].text, "A");

                    noteCount++;

                    selectedNote = noteCount - 1;

                }

            }



            keyboardMode = MODE_TYPING;

            textCursorPos = strlen(notes[selectedNote].text) - 1;

            if(textCursorPos < 0) textCursorPos = 0;



            awaitingLock = 0;

            noteState = NOTE_EDIT;

            clear();

            Note_DrawEdit();

            pressedKey = KEY_NONE;

            return;



        default:

            pressedKey = KEY_NONE;

            return;

    }



    if(pressedKey != KEY_NONE)

    {

        if(selectedNote < listOffset)

            listOffset = selectedNote;

        if(selectedNote >= listOffset + 4)

            listOffset = selectedNote - 3;



        if(listOffset != oldListOffset)

        {

            Note_DrawList();

        }

        else

        {

            if(oldSelectedNote < noteCount) {

                uint8_t oldRow = oldSelectedNote - listOffset;

                setCursor(0, oldRow);

                print("  ");

            } else if(oldSelectedNote == noteCount) {

                setCursor(19, 3);

                print("+");

            }



            if(selectedNote < noteCount) {

                uint8_t newRow = selectedNote - listOffset;

                setCursor(0, newRow);

                print("> ");

            } else if(selectedNote == noteCount) {

                setCursor(19, 3);

                print(">");

            }

        }

    }

    pressedKey = KEY_NONE;

}



static void Note_EditTask(void)

{

    if(pressedKey == KEY_NONE) return;

    Note_HandleKeyPress(pressedKey);

    pressedKey = KEY_NONE;

}



void Note_HandleKeyPress(KeyType key) {

    if (keyboardMode == MODE_TYPING)

    {

        switch(key)

        {

            case KEY_UP:

                Notes_CycleCharacter(1);

                lastKeyPressTime = HAL_GetTick();

                awaitingLock = 1;

                Note_DrawEdit();

                break;



            case KEY_DOWN:

                Notes_CycleCharacter(-1);

                lastKeyPressTime = HAL_GetTick();

                awaitingLock = 1;

                Note_DrawEdit();

                break;



            case KEY_RIGHT:

                awaitingLock = 0;

                if (textCursorPos < NOTE_TEXT_LEN - 2) {

                    textCursorPos++;

                    notes[selectedNote].text[textCursorPos] = ' ';

                    notes[selectedNote].text[textCursorPos + 1] = '\0';

                }

                Note_DrawEdit();

                break;



            case KEY_LEFT:

                awaitingLock = 0;

                if (textCursorPos > 0) {

                    notes[selectedNote].text[textCursorPos] = '\0';

                    textCursorPos--;

                } else {

                    notes[selectedNote].text[0] = '\0';

                }

                Note_DrawEdit();

                break;



            case KEY_SELECT:

                awaitingLock = 0;

                noBlink();

                noCursor();



                if(notes[selectedNote].text[textCursorPos] == ' ')

                    notes[selectedNote].text[textCursorPos] = '\0';



                keyboardMode = MODE_NAVIGATION;

                noteState = NOTE_LIST;

                Note_DrawList();

                break;



            default: break;

        }

    }

}



void Note_Task(void)

{

    if (noteState == NOTE_EDIT && keyboardMode == MODE_TYPING && awaitingLock)

    {

        if (HAL_GetTick() - lastKeyPressTime > MULTI_PRESS_TIMEOUT)

        {

            awaitingLock = 0;



            if (textCursorPos < NOTE_TEXT_LEN - 2) {

                textCursorPos++;



                if (notes[selectedNote].text[textCursorPos] == '\0') {

                    notes[selectedNote].text[textCursorPos] = ' ';

                    notes[selectedNote].text[textCursorPos + 1] = '\0';

                }

            }

            Note_DrawEdit();

        }

    }



    switch(noteState)

    {

        case NOTE_LIST: Note_ListTask(); break;

        case NOTE_EDIT: Note_EditTask(); break;

        default: break;

    }

}



static void Notes_CycleCharacter(int direction) {

    const char allowed_chars[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,!?";

    int total_chars = sizeof(allowed_chars) - 1;

    int current_index = 0;



    char current_char = notes[selectedNote].text[textCursorPos];

    if (current_char == '\0') current_char = ' ';



    for (int i = 0; i < total_chars; i++) {

        if (allowed_chars[i] == current_char) {

            current_index = i;

            break;

        }

    }



    current_index += direction;

    if (current_index >= total_chars) current_index = 0;

    if (current_index < 0) current_index = total_chars - 1;



    notes[selectedNote].text[textCursorPos] = allowed_chars[current_index];

}

