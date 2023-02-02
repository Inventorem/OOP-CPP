# **Task 1. Type BigInt**

### **Realisation**

class BigInt {

` `public:

`  `BigInt();

`  `BigInt(int);

`  `BigInt(std::string); // std::invalid\_argument for error

`  `BigInt(const BigInt&);

`  `~BigInt();

`  `BigInt& operator=(const BigInt&); //can be used to itself

`  `BigInt operator~() const;

`  `BigInt& operator++();

`  `const BigInt operator++(int) const;

`  `BigInt& operator--();

`  `const BigInt operator--(int) const;

`  `BigInt& operator+=(const BigInt&);

`  `BigInt& operator\*=(const BigInt&);

`  `BigInt& operator-=(const BigInt&);

`  `BigInt& operator/=(const BigInt&);

`  `BigInt& operator^=(const BigInt&);

`  `BigInt& operator%=(const BigInt&);

`  `BigInt& operator&=(const BigInt&);

`  `BigInt& operator|=(const BigInt&);

`  `BigInt operator+() const; // unary +

`  `BigInt operator-() const; // unary -

`  `bool operator==(const BigInt&) const;

`  `bool operator!=(const BigInt&) const;

`  `bool operator<(const BigInt&) const;

`  `bool operator>(const BigInt&) const;

`  `bool operator<=(const BigInt&) const;

`  `bool operator>=(const BigInt&) const;

`  `operator int() const;

`  `operator std::string() const;

`  `size\_t size() const; // size in bytes

};

BigInt operator+(const BigInt&, const BigInt&);

BigInt operator-(const BigInt&, const BigInt&);

BigInt operator\*(const BigInt&, const BigInt&);

BigInt operator/(const BigInt&, const BigInt&);

BigInt operator^(const BigInt&, const BigInt&);

BigInt operator%(const BigInt&, const BigInt&);

BigInt operator&(const BigInt&, const BigInt&);

BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream& o, const BigInt& i);
