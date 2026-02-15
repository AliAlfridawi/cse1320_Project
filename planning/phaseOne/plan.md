# Project Clarity: Phase 1 Architecture & Implementation Plan

**Project Name:** Clarity  
**Description:** A terminal-based Inventory Management System (IMS) for small restaurants.  
**Tech Stack:** C (Standard C99/C11), MySQL.  
**Target:** MVP (Minimum Viable Product) - A robust, crash-resistant command-line tool.

---

## 1. High-Level Overview

**The Goal:**
To build a highly efficient, text-based inventory system that allows restaurant owners to track ingredients, monitor costs, and receive automatic alerts when stock is low.

**The Design Philosophy:**
We are using a **3-Layer Architecture** to decouple the user interface from the data logic. This ensures the code is modular, testable, and "impressive" from a systems engineering standpoint, differentiating it from standard student projects that put everything in `main.c`.

---

## 2. System Architecture

The application is divided into three distinct layers:

1.  **Presentation Layer (UI):** Handles all `printf` and `scanf`. It knows *how* to display data but not *how* to calculate or store it.
2.  **Logic Layer (Controller):** The "Brain." It validates input (e.g., ensuring price > 0), performs calculations, and decides when to trigger alerts.
3.  **Data Layer (DAO - Data Access Object):** The only layer that speaks to MySQL. It executes queries and returns raw data to the Logic Layer.

### Directory Structure
Create this exact folder structure to keep the project organized.

```text
Clarity/
├── Makefile              # Build script (Links MySQL library)
├── README.md             # Project documentation
├── bin/                  # Stores the compiled executable (e.g., clarity.exe)
├── sql/                  # Database scripts
│   └── schema.sql        # The SQL commands to create tables
├── include/              # Header files (.h) - Function Prototypes & Structs
│   ├── db_manager.h      # Database connection functions
│   ├── inventory.h       # Core business logic
│   ├── auth.h            # Login/User management
│   ├── ui.h              # Menu display & table formatting
│   └── utils.h           # Input sanitization helpers
└── src/                  # Source files (.c) - Implementation
    ├── main.c            # The Main Loop (Entry Point)
    ├── db_manager.c      # MySQL specific code
    ├── inventory.c       # Logic for adding/editing items
    ├── auth.c            # Logic for authentication
    ├── ui.c              # Printing menus and tables
    └── utils.c           # Safe input handling