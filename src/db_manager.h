#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "../sqlite/sqlite3.h"

// Define a structure to hold inventory data
typedef struct {
    int item_id;
    int restaurant_id;
    char item_name[100];
    int quantity;
    int threshold;
} InventoryItem;

// Function prototypes
void db_initialize();
int db_executeQuery(const char* sql_command);
int db_fetchAllInventory(InventoryItem *items, int max_items);

#endif
