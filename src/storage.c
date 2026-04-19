#include <stdio.h>
#include "storage.h"
#include "inventory.h"
#include "menu.h"
#include "cart.h"

#define INVENTORY_FILE "inventory.txt"
#define MENU_FILE "menu.txt"
#define CART_FILE "cart.txt"

static void clearData() {
    int i;

    sInventoryCount = 0;
    sMenuCount = 0;

    for (i = 0; i < MAX_INGREDIENTS; i++) {
        sInventory[i].name[0] = '\0';
        sInventory[i].quantity = 0;
        sInventory[i].threshold = 0;
    }

    for (i = 0; i < MAX_MENU_ITEMS; i++) {
        sMenu[i].name[0] = '\0';
        sMenu[i].quantity = 0;
        sMenu[i].price = 0.0f;
        sCart.items[i] = 0;
    }
}

static void loadInventoryData() {
    FILE *invFile;
    char line[100];

    invFile = fopen(INVENTORY_FILE, "r");
    if (invFile == NULL) {
        return;
    }

    while (sInventoryCount < MAX_INGREDIENTS &&
           fgets(line, sizeof(line), invFile) != NULL) {
        Ingredient ingredient;
        char extra;

        if (sscanf(line, " %29[^,],%d,%d %c",
                ingredient.name,
                &ingredient.quantity,
                &ingredient.threshold,
                &extra) != 3) {
            printf("Warning: bad data in %s\n", INVENTORY_FILE);
            break;
        }

        sInventory[sInventoryCount] = ingredient;
        sInventoryCount++;
    }

    fclose(invFile);
}

static void loadMenuData() {
    FILE *menuFile;
    char line[100];

    menuFile = fopen(MENU_FILE, "r");
    if (menuFile == NULL) {
        return;
    }

    while (sMenuCount < MAX_MENU_ITEMS &&
           fgets(line, sizeof(line), menuFile) != NULL) {
        MenuItem item;
        char extra;

        if (sscanf(line, " %29[^,],%d,%f %c",
                item.name,
                &item.quantity,
                &item.price,
                &extra) != 3) {
            printf("Warning: bad data in %s\n", MENU_FILE);
            break;
        }

        sMenu[sMenuCount] = item;
        sMenuCount++;
    }

    fclose(menuFile);
}

static void loadCartData() {
    FILE *cartFile;
    char line[100];
    int index = 0;

    cartFile = fopen(CART_FILE, "r");
    if (cartFile == NULL) {
        return;
    }

    while (index < sMenuCount && fgets(line, sizeof(line), cartFile) != NULL) {
        int quantity;
        char extra;

        if (sscanf(line, "%d %c", &quantity, &extra) != 1 || quantity < 0) {
            printf("Warning: bad data in %s\n", CART_FILE);
            break;
        }

        sCart.items[index] = quantity;
        index++;
    }

    fclose(cartFile);
}

void loadData() {
    clearData();
    loadInventoryData();
    loadMenuData();
    loadCartData();
}

void saveData() {
    FILE *invFile;
    FILE *menuFile;
    FILE *cartFile;
    int i;

    invFile = fopen(INVENTORY_FILE, "w");
    if (invFile == NULL) {
        printf("Warning: could not save %s\n", INVENTORY_FILE);
    } else {
        for (i = 0; i < sInventoryCount; i++) {
            fprintf(invFile, "%s,%d,%d\n",
                sInventory[i].name,
                sInventory[i].quantity,
                sInventory[i].threshold);
        }
        fclose(invFile);
    }

    menuFile = fopen(MENU_FILE, "w");
    if (menuFile == NULL) {
        printf("Warning: could not save %s\n", MENU_FILE);
    } else {
        for (i = 0; i < sMenuCount; i++) {
            fprintf(menuFile, "%s,%d,%.2f\n",
                sMenu[i].name,
                sMenu[i].quantity,
                sMenu[i].price);
        }
        fclose(menuFile);
    }

    cartFile = fopen(CART_FILE, "w");
    if (cartFile == NULL) {
        printf("Warning: could not save %s\n", CART_FILE);
    } else {
        for (i = 0; i < sMenuCount; i++) {
            fprintf(cartFile, "%d\n", sCart.items[i]);
        }
        fclose(cartFile);
    }
}
