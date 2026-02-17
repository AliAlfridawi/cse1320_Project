# Detailed Plan for Nemotron Model Integration

This plan is divided into two parts to address both the predictive and chatbot functionalities you requested.

---

## Part A: Predictive Ordering Assistant

### 1. Objective
To use the Nemotron model to analyze historical ingredient usage and current stock levels to predict future needs. The model will recommend what to order and how much, moving from simple "low stock" alerts to intelligent forecasting.

### 2. Architectural Changes
- **Database:** A new table, `usage_log`, is required to track consumption over time.
    - **Schema:** `CREATE TABLE usage_log (log_id INT AUTO_INCREMENT PRIMARY KEY, item_id INT, quantity_used DECIMAL(10,2), log_timestamp DATETIME NOT NULL);`
- **Logic Layer:** The function that reduces stock must be updated to also `INSERT` a record into `usage_log`.
- **New Module:** `nemotron_service.c` will be created to handle all API calls to the Nemotron model using `libcurl`.

### 3. Step-by-Step Implementation

1.  **Modify Database & Logic:**
    -   Create the `usage_log` table in your MySQL database.
    -   Update your `decrease_item_quantity()` function in `inventory.c` to add a new record to `usage_log` every time it's called.

2.  **Create a Data Aggregation Function:**
    -   In your data layer, create a function: `char* get_usage_history_as_string(int item_id, int days)`.
    -   This function will query the `usage_log` for a specific item over the last `days` and format the data into a simple, clean string for the model (e.g., `"12,15,10,14,20,18,11"`).

3.  **Engineer the Prediction Prompt:**
    -   This is the key step. We will create a function that builds a detailed prompt for the Nemotron API.
    -   **Example Prompt Template:**
        ```
        You are an inventory prediction AI for a restaurant. Your goal is to recommend a reorder quantity. Analyze the provided data and respond ONLY with a JSON object.

        Context:
        - Item Name: {item_name}
        - Current Stock: {current_quantity} {unit}
        - Low Stock Threshold: {threshold} {unit}
        - Historical Daily Usage (last 21 days, oldest to newest): [{usage_data_string}]

        Task:
        Based on this data, analyze trends (like weekly cycles or growth) and predict the total usage for the next 7 days. Then, recommend a reorder quantity to ensure stock stays above the threshold.

        JSON Response Format:
        {
          "predicted_usage": <number>,
          "recommended_reorder_quantity": <number>,
          "confidence": "<High/Medium/Low>",
          "reasoning": "<Your brief analysis and reasoning for the recommendation.>"
        }
        ```

4.  **Build the API Call:**
    -   In `nemotron_service.c`, create a function `char* get_nemotron_prediction(char *prompt)` that uses `libcurl` to send the generated prompt to the Nemotron API endpoint.
    -   It must handle authentication (API key in header) and receive the JSON response as a string.

5.  **Parse the Response & Display in GUI:**
    -   Use a C JSON parsing library (like **cJSON**) to parse the JSON string returned by the API.
    -   In the GUI, on an item's detail page, add a "Get Forecast" button.
    -   When clicked, the application will execute the steps above.
    -   Display the `recommended_reorder_quantity` and `reasoning` in a `GtkMessageDialog` or a new frame in the window.

---

## Part B: Natural Language Chatbot (Text-to-SQL)

### 1. Objective
To allow a user to ask questions about the inventory in plain English (e.g., "which items are low on stock?") and get immediate, accurate answers from the database. The model's job is to convert the question into a SQL query.

### 2. Concept: Text-to-SQL
This is a powerful technique where the LLM doesn't know your data, but it knows your database *structure*. We give it the schema and the user's question, and it returns a valid SQL query. We then run that query ourselves. This is more secure and accurate than asking it to answer from memory.

### 3. Step-by-Step Implementation

1.  **Engineer the Text-to-SQL Prompt:**
    -   This prompt will be prepended to every user question sent to the model.
    -   **Example Prompt Template:**
        ```
        You are a highly intelligent Text-to-SQL bot for a restaurant inventory system. I will provide you with the database schema and a user's question. You will convert the question into a single, valid MySQL query.
        - **Only respond with the SQL query.**
        - Do not include any explanations, markdown, or any text other than the SQL code.
        - If the question cannot be answered by the schema, respond with "Error: Cannot answer."

        Database Schema:
        CREATE TABLE inventory_items (item_id INT, name VARCHAR(255), quantity INT, price DECIMAL(10, 2), unit VARCHAR(50), threshold INT);
        CREATE TABLE suppliers (supplier_id INT, name VARCHAR(255));

        User Question: {user_question_string}

        SQL Query:
        ```

2.  **Build the Chatbot GUI:**
    -   Create a new `GtkWindow` for the chatbot.
    -   Use a `GtkScrolledWindow` containing a `GtkTextView` for the chat history (set to be non-editable).
    -   Add a `GtkEntry` at the bottom for the user to type their questions.

3.  **Implement the Chat Logic:**
    -   When the user presses "Enter" in the `GtkEntry`:
        a. Get the text from the `GtkEntry` (the user's question).
        b. Append the question to the `GtkTextView` history (e.g., "**You:** how many tomatoes do we have").
        c. Create the full prompt using the Text-to-SQL template and the user's question.
        d. Send the prompt to Nemotron via your `nemotron_service.c` module.
        e. **CRITICAL: Sanitize the Returned SQL:** The string returned from the API *should* be a SQL query. Before executing it, perform a basic safety check:
           - **MUST start with `SELECT`**. Use `strncmp(sql_from_llm, "SELECT", 6) == 0`.
           - **MUST NOT contain destructive keywords** like `DROP`, `DELETE`, `UPDATE`, `INSERT`.
           - If the check fails, display an error message and do not proceed.
        f. **Execute and Display:** If the SQL is safe, execute it against your MySQL database.
        g. Format the results from the database into a human-readable table or list.
        h. Append the formatted result to the `GtkTextView` history (e.g., "**Clarity Bot:**\n- Tomatoes: 42 kg").
        i. Clear the `GtkEntry` for the next question.
