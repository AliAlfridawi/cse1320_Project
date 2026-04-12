/*
    Author: Ali Alfridawi
    
    Purpose: CLI Main Loop
*/

#include <stdio.h>
#include <stdbool.h>
#include "db_manager.h"
#include "inventory.h"

int main()
{
    // Initialize the database and create tables
    db_initialize();

    printf("--- Welcome to Clarity Inventory Management System ---\n");

    while(true)
    {
        // For now, let's just break the loop to keep it from being infinite
        break;
    }

    return 0;
}
