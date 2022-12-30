#include "BigInt.h"


bool BigInt::isNumber(std::string const &str) {
    auto it = str.begin();
    if (*it == '-')
        it++;
    while (it != str.end() && std::isdigit(*it)) {
        it++;
    }
    return !str.empty() && it == str.end();
}

BigInt::BigInt() {
    this->length = 0;
    this->sign = false;
    this->value;
}

BigInt::BigInt(int number) {
    if (number < 0) {
        this->value.assign(std::to_string(number), 1, std::to_string(number).length());
        this->sign = true;
    } else {
        this->sign = false;
        this->value = std::to_string(number);
    }
    this->length = this->value.length();
}

BigInt::BigInt(std::string string_number) {
    isNumber(string_number) ? this->value = string_number : throw std::invalid_argument("input data is not a digit");

    this->length = this->value.length();
    if (string_number[0] == '-') {
        this->sign = true;

        this->value.assign(this->value, 1, this->length - 1);
        this->length--;
    } else
        this->sign = false;

}

BigInt::BigInt(const BigInt &initial_number) {
    this->length = initial_number.length;
    this->sign = initial_number.sign;
    this->value = initial_number.value;
}

BigInt::~BigInt() {}

BigInt &BigInt::operator=(const BigInt &initial_number) {

    if (this == &initial_number) {
        return *this;
    }

    this->value = initial_number.value;
    this->length = initial_number.length;
    this->sign = initial_number.sign;
    return *this;
}

BigInt BigInt::operator~() const {
    BigInt result = *this;
    ++result;
    result.sign == 1 ? result.sign = false : result.sign = 1;
    return result;
}

//i++
BigInt &BigInt::operator++() {
    if (this->sign) {
        this->value[this->length - 1] -= 1;
        for (long long i = this->length - 1; i > 0; i--) {
            if (this->value[i] < '0') {
                this->value[i] = '9';
                this->value[i - 1] -= 1;
            } else
                break;
        }
        while (this->value[0] == '0' && this->length != 1) {
            this->value.assign(this->value, 1, this->length - 1);
            this->length--;
        }
    } else {
        this->value[this->length - 1] += 1;
        for (long long i = this->length - 1; i > 0; i--) {

            if (this->value[i] > '9') {
                this->value[i] = '0';
                this->value[i - 1] += 1;
            } else
                break;
        }
        if (this->value[0] > '9') {
            this->value[0] = '0';
            this->value = "1" + this->value;
            this->length = this->value.length();
        }
    }
    if (this->value == "0")
        this->sign = 0;
    return *this;
};

//++i
const BigInt BigInt::operator++(int) {
    BigInt new_number = *this;
    ++(*this);
    return new_number;
};

BigInt &BigInt::operator--() {
    this->sign == 1 ? this->sign = 0 : this->sign = 1;
    ++(*this);
    this->sign == 1 ? this->sign = 0 : this->sign = 1;
    if (this->value == "0")
        this->sign = 0;
    return *this;
};

const BigInt BigInt::operator--(int) {
    BigInt prev = *this;
    --(*this);
    return prev;
};

BigInt &BigInt::operator+=(const BigInt &increment_number) {
    BigInt temp = increment_number;
    if (temp.sign == 1 && this->sign == 0) {
        temp.sign = 0;
        *this -= temp;
        return *this;
    }
    if (temp.sign == 0 && this->sign == 1) {
        temp.sign = 1;
        *this -= temp;
        return *this;
    }

    std::string b;
    if (this->length > temp.length) {
        b.append(this->length - temp.length, '0');
        b += temp.value;
        for (long long i = this->length - 1; i > 0; i--) {
            this->value[i] += b[i] - '0';
            if (this->value[i] > '9') {
                this->value[i] -= 10;
                this->value[i - 1] += 1;
            }
        }
        this->value[0] += b[0] - '0';
        if (this->value[0] > '9') {
            this->value[0] -= 10;
            this->value = "1" + this->value;
            this->length = this->value.length();
        }
        return *this;
    } else {
        b.append(temp.length - this->length, '0');
        b += this->value;

        for (long long i = temp.length - 1; i > 0; i--) {
            temp.value[i] += b[i] - '0';
            if (temp.value[i] > '9') {
                temp.value[i] -= 10;
                temp.value[i - 1] += 1;
            }
        }
        temp.value[0] += b[0] - '0';
        if (temp.value[0] > '9') {
            temp.value[0] -= 10;

            temp.value = "1" + temp.value;
            temp.length = temp.value.length();
        }
        *this = temp;
        return *this;
    }
};

