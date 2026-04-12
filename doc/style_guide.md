# CSE 1320 Bakery Management System Style Guide

This document outlines the coding standards for the Bakery Management System project to ensure consistency across the codebase.

## Indentation and Formatting
- **Indentation:** Use 4 spaces per indentation level. Do not use tabs.
- **Line Length:** Try to keep lines within 80-100 characters.
- **Braces:** Use K&R style braces (opening brace on the same line as the statement).
    ```c
    void function() {
        if (condition) {
            // code
        }
    }
    ```

## Naming Conventions
- **Macros/Constants:** Use `ALL_CAPS` with underscores.
    - Example: `#define MAX_INGREDIENTS 20`
- **Structs:** Use `PascalCase` with typedefs.
    - Example: `typedef struct MenuItem { ... } MenuItem;`
- **Global Variables:** Use `camelCase` with an `s` prefix to indicate static/global state.
    - Example: `Ingredient sInventory[MAX_INGREDIENTS];`
- **Functions:** Use `camelCase` as the standard for all functions.
    - Example: `showInventory()`, `mainMenu()`, `inventoryMenu()`
    - *Legacy PascalCase functions (e.g., `BuyItem`) were retained for compatibility with the final prototype.*
- **Local Variables:** Use `camelCase`.
    - Example: `int choice;`, `float total;`

## Comments and Documentation
- Use `//` for single-line comments.
- Use `/* ... */` for multi-line comments.
- Use section headers to group related functions within files.

## Best Practices
- Initialize variables upon declaration.
- Rigorously check bounds for all static arrays.
- Use descriptive variable names (e.g., `inventoryCount` instead of `ic`).
