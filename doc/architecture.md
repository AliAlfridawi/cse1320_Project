# Architecture Documentation

## Current State: Monolithic Structure
Currently, all logic is contained within `project_1320.c`. This includes:
- UI / Menu handling
- Inventory management
- Menu item management
- Shopping cart logic
- Data structures

## Target Architecture: Modular Design
To improve maintainability and scalability, the project will be refactored into the following modules:

### 1. `main.c`
- Entry point of the application.
- Top-level menu loop.
- Orchestrates between other modules.

### 2. `inventory.h / inventory.c`
- Data structures: `Ingredient`
- Logic: Adding, restocking, and viewing raw ingredients.

### 3. `menu.h / menu.c`
- Data structures: `MenuItem`
- Logic: Managing the bakery's sale items.

### 4. `cart.h / cart.c`
- Data structures: `Cart`
- Logic: Adding/removing items from the cart, calculating totals.

## Data Structures
- **Ingredient**: `{char name[30], int quantity, int threshold}`
- **MenuItem**: `{char name[30], int quantity, float price}`
- **Cart**: `{int items[MAX_MENU_ITEMS]}` (An array mapping menu item indices to quantities).

## Component Diagram (Conceptual)
`Main` --> `Inventory`
`Main` --> `Menu`
`Main` --> `Cart`
`Cart` --> `Menu` (for price/name lookups)
