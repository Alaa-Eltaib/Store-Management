#include <iostream>
#include <limits>
#include <string>
using namespace std;

const int MAX_PRODUCTS = 100;
const int MAX_CART_ITEMS = 100;

struct Product {
    int id;
    string name;
    double price;
    double discount;
    double finalprice;
};

struct CartItem {
    string name;
    int productId;
    int quantity;
};

void showMenu() {
    cout << "1. Add product" << endl;
    cout << "2. Edit product" << endl;
    cout << "3. Delete product" << endl;
    cout << "4. Add item to cart" << endl;
    cout << "5. Remove item from cart" << endl;
    cout << "6. View cart total" << endl;
    cout << "7. Exit" << endl;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isNumber(const string& s) {
    return !s.empty() && s.find_first_not_of("0123456789.") == string::npos;
}

bool isAlpha(const string& s) {
    for (char c : s) {
        if (!isalpha(c) && !isspace(c) && c != '-') {
            return false;
        }
    }
    return !s.empty();
}

void addProduct(Product products[], int& productCount) {
    Product newProduct;
    bool idfound;

    do {
        idfound = false;
        string inputId;
        cout << "Enter product ID: ";
        cin >> inputId;

        if (!isNumber(inputId)) {
            cout << "Product ID must be a positive integer. Please enter again." << endl;
            idfound = true;
            continue;
        }

        newProduct.id = stoi(inputId);

        if (newProduct.id <= 0) {
            cout << "Product ID must be a positive integer. Please enter again." << endl;
            idfound = true;
            continue;
        }

        for (int i = 0; i < productCount; i++) {
            if (products[i].id == newProduct.id) {
                cout << "Product ID already exists. Please enter a unique ID." << endl;
                idfound = true;
                break;
            }
        }
    } while (idfound);

    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, newProduct.name);

    while (!isAlpha(newProduct.name)) {
        cout << "Product name must contain only letters, spaces, or hyphens. Please enter again." << endl;
        getline(cin, newProduct.name);
    }

    string inputPrice;
    do {
        cout << "Enter product price: ";
        cin >> inputPrice;

        if (!isNumber(inputPrice) || stod(inputPrice) <= 0) {
            cout << "Price must be a positive number. Please enter again." << endl;
        }
    } while (!isNumber(inputPrice) || stod(inputPrice) <= 0);

    newProduct.price = stod(inputPrice);

    string inputDiscount;
    do {
        cout << "Enter product discount: ";
        cin >> inputDiscount;

        if (!isNumber(inputDiscount) || stod(inputDiscount) < 0) {
            cout << "Discount cannot be negative. Please enter again." << endl;
        }
    } while (!isNumber(inputDiscount) || stod(inputDiscount) < 0);

    newProduct.discount = stod(inputDiscount);
    newProduct.finalprice = newProduct.price - (newProduct.discount / 100.0) * newProduct.price;

    products[productCount] = newProduct;
    productCount++;
}

void editProduct(Product products[], int productCount) {
    int id;
    string inputId;
    cout << "Enter product ID to edit: ";
    cin >> inputId;

    if (!isNumber(inputId)) {
        cout << "Product ID must be a positive integer. Please enter again." << endl;
        return;
    }

    id = stoi(inputId);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, products[i].name);
            cout << "Enter new price: ";
            cin >> products[i].price;
            cout << "Enter new discount: ";
            cin >> products[i].discount;
            products[i].finalprice = products[i].price - (products[i].discount / 100.0) * products[i].price;
            return;
        }
    }
    cout << "Product not found!" << endl;
}

void deleteProduct(Product products[], int& productCount) {
    int id;
    string inputId;
    cout << "Enter product ID to delete: ";
    cin >> inputId;

    if (!isNumber(inputId)) {
        cout << "Product ID must be a positive integer. Please enter again." << endl;
        return;
    }

    id = stoi(inputId);
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            products[i] = products[productCount - 1];
            productCount--;
            return;
        }
    }
    cout << "Product not found!" << endl;
}

void handleUserInput(Product products[], int& productCount) {
    int choice;
    while (true) {
        showMenu();
        string inputChoice;
        cin >> inputChoice;

        if (!isNumber(inputChoice)) {
            cout << "Invalid choice! Please enter a number between 1 and 7." << endl;
            continue;
        }

        choice = stoi(inputChoice);
        switch (choice) {
        case 1:
            addProduct(products, productCount);
            break;
        case 2:
            editProduct(products, productCount);
            break;
        case 3:
            deleteProduct(products, productCount);
            break;
        case 7:
            return;
        default:
            cout << "Invalid choice! Please enter a number between 1 and 7." << endl;
            break;
        }
    }
}

int main() {
    cout << "WELCOME TO THE STORE MANAGEMENT PROGRAM!" << endl;
    Product products[MAX_PRODUCTS];
    int productCount = 0;
    handleUserInput(products, productCount);
    return 0;
}
