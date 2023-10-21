#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Product {
public:
    string name;
    double price;
    int quantity;
    virtual double calculateTotalPrice() const {
        return price * quantity;
    }
    virtual void displayInfo() const {
        cout << name << " - $" << price << " - Quantity: " << quantity << endl;
    }
};
 
class Electronics : public Product {
public:
    int warranty;
    double calculateTotalPrice() const override {
        return price * quantity + 10; // Additional cost for warranty
    }
    void displayInfo() const override {
        cout << name << " (Electronics) - $" << price << " - Quantity: " << quantity << " - Warranty: " << warranty << " months" << endl;
    }
};

class Clothing : public Product {
public:
    string size;
    void displayInfo() const override {
        cout << name << " (Clothing) - $" << price << " - Quantity: " << quantity << " - Size: " << size << endl;
    }
};

class Medicine : public Product {
public:
    string type;
    void displayInfo() const override {
        cout << name << " (Medicine) - $" << price << " - Quantity: " << quantity << " - Type: " << type << endl;
    }
};
class Grocery : public Product {
public:
    string category;
    void displayInfo() const override {
        cout << name << " (Grocery) - $" << price << " - Quantity: " << quantity << " - Category: " << category << endl;
    }
};

class ShoppingCart {
public:
    vector<Product> cart;
    void addProduct(const Product& product, int quantity) {
        Product productCopy = product; // Create a copy of the product
        productCopy.quantity = quantity; // Set the desired quantity
        cart.push_back(productCopy); // Add the product to the cart
    }
    double calculateTotalPrice() const {
        double total = 0;
        for (const Product& product : cart) {
            total += product.calculateTotalPrice();
        }
        return total;
    }
void generateInvoice() const {
    cout << "\n--- Invoice ---\n";
    cout << left << setw(30) << "Product";
    cout << setw(12) << "Price";
    cout << setw(10) << "Quantity";
    cout << setw(15) << "Total Price" << endl;
    
    for (const Product& product : cart) {
        cout << left << setw(30) << product.name;
        cout << setw(12) << fixed << setprecision(2) << product.price;
        cout << setw(10) << product.quantity;
        cout << setw(15) << fixed << setprecision(2) << product.calculateTotalPrice() << endl;
    }
    
    double totalPrice = calculateTotalPrice();
    cout << right << "Total Price: $" << fixed << setprecision(2) << totalPrice << endl;
}
};

class Shop {
public:
    vector<Product> itemList;

    void addItem(const Product& product) {
        itemList.push_back(product);
    }

    void deleteItem(int index, int quantity) {
        if (index >= 0 && index < itemList.size()) {
            if (itemList[index].quantity >= quantity) {
                itemList[index].quantity -= quantity;
            } else {
                cout << "Error: Quantity specified for deletion exceeds available quantity." << endl;
            }
        }
    }

    void displayItems() const {
        cout << "Available Items:\n";
        for (size_t i = 0; i < itemList.size(); ++i) {
            cout << i + 1 << ". ";
            itemList[i].displayInfo();
        }
    }

    void inputProducts() {
        while (true) {
            cout << "Enter product type (1 for Electronics, 2 for Clothing, 3 for Medicine, 4 for Grocery, 0 to finish): ";
            int choice;
            cin >> choice;

            if (choice == 0) {
                break;  // Exit the loop
            }

            string name;
            double price;
            int quantity;
            if (choice == 1) {
                cout << "Enter electronics name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                int warranty;
                cout << "Enter warranty (months): ";
                cin >> warranty;
                Electronics product;
                product.name = name;
                product.price = price;
                product.quantity = quantity;
                product.warranty = warranty;
                addItem(product);
            } else if (choice == 2) {
                cout << "Enter clothing name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                string size;
                cout << "Enter size: ";
                cin.ignore();
                getline(cin, size);
                Clothing product;
                product.name = name;
                product.price = price;
                product.quantity = quantity;
                product.size = size;
                addItem(product);
            } else if (choice == 3) {
                cout << "Enter medicine name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                string type;
                cout << "Enter type: ";
                cin.ignore();
                getline(cin, type);
                Medicine product;
                product.name = name;
                product.price = price;
                product.quantity = quantity;
                product.type = type;
                addItem(product);
            } else if (choice == 4) {
                cout << "Enter grocery name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                string category;
                cout << "Enter category: ";
                cin.ignore();
                getline(cin, category);
                Grocery product;
                product.name = name;
                product.price = price;
                product.quantity = quantity;
                product.category = category;
                addItem(product);
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

int main() {
    Shop shop;
    ShoppingCart cart;

    cout << "Enter products available in the shop:\n";
    shop.inputProducts();

    shop.displayItems();

    while (true) {
        cout << "Enter item number to add to the cart (0 to finish, -1 to remove an item): ";
        int choice;
        cin >> choice;

        if (choice == 0) {
            break;  // Exit the loop
        } else if (choice == -1) {
            cout << "Enter the item number to remove: ";
            int itemIndex;
            cin >> itemIndex;
            cout << "Enter the quantity to remove: ";
            int removeQuantity;
            cin >> removeQuantity;
            shop.deleteItem(itemIndex - 1, removeQuantity);
        } else if (choice >= 1 && choice <= shop.itemList.size()) {
            cout << "Enter the quantity to add to the cart: ";
            int cartQuantity;
            cin >> cartQuantity;
            cart.addProduct(shop.itemList[choice - 1], cartQuantity);
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    cart.generateInvoice();

    return 0;
}