BigInt &BigInt::operator*=(const BigInt &mult) {
    BigInt product;
    bool sign_temp;
    if (mult.sign == this->sign) {
        sign_temp = 0;
    } else
        sign_temp = 1;
    product.sign = 0;
    product.length = 1;
    product.value = "0";
    BigInt Helper;
    Helper.sign = 0;
    size_t count = 0;
    for (long long i = mult.length - 1; i >= 0; i--) {
        Helper.value.append(this->length + 1, '0');
        for (long long j = this->length - 1; j >= 0; j--) {
            int mul = (this->value[j] - '0') * (mult.value[i] - '0');
            Helper.value[j + 1] += mul % 10;
            Helper.value[j] += mul / 10;
            if (Helper.value[j + 1] > '9') {
                Helper.value[j + 1] -= 10;
                Helper.value[j]++;
            }
        }
        Helper.value.append(mult.length - 1 - i, '0');
        Helper.length = Helper.value.length();
        product += Helper;
        Helper.value.clear();
    }
    product.sign = sign_temp;
    *this = product;
    while (this->value[0] == '0' && this->length != 1) {
        this->value.assign(this->value, 1, this->length - 1);
        this->length--;
    }
    return *this;
};

BigInt &BigInt::operator-=(const BigInt &decrement) {
    BigInt temp = decrement;
    if (temp.sign == 1 && this->sign == 0) {
        temp.sign = 0;
        *this += temp;
        return *this;
    }
    if (temp.sign == 0 && this->sign == 1) {
        temp.sign = 1;
        *this += temp;
        return *this;
    }
    if (*this == temp) {
        this->value = "0";
        this->sign = 0;
        this->length = 1;
        return *this;
    }
    std::string b;
    if (this->length > temp.length || ((this->length == temp.length) && (this->value > temp.value))) {
        b.append(this->length - temp.length, '0');
        b += temp.value;

        for (long long i = this->length - 1; i >= 0; i--) {
            this->value[i] -= b[i] - '0';
            if (this->value[i] < '0') {
                this->value[i] += 10;
                this->value[i - 1] -= 1;
            }
        }

    } else {
        if (this->length < temp.length || ((this->length == temp.length) && (this->value < temp.value))) {

            b.append(temp.length - this->length, '0');
            b += this->value;
            for (long long i = temp.length - 1; i >= 0; i--) {
                temp.value[i] -= b[i] - '0';
                if (temp.value[i] < '0') {
                    temp.value[i] += 10;
                    temp.value[i - 1] -= 1;
                }
            }

            *this = temp;
            this->sign == 1 ? this->sign = 0 : this->sign = 1;
        }
    }
    while (this->value[0] == '0' && this->length != 1) {
        this->value = this->value.assign(this->value, 1, this->length - 1);
        this->length--;
    }
    return *this;
};

BigInt &
BigInt::operator/=(const BigInt &divider) {
    if (divider.value == "0") {
        throw std::invalid_argument("div is not possible");
        return *this;
    }
    size_t count = 0;
    BigInt temp = divider;
    bool MorL;
    if (temp.sign == this->sign)
        MorL = 0;
    else
        MorL = 1;
    BigInt CopyThis;
    temp.sign = CopyThis.sign = 0;
    CopyThis.length = 0;
    for (long long i = 0; i < this->length; i) {
        if (CopyThis < temp) {

            CopyThis.value += this->value[i];
            CopyThis.length++;
            if (CopyThis < temp && (i != (this->length - 1)))
                count *= 10;
            i++;
        } else {
            while (CopyThis >= temp) {
                CopyThis -= temp;
                count++;
            }

            count *= 10;
        }

    }
    while (CopyThis >= temp) {
        CopyThis -= temp;
        count++;
    }
    if (count != 0) {
        this->sign = MorL;
        this->value = std::to_string(count);
        this->length = this->value.length();
    } else {
        this->sign = 0;
        this->value = "0";
        this->length = 1;
    }
    return *this;
};

