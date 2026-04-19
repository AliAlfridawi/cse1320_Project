# System Architecture

The Bakery Management System is designed with a modular, layered architecture to ensure a clear separation of concerns, scalability, and ease of maintenance.

## Architecture Overview

The system follows a three-tier design pattern:

1.  **Presentation/Orchestration Layer**: Represented by `main.c`, which handles the primary user interface loop, input processing, and high-level logic flow.
2.  **Service/Logic Layer**: Contains the core business logic, including `inventory.c` (ingredient management), `menu.c` (bakery item management), and `cart.c` (session-based shopping cart).
3.  **Persistence Layer**: Represented by `storage.c`, which manages the loading and saving of system state to flat-file databases (`inventory.txt`, `menu.txt`).

## Architecture Diagram

```mermaid
graph TD
    subgraph UI_Layer [Presentation & Orchestration]
        Main[Main Module (main.c)]
    end
    
    subgraph Logic_Layer [Core Business Logic]
        Inventory[Inventory Module (inventory.c)]
        Menu[Menu Module (menu.c)]
        Cart[Cart Module (cart.c)]
    end
    
    subgraph Persistence_Layer [Persistence & Data]
        Storage[Storage Module (storage.c)]
        InvFile[(inventory.txt)]
        MenuFile[(menu.txt)]
    end
    
    %% Relationships
    Main --> Inventory
    Main --> Menu
    Main --> Cart
    Main --> Storage
    
    Cart --> Menu
    Storage --> Inventory
    Storage --> Menu
    Storage --> InvFile
    Storage --> MenuFile
    
    %% Styling
    style Main fill:#f9f,stroke:#333,stroke-width:2px
    style Inventory fill:#bbf,stroke:#333,stroke-width:1px
    style Menu fill:#bbf,stroke:#333,stroke-width:1px
    style Cart fill:#bbf,stroke:#333,stroke-width:1px
    style Storage fill:#dfd,stroke:#333,stroke-width:1px
```

## Component Descriptions

### 1. Main Orchestrator (`main.c`)
The entry point of the application. It provides the top-level menu interface and delegates user requests to the appropriate logic modules. It ensures the correct sequence of operations, such as loading data before the main loop and saving data upon exit.

### 2. Inventory Management (`inventory.c`)
Responsible for managing the bakery's raw ingredients. It tracks current stock levels and alerts the user when an ingredient falls below its predefined threshold. It uses the `Ingredient` data structure.

### 3. Menu Management (`menu.c`)
Manages the list of items available for sale. This module handles item quantities and pricing, ensuring that customers can only purchase items that are currently in stock.

### 4. Shopping Cart (`cart.c`)
Manages a customer's active shopping session. It tracks selected items and quantities, and calculates the total price. It interacts with the `Menu` module to retrieve item details and update stock levels after a transaction.

### 5. Storage / Data Access (`storage.c`)
Handles the persistence of system data. It reads from and writes to `inventory.txt` and `menu.txt`. This module abstracts file I/O operations from the rest of the logic modules.

### 6. Common Utilities (`common.h`)
A shared header file that defines system-wide constants, limits (e.g., `MAX_INGREDIENTS`), and common configurations used across all modules.
