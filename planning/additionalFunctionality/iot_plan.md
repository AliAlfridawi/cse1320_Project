# Detailed Plan for IoT Phone Notifications

## 1. Objective
To integrate a system that sends real-time push notifications to the restaurant owner's phone, providing immediate alerts on what ingredients are running low and need to be reordered.

This approach treats the owner's phone as the "Thing" in the Internet of Things, connecting the C application's digital data directly to a physical device in the user's hand.

## 2. Technology Stack
- **Notification Service:** **Pushover** - Chosen for its extreme simplicity. It has a dead-simple REST API that we can call from C. The user only needs to install the Pushover app on their phone.
    - **User Requirement:** Create a Pushover account (the basic plan is a one-time purchase) to get a **User Key**.
    - **Application Requirement:** Register a new "Application" on the Pushover website to get an **API Token**.
- **C Library for HTTP Requests:** **libcurl** - The industry-standard, highly reliable C library for making HTTP requests to web APIs like Pushover.

## 3. Architectural Integration
- **New Module (`notifications.c`, `notifications.h`):** A new, self-contained module will be created to handle all interactions with the Pushover API. It will depend on `libcurl`.
- **Logic Layer (`inventory.c`):** The logic layer will decide *when* a notification is necessary. It will call the high-level functions from `notifications.h` (e.g., `send_low_stock_alert()`). It does not need to know *how* the notification is sent.
- **Configuration:** The User Key and API Token will be stored in a configuration file or entered in the GUI to avoid hardcoding sensitive information.

---

## 4. Key Features & Step-by-Step Implementation Plan

### Feature 1: Instant Low-Stock Alert
An immediate notification is sent the moment an item's quantity drops below its defined threshold.

- **Implementation Steps:**
    1.  **Trigger Point:** Locate the function in `inventory.c` that updates an item's quantity (e.g., `decrease_item_quantity()`).
    2.  **Add Logic:** After the quantity is updated, add a check: `if (new_quantity <= item_threshold && old_quantity > item_threshold)`. The second part of the condition ensures the notification is sent only once when the threshold is first crossed.
    3.  **Call Notification Function:** If the condition is met, call `send_low_stock_notification(item_name, new_quantity)`. This function will format a user-friendly message like "Heads up! You're running low on Tomatoes (12 left)." and pass it to the core Pushover function.

### Feature 2: Daily Reorder Digest
A user-triggered summary of all items that are currently low on stock.

- **Implementation Steps:**
    1.  **GUI/UI Trigger:** Add a "Send Daily Report" button to the main dashboard of the GUI.
    2.  **Logic Function:** The button's callback will trigger a new function, `send_reorder_digest()`, in the logic layer.
    3.  **Data Aggregation:** This function will:
        -   Query the database for all items where `quantity <= threshold`.
        -   Build a single, formatted string containing a list of these items (e.g., "- Tomatoes (12 left)\n- Onions (5 left)\n- Flour (8 left)").
    4.  **Send Notification:** Call the core `send_pushover_notification()` function with a title like "Daily Reorder List" and the aggregated message string.

---

## 5. Development Roadmap
1.  **Pushover Account Setup:**
    -   Sign up at `pushover.net`, download the app on your Android/iOS device, and note your **User Key**.
    -   Log in, click "Create an Application/API Token," and note the **API Token**.
2.  **Install `libcurl`:**
    -   Install the development package for your system (e.g., `sudo apt-get install libcurl4-openssl-dev` on Debian/Ubuntu or via `vcpkg` on Windows).
    -   Update your `Makefile` to link the library: `gcc $(...) -o $(...) $(...) -lcurl`.
3.  **Create `notifications.c` Module:**
    -   In `notifications.h`, declare one function: `void send_pushover_notification(const char *title, const char *message);`.
    -   In `notifications.c`, implement this function using `libcurl`:
        a. Initialize a `CURL *` handle with `curl_easy_init()`.
        b. Construct the POST fields string: `sprintf(post_data, "token=YOUR_API_TOKEN&user=YOUR_USER_KEY&title=%s&message=%s", title, message);`. (URL-encode the title and message for robustness).
        c. Set the Pushover API URL: `curl_easy_setopt(curl, CURLOPT_URL, "https://api.pushover.net/1/messages.json");`.
        d. Set the POST data: `curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);`.
        e. Execute the request with `curl_easy_perform()`.
        f. Check for errors and clean up with `curl_easy_cleanup()`.
4.  **Integrate with Logic Layer:**
    -   Modify `inventory.c` as described in "Feature 1" to call your new notification function when stock is low.
5.  **Build Configuration:**
    -   Create a settings screen in the GUI to allow the user to input and save their Pushover keys. Store these in a simple `.config` file. Your `notifications.c` module will read from this file.
6.  **Test End-to-End:**
    -   Run the application. Update an item's quantity until it drops below the threshold.
    -   **Expected Result:** A push notification should appear on your phone within seconds.
