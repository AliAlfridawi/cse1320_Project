# Implementation Plan: db_manager.c

---
**Authors:** Ali Alfridawi & Gemini (AI Assistant)  
**Purpose:** Provide clear, modular, and educational implementation guidance for the `db_manager.c` source file, focusing on SQLite database interaction and data persistence for freshman programmers.
---

## 1. Description
The `db_manager.c` file is the **Data Layer** of the Clarity application. Its primary responsibility is to interact with the SQLite database, execute SQL commands, and return data to the business logic layer.

## 2. High-Level Logic
1.  **Connection Management:** Open and close a connection to the SQLite database file (`clarity.db`).
2.  **Database Initialization:** Create the inventory and user tables if they don't already exist.
3.  **Statement Execution:** Execute common SQL operations: `INSERT`, `UPDATE`, `DELETE`, and `SELECT`.
4.  **Error Handling:** Check for SQLite error codes and report them to the calling function.

## 3. Pseudo-code
```text
FUNCTION db_initialize():
    // 1. Open the SQLite database
    IF sqlite3_open("clarity.db") != SQLITE_OK:
        PRINT "Error: Could not open database."
        RETURN ERROR

    // 2. Create tables if they don't exist
    sql_query = "CREATE TABLE IF NOT EXISTS inventory (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT NOT NULL,
                    quantity REAL NOT NULL,
                    price REAL NOT NULL,
                    alert_level REAL
                );"
    IF db_execute_query(sql_query) != SUCCESS:
        PRINT "Error: Could not create tables."
        RETURN ERROR

    PRINT "Database initialized."
    RETURN SUCCESS

FUNCTION db_execute_query(sql_command):
    // 1. Prepare the SQL statement
    // 2. Execute the statement
    // 3. Finalize/Close the statement
    RETURN result

FUNCTION db_fetch_all_inventory():
    // 1. Prepare "SELECT * FROM inventory"
    // 2. Loop through the rows returned by SQLite
    // 3. Store the rows in an array of Inventory structs
    // 4. Return the array to the inventory layer
```

## 4. Key Concepts for Freshmen
-   **Pointers:** SQLite functions use pointers to store references to the database (`sqlite3*`) and the results (`sqlite3_stmt*`).
-   **Error Codes:** Always check the return values of `sqlite3_open`, `sqlite3_prepare_v2`, and `sqlite3_step`.
-   **Structured Data:** Use a `struct` to group related fields (like name, quantity, and price) when passing data between the database and the logic layer.

## 5. Cites & Resources
-   **SQLite Official Docs:** [SQLite C Interface Introduction](https://www.sqlite.org/cintro.html)
-   **GeeksforGeeks:** [SQLite with C/C++](https://www.geeksforgeeks.org/sql-using-c-c-and-sqlite/)
-   **Book:** *C Programming: A Modern Approach* by K.N. King - Chapter 17 (Dynamic Memory Allocation & Structs).
-   **Book:** *The C Programming Language* (K&R) - Chapter 5 (Pointers and Arrays).
