#include <stdio.h>
#include <string.h>
#include "menu.h"

MenuItem sMenu[MAX_MENU_ITEMS];
int sMenuCount = 0;

void menuMenu() {
    int choice;

    do {
        printf("\n--- MENU ITEMS ---\n");
        printf("1. View Items\n");
        printf("2. Add Menu Item\n");
        printf("3. Restock Needed\n");
        printf("4. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showMenuItems(); break;
            case 2: addMenuItem(); break;
            case 3: restockMenu(); break;
        }
    } while (choice != 4);
}

void showMenuItems() {
    printf("\n+----------------------+-------+------------+\n");
    printf("| Item                 | Qty   | Price      |\n");
    printf("+----------------------+-------+------------+\n");
    for (int i = 0; i < sMenuCount; i++) {
        printf("| %-20s | %-5d | $ %8.2f |\n", sMenu[i].name, sMenu[i].quantity, sMenu[i].price);
    }
    printf("+----------------------+-------+------------+\n");
}

void addMenuItem() {
    char name[30];
    int quantity;
    int foundIndex = -1;

    printf("Enter item name: ");
    scanf("%s", name);

    for (int i = 0; i < sMenuCount; i++) {
        if (strcmp(sMenu[i].name, name) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Item already exists. Enter quantity to add: ");
        scanf("%d", &quantity);
        sMenu[foundIndex].quantity += quantity;
        printf("Menu item restocked!\n");
    } else {
        if (sMenuCount >= MAX_MENU_ITEMS) {
            printf("Menu full.\n");
            return;
        }
        strcpy(sMenu[sMenuCount].name, name);
        printf("Enter quantity: ");
        scanf("%d", &sMenu[sMenuCount].quantity);
        printf("Enter item price: ");
        scanf("%f", &sMenu[sMenuCount].price);
        sMenuCount++;
        printf("Menu item added!\n");
    }
}

void restockMenu() {
    printf("\n+----------------------+-------+\n");
    printf("| Needs Restock (< 5)  | Qty   |\n");
    printf("+----------------------+-------+\n");
    for (int i = 0; i < sMenuCount; i++) {
        if (sMenu[i].quantity < 5) {
            printf("| %-20s | %-5d |\n", sMenu[i].name, sMenu[i].quantity);
        }
    }
    printf("+----------------------+-------+\n");
}
