#include <stdio.h>
#include <string.h>

#define MAX_INGREDIENTS 20
#define MAX_MENU_ITEMS 20
#define PASSWORD "bakery123"

// ===== STRUCTS =====

struct Ingredient {
    char name[30];
    int quantity;
    int threshold;
};

struct MenuItem {
    char name[30];
    int quantity;
};

// ===== GLOBAL DATA =====

struct Ingredient inventory[MAX_INGREDIENTS];
struct MenuItem menu[MAX_MENU_ITEMS];

int inventoryCount = 0;
int menuCount = 0;

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

void buyItem();

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
            case 3: buyItem(); break;
            case 4: printf("Exiting system...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
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
    for (int i = 0; i < inventoryCount; i++) {
        printf("%s\t\t%d\t%d\n",
            inventory[i].name,
            inventory[i].quantity,
            inventory[i].threshold
        );
    }
}

void addIngredient() {
    if (inventoryCount >= MAX_INGREDIENTS) {
        printf("Inventory full.\n");
        return;
    }

    printf("Enter ingredient name: ");
    scanf("%s", inventory[inventoryCount].name);

    printf("Enter quantity: ");
    scanf("%d", &inventory[inventoryCount].quantity);

    printf("Enter restock threshold: ");
    scanf("%d", &inventory[inventoryCount].threshold);

    inventoryCount++;
    printf("Ingredient added!\n");
}

void restockInventory() {
    printf("\nItems needing restock:\n");
    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i].quantity < inventory[i].threshold) {
            printf("%s (Qty: %d)\n",
                inventory[i].name,
                inventory[i].quantity
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
    for (int i = 0; i < menuCount; i++) {
        printf("%s\t%d\n", menu[i].name, menu[i].quantity);
    }
}

void addMenuItem() {
    if (menuCount >= MAX_MENU_ITEMS) {
        printf("Menu full.\n");
        return;
    }

    printf("Enter item name: ");
    scanf("%s", menu[menuCount].name);

    printf("Enter quantity: ");
    scanf("%d", &menu[menuCount].quantity);

    menuCount++;
    printf("Menu item added!\n");
}

void restockMenu() {
    printf("\nMenu items needing restock (qty < 5):\n");
    for (int i = 0; i < menuCount; i++) {
        if (menu[i].quantity < 5) {
            printf("%s (Qty: %d)\n", menu[i].name, menu[i].quantity);
        }
    }
}

// ---------------- BUYING ----------------

void buyItem() {
    int choice, qty;

    showMenuItems();
    printf("\nChoose item number (1-%d): ", menuCount);
    scanf("%d", &choice);

    if (choice < 1 || choice > menuCount) {
        printf("Invalid choice.\n");
        return;
    }

    printf("Enter quantity to buy: ");
    scanf("%d", &qty);

    if (qty > menu[choice - 1].quantity) {
        printf("Not enough items available.\n");
    } else {
        menu[choice - 1].quantity -= qty;
        printf("Purchase successful!\n");
    }
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