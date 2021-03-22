#include "../src/TableProducts.h"
#include "../src/product.h"
#include<iostream>


int test() {
    TableProducts tp = TableProducts(8, 0.8);
    string s = "ZZZ";
    //  Hash hash;
    string s1 = "AAA";
    product p1 = product(s, 1, "12", "12");
    product p2 = product(s1, 1, "12", "12");
    for (int i = 0; i < 90; i++) {
        p1.name[2]--;
        p1.barcode = 100 + i;
        //     product p = product(to_string(i), 100 - i, "", "");
        cout << tp.Add(p1) << endl;
        p2.name[0]++;
        p2.barcode = 300 - i;
        tp.Add(p2);
    }

    cout << tp;


    for (int i = 0; i < 99; i++) {

        //   product p = product(to_string(i), 100 - i, "", "");
        //     cout << p1.name << " " << p1.barcode << endl;
        cout << tp.Remove(p1) << endl;
        p1.name[2] += 1;
        p1.barcode -= 1;
        cout << p2.name << " " << p2.barcode << endl;
        cout << tp.Remove(p2) << endl;
        p2.name[0] -= 1;
        p2.barcode += 1;
    }

    cout << tp;


    for (int i = 0; i < 10; i++) {
        p2.name[0] -= 2;
        p2.barcode += 2;
        tp.Add(p2);
        //   product p = product(to_string(i), 100 - i, "", "");
//        cout << p1.name << " " << p1.barcode << endl;
        cout << tp.Add(p2) << endl;
    }


    cout << tp;


    for (int i = 0; i < 5; i += 2) {
        s[2] -= 2;
        product p1 = product(s, i, "12", "12");
        cout << p1.name << " " << p1.barcode << " " << hash.HashFunction1(p1.name + std::to_string(p1.barcode), 20)
             << endl;
        tp.Add(p1);
    }
    cout << tp;
    cout << endl << "----------------------" << endl;


//    product p1 = product("z", 1, "12", "12");
//    product p2 = product("y", 2, "12", "12");
//
//    cout << "0 " << tp.Find(p2) << endl;
//    cout << "1 " << tp.Add(p1) << endl;
//    cout << "1 " << tp.Find(p1) << endl;
//    cout << "1 " << tp.Add(p2) << endl;
//    cout << "1 " << tp.Find(p1) << endl;
//    cout << "1 " << tp.Find(p2) << endl;
//    cout << "1 " << tp.Remove(p2) << endl;
//    cout << "0 " << tp.Find(p2) << endl;
//    cout << "0 " << tp.Remove(p2) << endl;
//    cout << "1 " << tp.Find(p1) << endl;
//    cout << "1 " << tp.Add(p2) << endl;
//    cout << tp;
    return 0;

}