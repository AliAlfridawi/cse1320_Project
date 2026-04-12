# Internal Interfaces (API)

This document defines the contracts between the planned modules.

## Inventory Module (`inventory.h`)
- `void inventory_init()`: Initialize the inventory list.
- `void inventory_add(const char* name, int qty, int threshold)`: Add a new ingredient.
- `void inventory_show()`: Print the current inventory to the terminal.
- `int inventory_get_qty(const char* name)`: Return the current quantity of an ingredient.

## Menu Module (`menu.h`)
- `void menu_add(const char* name, int qty, float price)`: Add a new menu item.
- `void menu_show()`: Print the current menu.
- `MenuItem* menu_get_item(int id)`: Return a pointer to a menu item by ID.

## Cart Module (`cart.h`)
- `void cart_clear()`: Reset the cart.
- `int cart_add_item(int itemId, int qty)`: Add a specific quantity of an item to the cart. Returns status code.
- `int cart_remove_item(int itemId, int qty)`: Remove a specific quantity from the cart. Returns status code.
- `float cart_calculate_total()`: Iterate through cart items and calculate the total price based on the Menu prices.