BigInt &BigInt::operator^=(const BigInt &another) {
    BigInt PromThis = *this;
    BigInt PromAnother = another;
    BigInt Prom = another;
    BigInt Another_2cc;
    BigInt This_2cc;
    BigInt cc(2);
    bool MorL = this->sign;

    while (PromThis.value != "0") {
        PromThis %= cc;
        if (MorL) {
            if (PromThis.value == "1")
                This_2cc.value = "0" + This_2cc.value;
            else
                This_2cc.value = "1" + This_2cc.value;
        } else {

            This_2cc.value = PromThis.value + This_2cc.value;
        }
        *this /= cc;
        PromThis = *this;
    }

    while (PromAnother.value != "0") {
        PromAnother %= cc;
        if (another.sign) {
            if (PromAnother.value == "1")
                Another_2cc.value = "0" + Another_2cc.value;
            else
                Another_2cc.value = "1" + Another_2cc.value;
        } else {

            Another_2cc.value = PromAnother.value + Another_2cc.value;
        }
        Prom /= cc;
        PromAnother = Prom;
    }

    Another_2cc.length = Another_2cc.value.length();
    long long i = Another_2cc.length - 1;
    if (another.sign) {
        Another_2cc.value[i]++;

        while (Another_2cc.value[i] == '2') {
            Another_2cc.value[i] = '0';
            Another_2cc.value[i - 1]++;
            i--;
        }
    }

    This_2cc.length = This_2cc.value.length();
    i = This_2cc.length - 1;
    if (MorL) {
        This_2cc.value[i]++;

        while (This_2cc.value[i] == '2') {
            This_2cc.value[i] = '0';
            This_2cc.value[i - 1]++;
            i--;
        }
    }

    if (Another_2cc.length > This_2cc.length) {
        std::string b;
        b.append(Another_2cc.length - This_2cc.length, MorL + '0');
        This_2cc.value = b + This_2cc.value;
    } else {
        std::string b;
        b.append(This_2cc.length - Another_2cc.length, another.sign + '0');
        Another_2cc.value = b + Another_2cc.value;
    }
    Another_2cc.length = This_2cc.length;

    if (another.sign) {
        Another_2cc.value = "1" + Another_2cc.value;
    } else {
        Another_2cc.value = "0" + Another_2cc.value;
    }
    Another_2cc.length++;
    if (MorL) {
        This_2cc.value = "1" + This_2cc.value;
    } else {
        This_2cc.value = "0" + This_2cc.value;
    }
    This_2cc.length++;


    for (long long j = This_2cc.length - 1; j >= 0; j--) {
        This_2cc.value[j] = ((This_2cc.value[j] - '0') ^ (Another_2cc.value[j] - '0')) + '0';
    }

    int temp;
    if (This_2cc.value[0] == '0') {
        for (long long j = 1; j < This_2cc.length; j++) {

            temp = This_2cc.value[j] - '0';

            PromThis *= cc;
            PromThis.value[PromThis.length - 1] += temp;
        }
        *this = PromThis;
        this->sign = 0;
    } else {
        i = This_2cc.length - 1;
        This_2cc.value[i]--;

        while (This_2cc.value[i] < '0') {
            This_2cc.value[i] = '1';
            This_2cc.value[i - 1]--;
            i--;
        }
        for (long long j = 1; j < This_2cc.length; j++) {

            if (This_2cc.value[j] == '1')
                This_2cc.value[j] = '0';
            else
                This_2cc.value[j] = '1';

            temp = This_2cc.value[j] - '0';

            PromThis *= cc;
            PromThis.value[PromThis.length - 1] += temp;
        }
        *this = PromThis;
        this->sign = 1;
    }
    return *this;
}

