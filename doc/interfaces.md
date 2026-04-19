# Internal Interfaces (API)

This document defines the interface and functionality provided by each module in the Bakery Management System.

## Inventory Module (`inventory.h`)
- `void inventoryMenu()`: Displays and handles the inventory-related user menu.
- `void showInventory()`: Prints all current items and their status to the terminal.
- `void addIngredient()`: Prompts the user to add a new ingredient type to the inventory.
- `void restockInventory()`: Identifies and lists ingredients that have fallen below their restock threshold.

## Menu Module (`menu.h`)
- `void menuMenu()`: Displays and handles the menu-item-related management interface.
- `void showMenuItems()`: Lists all items currently available for sale, including their price and quantity.
- `void addMenuItem()`: Adds a new product to the sale menu.
- `void restockMenu()`: Shows menu items that need restocking based on a pre-defined low-stock limit.

## Cart Module (`cart.h`)
- `void BuyItem()`: Orchestrates the customer purchase process, providing the buying-menu loop.
- `void viewCart()`: Shows current cart contents, along with prices and calculated totals.
- `void addToCart()`: Increments item quantities in the cart while decrementing from the main menu stock.
- `void removeFromCart()`: Decrements items from the cart and returns them to the available menu stock.
- `float determineTotalPrice()`: Calculates the final cost for all items currently in the cart.
