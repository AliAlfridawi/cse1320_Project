# Source Code Architecture & Developer Guide

This directory contains the C implementation of the Bakery Management System. The project is designed with a modular architecture, where each major feature is encapsulated in its own `.c` and `.h` file pair.

## System Architecture Overview

The system is orchestrated by `main.c`, which handles the initial login and the top-level CLI menu. Each functional area (Inventory, Menu, Cart) is a self-contained module with its own data structures and business logic.

### Module Breakdown

#### `main.c`
The entry point of the application. It contains the `login()` function and the `mainMenu()` loop, delegating specific functionality to the other modules.

#### `common.h`
A central header file that defines project-wide constants and macros.
*   `MAX_INGREDIENTS`: The maximum number of ingredients the inventory can track.
*   `MAX_MENU_ITEMS`: The maximum number of products in the bakery menu.
*   `PASSWORD`: The default administrative password (`bakery123`).

#### `inventory.c` / `inventory.h`
Manages the raw materials (ingredients) required for the bakery.
*   **Data Structure:** `Ingredient` struct (Name, Quantity, Threshold).
*   **Key Functions:** `showInventory()`, `addIngredient()`, `restockInventory()`.
*   **Thresholds:** Used to alert the user when an ingredient falls below a certain quantity.

#### `menu.c` / `menu.h`
Handles the bakery's product list.
*   **Data Structure:** `MenuItem` struct (Name, Quantity/Stock, Price).
*   **Key Functions:** `showMenuItems()`, `addMenuItem()`, `restockMenu()`.

#### `cart.c` / `cart.h`
The "Point of Sale" logic for the bakery.
*   **Data Structure:** `Cart` struct (an array mapping menu item counts).
*   **Key Functions:** `BuyItem()`, `AddToCart()`, `RemoveFromCart()`, `DetermineTotalPrice()`.
*   **Business Logic:** Calculates the cumulative price of all items currently in the cart.

## Data Flow & State Management

The system maintains a global state for simplicity, with external variables defined in the headers and instantiated in the source files (e.g., `sInventory`, `sMenu`, `sCart`).
1.  **Selection:** User selects items from the `menuMenu()`.
2.  **Cart Mutation:** Items are added to the `sCart` via `AddToCart()`.
3.  **Checkout:** `BuyItem()` triggers the checkout process, which uses `DetermineTotalPrice()` to calculate the final amount.

## Developer Guidelines

*   **Modularization:** When adding a new major feature, create a new header/source pair and register its menu entry in `main.c`.
*   **Global Access:** Be cautious when modifying global arrays like `sInventory` to avoid race conditions (though not a current concern in this single-threaded CLI).
*   **Documentation:** Follow the [Style Guide](../doc/style_guide.md) for naming conventions and commenting.