BigInt &
BigInt::operator%=(const BigInt &another) {
    if (another.value == "0") {
        return *this;
    }
    BigInt Temp = another;
    bool MorL = this->sign;
    BigInt CopyThis;
    Temp.sign = CopyThis.sign = 0;

    CopyThis.length = 0;
    for (long long i = 0; i < this->length; i) {
        if (CopyThis < Temp) {
            CopyThis.value += this->value[i];
            CopyThis.length++;
            i++;
        } else {
            while (CopyThis >= Temp)
                CopyThis -= Temp;
        }
    }
    while (CopyThis >= Temp)
        CopyThis -= Temp;
    while (CopyThis.value[0] == '0' && CopyThis.length != 1) {
        CopyThis.value = CopyThis.value.assign(CopyThis.value, 1, CopyThis.length - 1);
        CopyThis.length--;
    }
    this->value = CopyThis.value;
    this->length = CopyThis.length;
    this->sign = MorL;
    return *this;
}

BigInt &BigInt::operator&=(const BigInt &another) {
    BigInt PromThis = *this;
    BigInt PromAnother = another;
    BigInt Prom = another;
    BigInt Another_2cc;
    BigInt This_2cc;
    BigInt cc(2);
    bool MorL = this->sign;

    while (PromThis.value != "0") {
        PromThis %= cc;
        if (MorL) {
            if (PromThis.value == "1")
                This_2cc.value = "0" + This_2cc.value;
            else
                This_2cc.value = "1" + This_2cc.value;
        } else {

            This_2cc.value = PromThis.value + This_2cc.value;
        }
        *this /= cc;
        PromThis = *this;
    }

    while (PromAnother.value != "0") {
        PromAnother %= cc;
        if (another.sign) {
            if (PromAnother.value == "1")
                Another_2cc.value = "0" + Another_2cc.value;
            else
                Another_2cc.value = "1" + Another_2cc.value;
        } else {

            Another_2cc.value = PromAnother.value + Another_2cc.value;
        }
        Prom /= cc;
        PromAnother = Prom;
    }

    Another_2cc.length = Another_2cc.value.length();
    long long i = Another_2cc.length - 1;
    if (another.sign) {
        Another_2cc.value[i]++;

        while (Another_2cc.value[i] == '2') {
            Another_2cc.value[i] = '0';
            Another_2cc.value[i - 1]++;
            i--;
        }
    }

    This_2cc.length = This_2cc.value.length();
    i = This_2cc.length - 1;
    if (MorL) {
        This_2cc.value[i]++;

        while (This_2cc.value[i] == '2') {
            This_2cc.value[i] = '0';
            This_2cc.value[i - 1]++;
            i--;
        }
    }

    if (Another_2cc.length > This_2cc.length) {
        std::string b;
        b.append(Another_2cc.length - This_2cc.length, MorL + '0');
        This_2cc.value = b + This_2cc.value;
    } else {
        std::string b;
        b.append(This_2cc.length - Another_2cc.length, another.sign + '0');
        Another_2cc.value = b + Another_2cc.value;
    }
    Another_2cc.length = This_2cc.length;

    if (another.sign) {
        Another_2cc.value = "1" + Another_2cc.value;
    } else {
        Another_2cc.value = "0" + Another_2cc.value;
    }
    Another_2cc.length++;
    if (MorL) {
        This_2cc.value = "1" + This_2cc.value;
    } else {
        This_2cc.value = "0" + This_2cc.value;
    }
    This_2cc.length++;


    for (long long j = This_2cc.length - 1; j >= 0; j--) {
        This_2cc.value[j] = ((This_2cc.value[j] - '0') & (Another_2cc.value[j] - '0')) + '0';
    }

    int temp;
    if (This_2cc.value[0] == '0') {
        for (long long j = 1; j < This_2cc.length; j++) {

            temp = This_2cc.value[j] - '0';

            PromThis *= cc;
            PromThis.value[PromThis.length - 1] += temp;
        }
        *this = PromThis;
        this->sign = 0;
    } else {
        i = This_2cc.length - 1;
        This_2cc.value[i]--;

        while (This_2cc.value[i] < '0') {
            This_2cc.value[i] = '1';
            This_2cc.value[i - 1]--;
            i--;
        }
        for (long long j = 1; j < This_2cc.length; j++) {

            if (This_2cc.value[j] == '1')
                This_2cc.value[j] = '0';
            else
                This_2cc.value[j] = '1';

            temp = This_2cc.value[j] - '0';

            PromThis *= cc;
            PromThis.value[PromThis.length - 1] += temp;
        }
        *this = PromThis;
        this->sign = 1;
    }
    return *this;
};

