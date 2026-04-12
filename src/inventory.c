#include <stdio.h>
#include "inventory.h"

Ingredient sInventory[MAX_INGREDIENTS];
int sInventoryCount = 0;

void inventoryMenu() {
    int choice;

    do {
        printf("\n--- INVENTORY MENU ---\n");
        printf("1. View Inventory\n");
        printf("2. Add Ingredient\n");
        printf("3. Restock Needed\n");
        printf("4. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showInventory(); break;
            case 2: addIngredient(); break;
            case 3: restockInventory(); break;
        }
    } while (choice != 4);
}

void showInventory() {
    printf("\nIngredient\tQty\tThreshold\n");
    for (int i = 0; i < sInventoryCount; i++) {
        printf("%s\t\t%d\t%d\n",
            sInventory[i].name,
            sInventory[i].quantity,
            sInventory[i].threshold
        );
    }
}

void addIngredient() {
    if (sInventoryCount >= MAX_INGREDIENTS) {
        printf("Inventory full.\n");
        return;
    }

    printf("Enter ingredient name: ");
    scanf("%s", sInventory[sInventoryCount].name);

    printf("Enter quantity: ");
    scanf("%d", &sInventory[sInventoryCount].quantity);

    printf("Enter restock threshold: ");
    scanf("%d", &sInventory[sInventoryCount].threshold);

    sInventoryCount++;
    printf("Ingredient added!\n");
}

void restockInventory() {
    printf("\nItems needing restock:\n");
    for (int i = 0; i < sInventoryCount; i++) {
        if (sInventory[i].quantity < sInventory[i].threshold) {
            printf("%s (Qty: %d)\n",
                sInventory[i].name,
                sInventory[i].quantity
            );
        }
    }
}
