#include "contact.h"
#include <string.h>
#include <stdio.h>
#include "LiquidCrystal.h"

typedef enum {
    CT_MODE_NAVIGATION,
    CT_MODE_TYPING
} ContactKeyboardMode_t;

static ContactKeyboardMode_t contactKeyboardMode = CT_MODE_NAVIGATION;
static uint8_t contactCursorPos = 0;
static uint8_t contactCurrentField = 0;  // 0 = Name, 1 = Phone

static uint32_t contactLastKeyPressTime = 0;
static uint8_t contactAwaitingLock = 0;
#define CT_MULTI_PRESS_TIMEOUT 1500

Contact_t contacts[MAX_CONTACTS] =
{
    {"Masiha Mohammadi", "09123456789"},
    {"Ali Rezaei",       "09111111111"},
    {"Sara Ahmadi",      "09222222222"},
    {"Uni Office",       "02188888888"},
    {"Emergency",        "115"}
};

uint8_t contactCount = 5;
uint8_t contactSelected = 0;
uint8_t contactListOffset = 0;
ContactState_t contactState = CONTACT_LIST;

static void Contact_CycleCharacter(int direction);
static void Contact_HandleKeyPress(ContactKeyType key);
static void Contact_ListTask(void);
static void Contact_EditTask(void);

void Contact_Init(void)
{
    contactState = CONTACT_LIST;
    contactSelected = 0;
    contactListOffset = 0;
    contactKeyboardMode = CT_MODE_NAVIGATION;
    contactCurrentField = 0;
    contactCursorPos = 0;
}

void Contact_DrawList(void)
{
    clear();
    noCursor();
    noBlink();

    if(contactSelected < contactListOffset)
        contactListOffset = contactSelected;

    if(contactSelected >= contactListOffset + 4)
        contactListOffset = contactSelected - 3;

    for(uint8_t i = 0; i < 4; i++)
    {
        uint8_t index = contactListOffset + i;

        setCursor(0, i);
        if(index == contactSelected && index < contactCount) {
            print("> ");
        } else {
            print("  ");
        }

        if(index < contactCount) {
            print(contacts[index].name);
        }

        if(i == 3) {
            setCursor(19, 3);
            if(contactSelected == contactCount) {
                print(">");
            } else {
                print("+");
            }
        }
    }
}

void Contact_DrawEdit(void)
{
    setCursor(0, 0);
    print("N: ");
    print(contacts[contactSelected].name);
    for(int fill = strlen(contacts[contactSelected].name) + 3; fill < 20; fill++) {
        print(" ");
    }

    setCursor(0, 1);
    print("P: ");
    print(contacts[contactSelected].phone);
    for(int fill = strlen(contacts[contactSelected].phone) + 3; fill < 20; fill++) {
        print(" ");
    }

    if(contactKeyboardMode == CT_MODE_TYPING) {
        int lcd_x = 3 + contactCursorPos;
        int lcd_y = (contactCurrentField == 0) ? 0 : 1;

        if(lcd_x >= 20) lcd_x = 19;

        setCursor(lcd_x, lcd_y);
        cursor();
        blink();
    } else {
        noCursor();
        noBlink();
    }
}

static void Contact_ListTask(void)
{
    uint8_t oldSelected = contactSelected;
    uint8_t oldOffset = contactListOffset;

    switch(contactPressedKey)
    {
        case CT_KEY_UP:
            if(contactSelected > 0) contactSelected--;
            break;

        case CT_KEY_DOWN:
            if(contactSelected <= contactCount) contactSelected++;
            break;

        case CT_KEY_SELECT:
            if(contactSelected == contactCount)
            {
                if(contactCount < MAX_CONTACTS)
                {
                    sprintf(contacts[contactCount].name, "Contact %d", contactCount + 1);
                    strcpy(contacts[contactCount].phone, "0");
                    contactCount++;
                    contactSelected = contactCount - 1;
                }
            }

            contactKeyboardMode = CT_MODE_TYPING;
            contactCurrentField = 0;  // ابتدا نام

            int len = strlen(contacts[contactSelected].name);
            contactCursorPos = (len > 0) ? (len - 1) : 0;

            contactAwaitingLock = 0;
            contactState = CONTACT_EDIT_NAME;
            clear();
            Contact_DrawEdit();
            contactPressedKey = CT_KEY_NONE;
            return;

        default:
            contactPressedKey = CT_KEY_NONE;
            return;
    }

    if(contactPressedKey != CT_KEY_NONE)
    {
        if(contactSelected < contactListOffset)
            contactListOffset = contactSelected;
        if(contactSelected >= contactListOffset + 4)
            contactListOffset = contactSelected - 3;

        if(contactListOffset != oldOffset)
        {
            Contact_DrawList();
        }
        else
        {
            if(oldSelected < contactCount) {
                uint8_t oldRow = oldSelected - contactListOffset;
                setCursor(0, oldRow);
                print("  ");
            } else if(oldSelected == contactCount) {
                setCursor(19, 3);
                print("+");
            }

            if(contactSelected < contactCount) {
                uint8_t newRow = contactSelected - contactListOffset;
                setCursor(0, newRow);
                print("> ");
            } else if(contactSelected == contactCount) {
                setCursor(19, 3);
                print(">");
            }
        }
    }
    contactPressedKey = CT_KEY_NONE;
}

