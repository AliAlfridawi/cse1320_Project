# Implementation Plan: inventory.c

---
**Authors:** Ali Alfridawi & Gemini (AI Assistant)  
**Purpose:** Provide clear, modular, and educational implementation guidance for the `inventory.c` source file, focusing on core business logic and stock management for freshman programmers.
---

## 1. Description
The `inventory.c` file is the **Logic Layer** (the "Brain") of the Clarity application. Its primary responsibility is to handle the business logic for managing inventory items, calculating costs, and validating user input before it reaches the database.

## 2. High-Level Logic
1.  **Item Management:** Define logic to add, edit, or delete items from the inventory.
2.  **Validation:** Ensure quantities are positive, prices are greater than zero, and item names are not empty.
3.  **Stock Monitoring:** Identify which items are below their "alert level" and trigger an alert to the user.
4.  **Calculations:** Calculate the total value of all stock in the inventory (Quantity * Unit Price).

## 3. Pseudo-code
```text
FUNCTION inventory_handle_add_item():
    // 1. Prompt the user for item details (via UI functions)
    item_name = ui_get_string("Enter Item Name:")
    item_qty = ui_get_float("Enter Quantity:")
    item_price = ui_get_float("Enter Price per Unit:")
    item_alert = ui_get_float("Enter Alert Level (Minimum Stock):")

    // 2. Validate the data (Logic Layer's job)
    IF item_qty < 0 OR item_price < 0:
        ui_show_error("Quantity and Price must be positive!")
        RETURN ERROR

    IF item_name IS empty:
        ui_show_error("Item name cannot be empty.")
        RETURN ERROR

    // 3. Call the Data Layer to save the item
    result = db_insert_inventory_item(item_name, item_qty, item_price, item_alert)
    IF result == SUCCESS:
        ui_show_success("Item added successfully!")
    ELSE:
        ui_show_error("Failed to add item to the database.")

FUNCTION inventory_check_stock_alerts():
    // 1. Fetch all items from the database (via Data Layer)
    items_list = db_fetch_all_inventory()

    // 2. Loop through each item and check stock levels
    FOR EACH item IN items_list:
        IF item.quantity <= item.alert_level:
            ui_show_alert("LOW STOCK: " + item.name + " (" + item.quantity + " remaining)")
```

## 4. Key Concepts for Freshmen
-   **Separation of Concerns:** Notice that `inventory.c` doesn't use `printf` directly. It calls `ui_show_error` or `ui_show_success` so the logic stays separate from how it's displayed.
-   **Conditional Logic:** Using `if/else` statements to validate user input.
-   **Structs:** Passing an `InventoryItem` struct between functions instead of four individual variables.

## 5. Cites & Resources
-   **GeeksforGeeks:** [Decision Making in C (if...else)](https://www.geeksforgeeks.org/decision-making-c-if-else-nested-if/)
-   **GeeksforGeeks:** [C Structures (Structs)](https://www.geeksforgeeks.org/structures-c/)
-   **Book:** *C Programming: A Modern Approach* by K.N. King - Chapter 16 (Structures, Unions, and Enumerations).
-   **Book:** *The C Programming Language* (K&R) - Chapter 6 (Structures).
