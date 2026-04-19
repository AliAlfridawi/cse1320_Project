# Source Code Architecture & Developer Guide

This directory contains the C source code for the Bakery Management System.
The program is split into small modules so each part of the bakery logic has
its own file.

## Module Breakdown

- `main.c`: Login, startup, shutdown, and the main menu.
- `common.h`: Shared constants used across the project.
- `inventory.c` / `inventory.h`: Ingredient storage and inventory menu logic.
- `menu.c` / `menu.h`: Bakery menu items and menu management logic.
- `cart.c` / `cart.h`: Shopping cart logic and checkout flow.
- `storage.c` / `storage.h`: Loading and saving data in text files.

## Data Files

- `inventory.txt`: `name,quantity,threshold`
- `menu.txt`: `name,quantity,price`
- `cart.txt`: one cart quantity per line

## Notes

- The project uses simple global arrays to keep the code easy to follow.
- Data is loaded when the program starts and saved whenever the data changes.
- Checkout clears the cart and returns the user to the main menu.
