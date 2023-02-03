#include <iostream>
#include "class.h"
#include "fibbo.h"

int main(){
    int table[10];
    for (int j = 0; j < 10; ++j) {
        table[j] = j%3;
    }
    communication * com;
    for (int i: table) {
        com = getcom(i);
        com->contact();
        std::cout<<std::endl;
    }
    std::cout<<factorial<5>::value;

}

