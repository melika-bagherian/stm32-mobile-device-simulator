#ifndef __CONTACT_H
#define __CONTACT_H

#include "main.h"

#define MAX_CONTACTS      10
#define CONTACT_NAME_LEN  20
#define CONTACT_PHONE_LEN 15

// ساختار مربوط به ذخیره مخاطبین
typedef struct
{
    char name[CONTACT_NAME_LEN];
    char phone[CONTACT_PHONE_LEN];
} Contact_t;

typedef enum
{
    CONTACT_LIST,
    CONTACT_EDIT_NAME,
    CONTACT_EDIT_PHONE
} ContactState_t;

void Contact_Init(void);
void Contact_Task(void);
void Contact_DrawList(void);

typedef enum
{
    CT_KEY_NONE,
    CT_KEY_LEFT,
    CT_KEY_RIGHT,
    CT_KEY_UP,
    CT_KEY_DOWN,
    CT_KEY_7,
    CT_KEY_8,
    CT_KEY_SELECT
} ContactKeyType;

extern volatile ContactKeyType contactPressedKey;

#endif