BigInt &BigInt::operator|=(const BigInt &another) {
    BigInt PromThis = *this;
    BigInt PromAnother = another;
    BigInt Prom = another;
    BigInt Another_2cc;
    BigInt This_2cc;
    BigInt cc(2);
    bool MorL = this->sign;

    while (PromThis.value != "0") {
        PromThis %= cc;
        if (MorL) {
            if (PromThis.value == "1")
                This_2cc.value = "0" + This_2cc.value;
            else
                This_2cc.value = "1" + This_2cc.value;
        } else {

            This_2cc.value = PromThis.value + This_2cc.value;
        }
        *this /= cc;
        PromThis = *this;
    }

    while (PromAnother.value != "0") {
        PromAnother %= cc;
        if (another.sign) {
            if (PromAnother.value == "1")
                Another_2cc.value = "0" + Another_2cc.value;
            else
                Another_2cc.value = "1" + Another_2cc.value;
        } else {

            Another_2cc.value = PromAnother.value + Another_2cc.value;
        }
        Prom /= cc;
        PromAnother = Prom;
    }

    Another_2cc.length = Another_2cc.value.length();
    long long i = Another_2cc.length - 1;
    if (another.sign) {
        Another_2cc.value[i]++;

        while (Another_2cc.value[i] == '2') {
            Another_2cc.value[i] = '0';
            Another_2cc.value[i - 1]++;
            i--;
        }
    }

    This_2cc.length = This_2cc.value.length();
    i = This_2cc.length - 1;
    if (MorL) {
        This_2cc.value[i]++;

        while (This_2cc.value[i] == '2') {
            This_2cc.value[i] = '0';
            This_2cc.value[i - 1]++;
            i--;
        }
    }

    if (Another_2cc.length > This_2cc.length) {
        std::string b;
        b.append(Another_2cc.length - This_2cc.length, MorL + '0');
        This_2cc.value = b + This_2cc.value;
    } else {
        std::string b;
        b.append(This_2cc.length - Another_2cc.length, another.sign + '0');
        Another_2cc.value = b + Another_2cc.value;
    }
    Another_2cc.length = This_2cc.length;

    if (another.sign) {
        Another_2cc.value = "1" + Another_2cc.value;
    } else {
        Another_2cc.value = "0" + Another_2cc.value;
    }
    Another_2cc.length++;
    if (MorL) {
        This_2cc.value = "1" + This_2cc.value;
    } else {
        This_2cc.value = "0" + This_2cc.value;
    }
    This_2cc.length++;


    for (long long j = This_2cc.length - 1; j >= 0; j--) {
        This_2cc.value[j] = ((This_2cc.value[j] - '0') | (Another_2cc.value[j] - '0')) + '0';
    }

    int temp;
    if (This_2cc.value[0] == '0') {
        for (long long j = 1; j < This_2cc.length; j++) {

            temp = This_2cc.value[j] - '0';

            PromThis *= cc;
            PromThis.value[PromThis.length - 1] += temp;
        }
        *this = PromThis;
        this->sign = 0;
    } else {
        i = This_2cc.length - 1;
        This_2cc.value[i]--;

        while (This_2cc.value[i] < '0') {
            This_2cc.value[i] = '1';
            This_2cc.value[i - 1]--;
            i--;
        }
        for (long long j = 1; j < This_2cc.length; j++) {

            if (This_2cc.value[j] == '1')
                This_2cc.value[j] = '0';
            else
                This_2cc.value[j] = '1';

            temp = This_2cc.value[j] - '0';

            PromThis *= cc;
            PromThis.value[PromThis.length - 1] += temp;
        }
        *this = PromThis;
        this->sign = 1;
    }
    return *this;
};

BigInt BigInt::operator+() const { return *this; }; // unary +

BigInt BigInt::operator-() const {
    BigInt copy = *this;
    copy.sign == 1 ? copy.sign = 0 : copy.sign = 1;
    return copy;
}; // unary -

bool BigInt::operator==(const BigInt &another) const {

    return (this->value == another.value) && (this->sign == another.sign);
};

bool BigInt::operator!=(const BigInt &another) const {

    return !(this->value == another.value) || (this->sign != another.sign);
};

