#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ========== Base class: Product ==========
class Product {
private:                    // hidden data (Encapsulation)
    double price;

protected:                  // visible to child classes
    string name;

public:                     // visible to everyone
    // Constructor
    Product(string name, double price) {
        this->name = name;
        setPrice(price);
    }

    // Destructor
    virtual ~Product() {
        cout << "Product " << name << " deleted\n";
    }

    // Getter and Setter
    double getPrice() const { return price; }
    void setPrice(double p) {
        if (p >= 0) price = p;
        else price = 0;     // negative price not allowed
    }
    string getName() const { return name; }

    // Virtual functions (Polymorphism)
    virtual void display() const {
        cout << name << " | Price: " << price;
    }
    virtual double getDiscount() const {
        return 0;
    }

    // Function Overloading: same name, different parameters
    double getTotal(int quantity) const {
        return price * quantity;
    }
    double getTotal(int quantity, double discountPercent) const {
        double total = price * quantity;
        return total - (total * discountPercent / 100);
    }
};

// ========== Child class 1: Clothing ==========
class Clothing : public Product {
private:
    string size;

public:
    Clothing(string name, double price, string size) : Product(name, price) {
        this->size = size;
    }

    void display() const override {
        cout << "[Clothing] ";
        Product::display();
        cout << " | Size: " << size << endl;
    }
    double getDiscount() const override { return 10; }   // 10%
};

// ========== Child class 2: Shoes ==========
class Shoes : public Product {
private:
    int shoeSize;

public:
    Shoes(string name, double price, int shoeSize) : Product(name, price) {
        this->shoeSize = shoeSize;
    }

    void display() const override {
        cout << "[Shoes] ";
        Product::display();
        cout << " | Size: " << shoeSize << endl;
    }
    double getDiscount() const override { return 15; }   // 15%
};

// ========== Main program ==========
int main() {
    vector<Product*> products;          // list of products (base pointers)

    products.push_back(new Clothing("Blazer", 75, "M"));
    products.push_back(new Shoes("Heels", 60, 38));

    int choice;
    do {
        cout << "\n=== BAH by SAFANA Boutique ===\n";
        cout << "1. Add product\n";
        cout << "2. Show products\n";
        cout << "3. Sell product\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            int type;
            string name;
            double price;
            cout << "1) Clothing  2) Shoes: ";
            cin >> type;
            cout << "Name (no spaces): ";
            cin >> name;
            cout << "Price: ";
            cin >> price;

            if (type == 1) {
                string size;
                cout << "Size: ";
                cin >> size;
                products.push_back(new Clothing(name, price, size));
            } else if (type == 2) {
                int s;
                cout << "Shoe size: ";
                cin >> s;
                products.push_back(new Shoes(name, price, s));
            } else {
                cout << "Invalid type\n";
            }
        }
        else if (choice == 2) {
            for (size_t i = 0; i < products.size(); i++) {
                cout << i + 1 << ". ";
                products[i]->display();          // Polymorphism
            }
        }
        else if (choice == 3) {
            int number, qty;
            cout << "Product number: ";
            cin >> number;
            if (number < 1 || number > (int)products.size()) {
                cout << "Product not found\n";
            } else {
                Product* p = products[number - 1];
                cout << "Quantity: ";
                cin >> qty;
                cout << "Total: $" << p->getTotal(qty) << endl;
                cout << "Total after " << p->getDiscount() << "% discount: $"
                     << p->getTotal(qty, p->getDiscount()) << endl;
            }
        }
    } while (choice != 0);

    // Free memory (calls destructors)
    for (size_t i = 0; i < products.size(); i++) {
        delete products[i];
    }
    return 0;
}