#include <stdio.h>
#include "inventory.h"
#include "db_manager.h"

void add_item_to_inventory()
{
    char item_name[100];
    int quantity, threshold;
    float price;

    printf("Enter item name: ");
    scanf("%s", item_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    printf("Enter price: ");
    scanf("%f", &price);
    printf("Enter threshold: ");
    scanf("%d", &threshold);

    if(quantity < 0 || price < 0 || threshold < 0)
    {
        printf("Invalid input. Quantity, price, and threshold must be non-negative.\n");
        return;
    }
    else if(item_name == NULL || item_name[0] == '\0')
    {
        printf("Invalid input. Item name cannot be empty.\n");
        return;
    }
    int result = db_executeQuery("INSERT INTO inventory (item_name, quantity, price, threshold) VALUES (?, ?, ?, ?)", item_name, quantity, price, threshold);
    if(result != 0)
    {
        printf("Failed to add item to inventory.\n");
    }
    else
    {
        printf("Item added to inventory successfully.\n");
    }
}
