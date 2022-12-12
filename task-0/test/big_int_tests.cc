#include <BigInt.h>
#include <gtest/gtest.h>
#include <climits>

class ConstructorTest{
public:
    static void DefaultConstructorTester() {
        BigInt a;
        EXPECT_FALSE(a.IsSignNegative());
        EXPECT_EQ(a, 0);
    }
    static void IntConstructorTester(int value) {
        BigInt bi(value);
        EXPECT_EQ(bi, value);
    }
    static void StringConstructorTester(const std::string str, const std::string res,
                                        bool isCorrect) {
        if (isCorrect) {
            BigInt bi(str);
            std::stringstream ss;
            std::string string_from_bigint;
            ss << bi;
            ss >> string_from_bigint;
            EXPECT_EQ(res, string_from_bigint);
        } else {
            try {
                BigInt bi(str);
                FAIL() << "Expected std::invalid_argument";
            } catch (const std::invalid_argument &e) {
            }
        }
    }
    static void CopyConstructorTester(const std::string value) {
        BigInt first(value);
        BigInt second(first);
        EXPECT_EQ(first, second);
    }
};

TEST(ConstructorTest, DefaultConstructor) {
ConstructorTest::DefaultConstructorTester();
}
TEST(ConstructorTest, IntConstructor) {
int value_lower_than_base = 100;
int value_greater_than_base = kBase + 12345;
ConstructorTest::IntConstructorTester(value_lower_than_base);
ConstructorTest::IntConstructorTester(-value_lower_than_base);
ConstructorTest::IntConstructorTester(value_greater_than_base);
ConstructorTest::IntConstructorTester(-value_greater_than_base);
}
TEST(ConstructorTest, StringConstructor) {
std::string correct_input = "-1234567890098765456789876543234567";
std::string incorrect_input = "124535 124 ";
std::string with_leading_zeros = "00000236345744";
ConstructorTest::StringConstructorTester(correct_input, correct_input, true);
ConstructorTest::StringConstructorTester(incorrect_input, incorrect_input, false);
ConstructorTest::StringConstructorTester(with_leading_zeros, "236345744", true);
}
TEST(ConstructorTest, CopyConstructor) {
std::string value = "123456789098765432334324357456123435474362";
ConstructorTest::CopyConstructorTester(value);
}

