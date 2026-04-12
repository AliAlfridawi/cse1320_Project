#include <stdio.h>
#include <string.h>
#include "storage.h"
#include "inventory.h"
#include "menu.h"

#define INVENTORY_FILE "inventory.txt"
#define MENU_FILE "menu.txt"

void loadData() {
    FILE *invFile = fopen(INVENTORY_FILE, "r");
    if (invFile != NULL) {
        sInventoryCount = 0;
        while (sInventoryCount < MAX_INGREDIENTS && 
               fscanf(invFile, " %[^,],%d,%d\n", 
                      sInventory[sInventoryCount].name, 
                      &sInventory[sInventoryCount].quantity, 
                      &sInventory[sInventoryCount].threshold) == 3) {
            sInventoryCount++;
        }
        fclose(invFile);
    }

    FILE *menuFile = fopen(MENU_FILE, "r");
    if (menuFile != NULL) {
        sMenuCount = 0;
        while (sMenuCount < MAX_MENU_ITEMS && 
               fscanf(menuFile, " %[^,],%d,%f\n", 
                      sMenu[sMenuCount].name, 
                      &sMenu[sMenuCount].quantity, 
                      &sMenu[sMenuCount].price) == 3) {
            sMenuCount++;
        }
        fclose(menuFile);
    }
}

void saveData() {
    FILE *invFile = fopen(INVENTORY_FILE, "w");
    if (invFile != NULL) {
        for (int i = 0; i < sInventoryCount; i++) {
            fprintf(invFile, "%s,%d,%d\n", 
                    sInventory[i].name, 
                    sInventory[i].quantity, 
                    sInventory[i].threshold);
        }
        fclose(invFile);
    }

    FILE *menuFile = fopen(MENU_FILE, "w");
    if (menuFile != NULL) {
        for (int i = 0; i < sMenuCount; i++) {
            fprintf(menuFile, "%s,%d,%.2f\n", 
                    sMenu[i].name, 
                    sMenu[i].quantity, 
                    sMenu[i].price);
        }
        fclose(menuFile);
    }
}
