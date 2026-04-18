#ifndef CART_H
#define CART_H

#include "common.h"

typedef struct Cart {
    int items[MAX_MENU_ITEMS]; // an array of the counts of items in cart
} Cart;

extern Cart sCart;

void BuyItem(); // Legacy exception
void viewCart();
void addToCart();
void removeFromCart();
float determineTotalPrice();

#endif // CART_H
