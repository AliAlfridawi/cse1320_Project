# Implementation Plan: main.c

---
**Authors:** Ali Alfridawi & Gemini (AI Assistant)  
**Purpose:** Provide clear, modular, and educational implementation guidance for the `main.c` source file, focusing on the application's entry point and lifecycle management for freshman programmers.
---

## 1. Description
The `main.c` file is the **Entry Point** of the Clarity application. Its primary responsibility is to manage the application's lifecycle, which includes initializing the database, handling user authentication, and running the main menu loop.

## 2. High-Level Logic
1.  **Initialization:** Call the database manager to ensure the SQLite database and necessary tables exist.
2.  **Authentication:** Call the authentication module to verify the user. If login fails, the program should terminate.
3.  **Main Loop:** Once logged in, enter a loop that:
    - Calls the UI module to display the main menu.
    - Captures the user's choice.
    - Routes that choice to the appropriate function (e.g., Add Item, View Inventory).
    - Continues until the user selects "Exit."
4.  **Cleanup:** Close any open database connections and gracefully exit the program.

## 3. Pseudo-code
```text
FUNCTION main():
    // 1. Initialize Database
    IF db_initialize() != SUCCESS:
        PRINT "Error: Could not initialize database."
        RETURN 1

    // 2. User Authentication
    WHILE NOT auth_is_logged_in():
        user_choice = ui_show_login_prompt()
        IF user_choice == "Exit":
            db_close()
            RETURN 0
        auth_attempt_login()

    // 3. Main Application Loop
    WHILE app_running:
        choice = ui_display_main_menu()
        
        SWITCH choice:
            CASE "Add Item":
                inventory_handle_add_item()
            CASE "View Inventory":
                inventory_handle_view_all()
            CASE "Generate Reports":
                inventory_handle_reports()
            CASE "Exit":
                app_running = FALSE
            DEFAULT:
                ui_show_error("Invalid Choice")

    // 4. Cleanup
    db_close()
    PRINT "Goodbye!"
    RETURN 0
```

## 4. Key Concepts for Freshmen
-   **The `main` function:** Every C program starts here.
-   **Header Guards:** Ensure you include `ui.h`, `db_manager.h`, `auth.h`, and `inventory.h` correctly.
-   **Return Codes:** Returning `0` usually means success, while non-zero values indicate an error.

## 5. Cites & Resources
-   **GeeksforGeeks:** [C main() function](https://www.geeksforgeeks.org/main-function-in-c/)
-   **Book:** *C Programming: A Modern Approach* by K.N. King - Chapter 2 (C Fundamentals).
-   **Book:** *The C Programming Language* (K&R) - Section 1.1 (Getting Started).
