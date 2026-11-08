#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ===== Base class =====
class Product {
    double price;                       // Encapsulation
protected:
    string name;
public:
    Product(string n, double p) : name(n) { setPrice(p); }
    virtual ~Product() { cout << "Product " << name << " deleted\n"; }

    double getPrice() const { return price; }
    void setPrice(double p) { price = p >= 0 ? p : 0; }

    virtual void display() const { cout << name << " | Price: " << price; }
    virtual double getDiscount() const { return 0; }

    // Overloading
    double getTotal(int q) const { return price * q; }
    double getTotal(int q, double d) const { return price * q * (1 - d / 100); }
};

// ===== Child classes =====
class Clothing : public Product {
    string size;
public:
    Clothing(string n, double p, string s) : Product(n, p), size(s) {}
    void display() const override {
        cout << "[Clothing] ";
        Product::display();
        cout << " | Size: " << size << endl;
    }
    double getDiscount() const override { return 10; }
};

class Shoes : public Product {
    int size;
public:
    Shoes(string n, double p, int s) : Product(n, p), size(s) {}
    void display() const override {
        cout << "[Shoes] ";
        Product::display();
        cout << " | Size: " << size << endl;
    }
    double getDiscount() const override { return 15; }
};

// ===== Menu functions =====
void addProduct(vector<Product*>& products) {
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
        int size;
        cout << "Shoe size: ";
        cin >> size;
        products.push_back(new Shoes(name, price, size));
    } else {
        cout << "Invalid type\n";
    }
}

void showProducts(const vector<Product*>& products) {
    for (size_t i = 0; i < products.size(); i++) {
        cout << i + 1 << ". ";
        products[i]->display();         // Polymorphism
    }
}

void sellProduct(const vector<Product*>& products) {
    int n, q;
    cout << "Product number: ";
    cin >> n;

    if (n < 1 || n > (int)products.size()) {
        cout << "Product not found\n";
        return;
    }

    Product* p = products[n - 1];
    cout << "Quantity: ";
    cin >> q;
    cout << "Total: $" << p->getTotal(q) << endl;
    cout << "Total after " << p->getDiscount() << "% discount: $"
         << p->getTotal(q, p->getDiscount()) << endl;
}

// ===== Main =====
int main() {
    vector<Product*> products = { new Clothing("Blazer", 75, "M"),
                                  new Shoes("Heels", 60, 38) };
    int choice;
    do {
        cout << "\n=== BAH by SAFANA Boutique ===\n"
             << "1. Add product\n2. Show products\n3. Sell product\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1)      addProduct(products);
        else if (choice == 2) showProducts(products);
        else if (choice == 3) sellProduct(products);
    } while (choice != 0);

    for (auto p : products) delete p;   // calls destructors
    return 0;
}
