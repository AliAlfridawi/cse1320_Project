#ifndef MENU_H
#define MENU_H

#include "common.h"

typedef struct MenuItem {
    char name[30];
    int quantity;
    float price;
} MenuItem;

extern MenuItem sMenu[MAX_MENU_ITEMS];
extern int sMenuCount;

void menuMenu();
void showMenuItems();
void addMenuItem();
void restockMenu();

#endif // MENU_H
