#include <stdio.h>
#include <string.h>

#define MAX_INGREDIENTS 20
#define MAX_MENU_ITEMS 20
#define PASSWORD "bakery123"

// ===== STRUCTS =====

typedef struct Ingredient {
    char name[30];
    int quantity;
    int threshold;
} Ingredient;

typedef struct MenuItem {
    char name[30];
    int quantity;
    float price;
} MenuItem;

typedef struct Cart {
    int items[MAX_MENU_ITEMS]; // an array of the counts of items in cart
} Cart;

// ===== GLOBAL DATA =====

Ingredient sInventory[MAX_INGREDIENTS];
MenuItem sMenu[MAX_MENU_ITEMS];
Cart sCart;

int sInventoryCount = 0;
int sMenuCount = 0;

// ===== FUNCTION DECLARATIONS =====

int login();
void mainMenu();

void inventoryMenu();
void showInventory();
void addIngredient();
void restockInventory();

void menuMenu();
void showMenuItems();
void addMenuItem();
void restockMenu();

void BuyItem();

void ViewCart();
void AddToCart();
void RemoveFromCart();
float DetermineTotalPrice();

// ===== FUNCTIONS =====

int login() {
    char input[20];

    printf("Enter password: ");
    scanf("%s", input);

    if (strcmp(input, PASSWORD) == 0) {
        return 1;
    }
    return 0;
}

// ---------------- MAIN MENU ----------------

void mainMenu() {
    int choice;

    do {
        printf("\n=== BAKERY MANAGEMENT SYSTEM ===\n");
        printf("1. Inventory\n");
        printf("2. Menu\n");
        printf("3. Buy Items\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: inventoryMenu(); break;
            case 2: menuMenu(); break;
            case 3: BuyItem(); // no break statement to allow fallthrough
            case 4: printf("Exiting system...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3 && choice != 4);
}

// ---------------- INVENTORY ----------------

void inventoryMenu() {
    int choice;

    do {
        printf("\n--- INVENTORY MENU ---\n");
        printf("1. View Inventory\n");
        printf("2. Add Ingredient\n");
        printf("3. Restock Needed\n");
        printf("4. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showInventory(); break;
            case 2: addIngredient(); break;
            case 3: restockInventory(); break;
        }
    } while (choice != 4);
}

void showInventory() {
    printf("\nIngredient\tQty\tThreshold\n");
    for (int i = 0; i < sInventoryCount; i++) {
        printf("%s\t\t%d\t%d\n",
            sInventory[i].name,
            sInventory[i].quantity,
            sInventory[i].threshold
        );
    }
}

void addIngredient() {
    if (sInventoryCount >= MAX_INGREDIENTS) {
        printf("Inventory full.\n");
        return;
    }

    printf("Enter ingredient name: ");
    scanf("%s", sInventory[sInventoryCount].name);

    printf("Enter quantity: ");
    scanf("%d", &sInventory[sInventoryCount].quantity);

    printf("Enter restock threshold: ");
    scanf("%d", &sInventory[sInventoryCount].threshold);

    sInventoryCount++;
    printf("Ingredient added!\n");
}

void restockInventory() {
    printf("\nItems needing restock:\n");
    for (int i = 0; i < sInventoryCount; i++) {
        if (sInventory[i].quantity < sInventory[i].threshold) {
            printf("%s (Qty: %d)\n",
                sInventory[i].name,
                sInventory[i].quantity
            );
        }
    }
}

// ---------------- MENU ITEMS ----------------

void menuMenu() {
    int choice;

    do {
        printf("\n--- MENU ITEMS ---\n");
        printf("1. View Items\n");
        printf("2. Add Menu Item\n");
        printf("3. Restock Needed\n");
        printf("4. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showMenuItems(); break;
            case 2: addMenuItem(); break;
            case 3: restockMenu(); break;
        }
    } while (choice != 4);
}

void showMenuItems() {
    printf("\nItem\tQty\n");
    for (int i = 0; i < sMenuCount; i++) {
        printf("%s\t%d\t%f\n", sMenu[i].name, sMenu[i].quantity, sMenu[i].price);
    }
}

void addMenuItem() {
    if (sMenuCount >= MAX_MENU_ITEMS) {
        printf("Menu full.\n");
        return;
    }

    printf("Enter item name: ");
    scanf("%s", sMenu[sMenuCount].name);

    printf("Enter quantity: ");
    scanf("%d", &sMenu[sMenuCount].quantity);

    printf("Enter item price: ");
    scanf("%f", &sMenu[sMenuCount].price);

    sMenuCount++;
    printf("Menu item added!\n");
}

void restockMenu() {
    printf("\nMenu items needing restock (qty < 5):\n");
    for (int i = 0; i < sMenuCount; i++) {
        if (sMenu[i].quantity < 5) {
            printf("%s (Qty: %d)\n", sMenu[i].name, sMenu[i].quantity);
        }
    }
}

// ---------------- BUYING ----------------

void BuyItem() {
    int choice;

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
                ViewCart();
                break;
            }

            case 2: {
                AddToCart();
                break;
            }

            case 3: {
                RemoveFromCart();
                break;
            }

            case 4: {
                showMenuItems();
                break;
            }
        }
    } while (choice != 5);


    printf("Total price: %.2f\n", DetermineTotalPrice());
}

void ViewCart() {
    printf("\nItem\tQty\n");
    
    for (int i = 0; i < sMenuCount; i++) {
        printf("%s\t%d\t%f\n", sMenu[i].name, sCart.items[i], sMenu[i].price);
    }
}

void AddToCart() {
    int choice, qty;

    printf("Enter item number (1-%d): ", sMenuCount);
    scanf("%d", &choice);

    if (choice < 1 || choice > sMenuCount) {
        printf("Invalid choice.\n");
        return;
    }

    printf("Enter quantity to buy: ");
    scanf("%d", &qty);

    if (qty > sMenu[choice - 1].quantity) {
        printf("Not enough items available.\n");
    } else {
        sMenu[choice - 1].quantity -= qty;
        sCart.items[choice - 1] += qty;
    }
}

void RemoveFromCart() {
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

float DetermineTotalPrice() {
    float total = 0.0f;

    for (int i = 0; i < sMenuCount; i++) {
        total += (float)sCart.items[i] * sMenu[i].price;
    }

    return total;
}

// ---------------- MAIN ----------------

int main() {
    if (!login()) {
        printf("Incorrect password.\n");
        return 0;
    }

    mainMenu();
    return 0;
}