#include <stdio.h>
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
    printf("\nItem\tQty\tPrice\n");
    for (int i = 0; i < sMenuCount; i++) {
        printf("%s\t%d\t%f\n", sMenu[i].name, sMenu[i].quantity, sMenu[i].price);
    }
}

void addMenuItem() {
    if (sMenuCount >= MAX_MENU_ITEMS) {
        printf("Menu full.\n");
        return;
    }

    printf("Enter item name: ");
    scanf("%s", sMenu[sMenuCount].name);

    printf("Enter quantity: ");
    scanf("%d", &sMenu[sMenuCount].quantity);

    printf("Enter item price: ");
    scanf("%f", &sMenu[sMenuCount].price);

    sMenuCount++;
    printf("Menu item added!\n");
}

void restockMenu() {
    printf("\nMenu items needing restock (qty < 5):\n");
    for (int i = 0; i < sMenuCount; i++) {
        if (sMenu[i].quantity < 5) {
            printf("%s (Qty: %d)\n", sMenu[i].name, sMenu[i].quantity);
        }
    }
}
