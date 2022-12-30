#pragma once

#include <string>
#include <iostream>
#include <climits>
#include <cmath>
#include <algorithm>

class BigInt {
public:

    unsigned long long length;
    std::string value;
    bool sign;

    BigInt();

    explicit BigInt(int);

    explicit BigInt(std::string);

    BigInt(const BigInt &);

    ~BigInt();

    BigInt &operator=(const BigInt &);

    BigInt operator~() const;

    BigInt &operator++();

    const BigInt operator++(int);

    BigInt &operator--();

    const BigInt operator--(int);

    BigInt &operator+=(const BigInt &);

    BigInt &operator*=(const BigInt &);

    BigInt &operator-=(const BigInt &);

    BigInt &operator/=(const BigInt &);

    BigInt &operator^=(const BigInt &);

    BigInt &operator%=(const BigInt &);

    BigInt &operator&=(const BigInt &);

    BigInt &operator|=(const BigInt &);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt &) const;

    bool operator!=(const BigInt &) const;

    bool operator<(const BigInt &) const;

    bool operator>(const BigInt &) const;

    bool operator<=(const BigInt &) const;

    bool operator>=(const BigInt &) const;

    explicit operator int() const;

    explicit operator std::string() const;

    size_t size() const;

    static bool isNegative(BigInt &number);
private:
    static bool isNumber(std::string const &str);
};

BigInt operator+(const BigInt &, const BigInt &);

BigInt operator-(const BigInt &, const BigInt &);

BigInt operator*(const BigInt &, const BigInt &);

BigInt operator/(const BigInt &, const BigInt &);

BigInt operator^(const BigInt &, const BigInt &);

BigInt operator%(const BigInt &, const BigInt &);

BigInt operator&(const BigInt &, const BigInt &);

BigInt operator|(const BigInt &, const BigInt &);


std::ostream &operator<<(std::ostream &output_stream, const BigInt &number);