static void Contact_EditTask(void)
{
    if(contactPressedKey == CT_KEY_NONE) return;
    Contact_HandleKeyPress(contactPressedKey);
    contactPressedKey = CT_KEY_NONE;
}

static void Contact_HandleKeyPress(ContactKeyType key) {
    if (contactKeyboardMode == CT_MODE_TYPING)
    {
        char* activeStr = (contactCurrentField == 0) ?
                           contacts[contactSelected].name :
                           contacts[contactSelected].phone;
        int maxLen = (contactCurrentField == 0) ? CONTACT_NAME_LEN : CONTACT_PHONE_LEN;

        switch(key)
        {
            case CT_KEY_UP:
                Contact_CycleCharacter(1);
                contactLastKeyPressTime = HAL_GetTick();
                contactAwaitingLock = 1;
                Contact_DrawEdit();
                break;

            case CT_KEY_DOWN:
                Contact_CycleCharacter(-1);
                contactLastKeyPressTime = HAL_GetTick();
                contactAwaitingLock = 1;
                Contact_DrawEdit();
                break;

            case CT_KEY_RIGHT:
                contactAwaitingLock = 0;
                if (contactCursorPos < maxLen - 2) {
                    contactCursorPos++;
                    if (activeStr[contactCursorPos] == '\0') {
                        activeStr[contactCursorPos] = ' ';
                        activeStr[contactCursorPos + 1] = '\0';
                    }
                }
                Contact_DrawEdit();
                break;

            case CT_KEY_LEFT:
                contactAwaitingLock = 0;
                if (contactCursorPos > 0) {
                    activeStr[contactCursorPos] = '\0';
                    contactCursorPos--;
                } else {
                    activeStr[0] = '\0';
                }
                Contact_DrawEdit();
                break;

            case CT_KEY_SELECT:
                contactAwaitingLock = 0;
                noBlink();
                noCursor();

                if(activeStr[contactCursorPos] == ' ')
                    activeStr[contactCursorPos] = '\0';

                if (contactCurrentField == 0) {
                    contactCurrentField = 1;  // برو به Phone
                    int phoneLen = strlen(contacts[contactSelected].phone);
                    contactCursorPos = (phoneLen > 0) ? (phoneLen - 1) : 0;
                    Contact_DrawEdit();
                } else {
                    contactKeyboardMode = CT_MODE_NAVIGATION;
                    contactState = CONTACT_LIST;
                    contactCurrentField = 0;
                    Contact_DrawList();
                }
                break;

            default: break;
        }
    }
}

void Contact_Task(void)
{
    if ((contactState == CONTACT_EDIT_NAME || contactState == CONTACT_EDIT_PHONE) &&
        contactKeyboardMode == CT_MODE_TYPING && contactAwaitingLock)
    {
        if (HAL_GetTick() - contactLastKeyPressTime > CT_MULTI_PRESS_TIMEOUT)
        {
            contactAwaitingLock = 0;

            char* activeStr = (contactCurrentField == 0) ?
                               contacts[contactSelected].name :
                               contacts[contactSelected].phone;
            int maxLen = (contactCurrentField == 0) ? CONTACT_NAME_LEN : CONTACT_PHONE_LEN;

            if (contactCursorPos < maxLen - 2) {
                contactCursorPos++;
                if (activeStr[contactCursorPos] == '\0') {
                    activeStr[contactCursorPos] = ' ';
                    activeStr[contactCursorPos + 1] = '\0';
                }
            }
            Contact_DrawEdit();
        }
    }

    switch(contactState)
    {
        case CONTACT_LIST: Contact_ListTask(); break;
        case CONTACT_EDIT_NAME:
        case CONTACT_EDIT_PHONE: Contact_EditTask(); break;
        default: break;
    }
}


static void Contact_CycleCharacter(int direction) {
    const char name_chars[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,-_";
    const char phone_chars[] = "0123456789+";
    const char* allowed = (contactCurrentField == 0) ? name_chars : phone_chars;
    int total_chars = strlen(allowed);
    int current_index = 0;

    char* activeStr = (contactCurrentField == 0) ?
                       contacts[contactSelected].name :
                       contacts[contactSelected].phone;
    char current_char = activeStr[contactCursorPos];

    if (current_char == '\0' || current_char == ' ')
        current_char = allowed[0];

    for (int i = 0; i < total_chars; i++) {
        if (allowed[i] == current_char) {
            current_index = i;
            break;
        }
    }

    current_index += direction;
    if (current_index >= total_chars) current_index = 0;
    if (current_index < 0) current_index = total_chars - 1;

    activeStr[contactCursorPos] = allowed[current_index];
}
