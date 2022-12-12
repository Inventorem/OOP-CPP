#include "BigInt.h"

BigInt::BigInt() {

}

BigInt::BigInt(){

}
BigInt::BigInt(int value){

}
BigInt::BigInt(std::string value){

} // бросать исключение std::invalid_argument при ошибке

// copying contructor
/* 1. аргумент функции по значению, возвращение
 2. Декларирование и инициализация в одной строчке
 3. операторы и прочее
 Компилятор создает дефолтный копир.конструктор*/
BigInt(const BigInt&);

/*Простой человеческий деструктор, стоит попробовать с динамической памятью*/
BigInt::~BigInt();

BigInt BigInt& ::operator=(const BigInt&) {//возможно присваивание самому себе!


}