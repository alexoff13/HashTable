#include "TableProducts.h"
#include "product.h"
#include<iostream>


int main() {
    TableProducts tp = TableProducts(50, 1.0);
    string s="ZZZ";
  for (int i = 0; i < 5; i++) {
      s[2]--;
      product p1 = product(s, i, "12", "12");
        tp.Add(p1);
    }
    cout << tp;
  cout<<endl<<"----------------------"<<endl;

    s="ZZZ";
    for (int i = 0; i < 5; i+=2) {
        s[2]-=2;
        product p1 = product(s, i, "12", "12");
        tp.Add(p1);
    }
    cout << tp;
    cout<<endl<<"----------------------"<<endl;


    s="ZZZ";
    for (int i = 0; i < 5; i+=2) {
        s[2]-=2;
        product p1 = product(s, i, "12", "12");
        tp.Add(p1);
    }
    cout << tp;
    cout<<endl<<"----------------------"<<endl;

     s="ZZZ";
    for (int i = 0; i < 5; i+=2) {
        s[2]-=2;
        product p1 = product(s, i, "12", "12");
        tp.Remove(p1);
    }
    cout << tp;


    s="ZZZ";
    for (int i = 0; i < 5; i+=1) {
        s[2]-=1;
        product p1 = product(s, i, "12", "12");
        cout<<tp.Find(p1)<<endl;
    }
    cout << tp;

//for(int i=0;i<50;++i){
//    product p1 = product("name", i, "12", "12");
//       tp.Add(p1);
//}
//    cout<<tp<<endl;
//    product p1 = product("name", 48, "12", "12");
//    tp.Add(p1);
//cout<<tp<<endl;

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