class OperatorTest{
public:
    static void ComparisonOperatorTester() {
        std::string small = "123454567890000";
        std::string great = "123456789999999";
        BigInt smaller(small);
        BigInt smaller_cp(smaller);
        BigInt greater(great);
        BigInt short_ = 1;
        BigInt greater_negative_cp = -greater;
        BigInt smaller_negative_cp = -short_;

        EXPECT_TRUE(smaller == smaller_cp);
        EXPECT_FALSE(smaller == greater);

        EXPECT_TRUE(smaller != greater);
        EXPECT_FALSE(smaller != smaller);

        EXPECT_TRUE(smaller < greater);
        EXPECT_TRUE(short_ < greater);
        EXPECT_TRUE(greater_negative_cp < smaller);
        EXPECT_TRUE(greater_negative_cp < smaller_negative_cp);

        EXPECT_TRUE(smaller <= smaller);
        EXPECT_TRUE(smaller <= greater);
        EXPECT_FALSE(greater <= smaller);

        EXPECT_TRUE(greater > smaller);
        EXPECT_FALSE(greater > greater);
        EXPECT_TRUE(greater > short_);

        EXPECT_TRUE(greater >= greater);
        EXPECT_TRUE(greater >= greater_negative_cp);
    }
    static void AssignmentOperatorTester(const std::string str) {
        BigInt a(str);
        BigInt b = a;
        EXPECT_EQ(a, b);
        b = b;
        EXPECT_EQ(b, b);
    }
    static void AddTester(const std::string a, const std::string b,
                          const std::string res) {
        BigInt bi_a(a);
        BigInt bi_b(b);
        EXPECT_EQ(bi_a + bi_b, res);
        bi_a += bi_b;
        EXPECT_EQ(bi_a, res);
    }
    static void SubTester(const std::string a, const std::string b,
                          const std::string res) {
        BigInt bi_a(a);
        BigInt bi_b(b);
        EXPECT_EQ(bi_a - bi_b, res);
        bi_a -= bi_b;
        EXPECT_EQ(bi_a, res);
    }
    static void MultiplicationTester(const std::string a, const std::string b,
                                     const std::string res) {
        BigInt bi_a(a);
        BigInt bi_b(b);
        BigInt bi_res(res);
        EXPECT_EQ(bi_a * bi_b, bi_res);
        bi_a *= bi_b;
        EXPECT_EQ(bi_a, bi_res);
    }
    static void DivisionTester(const std::string a, const std::string b,
                               const std::string res) {
        BigInt bi_a(a);
        BigInt bi_b(b);
        BigInt bi_res(res);
        const BigInt &div = bi_a / bi_b;
        EXPECT_EQ(div, bi_res);
        bi_a /= bi_b;
        EXPECT_EQ(bi_a, bi_res);
    }
    static void ModTester(const std::string a, const std::string b,
                          const std::string res) {
        BigInt bi_a(a);
        BigInt bi_b(b);
        EXPECT_EQ(bi_a % bi_b, res);
        bi_a %= bi_b;
        EXPECT_EQ(bi_a, res);
    }
    static void StringOperatorTester(std::string actual, std::string expectation) {
        BigInt a(actual);
        std::string r = a;
        EXPECT_EQ(r, expectation);
    }
    static void IncrementDecrementTester(const std::string str) {
        BigInt a(str);
        BigInt prefix_inc = ++a;
        EXPECT_EQ(prefix_inc, a);
        BigInt postfix_inc = a++;
        EXPECT_EQ(postfix_inc + 1, a);
        BigInt prefix_dec = --a;
        EXPECT_EQ(prefix_dec, postfix_inc);
        BigInt postfix_dec = a--;
        EXPECT_EQ(postfix_dec, a + 1);
    }
    static void AndTester(const std::string a, const std::string b,
                          const std::string res) {
        BigInt bi_a(a);
        BigInt bi_b(b);
        EXPECT_EQ(bi_a & bi_b, res);
        bi_a &= bi_b;
        EXPECT_EQ(bi_a, res);
    }
    static void OrTester(const std::string a, const std::string b,
                         const std::string res) {
        BigInt bi_a(a);
        BigInt bi_b(b);
        EXPECT_EQ(bi_a | bi_b, res);
        bi_a |= bi_b;
        EXPECT_EQ(bi_a, res);
    }
    static void XorTester(const std::string a, const std::string b,
                          const std::string res) {
        BigInt bi_a(a);
        BigInt bi_b(b);
        EXPECT_EQ(bi_a ^ bi_b, res);
        bi_a ^= bi_b;
        EXPECT_EQ(bi_a, res);
    }
};
TEST(OperatorTest, Comparison) { OperatorTest::ComparisonOperatorTester(); }
TEST(OperatorTest, Assignment) {
OperatorTest::AssignmentOperatorTester("232546323512432555");
}
TEST(OperatorTest, Unary) {
BigInt a = 12353464;
EXPECT_TRUE(a == +a);
EXPECT_TRUE(a != -a);
EXPECT_FALSE(a < -a);
}
TEST(OperatorTest, StringOperator) {
std::string digit = "-21256754325";
OperatorTest::StringOperatorTester(digit, digit);
}
TEST(OperatorTest, Add) {
std::string a = "155086289231547392104593177371170113235101627633146991946153"
                "15917544667310457012179991449";
std::string b = "15508628923154739210459";
std::string a_plus_b = "15508628923154739210459317737117011323510162763314699"
                       "194615315917560175939380166919201908";
std::string a_plus_minus_b = "15508628923154739210459317737117011323510162763"
                             "314699194615315917529158681533857440780990";
OperatorTest::AddTester(a, b, a_plus_b);
OperatorTest::AddTester(a, "-" + b, a_plus_minus_b);
OperatorTest::AddTester("-" + a, b, "-" + a_plus_minus_b);
}
TEST(OperatorTest, Sub) {
std::string a = "155086289231547392104593177371170113235101627633146991946153"
                "15917544667310457012179991449";
std::string b = "15508628923154739210459";
std::string a_minus_b = "1550862892315473921045931773711701132351016276331469"
                        "9194615315917529158681533857440780990";
std::string a_plus_b = "15508628923154739210459317737117011323510162763314699"
                       "194615315917560175939380166919201908";
OperatorTest::SubTester(a, b, a_minus_b);
OperatorTest::SubTester(b, a, "-" + a_minus_b);
OperatorTest::SubTester(a, "-" + b, a_plus_b);
}
TEST(OperatorTest, Multiplication) {
std::string a = "1550862892315473921045931773711701132351016276331469919461"
                "5315917544667310457012179991449";
std::string res =
        "240517571076111725918727062568653157921988361034312220508895073028480190"
        "143529755471087446659983750822120115312706677606874010706294380610687902"
        "276822682832324916577697713119601";
OperatorTest::MultiplicationTester(a, a, res);
OperatorTest::MultiplicationTester(a, "0", "0");
OperatorTest::MultiplicationTester("-100", "100", "-10000");
}
TEST(OperatorTest, Division) {
std::string a = "155086289231547392104593177371170113235101627633146991946153"
                "15917544667310457012179991449";
std::string b = "15508628923154739210459";
std::string res =
        "1000000000000000000000020487763204968731706906383742939293363999734";
OperatorTest::DivisionTester(a, b, res);
OperatorTest::DivisionTester(b, a, "0");
}
TEST(OperatorTest, Mod) {
std::string a = "155086289231547392104593177371170113235101627633146991946153"
                "15917544667310457012179991449";
std::string b = "15508628923154739210459";
std::string mod = "3519491278078733973543";
OperatorTest::ModTester(a, b, mod);
}
TEST(OperatorTest, IncrementDecrement) {
OperatorTest::IncrementDecrementTester("214235365745346251532364");
}

TEST(OperatorTest, Logic) {
std::string a = "123456789";
std::string b = "987654321";
std::string a_and_b = "39471121";
std::string a_or_b = "71639989";
std::string a_xor_b = "32168868";
OperatorTest::AndTester(a, b, a_and_b);
OperatorTest::OrTester(a, b, a_or_b);
OperatorTest::XorTester(a, b, a_xor_b);
}

TEST(OperatorTest,ConvertToInt) {
std::string big = "523643574685976568473642541235364574";
int small = 23562;
EXPECT_EQ(small,BigInt(small).operator int());
EXPECT_EQ(BigInt(big).operator int(),INT_MAX);
}
