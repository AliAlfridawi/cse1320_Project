#include <stdio.h>
#include <string.h>
#include "cart.h"
#include "menu.h"

Cart sCart;

void BuyItem() {
    int choice;

    memset(&sCart, 0, sizeof(Cart));

    do {
        printf("\n--- Cart ---\n");
        printf("1. View Cart\n");
        printf("2. Add to Cart\n");
        printf("3. Remove from Cart\n");
        printf("4. View Menu Items\n");
        printf("5. Buy and Complete Transaction\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                viewCart();
                break;
            }
            case 2: {
                addToCart();
                break;
            }
            case 3: {
                removeFromCart();
                break;
            }
            case 4: {
                showMenuItems();
                break;
            }
        }
    } while (choice != 5);

    printf("Total price: %.2f\n", determineTotalPrice());
}

void viewCart() {
    printf("\nItem\tQty\tPrice\n");
    
    for (int i = 0; i < sMenuCount; i++) {
        printf("%s\t%d\t%f\n", sMenu[i].name, sCart.items[i], sMenu[i].price);
    }
}

void addToCart() {
    int choice, qty;

    printf("Enter item number (1-%d): ", sMenuCount);
    scanf("%d", &choice);

    if (choice < 1 || choice > sMenuCount) {
        printf("Invalid choice.\n");
        return;
    }

    printf("Enter quantity to buy: ");
    scanf("%d", &qty);

    if (qty <= 0) {
        printf("Invalid quantity.\n");
        return;
    }

    if (qty > sMenu[choice - 1].quantity) {
        printf("Not enough items available.\n");
    } else {
        sMenu[choice - 1].quantity -= qty;
        sCart.items[choice - 1] += qty;
    }
}

void removeFromCart() {
    int choice, qty;

    printf("Enter item number (1-%d): ", sMenuCount);
    scanf("%d", &choice);

    if (choice < 1 || choice > sMenuCount) {
        printf("Invalid choice.\n");
        return;
    }

    printf("Enter quantity to remove: ");
    scanf("%d", &qty);

    if (qty < 0) {
        printf("Invalid quantity.\n");
        return;
    }
    
    if (qty >= sCart.items[choice - 1]) {
        printf("Removing all items.\n");
        qty = sCart.items[choice - 1]; // clamp the item count  
    }
    
    sMenu[choice - 1].quantity += qty;
    sCart.items[choice - 1] -= qty;   

    printf("Removed %d items from cart\n", qty);
}

float determineTotalPrice() {
    float total = 0.0f;

    for (int i = 0; i < sMenuCount; i++) {
        total += (float)sCart.items[i] * sMenu[i].price;
    }

    return total;
}
