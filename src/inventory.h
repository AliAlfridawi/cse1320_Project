#ifndef INVENTORY_H
#define INVENTORY_H

#include "common.h"

typedef struct Ingredient {
    char name[30];
    int quantity;
    int threshold;
} Ingredient;

extern Ingredient sInventory[MAX_INGREDIENTS];
extern int sInventoryCount;

void inventoryMenu();
void showInventory();
void addIngredient();
void restockInventory();

#endif // INVENTORY_H
