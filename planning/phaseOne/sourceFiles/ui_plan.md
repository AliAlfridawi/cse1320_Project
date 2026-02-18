# Implementation Plan: ui.c

---
**Authors:** Ali Alfridawi & Gemini (AI Assistant)  
**Purpose:** Provide clear, modular, and educational implementation guidance for the `ui.c` source file, focusing on terminal output and user interface formatting for freshman programmers.
---

## 1. Description
The `ui.c` file is the **Presentation Layer** for Clarity. Its primary responsibility is to handle all terminal interactions—displaying menus, rendering tables, and showing alerts or errors. It communicates with the logic layer to get the data it needs but doesn't perform calculations or database queries.

## 2. High-Level Logic
1.  **Menu Display:** Use `printf` to draw organized, easy-to-read menus for the user.
2.  **Table Rendering:** Use formatted `printf` (e.g., `%20s` or `%-10.2f`) to create a neat table of inventory items.
3.  **Input Handling:** Get user choices (integers for menus) and strings (for item names). Use helper functions from `utils.c` to make this safe.
4.  **Formatting:** Use colors or separators (`---------`) to make the CLI look professional.

## 3. Pseudo-code
```text
FUNCTION ui_display_main_menu():
    // 1. Print the header
    PRINT "------------------------------------"
    PRINT "      CLARITY - INVENTORY SYSTEM     "
    PRINT "------------------------------------"

    // 2. Print menu options
    PRINT "1. View All Inventory"
    PRINT "2. Add New Item"
    PRINT "3. Edit Existing Item"
    PRINT "4. View Stock Alerts"
    PRINT "5. Exit"

    // 3. Prompt the user for their choice
    PRINT "Please select an option (1-5): "
    choice = utils_get_int_input()

    RETURN choice

FUNCTION ui_render_inventory_table(items_list):
    // 1. Print the table headers
    PRINT "ID    | Item Name           | Qty   | Price | Total Value"
    PRINT "---------------------------------------------------------"

    // 2. Loop through the list of items
    FOR EACH item IN items_list:
        total_val = item.quantity * item.price
        PRINT FORMATTED(item.id, item.name, item.quantity, item.price, total_val)

    PRINT "---------------------------------------------------------"
```

## 4. Key Concepts for Freshmen
-   **Formatted `printf`:** Use format specifiers like `%-15s` (left-aligned string with 15 characters of padding) to keep columns straight in a table.
-   **Separation of Logic and UI:** Don't put any SQL queries or calculations (like total value) inside `ui.c`. Let the Logic Layer (`inventory.c`) or Data Layer (`db_manager.c`) handle that and just pass the result to `ui.c` for printing.

## 5. Cites & Resources
-   **GeeksforGeeks:** [Formatted I/O in C](https://www.geeksforgeeks.org/formatted-input-output-c/)
-   **GeeksforGeeks:** [Printf and Scanf](https://www.geeksforgeeks.org/printf-and-scanf-in-c/)
-   **Book:** *C Programming: A Modern Approach* by K.N. King - Chapter 22 (Input/Output).
-   **Book:** *The C Programming Language* (K&R) - Chapter 7 (Input and Output).
