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

    static const int default_size = 8;
    constexpr static const double rehash_size = 0.95;
    int size; // сколько элементов у нас сейчас в массиве
    int buffer_size; // сколько памяти выделено

    Hash hash;
public:
    Node **values;

    TableProducts() {
        values = new Node *[default_size];
        buffer_size = default_size;
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

//    void Rehash() {
//        size_all_non_nullptr = 0;
//        size = 0;
//        Node **arr2 = new Node *[buffer_size];
//        for (int i = 0; i < buffer_size; ++i)
//            arr2[i] = nullptr;
//        std::swap(values, arr2);
//        for (int i = 0; i < buffer_size; ++i) {
//            if (arr2[i] && arr2[i]->state)
//                Add(arr2[i]->value);
//        }
//        // удаление предыдущего массива
//        for (int i = 0; i < buffer_size; ++i)
//            if (arr2[i])
//                delete arr2[i];
//        delete[] arr2;
//    }

    //TODO добавить проверку на добавление одинаковых элементов
    bool Add(product product_) {
        if (size + 1 > int(rehash_size * buffer_size))
            Resize();
        int hash1 = hash.HashFunction1(product_.name + std::to_string(product_.barcode), buffer_size);
        ++size;
        if (values[hash1] == nullptr) {
            values[hash1] = new Node(product_);
            return true;
        }
        if (!values[hash1]->state) {
            values[hash1]->value = product_;
            values[hash1]->state = true;
            return true;
        }
        for (int i = 0; i < buffer_size; ++i) {
            int hash2 = hash.HashFunction2(hash1, i, buffer_size);
            if (values[hash2] == nullptr) {
                values[hash2] = new Node(product_);
                return true;
            } else if (!values[hash2]->state) {
                values[hash2]->value = product_;
                values[hash2]->state = true;
                return true;
            }
        }
        --size;
        return false;
    }

    bool Find(product product_) {
        int hash1 = hash.HashFunction1(product_.name + std::to_string(product_.barcode), buffer_size);
        if (values[hash1] != nullptr && values[hash1]->state && values[hash1]->value == product_) {
            return true;
        }
        for (int i = 0; i < buffer_size; ++i) {
            int hash2 = hash.HashFunction2(hash1, i, buffer_size);
            if (values[hash2] == nullptr)
                continue;
            if (values[hash2]->state && values[hash1]->value == product_) {
                return true;
            }
        }
        return false;
    }

    bool Remove(product product_) {
        int hash1 = hash.HashFunction1(product_.name + std::to_string(product_.barcode), buffer_size);
        if (values[hash1] != nullptr && values[hash1]->state && values[hash1]->value == product_) {
            values[hash1]->state = false;
            --size;
            return true;
        }
        for (int i = 0; i < buffer_size; ++i) {
            int hash2 = hash.HashFunction2(hash1, i, buffer_size);
            if (values[hash2] == nullptr)
                continue;
            if (values[hash2]->state && values[hash1]->value == product_) {
                --size;
                values[hash2]->state = false;
                return true;
            }
        }
        return false;
    }

};


#endif //HASH_TABLE_TABLEPRODUCTS_H






