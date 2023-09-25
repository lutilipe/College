#include <iostream>
#include "ringArray.hpp"
#include "item.hpp"

using namespace std;

void t1(){
    RingArray<int> ringArray(10);
    ringArray.push(0);
    ringArray.push(1);
    ringArray.push(2);
    ringArray.push(3);
    ringArray.print();
}

void t2(){
    RingArray<int> ringArray(10);
    ringArray.push(0);
    ringArray.push(1);
    ringArray.push(2);
    ringArray.push(3);
    cout << "Removido: " << ringArray.pop() << endl;
    ringArray.print();
}

void t3(){
    RingArray<int> ringArray(1);
    ringArray.push(-1);
    ringArray.print();
    ringArray.push(100);
    ringArray.print();
    ringArray.push(2);
    ringArray.print();
}

void t4(){
    RingArray<int> ringArray(4);
    ringArray.push(0);
    ringArray.push(1);
    ringArray.push(2);
    ringArray.push(3);
    cout << "Get: " << ringArray.get(2) << endl;
    ringArray.print();
}

void t5(){
    RingArray<int> ringArray(4);
    ringArray.push(0);
    ringArray.push(1);
    ringArray.push(100);
    ringArray.push(3);
    cout << "Maior: " << ringArray.get_maior() << endl;
}

void t6(){
    RingArray<int> ringArray(2);
    ringArray.push(1);
    ringArray.push(2);
    ringArray.push(3);
    cout << "Get: " << ringArray.get(0) << endl;
    cout << "Get: " << ringArray.get(1) << endl;
}

void t7(){
    RingArray<float> ringArray(4);
    ringArray.push(-0.5);
    ringArray.push(-5.5);
    ringArray.push(0.5);
    ringArray.push(4.5);
    cout << "Cheio: " << ringArray.is_full() << endl;
}

void t8(){
    RingArray<Item> ringArray(10);
    ringArray.push(Item(4,1000));
    ringArray.push(Item(1,3));
    ringArray.push(Item(2,100));
    ringArray.push(Item(3,-100));
    cout << "Removido: " << ringArray.pop() << endl;
    cout << "Maior: " << ringArray.get_maior() << endl;
    ringArray.print();
}

void t9(){
    RingArray<Item> ringArray(10);
    ringArray.push(Item(1,3));
    ringArray.push(Item(2,100));
    ringArray.push(Item(3,-100));
    cout << "Tamanho: " << ringArray.size() << endl;
    cout << "Removido: " << ringArray.pop() << endl;
    cout << "Removido: " << ringArray.pop() << endl;
    cout << "Get: " << ringArray.get(20) << endl;
    cout << "Maior: " << ringArray.get_maior() << endl;
    cout << "Removido: " << ringArray.pop() << endl;
    cout << "Tamanho: " << ringArray.size() << endl;
}

void t10(){
    RingArray<Item> ringArray(3);
    ringArray.push(Item(4,1000));
    ringArray.push(Item(1,3));
    ringArray.push(Item(2,100));
    ringArray.push(Item(3,-100));

    cout << "Get: " << ringArray.get(0) << endl;
    cout << "Get: " << ringArray.get(1) << endl;
    cout << "Get: " << ringArray.get(2) << endl;
    cout << "Get: " << ringArray.get(3) << endl;
    cout << "Cheio: " << ringArray.is_full() << endl;
    cout << "Removido: " << ringArray.pop() << endl;
    cout << "Get: " << ringArray.get(0) << endl;
    cout << "Get: " << ringArray.get(1) << endl;
    cout << "Get: " << ringArray.get(2) << endl;
    cout << "Get: " << ringArray.get(3) << endl;
    cout << "Maior: " << ringArray.get_maior() << endl;
}


int main(){
    int i;
    cin >> i;

    switch (i)
    {
    case 1:
        t1();
        break;
    case 2:
        t2();
        break;
    case 3:
        t3();
        break;
    case 4:
        t4();
        break;
    case 5:
        t5();
        break;
    case 6:
        t6();
        break;
    case 7:
        t7();
        break;
    case 8:
        t8();
        break;
    case 9:
        t9();
        break;
    case 10:
        t10();
        break;
    default:
        break;
    }
    return 0;
}

