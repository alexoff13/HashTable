#ifndef HASH_TABLE_TABLEPRODUCTS_H
#define HASH_TABLE_TABLEPRODUCTS_H

#include <utility>

#include "product.h"
#include "Hash.h"

struct Node {
    bool state;
    product value;

    explicit Node(product value_) : value(std::move(value_)), state(true) {}
};

class TableProducts {

//    static const int default_size = 8;
//    constexpr static const double default_rehash_size = 0.95;
    double rehash_size;
    int size; // сколько элементов у нас сейчас в массиве
    int buffer_size; // сколько памяти выделено

    Hash hash;
    Node **values;

    void Resize() {
        int past_buffer_size = buffer_size;
        buffer_size *= 2;

        size = 0;
        Node **arr2 = new Node *[buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr2[i] = nullptr;
        std::swap(values, arr2);
        for (int i = 0; i < past_buffer_size; ++i) {
            if (arr2[i] && arr2[i]->state)
                Add(arr2[i]->value); // добавляем элементы в новый массив
        }
        // удаление предыдущего массива
        for (int i = 0; i < past_buffer_size; ++i)
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

    void Rehash() {
        size = 0;
        Node **arr2 = new Node *[buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr2[i] = nullptr;
        std::swap(values, arr2);
        for (int i = 0; i < buffer_size; ++i) {
            if (arr2[i] && arr2[i]->state)
                Add(arr2[i]->value);
        }
        // удаление предыдущего массива
        for (int i = 0; i < buffer_size; ++i)
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

public:

    TableProducts(int buffer_size_ = 8, double rehash_size_ = 0.95) {
        buffer_size = buffer_size_;
        rehash_size = rehash_size_;
        values = new Node *[buffer_size];
        size = 0;

        for (int i = 0; i < buffer_size; ++i)
            values[i] = nullptr; // заполняем nullptr - то есть если значение отсутствует, и никто раньше по этому адресу не обращался}
    }

    ~TableProducts() {
        for (int i = 0; i < buffer_size; ++i)
            if (values[i])
                delete values[i];
        delete[] values;
    }


    bool Add(product product_) {
        if (size + 1 > int(rehash_size * buffer_size))
            Resize();
        int hash1 = hash.HashFunction1(product_.name + std::to_string(product_.barcode), buffer_size);
        if (values[hash1] == nullptr) {
            ++size;
            values[hash1] = new Node(product_);
            return true;
        }
        if (values[hash1]->value == product_) {
            return false;
        }

        int i = 0;
        int hash2 = hash.HashFunction2(hash1, i, buffer_size);
        while (/*values[hash2] == nullptr &&*/ i < buffer_size) {
            hash2 = hash.HashFunction2(hash1, i, buffer_size);

            if (values[hash2] == nullptr) {
                ++size;
                values[hash2] = new Node(product_);
                return true;
            }
            if (values[hash2]->value == product_) {
                return false;
            }
            ++i;
        }
    }


    bool Find(product product_) {
        int hash1 = hash.HashFunction1(product_.name + std::to_string(product_.barcode), buffer_size);
        if (values[hash1] != nullptr && values[hash1]->state && values[hash1]->value == product_) {
            return true;
        }
        int i = 0;
        int hash2 = hash.HashFunction2(hash1, i, buffer_size);
        while (values[hash2] != nullptr && i < buffer_size) {
            hash2 = hash.HashFunction2(hash1, i, buffer_size);
            if (values[hash2]->state && values[hash2]->value == product_) {
                return true;
            }
            ++i;
        }
        return false;
    }

    bool Remove(product product_) {
        int hash1 = hash.HashFunction1(product_.name + std::to_string(product_.barcode), buffer_size);
        if (values[hash1] != nullptr && values[hash1]->state && values[hash1]->value == product_) {
            values[hash1]->state = false;
            Rehash();
            return true;
        }
        int i = 0;
        int hash2 = hash.HashFunction2(hash1, i, buffer_size);
        while (values[hash2] != nullptr && i < buffer_size) {
            hash2 = hash.HashFunction2(hash1, i, buffer_size);
            if (values[hash2]->state && values[hash2]->value == product_) {
                values[hash2]->state = false;
                Rehash();
                return true;
            }
            ++i;
        }
        return false;
    }


    friend std::ostream &operator<<(std::ostream &out, const TableProducts &products) {
        cout << products.buffer_size << endl;
        cout << products.size << endl;
        for (int i = 0; i < products.buffer_size; i++) {
            if (products.values[i] != nullptr && products.values[i]->state) {
                cout << i << " " << products.values[i]->value;
            }
        }

        return out;
    }
};


#endif //HASH_TABLE_TABLEPRODUCTS_H






