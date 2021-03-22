#ifndef HASH_TABLE_TABLEPRODUCTS_H
#define HASH_TABLE_TABLEPRODUCTS_H

#include <utility>
#include "math.h"
#include "product.h"
#include "Hash.h"

struct Node {
    bool state;
    product value;

    explicit Node(product value_) : value(std::move(value_)), state(true) {}
};

class TableProducts {
private:
    double rehashSize;
    int size; // сколько элементов у нас сейчас в массиве
    int bufferSize; // сколько памяти выделено
    Hash hash;
    Node **values;

    void resize_base(bool flag) {
        int past_buffer_size = bufferSize;
        if (flag) {
            bufferSize *= 2;
        } else {
            bufferSize /= 2;
        }

        size = 0;
        Node **arr2 = new Node *[bufferSize];
        for (int i = 0; i < bufferSize; ++i)
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

    void constriction() {
        resize_base(false);
    }

    void resize() {
        resize_base(true);
    }

    void rehash() {
        size = 0;
        Node **arr2 = new Node *[bufferSize];
        for (int i = 0; i < bufferSize; ++i)
            arr2[i] = nullptr;
        std::swap(values, arr2);
        for (int i = 0; i < bufferSize; ++i) {
            if (arr2[i] && arr2[i]->state)
                Add(arr2[i]->value);
        }
        // удаление предыдущего массива
        for (int i = 0; i < bufferSize; ++i)
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

public:

    TableProducts(int pow_size = 3, double rehash_size_ = 0.95) {
        bufferSize = pow(2, pow_size);
        rehashSize = rehash_size_;
        if (rehashSize >= 1.0) {
            rehashSize = 0.80;
        }
        values = new Node *[bufferSize];
        size = 0;

        for (int i = 0; i < bufferSize; ++i)
            values[i] = nullptr; // заполняем nullptr - то есть если значение отсутствует, и никто раньше по этому адресу не обращался}
    }

    ~TableProducts() {
        for (int i = 0; i < bufferSize; ++i)
            if (values[i])
                delete values[i];
        delete[] values;
    }


    bool Add(product product_) {
        if (size + 1 > int(rehashSize * bufferSize))
            resize();
        int hash1 = hash.HashFunction1(product_.name + std::to_string(product_.barcode), bufferSize);
        if (values[hash1] == nullptr) {
            ++size;
            values[hash1] = new Node(product_);
            return true;
        }
        if (values[hash1]->value == product_) {
            return false;
        }

        int i = 1;
        int hash2;
        while (i < bufferSize) {
            hash2 = hash.HashFunction2(hash1, i, bufferSize);

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
        return false;
    }


    bool Find(product product_) {
        int hash1 = hash.HashFunction1(product_.name + std::to_string(product_.barcode), bufferSize);
        if (values[hash1] != nullptr && values[hash1]->state && values[hash1]->value == product_) {
            return true;
        }
        int i = 0;
        int hash2 = hash.HashFunction2(hash1, i, bufferSize);
        while (values[hash2] != nullptr && i < bufferSize) {
            hash2 = hash.HashFunction2(hash1, i, bufferSize);
            if (values[hash2]->state && values[hash2]->value == product_) {
                return true;
            }
            ++i;
        }
        return false;
    }

    bool Remove(product product_) {
        if (size + 30 < int(rehashSize * bufferSize))
            constriction();
        int hash1 = hash.HashFunction1(product_.name + std::to_string(product_.barcode), bufferSize);
        if (values[hash1] != nullptr && values[hash1]->state && values[hash1]->value == product_) {
            values[hash1]->state = false;
            rehash();
            return true;
        }
        int i = 0;
        int hash2 = hash.HashFunction2(hash1, i, bufferSize);
        while (values[hash2] != nullptr && i < bufferSize) {
            hash2 = hash.HashFunction2(hash1, i, bufferSize);
            if (values[hash2] != nullptr && values[hash2]->state && values[hash2]->value == product_) {
                values[hash2]->state = false;
                rehash();
                return true;
            }
            ++i;
        }
        return false;
    }


    friend std::ostream &operator<<(std::ostream &out, const TableProducts &products) {
        cout << products.bufferSize << endl;
        cout << products.size << endl;
        for (int i = 0; i < products.bufferSize; i++) {
            if (products.values[i] != nullptr && products.values[i]->state) {
                cout << i << " " << products.values[i]->value;
            }
        }
        return out;
    }
};


#endif //HASH_TABLE_TABLEPRODUCTS_H