bool BigInt::operator<(const BigInt &number) const {
    BigInt temp_from_this = *this;
    BigInt temp_from_number = number;
    if (temp_from_this.sign > number.sign) {
        return true;
    }
    if (temp_from_this.sign < number.sign) {
        return false;
    }
    if (temp_from_this.length < temp_from_number.length) {
        std::string b;
        b.append(temp_from_number.length - temp_from_this.length, '0');
        temp_from_this.value = b + temp_from_this.value;
        temp_from_this.length = temp_from_number.length;
    } else {
        std::string b;
        b.append(temp_from_this.length - temp_from_number.length, '0');
        temp_from_number.value = b + temp_from_number.value;
        temp_from_number.length = temp_from_this.length;
    }

    if (temp_from_this.sign) {

        switch (temp_from_this.value.compare(temp_from_number.value)) {
            case 1: {
                return true;
            }
            default: {
                return false;
            }
        }
    } else {

        switch (temp_from_this.value.compare(temp_from_number.value)) {
            case -1: {
                return true;
            }
            default: {
                return false;
            }
        }
    }
};

bool BigInt::operator>(const BigInt &another) const {
    BigInt temp_from_this = *this;
    BigInt temp_from_another = another;
    if (temp_from_this.sign > temp_from_another.sign) {
        return false;
    }
    if (temp_from_this.sign < temp_from_another.sign) {
        return true;
    }
    if (temp_from_this.length < temp_from_another.length) {
        std::string b;
        b.append(temp_from_another.length - temp_from_this.length, '0');
        temp_from_this.value = b + temp_from_this.value;
        temp_from_this.length = temp_from_another.length;
    } else {
        std::string b;
        b.append(temp_from_this.length - temp_from_another.length, '0');
        temp_from_another.value = b + temp_from_another.value;
        temp_from_another.length = temp_from_this.length;
    }
    if (temp_from_this.sign) {

        switch (temp_from_this.value.compare(temp_from_another.value)) {
            case 1: {
                return false;
            }
            default: {
                return true;
            }
        }
    } else {

        switch (temp_from_this.value.compare(temp_from_another.value)) {
            case -1: {
                return false;
            }
            default: {
                return true;
            }
        }
    }
};

bool BigInt::operator<=(const BigInt &number) const { return !((*this) > number); };

bool BigInt::operator>=(const BigInt &number) const { return !((*this) < number); };

BigInt::operator int() const {

    long long int_result = 0;

    int t = pow(-1, this->sign);
    for (long long i = 0; i < this->length; i++) {
        int_result = int_result * 10 + (this->value[i] - '0') * t;
        if (int_result > INT_MAX || int_result < INT_MIN)
            throw std::length_error("Number in string bigger then int");
    }


    return (int) int_result;
};

BigInt::operator std::string() const { return this->value; };

size_t BigInt::size() const { return this->length; }

bool BigInt::isNegative(BigInt &number) {
    return number.sign;
}

BigInt operator+(const BigInt &left_operand, const BigInt &right_operand) {
    BigInt result = left_operand;
    result += right_operand;
    return result;
}

BigInt operator-(const BigInt &left_operand, const BigInt &right_operand) {
    BigInt result = left_operand;
    result -= right_operand;
    return result;
}

BigInt operator*(const BigInt &left_operand, const BigInt &right_operand) {
    BigInt result = left_operand;
    result *= right_operand;
    return result;
}

BigInt operator/(const BigInt &left_operand, const BigInt &right_operand) {
    BigInt result = left_operand;
    result /= right_operand;
    return result;
};

BigInt operator^(const BigInt &left_operand, const BigInt &right_operand) {
    BigInt result = left_operand;
    result ^= right_operand;
    return result;
};

BigInt operator%(const BigInt &left_operand, const BigInt &right_operand) {
    BigInt result = left_operand;
    result %= right_operand;
    return result;
};

BigInt operator&(const BigInt &left_operand, const BigInt &right_operand) {
    BigInt result = left_operand;
    result &= right_operand;
    return result;
};

BigInt operator|(const BigInt &left_operand, const BigInt &right_operand) {
    BigInt result = left_operand;
    result |= right_operand;
    return result;
};

std::ostream &operator<<(std::ostream &output_stream, const BigInt &number) {
    output_stream << static_cast<std::string>(number);
    return output_stream;
};
