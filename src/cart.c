#include <stdio.h>
#include "cart.h"
#include "menu.h"
#include "storage.h"
#include "input.h"

Cart sCart;

static int cartIsEmpty() {
    int i;

    for (i = 0; i < sMenuCount; i++) {
        if (sCart.items[i] > 0) {
            return 0;
        }
    }

    return 1;
}

static void clearCart() {
    int i;

    for (i = 0; i < MAX_MENU_ITEMS; i++) {
        sCart.items[i] = 0;
    }
}

void BuyItem() {
    int choice = 0;

    if (sMenuCount == 0) {
        printf("\nNo menu items available.\n");
        return;
    }

    do {
        printf("\n--- CART MENU ---\n");
        printf("1. View Cart\n");
        printf("2. Add to Cart\n");
        printf("3. Remove from Cart\n");
        printf("4. View Menu Items\n");
        printf("5. Buy and Complete Transaction\n");
        printf("6. Back\n");
        choice = readIntInput("Choose: ");

        switch (choice) {
            case 1:
                ViewCart();
                break;
            case 2:
                AddToCart();
                break;
            case 3:
                RemoveFromCart();
                break;
            case 4:
                showMenuItems();
                break;
            case 5:
                if (cartIsEmpty()) {
                    printf("Cart is empty.\n");
                    break;
                }

                printf("Total price: %.2f\n", DetermineTotalPrice());
                clearCart();
                saveData();
                printf("Transaction complete.\n");
                return;
            case 6:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 6);
}

void ViewCart() {
    int i;

    if (cartIsEmpty()) {
        printf("\nCart is empty.\n");
        return;
    }

    printf("\nNo.\tItem\tQty\tPrice\n");
    for (i = 0; i < sMenuCount; i++) {
        if (sCart.items[i] > 0) {
            printf("%d\t%s\t%d\t%.2f\n",
                i + 1,
                sMenu[i].name,
                sCart.items[i],
                sMenu[i].price);
        }
    }

    printf("Total price: %.2f\n", DetermineTotalPrice());
}

void AddToCart() {
    int choice;
    int qty;

    if (sMenuCount == 0) {
        printf("\nNo menu items available.\n");
        return;
    }

    showMenuItems();
    choice = readIntInput("Enter item number: ");

    if (choice < 1 || choice > sMenuCount) {
        printf("Invalid choice.\n");
        return;
    }

    qty = readIntInput("Enter quantity to buy: ");

    if (qty <= 0) {
        printf("Invalid quantity.\n");
        return;
    }

    if (qty > sMenu[choice - 1].quantity) {
        printf("Not enough items available.\n");
        return;
    }

    sMenu[choice - 1].quantity -= qty;
    sCart.items[choice - 1] += qty;
    saveData();
    printf("Added %d item(s) to cart.\n", qty);
}

void RemoveFromCart() {
    int choice;
    int qty;

    if (cartIsEmpty()) {
        printf("\nCart is empty.\n");
        return;
    }

    ViewCart();
    choice = readIntInput("Enter item number: ");

    if (choice < 1 || choice > sMenuCount) {
        printf("Invalid choice.\n");
        return;
    }

    if (sCart.items[choice - 1] == 0) {
        printf("That item is not in the cart.\n");
        return;
    }

    qty = readIntInput("Enter quantity to remove: ");

    if (qty <= 0) {
        printf("Invalid quantity.\n");
        return;
    }

    if (qty >= sCart.items[choice - 1]) {
        printf("Removing all of that item.\n");
        qty = sCart.items[choice - 1];
    }

    sMenu[choice - 1].quantity += qty;
    sCart.items[choice - 1] -= qty;
    saveData();

    printf("Removed %d item(s) from cart.\n", qty);
}

float DetermineTotalPrice() {
    float total = 0.0f;
    int i;

    for (i = 0; i < sMenuCount; i++) {
        total += (float) sCart.items[i] * sMenu[i].price;
    }

    return total;
}
