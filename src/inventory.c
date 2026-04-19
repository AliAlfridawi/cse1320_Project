#include <stdio.h>
#include <string.h>
#include "inventory.h"
#include "storage.h"

Ingredient sInventory[MAX_INGREDIENTS];
int sInventoryCount = 0;

void inventoryMenu() {
    int choice = 0;

    do {
        printf("\n--- INVENTORY MENU ---\n");
        printf("1. View Inventory\n");
        printf("2. Add Ingredient\n");
        printf("3. Restock Needed\n");
        printf("4. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showInventory();
                break;
            case 2:
                addIngredient();
                break;
            case 3:
                restockInventory();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);
}

void showInventory() {
    int i;

    if (sInventoryCount == 0) {
        printf("\nNo inventory items available.\n");
        return;
    }

    printf("\nIngredient\tQty\tThreshold\n");
    for (i = 0; i < sInventoryCount; i++) {
        printf("%s\t\t%d\t%d\n",
            sInventory[i].name,
            sInventory[i].quantity,
            sInventory[i].threshold);
    }
}

void addIngredient() {
    char name[30];
    int quantity;
    int threshold;
    int i;

    printf("Enter ingredient name: ");
    scanf("%29s", name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    printf("Enter restock threshold: ");
    scanf("%d", &threshold);

    for (i = 0; i < sInventoryCount; i++) {
        if (strcmp(sInventory[i].name, name) == 0) {
            sInventory[i].quantity += quantity;
            sInventory[i].threshold = threshold;
            saveData();
            printf("Ingredient quantity updated!\n");
            return;
        }
    }

    if (sInventoryCount >= MAX_INGREDIENTS) {
        printf("Inventory full.\n");
        return;
    }

    strcpy(sInventory[sInventoryCount].name, name);
    sInventory[sInventoryCount].quantity = quantity;
    sInventory[sInventoryCount].threshold = threshold;
    sInventoryCount++;
    saveData();
    printf("Ingredient added!\n");
}

void restockInventory() {
    int found = 0;
    int i;

    if (sInventoryCount == 0) {
        printf("\nNo inventory items available.\n");
        return;
    }

    printf("\nItems needing restock:\n");
    for (i = 0; i < sInventoryCount; i++) {
        if (sInventory[i].quantity < sInventory[i].threshold) {
            printf("%s (Qty: %d)\n",
                sInventory[i].name,
                sInventory[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No ingredients need restocking.\n");
    }
}
