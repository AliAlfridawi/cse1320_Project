# Test Plan

## Objective
Ensure the reliability of core bakery management logic through structured testing.

## Testing Strategy

### 1. Manual Testing (Current)
- Navigate through terminal menus.
- Verify inventory updates after adding items.
- Verify cart totals after adding/removing items.

### 2. Automated Unit Testing (Planned)
- Use a simple assert-based test runner in C.
- Focus on the `Cart` module first.

**Target Functions for Testing:**
- `DetermineTotalPrice()`: Verify correct math for multiple items and prices.
- `AddToCart()`: Ensure inventory is correctly decremented and cart incremented.
- `RemoveFromCart()`: Ensure inventory is correctly restored and cart decremented.

## Test Cases (Example)
| Test Case | Description | Expected Outcome |
|---|---|---|
| `TC-01` | Add 2 items priced at $1.50 each to an empty cart. | `DetermineTotalPrice()` returns `3.00`. |
| `TC-02` | Remove 1 item from a cart containing 2 items. | `DetermineTotalPrice()` returns `1.50`. |
| `TC-03` | Try to add an item with quantity exceeding available stock. | Error message shown; cart/inventory remain unchanged. |
