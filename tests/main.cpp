#include <QtTest/QtTest>
#include "../bignum/BigNum.h"

class TestCBigNum : public QObject
{
    Q_OBJECT;

private slots:
    void fromString();
    void emptyNum();
    void fromBigNum();
    void addNums();
    void differentLen();

public:
    ~TestCBigNum() {}
};

static const QString pi_str{ "3141592653589793238462643383279502884197169399375105820974944592307816406286" };
static const QString long_str{ "12345678901234567890123456789012345678901234567890123456789012345678901234567890" };
static const QString diff_sum_str{ "12345678901234567890123456789012345678901234567890123456789012345678902469135780" };
static const QString long_sum_str = { "24691357802469135780246913578024691357802469135780246913578024691357802469135780" };

void TestCBigNum::fromString()
{
    CBigNum n{ pi_str };
    QCOMPARE(n.toString(), pi_str);
}

void TestCBigNum::emptyNum()
{
    CBigNum n;
    QCOMPARE(n.toString(), QString{ "0" });
}

void TestCBigNum::fromBigNum()
{
    CBigNum n{ long_str };
    CBigNum m{ n };
    QCOMPARE(m.toString(), long_str);
}

void TestCBigNum::addNums()
{
    CBigNum n{ long_str };
    CBigNum m = n + n;
    // https://defuse.ca/big-number-calculator.htm
    QCOMPARE(m.toString(), long_sum_str);
}

void TestCBigNum::differentLen()
{
    CBigNum n{ long_str };
    CBigNum m = n + CBigNum{"1234567890"};
    QCOMPARE(m.toString(), diff_sum_str);
}

QTEST_MAIN(TestCBigNum)
#include "main.moc"