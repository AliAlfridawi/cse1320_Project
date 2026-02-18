# Implementation Plan: auth.c

---
**Authors:** Ali Alfridawi & Gemini (AI Assistant)  
**Purpose:** Provide clear, modular, and educational implementation guidance for the `auth.c` source file, focusing on user login and session security logic for freshman programmers.
---

## 1. Description
The `auth.c` file is the **Security Logic Layer** for Clarity. Its primary responsibility is to verify user credentials and ensure that only authorized personnel can access the inventory management system.

## 2. High-Level Logic
1.  **Login Attempt:** Ask the user for their username and password.
2.  **Verification:** Compare the provided credentials with the stored records in the database.
3.  **Session Management:** Keep track of whether a user is currently logged in (and who they are).
4.  **Logging Out:** Safely clear any logged-in session data when the user chooses to exit.

## 3. Pseudo-code
```text
FUNCTION auth_attempt_login():
    // 1. Get username and password from the UI module
    username = ui_get_string("Username: ")
    password = ui_get_string("Password: ")

    // 2. Fetch the user's stored password from the database (via db_manager)
    stored_password = db_get_user_password(username)

    // 3. Compare the provided password with the stored one
    IF stored_password == NULL:
        ui_show_error("User does not exist!")
        RETURN ERROR

    IF password == stored_password:
        is_logged_in = TRUE
        current_user = username
        ui_show_success("Login Successful! Welcome, " + username)
        RETURN SUCCESS
    ELSE:
        ui_show_error("Incorrect Password!")
        RETURN ERROR

FUNCTION auth_logout():
    // 1. Clear session variables
    is_logged_in = FALSE
    current_user = ""
    ui_show_success("Logged out successfully.")
```

## 4. Key Concepts for Freshmen
-   **String Comparison:** Use `strcmp()` from `<string.h>` to compare the username and password strings.
-   **Static Variables:** You can use a `static` global variable in `auth.c` to keep track of the `is_logged_in` state (so it’s not accessible outside of `auth.c`).
-   **Hashing (Optional):** In a professional system, passwords are never stored in "plain text." For this project, you can keep it simple, but research "password hashing" to understand how it's done in the real world.

## 5. Cites & Resources
-   **GeeksforGeeks:** [String functions in C](https://www.geeksforgeeks.org/string-functions-in-c/)
-   **GeeksforGeeks:** [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)
-   **Book:** *C Programming: A Modern Approach* by K.N. King - Chapter 13 (Strings).
-   **Book:** *The C Programming Language* (K&R) - Chapter 5 (Pointers and Arrays, Section 5.5: Character Pointers and Functions).
