#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Product catalog
struct Product {
    string name;
    int price;
};

Product productCatalog[100];
int numProducts = 0;

// Product search and display class
class ProductSearch {
private:
    struct Product {
        string name;
        int quantity; // Changed from price to quantity
    };

    queue<Product> productList;

public:
    void addProduct(const string& productName, int quantity) {
        productList.push({productName, quantity});
    }

    void displayProductList() {
        if (productList.empty()) {
            cout << "Product list is empty." << endl;
            return;
        }

        cout << "Product List:" << endl;
        queue<Product> tempQueue = productList; // Create a temporary queue to iterate without modifying original
        while (!tempQueue.empty()) {
            cout << tempQueue.front().name << " - " << tempQueue.front().quantity << " units" << endl;
            tempQueue.pop(); // Remove the front element after printing
        }
    }

    void searchProduct(const string& productName) {
        bool found = false;
        queue<Product> tempQueue = productList;

        while (!tempQueue.empty()) {
            if (tempQueue.front().name == productName) {
                cout << "Product: " << tempQueue.front().name << ", Quantity: " << tempQueue.front().quantity << endl;
                found = true;
                break;
            }
            tempQueue.pop();
        }

        if (!found) {
            cout << "Product not found." << endl;
        }
    }
};

ProductSearch productSearch; // Global instance of ProductSearch

// Admin login
void adminLogin() {
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;
    if (username == "admin" && password == "password") {
        cout << "Admin login successful!" << endl;

        // Display the current product list
        productSearch.displayProductList();

        // Prompt admin to add more products
        char addMore;
        cout << "Do you want to add more products? (Y/N): ";
        cin >> addMore;

        while (addMore == 'Y' || addMore == 'y') {
            string name;
            int price;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product price: ";
            cin >> price;
            productCatalog[numProducts] = {name, price};
            productSearch.addProduct(name, price);
            numProducts++;
            cout << "Product added successfully!" << endl;
            cout << "Do you want to add more products? (Y/N): ";
            cin >> addMore;
        }

        // Display the updated product list
        productSearch.displayProductList();
    } else {
        cout << "Invalid admin credentials!" << endl;
    }
}

// Customer login
void customerLogin() {
    string username, password;
    cout << "Enter customer username: ";
    cin >> username;
    cout << "Enter customer password: ";
    cin >> password;
    // For simplicity, assuming any username/password combination is valid for customers
    cout << "Customer login successful! Welcome, " << username << "!" << endl;

    // Display the product list for the customer
    productSearch.displayProductList();
}

// Shopping cart management
struct CartItem {
    string productName;
    int quantity;
};

CartItem cart[100];
int cartSize = 0;

void addToCart() {
    string productName;
    int quantity;
    cout << "Enter product name: ";
    cin >> productName;
    cout << "Enter quantity: ";
    cin >> quantity;
    bool found = false;
    for (int i = 0; i < numProducts; i++) {
        if (productCatalog[i].name == productName) {
            cart[cartSize].productName = productName;
            cart[cartSize].quantity = quantity;
            cartSize++;
            cout << "Product added to cart!" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Product not found!" << endl;
    }
}

// Apply discount based on entered code
double applyDiscount(double total, const string& code) {
    if (code == "discount10") {
        return total * 0.9;
    } else if (code == "discount20") {
        return total * 0.8;
    } else if (code == "discount30") {
        return total * 0.7;
    } else if (code == "discount40") {
        return total * 0.6;
    } else if (code == "discount50") {
        return total * 0.5;
    } else if (code == "discount60") {
        return total * 0.4;
    } else if (code == "discount70") {
        return total * 0.3;
    } else if (code == "discount80") {
        return total * 0.2;
    } else if (code == "discount90") {
        return total * 0.1;
    } else if (code == "discount100") {
        return 0; // 100% discount
    } else {
        return total; // No discount
    }
}

// Checkout management
void checkout() {
    int total = 0;
    int totalQuantity = 0; // Variable to store total quantity of products in cart

    cout << "Products in cart:" << endl;
    for (int i = 0; i < cartSize; i++) {
        bool found = false;
        for (int j = 0; j < numProducts; j++) {
            if (productCatalog[j].name == cart[i].productName) {
                cout << cart[i].productName << " x " << cart[i].quantity << " = " << cart[i].quantity * productCatalog[j].price << endl;
                total += cart[i].quantity * productCatalog[j].price;
                totalQuantity += cart[i].quantity; // Increment total quantity
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Product not found in catalog!" << endl;
        }
    }
    cout << "Total: " << total << endl;
    string cardNumber;
    cout << "Enter card number: ";
    cin >> cardNumber;

    // Ask for discount code
    string discountCode;
    cout << "Do you have a discount code? (Enter 'none' if you don't have): ";
    cin >> discountCode;

    total = applyDiscount(total, discountCode); // Apply discount

    cout << "Total after discount: " << total << endl;

    if (total <= 1000) { // assume card has sufficient funds
        cout << "Payment successful!" << endl;
        
        // Check total quantity of products in cart
        if (totalQuantity <= 10) {
            cout << "You are redirected to Express line." << endl;
        } else {
            cout << "You are redirected to normal line." << endl;
        }
    } else {
        cout << "Insufficient funds!" << endl;
    }
}

int main() {
    // Predefined products
    productCatalog[numProducts++] = {"laptop", 200};
    productSearch.addProduct("laptop", 200);
    productCatalog[numProducts++] = {"phone", 100};
    productSearch.addProduct("phone", 100);
    productCatalog[numProducts++] = {"headphones", 50};
    productSearch.addProduct("headphones", 50);

    cout << "Welcome to the Online Shopping Management System" << endl;
    cout << "Please choose your role: " << endl;
    cout << "1. Admin" << endl;
    cout << "2. Customer" << endl;
    int role;
    cin >> role;

    if (role == 1) {
        adminLogin();
    } else if (role == 2) {
        customerLogin();
    } else {
        cout << "Invalid role selected!" << endl;
        return 0;
    }

    while (true) {
        cout << "1. Product search" << endl;
        cout << "2. Add to cart" << endl;
        cout << "3. Checkout" << endl;
        cout << "4. Exit" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:                             
                // Product search
                {
                    string searchName;
                    cout << "Enter product name to search: ";
                    cin >> searchName;
                    productSearch.searchProduct(searchName);
                }
                break;
            case 2:
                addToCart();
                break;
            case 3:
                checkout();
                break;
            case 4: 
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}

