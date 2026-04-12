# Bakery Management System 

A robust, CLI-based management tool developed in C for the CSE 1320 course. This system streamlines the operations of a bakery by integrating inventory tracking, menu management, and a simplified point-of-sale interface.

## Key Features

*   **Secure Access:** Simple login system to protect administrative functions (Default Password: `bakery123`).
*   **Inventory Control:** Track ingredient levels with custom thresholds and easy restocking capabilities.
*   **Menu Management:** Define bakery items with pricing and quantities.
*   **Shopping Cart:** A functional cart system that allows adding/removing items and calculates the total price for customer orders.

## Getting Started

### Prerequisites

*   **GCC:** The GNU Compiler Collection.
*   **Make:** A build automation tool (standard on Linux/macOS, available via MinGW/Cygwin on Windows).

### Build Instructions

1.  Open your terminal or command prompt in the project root.
2.  Run the `make` command:
    ```bash
    make
    ```
3.  This will create an `obj/` directory for object files and compile the executable named `bakery_system`.

### Running the Application

Execute the compiled binary:
```bash
./bakery_system
```

## Project Structure

*   `src/`: Contains the C source code and header files. See [src/README.md](./src/README.md) for architectural details.
*   `doc/`: Comprehensive project documentation including architecture, test plans, and style guides.
*   `Makefile`: Automated build script for the project.

## Documentation Links

For more in-depth information, please refer to the files in the `doc/` directory:
*   [System Architecture](./doc/architecture.md)
*   [Interface Definitions](./doc/interfaces.md)
*   [Testing Plan](./doc/test_plan.md)
*   [Coding Style Guide](./doc/style_guide.md)
*   [Product Backlog](./doc/product_backlog.md)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
