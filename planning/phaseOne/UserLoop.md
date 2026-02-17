# User Loop & UI Flow Plan

## 1. Objective
This document outlines the primary user loop for the C-based GTK+ application. The flow is designed to be simple, efficient, and focused on the core daily tasks of a restaurant owner: quickly identifying low-stock items and updating inventory levels. Complex features like analytics and the chatbot are excluded from this primary loop for clarity and focus.

## 2. Guiding Principle
The application should immediately present the most urgent information to the user upon launch, requiring the fewest clicks possible to perform the most common actions.

## 3. The Primary User Loop

**Step 1: Application Launch**
- The user starts the application.
- The application initializes the GTK+ environment and connects to the MySQL database.

**Step 2: The Dashboard Window (The "Triage Center")**
- The main window appears. Its primary purpose is to provide immediate, actionable information.
- **Main Feature:** A prominent list box or frame titled **"Urgent Reorder Alert"**.
    - This list is the first thing the user sees.
    - It is automatically populated with the names and current quantities of all items where `quantity <= threshold`.
    - If no items are low on stock, it displays a clear message like "Inventory levels are healthy."
- **Primary Actions (Buttons):**
    - **`[View & Edit Full Inventory]`**: Takes the user to a detailed view of all items.
    - **`[Add New Item]`**: Opens a dialog to add a new product to the database.
    - **`[Quit]`**: Exits the application.

**Step 3: The Full Inventory Window (The "Stock Room")**
- Accessed by clicking `[View & Edit Full Inventory]`.
- This window displays a complete, scrollable, and sortable `GtkTreeView` of every item in the database.
- Columns will include: `Name`, `Quantity`, `Unit`, `Low Stock Threshold`.
- **Interaction:**
    - The user can scroll through the list to see all items.
    - The user clicks to **select a single item** from the list.
- **Contextual Actions (Buttons become active after an item is selected):**
    - **`[Update Selected Item's Stock]`**: Opens the stock update dialog for the highlighted item.
    - **`[Edit Selected Item's Details]`**: Opens a form to change the name, unit, threshold, etc., of the item.

**Step 4: The Stock Update Dialog (The "Action")**
- This is a simple, purpose-built dialog that opens when the user clicks `[Update Selected Item's Stock]`.
- **Information Displayed:** The item's name (e.g., "Tomatoes") and its current quantity (e.g., "15 kg").
- **Core Interaction:** Two primary buttons are presented:
    - **`[Record Ingredient Usage]`**: For when ingredients are used in the kitchen.
    - **`[Record New Stock/Delivery]`**: For when a new shipment arrives.
- Clicking either button opens a final, small dialog with:
    - A `GtkSpinButton` (or a simple text entry) to input a number (e.g., "5").
    - An `[OK]` button.
- **Logic:**
    - Pressing `[OK]` calls the appropriate C function from the logic layer (`increase_item_quantity()` or `decrease_item_quantity()`) with the specified amount.
    - **Feedback:** The dialog closes. The "Full Inventory Window" behind it automatically refreshes its data from the database, showing the new quantity.
    - **Alerting:** If the update causes the item's quantity to cross its threshold, the system automatically triggers the `send_low_stock_notification()` function in the background, sending a push notification to the owner's phone.

**Step 5: Loop back or Exit**
- From the "Full Inventory Window" or the "Dashboard," the user can continue to manage items, looping back to Step 3 or 4.
- Alternatively, they can close the windows or use the `[Quit]` button to exit the application.
