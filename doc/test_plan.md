# Test Plan and Verification Report

## Objective
Ensure the reliability of the Bakery Management System core logic through structured manual and functional testing.

## Testing Strategy

### 1. Manual Acceptance Testing (Completed)
The following functionality was verified through comprehensive execution of the terminal menus:
- **Inventory Management**: Verified adding new ingredients and tracking low-stock thresholds.
- **Menu Management**: Verified adding bakery items and updating stock levels during transactions.
- **Cart & Transactions**: Verified adding/removing items from the shopping cart and accurate price calculations.

### 2. Functional Verification
The modular refactoring was validated by ensuring seamless communication between the `main`, `inventory`, `menu`, and `cart` modules via their respective headers.

## Test Results

| ID | Test Case | Expected Outcome | Status |
|---|---|---|---|
| `TC-01` | Add 2 items priced at $1.50 each to an empty cart. | `DetermineTotalPrice()` returns `3.00`. | **Pass** |
| `TC-02` | Remove 1 item from a cart containing 2 items. | `DetermineTotalPrice()` returns `1.50`. | **Pass** |
| `TC-03` | Try to add an item with quantity exceeding available stock. | System correctly identifies stock shortage. | **Pass** |
| `TC-04` | Access menu functions after modular refactoring. | System functions identically to the monolithic version. | **Pass** |

## Conclusion
The current software meets the functional requirements for the initial prototype and has been verified to operate correctly in a modular configuration.
