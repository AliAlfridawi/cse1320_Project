#include <stdio.h>
#include <string.h>
#include "common.h"
#include "inventory.h"
#include "menu.h"
#include "cart.h"
#include "storage.h"

int login();
void mainMenu();

int login() {
    char input[20];

    printf("Enter password: ");
    scanf("%19s", input);

    if (strcmp(input, PASSWORD) == 0) {
        return 1;
    }

    return 0;
}

void mainMenu() {
    int choice = 0;

    do {
        printf("\n=== BAKERY MANAGEMENT SYSTEM ===\n");
        printf("1. Inventory\n");
        printf("2. Menu\n");
        printf("3. Buy Items\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inventoryMenu();
                break;
            case 2:
                menuMenu();
                break;
            case 3:
                BuyItem();
                break;
            case 4:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);
}

int main() {
    if (!login()) {
        printf("Incorrect password.\n");
        return 0;
    }

    loadData();
    mainMenu();
    saveData();
    return 0;
}
