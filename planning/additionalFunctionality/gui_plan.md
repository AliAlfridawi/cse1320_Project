# Detailed Plan for C-Based GUI Implementation

---
**Authors:** Ali Alfridawi & Gemini (AI Assistant)  
**Purpose:** Explore future development plans for upgrading the Clarity Inventory Management System with a Graphical User Interface to improve usability and visual appeal.
---

## 1. Objective
To build a user-friendly and feature-rich Graphical User Interface (GUI) for the Inventory Management System **using only the C language and C-compatible libraries**. This plan replaces the original terminal-based presentation layer with a full graphical interface, including data visualization.

## 2. Technology Stack
- **Language:** C (Standard C99/C11)
- **GUI Toolkit:** **GTK+ 3** - A stable, cross-platform, and widely-used GUI library for C.
- **Graphics Library:** **Cairo** (integrated with GTK+) - For drawing 2D graphics, which we will use to create custom charts and graphs.
- **Database Backend:** MySQL (using the existing C connector and Data Layer).

## 3. Architectural Integration
This GUI will directly replace the `Presentation Layer (ui.c, ui.h)` from the original architecture.

- **`gui.c` / `gui.h`:** New files that will contain all GTK+ widget creation, layout, and signal handling.
- **Logic & Data Layers:** Remain unchanged. The GUI's event handlers (e.g., a "Save" button click) will call the existing functions in `inventory.c` and `auth.c` to perform business logic and database operations. This maintains our clean 3-layer architecture.

---

## 4. Key Features & Step-by-Step Implementation Plan

### Feature 1: Main Dashboard
A central window providing at-a-glance information and navigation.

- **Implementation Steps:**
    1.  Use a `GtkWindow` as the main container.
    2.  Use a `GtkGrid` to structure the layout.
    3.  **Info Panels:** Use `GtkFrame` and `GtkLabel` widgets to display key metrics.
        -   *How-to:* Create a function `update_dashboard_metrics()` that calls logic functions (e.g., `get_total_item_count()`, `get_low_stock_item_count()`) and updates the label text using `gtk_label_set_text()`.
    4.  **Navigation:** Add `GtkButton` widgets for "View Full Inventory," "Add New Item," and "View Analytics."
        -   *How-to:* Connect the `"clicked"` signal of each button to a callback function that opens the corresponding window (e.g., `on_view_inventory_clicked()`).

### Feature 2: Scrollable Inventory Table
A detailed, sortable view of all items in the inventory.

- **Implementation Steps:**
    1.  Create a new `GtkWindow` for this view.
    2.  Use a `GtkTreeView` widget to display the data.
    3.  Define the data model using `GtkListStore`. This will define the columns (e.g., ID, Name, Quantity, Price).
    4.  Create a function `populate_inventory_table()` that:
        -   Fetches all items from the database via the Data Layer.
        -   Loops through the results and adds each item as a new row to the `GtkListStore` using `gtk_list_store_append()`.
    5.  **Sorting:** Enable sorting by setting `gtk_tree_view_column_set_sort_column_id()` for each column header.

### Feature 3: Data Entry & Query Forms
User-friendly forms for adding, editing, and searching for items.

- **Implementation Steps:**
    1.  For the "Add Item" form, create a `GtkDialog` window.
    2.  Use `GtkEntry` for text fields (Name), `GtkSpinButton` for numeric fields (Quantity, Price), and `GtkLabel`s for field descriptions.
    3.  Add "Save" and "Cancel" buttons (`GtkButton`).
    4.  **Input Validation:** The "Save" button's callback function will first retrieve data from the input widgets (`gtk_entry_get_text()`). It will then call validation functions in your logic layer (e.g., `is_price_valid()`).
    5.  **Saving Data:** If validation passes, the callback will call the existing `add_inventory_item()` function from your logic layer and close the dialog. If it fails, display a `GtkMessageDialog` with the error.

### Feature 4: Graphical Data Visualization
A dedicated analytics view to display graphs.

- **Example Graph:** Bar chart of the 5 items with the lowest stock.
- **Implementation Steps:**
    1.  Create a new `GtkWindow` for "Analytics".
    2.  Add a `GtkDrawingArea` widget to this window. This widget provides a blank canvas to draw on.
    3.  Connect a callback function (e.g., `on_draw_event`) to the `"draw"` signal of the `GtkDrawingArea`. This function will be given a `cairo_t` drawing context.
    4.  **Inside the `on_draw_event` callback:**
        a. **Fetch Data:** Call a logic layer function like `get_lowest_stock_items(5)` to get the data to be graphed.
        b. **Set Colors & Fonts:** Use `cairo_set_source_rgb()` to set colors and `cairo_select_font_face()` for fonts.
        c. **Draw Axes:** Use `cairo_move_to()` and `cairo_line_to()` to draw the X and Y axes.
        d. **Draw Labels:** Use `cairo_show_text()` to write axis labels (e.g., "Item Name," "Quantity") and a title for the graph.
        e. **Draw Bars:** Loop through your data. For each item, calculate the bar's height and position relative to the drawing area's size. Draw the rectangle using `cairo_rectangle()` and fill it using `cairo_fill()`.
    5.  To update the graph, simply call `gtk_widget_queue_draw()` on the drawing area, which will trigger a new "draw" event.

---

## 5. Development Roadmap
1.  **Setup:** Install GTK+ 3 development libraries (`libgtk-3-dev` on Debian/Ubuntu). Update your `Makefile` to link against GTK+.
    -   *Makefile flags:* `gcc $(...) -o $(...) $(...) \`pkg-config --cflags --libs gtk+-3.0\``
2.  **Bootstrap:** Create a `gui_main.c` file. Initialize GTK+ (`gtk_init()`) and display a basic, empty `GtkWindow`.
3.  **Build Dashboard:** Implement the main dashboard layout with static (non-functional) buttons and labels.
4.  **Implement Read-Only View:** Wire up the "View Full Inventory" button to open a new window and display the `GtkTreeView` populated with real data from your database.
5.  **Implement Write Functionality:** Build the "Add Item" dialog and connect its "Save" button to your data layer. Ensure the main inventory view refreshes after an item is added.
6.  **Prototype Graph:** Create the analytics window with a `GtkDrawingArea` and implement the drawing callback to render a **static, hard-coded** bar chart. This isolates the graphics programming.
7.  **Dynamic Graph:** Connect the graphing function to the database to draw the chart using real, dynamic data.
8.  **Final Polish:** Add `GtkMessageDialog`s for error and confirmation messages, refine widget spacing and layout, and perform thorough testing.
