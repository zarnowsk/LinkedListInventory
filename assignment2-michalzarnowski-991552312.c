/* *****************************
 * Michal Zarnowski, 991552312 *
 *        Assignment 2         *
 ***************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *** STRUCTS ***
typedef struct product {
    char productName[25];
    double price;
    struct product * next;
} Product;

typedef struct productList {
    Product *  head;
} ProductList;

// *** METHODS ***
void addToInventory(ProductList * productList, char newProductName[], double newProductPrice);
void printInventory(ProductList * productList);
void searchInventory(ProductList * productList, char searchedProductName[]);
void updatePrice(ProductList * productList, char searchedProductName[], double newPrice);
Product * findProduct(ProductList * productList, char searchedProductName[]);
void deleteFromInventory(ProductList * productList, char productToDelete[]);
void clearInventory(ProductList * productList);

int main() {

    // Create new product list
    ProductList * productList = (ProductList * ) malloc(sizeof(ProductList));
    productList->head = NULL;

    // Add inventory items
    addToInventory(productList, "Parsnips", 20.00);
    addToInventory(productList, "Cauliflower", 100.00);
    addToInventory(productList, "Kale", 70.00);
    addToInventory(productList, "Potatoes", 50.00);
    addToInventory(productList, "Beans", 60.00);

    // Print the inventory
    printInventory(productList);

    // Look up items in the inventory
    searchInventory(productList, "Potatoes");
    searchInventory(productList, "Cranberries");

    // Delete from inventory
    deleteFromInventory(productList, "Kale");
    deleteFromInventory(productList, "Cauliflower");
    printInventory(productList);

    // Update price of items
    updatePrice(productList, "Parsnips", (20 * 0.8));
    printInventory(productList);

    // Clear inventory
    clearInventory(productList);
    printInventory(productList);

    // Free memory
    free(productList);

    return 0;
}

void addToInventory(ProductList * productList, char newProductName[], double newProductPrice) {

    // Create new Product struct
    Product * newProduct = (Product *) malloc(sizeof(Product));
    strcpy(newProduct->productName, newProductName);
    newProduct->price = newProductPrice;
    newProduct->next = NULL;

    // Find place in linked list to add new value (ascending price order)
    if (productList->head == NULL) {
        productList->head = newProduct;
    } else {
        Product * currentProduct = productList->head;
        while (currentProduct->next != NULL && currentProduct->next->price < newProductPrice) {
            currentProduct = currentProduct->next;
        }
        newProduct->next = currentProduct -> next;
        currentProduct->next = newProduct;

    }
    printf("%s at $%.2f added to inventory list!\n", newProductName, newProductPrice);
}

void printInventory(ProductList * productList) {

    printf("\nDisplaying current inventory\n");

    Product * currentProduct = productList->head;
    if (currentProduct == NULL) {
        printf("\tNo items in the inventory!\n");
    } else {
        // Loop through the list till the end printing inventory details
        while (currentProduct != NULL) {
            printf("\t%s, $%.2f\n", currentProduct->productName, currentProduct->price);
            currentProduct = currentProduct->next;
        }
    }

    printf("\n");
}

void searchInventory(ProductList * productList, char searchedProductName[]) {

    printf("Searching for %s, please wait...\n\n", searchedProductName);

    // Assign a pointer to the searched product in the list
    Product * matchedProduct = findProduct(productList, searchedProductName);

    // If matchedProduct is pointing to a Product, print its details
    if (matchedProduct == NULL) {
        printf("Oops, %s not in the inventory.\n\n", searchedProductName);
    } else {
        printf("%s found! Costing: $%.2f\n\n", searchedProductName, matchedProduct->price);
    }
}

void updatePrice(ProductList * productList, char searchedProductName[], double newPrice) {

    printf("Updating price for %s, please wait...\n\n", searchedProductName);

    // Assign a pointer to the searched product in the list
    Product * matchedProduct = findProduct(productList, searchedProductName);

    // If matchedProduct is pointing to a Product, update its price
    if (matchedProduct == NULL) {
        printf("Oops, %s not in the inventory.\n\n", searchedProductName);
    } else {
        matchedProduct->price = newPrice;
        printf("%s found! Price updated to: $%.2f\n\n", matchedProduct->productName, matchedProduct->price);
    }
}

Product * findProduct(ProductList * productList, char searchedProductName[]) {

    // Get first product in the inventory
    Product * currentProduct = productList->head;

    // Loop through the inventory, if product name is matched, return matched Product pointer
    if (currentProduct != NULL) {
        while (currentProduct != NULL) {
            if (strcmp(currentProduct->productName, searchedProductName) == 0) {
                return currentProduct;
            }
            currentProduct = currentProduct->next;
        }
    }

    return NULL;
}

void deleteFromInventory(ProductList * productList, char productToDelete[]) {

    // Get first product in the inventory
    Product * currentProduct = productList->head;

    Product * prevProduct;

    if (currentProduct == NULL) {
        // If inventory is already empty
        printf("The inventory is already empty!\n\n");
    } else if (strcmp(currentProduct->productName, productToDelete) == 0) {
        // If first product is the one to be deleted, assign it's next Product
        // pointer to be the new 'head' and free the space
        productList->head = currentProduct->next;
        free(currentProduct);
        printf("%s deleted from inventory!\n\n", productToDelete);
    } else {
        // Loop through the linked products of the list until end is reached (NULL pointer) or
        // currentProduct pointer is pointing towards matched Product to delete
        // Keep track of the previous to current Product
        while (currentProduct != NULL && strcmp(currentProduct->productName, productToDelete) != 0) {
            prevProduct = currentProduct;
            currentProduct = currentProduct->next;
        }

        // If Product was found (pointer not NULL):
        // 1) Point the Product before one to be deleted (previous) to the one after deleted one
        // 2) Free the space
        if (currentProduct != NULL) {
            prevProduct->next = currentProduct->next;
            free(currentProduct);
            printf("%s deleted from inventory!\n\n", productToDelete);
        } else {
            // If product wasn't found in the list
            printf("%s not in the inventory!\n\n", productToDelete);
        }
    }
}

void clearInventory(ProductList * productList) {

    printf("Closing down the store, donating all the products!\n");

    // Get first product in the inventory
    Product * currentProduct = productList->head;

    if (currentProduct == NULL) {
        // If inventory is already empty
        printf("The inventory is already empty!\n\n");
    } else {
        // Loop through the inventory till Product pointer is NULL (no more products)
        while (currentProduct != NULL) {
            // Assign list's first position to the Product after current, delete current Product
            // and assign currentProduct pointer to the new 'head' of the list
            productList->head = currentProduct->next;
            free(currentProduct);
            currentProduct = productList->head;
        }
        printf("The inventory has been cleared!\n\n");
    }
}