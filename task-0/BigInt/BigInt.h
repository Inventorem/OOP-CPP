#ifndef OOP_BIGINT_H
#define OOP_BIGINT_H
#include <iostream>
#include <vector>
class BigInt;
typedef BigInt bd;
typedef BigInt bigint;
class BigInt {
public:
    BigInt(){}
    BigInt(int value){

    }
    BigInt(std::string value){

    } // бросать исключение std::invalid_argument при ошибке

    // copying contructor
   /* 1. аргумент функции по значению, возвращение
    2. Декларирование и инициализация в одной строчке
    3. операторы и прочее
    Компилятор создает дефолтный копир.конструктор*/
    BigInt(const BigInt&);

    /*Простой человеческий деструктор, стоит попробовать с динамической памятью*/
    ~BigInt();

    BigInt& operator=(const BigInt&) {//возможно присваивание самому себе!
    }
    BigInt operator~() const;

    BigInt& operator++();
    const BigInt operator++(int) const;
    BigInt& operator--();
    const BigInt operator--(int) const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    operator std::string() const;

    size_t size() const;  // size in bytes

private:
    char sign;
    std::vector<int> value();
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i);


#endif //OOP_BIGINT_H
