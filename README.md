# Bakery Management System

A simple command-line bakery manager written in C for CSE 1320. The program
keeps track of ingredient inventory, bakery menu items, and a customer cart.
It also saves data between runs using text files.

## Features

- Password-protected login
- Inventory tracking with restock thresholds
- Menu item management with quantity and price
- Shopping cart with add, remove, and checkout
- Automatic saving to `inventory.txt`, `menu.txt`, and `cart.txt`
- Multi-file source layout that is easier to read and maintain

## Project Layout

- `src/` - C source and header files
- `obj/` - object files created during build
- `Makefile` - build commands
- `inventory.txt` - saved ingredient data
- `menu.txt` - saved bakery menu data
- `cart.txt` - saved cart data

See [src/README.md](./src/README.md) for the source code breakdown.

## Build

### Windows with MSYS2 / MinGW

If `mingw32-make.exe` is installed, run:

```powershell
C:\msys64\ucrt64\bin\mingw32-make.exe
```

### Systems with `make`

If your environment already has `make`, run:

```bash
make
```

## Common Make Targets

- Build the program:

```bash
make
```

- Run the program after building:

```bash
make run
```

- Delete build files:

```bash
make clean
```

- Rebuild from scratch:

```bash
make rebuild
```

On this Windows setup, replace `make` with
`C:\msys64\ucrt64\bin\mingw32-make.exe`.

## Run

After building, run:

```powershell
.\bakery_system.exe
```

Default password:

```text
bakery123
```

## Data Files

The program stores its data in text files in the project root:

- `inventory.txt` uses `name,quantity,threshold`
- `menu.txt` uses `name,quantity,price`
- `cart.txt` stores one cart quantity per line

If a file is missing, the program starts with empty data for that section.
If a file contains bad data, the program prints a warning and keeps running.

## Notes

- Item names are currently read with `scanf("%s", ...)`, so names should be
  single words like `Bread` or `Croissant`.
- The checkout flow clears the cart and returns to the main menu.
- The code is intentionally straightforward and beginner-friendly.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE).
