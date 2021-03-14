#ifndef HASH_TABLE_PRODUCT_H
#define HASH_TABLE_PRODUCT_H

#include <utility>
#include "iostream"
#include "string"

using namespace std;

class product {
public:
    string name;
    unsigned long barcode;
    string dateOfPurchase;
    string dateOfExpiration;

    product(string Name, unsigned long Barcode, string DateOfPurchase, string DateOfExpiration) {
        this->name = std::move(Name);
        this->barcode = Barcode;
        this->dateOfPurchase = std::move(DateOfPurchase);
        this->dateOfExpiration = std::move(DateOfExpiration);
    }

    friend std::ostream &operator<<(std::ostream &out, const product &product) {
        out << "Product: " << product.name << "\nКуплен: " << product.dateOfPurchase << "\nГоден до: "
            << product.dateOfExpiration << "\nШтрихкод: " << product.barcode << "\n";

        return out;
    }

//    friend std::ostream &operator<<(std::ostream &out, const product &product) {
//        out << "Штрихкод: " << product.barcode << "\n";
//
//        return out;
//    }

    friend bool operator==(const product &a, const product &b) {
        return b.name == a.name && b.barcode == a.barcode && b.dateOfPurchase == a.dateOfPurchase &&
               b.dateOfExpiration == a.dateOfExpiration;
    }

};


#endif //HASH_TABLE_PRODUCT_H
