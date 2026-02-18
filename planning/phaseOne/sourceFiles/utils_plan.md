# Implementation Plan: utils.c

---
**Authors:** Ali Alfridawi & Gemini (AI Assistant)  
**Purpose:** Provide clear, modular, and educational implementation guidance for the `utils.c` source file, focusing on safe input handling and data sanitization for freshman programmers.
---

## 1. Description
The `utils.c` file provides **Safe Utility Functions** for the Clarity application. Its primary responsibility is to handle input sanitization and common helper tasks. This prevents common C bugs like buffer overflows and crashes caused by unexpected user input (like typing a letter where a number is expected).

## 2. High-Level Logic
1.  **Numeric Input Sanitization:** Safely read an integer or float from the user. If the user enters a character, clear the input buffer and ask again.
2.  **String Input Sanitization:** Safely read a string (like an item name) while avoiding buffer overflows using `fgets()`.
3.  **Buffer Clearing:** Remove leftover characters (like the newline `
`) from the input stream (`stdin`) so they don't mess up the next `scanf`.

## 3. Pseudo-code
```text
FUNCTION utils_get_int_input():
    // 1. Read input from the user (e.g., scanf("%d", &num))
    IF scanf() succeeds:
        // 2. Clear any leftover characters (like the 
)
        WHILE (getchar() != '
');
        RETURN num
    ELSE:
        // 3. If it fails (e.g., user typed a letter), clear the buffer
        WHILE (getchar() != '
');
        PRINT "Invalid input! Please enter a number."
        RETURN ERROR

FUNCTION utils_get_string_input(buffer, size):
    // 1. Use fgets() to read a line from stdin (up to 'size' characters)
    IF fgets(buffer, size, stdin) != NULL:
        // 2. Remove the trailing newline character that fgets() captures
        len = strlen(buffer)
        IF buffer[len-1] == '
':
            buffer[len-1] = '\0'
        RETURN SUCCESS
    ELSE:
        RETURN ERROR

FUNCTION utils_clear_buffer():
    // 1. Loop through the input buffer until the newline or EOF
    WHILE (getchar() != '
');
```

## 4. Key Concepts for Freshmen
-   **Buffer Overflow:** If you use `scanf("%s", buffer)`, the user can type more than the buffer can hold, which might crash the program or create a security vulnerability. Using `fgets()` is much safer.
-   **Cleaning `stdin`:** When you press "Enter" after a `scanf`, the newline character `
` stays in the keyboard buffer. If you don't clear it, the *next* `scanf` or `fgets` might skip over it and capture that `
` instead of what the user types.

## 5. Cites & Resources
-   **GeeksforGeeks:** [fgets() and gets() in C](https://www.geeksforgeeks.org/fgets-gets-c-language/)
-   **GeeksforGeeks:** [Clearing the input buffer in C](https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/)
-   **Book:** *C Programming: A Modern Approach* by K.N. King - Chapter 13 (Strings, Section 13.3: Reading Strings).
-   **Book:** *The C Programming Language* (K&R) - Chapter 1 (Introduction, Section 1.5: Character Input and Output).
