#include <iostream>
#include "source.h"

//  4.  Напишите функцию swap для двух int * и int &amp;.
void swap(int * a, int * b){
    int temp= *a;
    *a = *b;
    *b = temp;
}

void swap(int & a, int & b){
    int temp= a;
    a = b;
    b = temp;
}


int main(){
    /*
     *1.  Напишите следующие объявления: указатель на символ, массив из 10 целых,
ссылка на массив из 10 целых, указатель на массив строк, указатель на указатель на
символ, целая константа, указатель на целую константу, константный указатель на
целое. Проинициализируйте все объекты.
     *
     * */
    char c = 'c';
    char * s = &c;
    std::cout<<*s;

    int * k = new int[10]{1,2,3,4,5,6,7,8,9,10};

    int* (&p) = k;
    for (int i = 0; i< 10;i++) {
        std::cout << p[i];
    }
    delete[] k;

    std::string * string_pointer  = new std::string[2]{"abc","abc"};
    std::string * (*pp_string) = &string_pointer;
    for (int i = 0; i < 2; ++i) {
        std::cout<<(*pp_string)[i];
    }

    char symbol = '|';
    char (*ww) = &symbol;
    char * (*ws) = &ww;
    std::cout<<*(*ws);

    const int const_int = 5;
    const int * qwe = &const_int;
    std::cout<<*qwe;

    int l = 4;
    const int * r = &l;
    std::cout<<*r;

//   2. Примитивные типы С++ и ограничения на их размеры.
    //Тут все понятно

//   3. Перечислите характеристики объекта в ООП.
//Все понятно

//  4.  Напишите функцию swap для двух int * и int &amp;.
    int swap_1 = 3;
    int swap_2 = 4;
    swap(swap_1, swap_2);
    std::cout<<std::endl<<"Must be 4 and 3, then 3 and 4"<<std::endl;
    std::cout<<swap_1<<swap_2<<std::endl;
    swap(&swap_1, &swap_2);
    std::cout<<swap_1<<swap_2;

    //задача 6
// class A;
//class B: public A;
//class C: public B;
//Напишите try-catch, который ловит и различает исключения типов A, B и С.
//Реализуйте эти классы так, чтобы в качестве дополнительной информации в
//        исключении хранился его код. Код каждого исключения передается в момент его
//        создания и получался следующим образом: конкатенация переданного кода и
//порядкового номера класса в ветке наследования (А – 0, B – 1 и т.д.). Порядковый
//        номер должен считаться автоматически.
    std::cout<<std::endl;
    try{
        throw Bs("Nothing");
    }
    catch (Cs & excep){

    }
    catch (Bs & excep){

    }
    catch (As & excep)
    {

    }
}
