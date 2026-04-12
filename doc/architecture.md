# Architecture Documentation

The Bakery Management System is built using a modular architecture to ensure scalability and ease of maintenance.

## System Architecture: Modular Design

The codebase is split into several logical modules, each responsible for a distinct part of the application:

### 1. `main.c`
- Program entry point and top-level user interface.
- Orchestrates between other modules.

### 2. `inventory.h / inventory.c`
- Data structures: `Ingredient`
- Logic: Functions for managing ingredients (adding, restocking, and viewing).

### 3. `menu.h / menu.c`
- Data structures: `MenuItem`
- Logic: Functions for managing the bakery's sale items.

### 4. `cart.h / cart.c`
- Data structures: `Cart`
- Logic: Functions for managing the customer's shopping cart (adding/removing items and calculating totals).

### 5. `common.h`
- Shared global constants and configurations (e.g., `MAX_INGREDIENTS`, `MAX_MENU_ITEMS`, `PASSWORD`).

## Data Structures
- **Ingredient**: `{char name[30], int quantity, int threshold}`
- **MenuItem**: `{char name[30], int quantity, float price}`
- **Cart**: `{int items[MAX_MENU_ITEMS]}` (An array mapping menu item indices to quantities).

## Component Diagram (Conceptual)
`Main` --> `Inventory`
`Main` --> `Menu`
`Main` --> `Cart`
`Cart` --> `Menu` (for price/name lookups)
