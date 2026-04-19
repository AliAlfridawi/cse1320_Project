#ifndef CART_H
#define CART_H

#include "common.h"

typedef struct Cart {
    int items[MAX_MENU_ITEMS];
} Cart;

extern Cart sCart;

void BuyItem();
void ViewCart();
void AddToCart();
void RemoveFromCart();
float DetermineTotalPrice();

#endif // CART_H
