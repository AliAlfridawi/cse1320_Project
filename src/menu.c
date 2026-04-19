#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "storage.h"

MenuItem sMenu[MAX_MENU_ITEMS];
int sMenuCount = 0;

void menuMenu() {
    int choice = 0;

    do {
        printf("\n--- MENU ITEMS ---\n");
        printf("1. View Items\n");
        printf("2. Add Menu Item\n");
        printf("3. Restock Needed\n");
        printf("4. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showMenuItems();
                break;
            case 2:
                addMenuItem();
                break;
            case 3:
                restockMenu();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);
}

void showMenuItems() {
    int i;

    if (sMenuCount == 0) {
        printf("\nNo menu items available.\n");
        return;
    }

    printf("\nNo.\tItem\tQty\tPrice\n");
    for (i = 0; i < sMenuCount; i++) {
        printf("%d\t%s\t%d\t%.2f\n",
            i + 1,
            sMenu[i].name,
            sMenu[i].quantity,
            sMenu[i].price);
    }
}

void addMenuItem() {
    char name[30];
    int quantity;
    float price;
    int i;

    printf("Enter item name: ");
    scanf("%29s", name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    printf("Enter item price: ");
    scanf("%f", &price);

    for (i = 0; i < sMenuCount; i++) {
        if (strcmp(sMenu[i].name, name) == 0) {
            sMenu[i].quantity += quantity;
            sMenu[i].price = price;
            saveData();
            printf("Menu item quantity updated!\n");
            return;
        }
    }

    if (sMenuCount >= MAX_MENU_ITEMS) {
        printf("Menu full.\n");
        return;
    }

    strcpy(sMenu[sMenuCount].name, name);
    sMenu[sMenuCount].quantity = quantity;
    sMenu[sMenuCount].price = price;
    sMenuCount++;
    saveData();
    printf("Menu item added!\n");
}

void restockMenu() {
    int found = 0;
    int i;

    if (sMenuCount == 0) {
        printf("\nNo menu items available.\n");
        return;
    }

    printf("\nMenu items needing restock (qty < 5):\n");
    for (i = 0; i < sMenuCount; i++) {
        if (sMenu[i].quantity < 5) {
            printf("%s (Qty: %d)\n", sMenu[i].name, sMenu[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No menu items need restocking.\n");
    }
}
