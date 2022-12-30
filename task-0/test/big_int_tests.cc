#include <gtest/gtest.h>
#include "../BigInt/BigInt.h"

TEST(ConstructEmpty, Test1) {
    BigInt A = BigInt();
    EXPECT_TRUE(A.value.empty());
    EXPECT_EQ(0, A.length);
    EXPECT_EQ(0, A.sign);
}


TEST(ConstructWithInt_InInput, Test2) {
    BigInt a = BigInt(4578912);
    BigInt b = BigInt(-71256);
    EXPECT_EQ(7, a.length);
    EXPECT_EQ(5, b.length);
    EXPECT_EQ(1, b.sign);
    EXPECT_EQ("71256", b.value);
    EXPECT_EQ("4578912", a.value);
}

TEST(Errors, Test3) {
    try {
        BigInt s = BigInt("abc");
    }
    catch (std::invalid_argument &a) {
        EXPECT_STREQ(a.what(), "input data is not a digit");
    }

}

TEST(ConstructCopy, Test4) {
    BigInt first = BigInt("94210");
    BigInt second(first);


    EXPECT_TRUE(second == first);                    //OOOOOOOOOOOOOOOOOOOOOOOOooooooooooooooooOooOOOooo
}

TEST(Operator_ravno, Test5) {
    BigInt first = BigInt(-624);
    BigInt second = BigInt(10267);
    BigInt Prom;
    Prom = first;
    EXPECT_TRUE(Prom == first);
    first = second;
    EXPECT_TRUE(second == first); //OOOOOOOOOOOOoOOOOOOOOOOOooooooooOOOOOOOOO
}

TEST(Unary_operators, Test6) {
    BigInt aaa = BigInt("184");
    BigInt second = BigInt("-10000");
    BigInt third = BigInt("5426357989");
    BigInt first = BigInt(9999999);
    EXPECT_FALSE(aaa > third);
    EXPECT_TRUE(aaa > second);
    EXPECT_TRUE(first <= third);
    EXPECT_TRUE(first >= second);
    EXPECT_TRUE(first >= aaa);

    EXPECT_EQ(aaa, +aaa);
    aaa = -aaa;
    EXPECT_EQ(1, aaa.sign);
    aaa = BigInt(-9999);
    ++second;
    EXPECT_EQ(aaa, second);
    EXPECT_EQ(4, aaa.length);
    EXPECT_EQ(4, second.length);
    aaa++;
    second--;
    EXPECT_TRUE(aaa != second);
    EXPECT_FALSE(aaa == second);
    aaa = BigInt("5426357990");
    ++third;
    EXPECT_TRUE(aaa == third);
    aaa--;
    --third;
    EXPECT_EQ(aaa, third);
    aaa = BigInt(10000000);
    first++;
    EXPECT_EQ(aaa, first);
    EXPECT_EQ(8, first.length);
    BigInt a = BigInt(-1);
    a++;
    EXPECT_EQ(0, int(a));
    a++;
    a--;

    EXPECT_EQ(0, int(a));
}

TEST(Operator_plus, Test7) {
    BigInt result = BigInt(9261);
    BigInt first = BigInt(-251);
    BigInt second = BigInt(9512);
    BigInt temp = first + second;
    EXPECT_EQ(result, temp);
    temp = -second + -first;
    EXPECT_EQ(-result, temp);
    result = BigInt(-502);
    temp = first + first;
    EXPECT_EQ(result, temp);

}

TEST(Operator_minus, Test8) {
    BigInt result = BigInt(-9763);
    BigInt first = BigInt(-251);
    BigInt second = BigInt(9512);
    BigInt temp = first - second;
    EXPECT_EQ(result, temp);
    result = BigInt(-9261);
    temp = -second + -first;
    EXPECT_EQ(result, temp);
    result = BigInt(0);
    temp = first - first;
    EXPECT_EQ(result, temp);
}

TEST(Operator_mul, Test9) {
    BigInt result = BigInt(305440737);
    BigInt first = BigInt(67921);
    BigInt second = BigInt(4497);
    BigInt temp = first * second;
    EXPECT_EQ(result, temp);
    temp = -first * -second;
    EXPECT_EQ(result, temp);
    temp = first * -second;
    result = -result;
    EXPECT_EQ(result, temp);

}

TEST(Operator_del, Test10) {
    BigInt result = BigInt(15);
    BigInt first = BigInt(67921);
    BigInt second = BigInt(4497);
    BigInt temp = first / second;
    EXPECT_EQ(result, temp);
    result = -result;
    temp = first / -second;
    EXPECT_EQ(result, temp);
    result = BigInt(0);
    try {
        temp = first / result;

    }
    catch (std::invalid_argument &a) {
        EXPECT_STREQ(a.what(), "div is not possible");
    }
}

TEST(Operator_mod, Test11) {
    BigInt result = BigInt(466);
    BigInt first = BigInt(67921);
    BigInt second = BigInt(4497);
    BigInt temp = first % second;
    EXPECT_EQ(result, temp);
    result = -result;
    temp = -first % second;
    EXPECT_EQ(result, temp);
    result = -result;
    temp = first % -second;
    EXPECT_EQ(result, temp);
    result = BigInt(0);
    try {
        temp = first % result;

    }
    catch (std::invalid_argument &a) {
        EXPECT_STREQ(a.what(), "mod impossible");
    }
}

TEST(Logic_Operators, Test12) {
    BigInt first = BigInt("873984364375");
    BigInt second = BigInt("295681");
    BigInt temp = first | second;
    BigInt result = BigInt("873984397143");
    EXPECT_EQ(result, temp);
    result = -result;
    temp = -first & -second;
    EXPECT_EQ(result, temp);
    temp = first | -second;
    result = BigInt("-32769");
    EXPECT_EQ(result, temp);
    EXPECT_TRUE(result < first);
    EXPECT_TRUE(result <= first);
    temp = -first | second;
    result = BigInt("-873984101463");
    EXPECT_EQ(result, temp);
    temp = first & -second;
    result = -result;
    EXPECT_EQ(result, temp);
    temp = first & second;
    result = BigInt("262913");
    EXPECT_EQ(result, temp);
    result = -result;
    temp = -first | -second;
    EXPECT_EQ(result, temp);
    temp = first ^ second;
    result = BigInt("873984134230");
    EXPECT_EQ(result, temp);
    temp = -first ^ -second;
    EXPECT_EQ(result, temp);
    temp = -first ^ second;
    result = BigInt("-873984134232");
    EXPECT_EQ(result, temp);
    temp = first ^ -second;
    EXPECT_EQ(result, temp);


}

TEST(Operator_StrToInt, Test13) {
    BigInt first = BigInt("-7528341");
    int result = first.operator int();
    EXPECT_EQ(-7528341, result);
    first = BigInt("30128441");
    result = first.operator int();
    EXPECT_EQ(30128441, result);

    first = BigInt("1111791479081641111111111111111111111111111111111111111111111111111111111111");
    try {
        result = first.operator int();

    }
    catch (std::length_error &a) {
        EXPECT_STREQ(a.what(), "Digit in string bigger then int");
    }
}

TEST(Operators_ToStr_and_size, Test14) {
    BigInt first = BigInt("30128441");
    std::string result = first.operator std::string();
    EXPECT_EQ(first.value, result);
    size_t r = first.size();
    EXPECT_EQ(8, r);

}

TEST(Operator_output, Test15) {
    std::ostringstream out;
    out << BigInt("1238621236");
    EXPECT_STREQ(out.str().data(), "1238621236");
}

