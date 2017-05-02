#include <QtCore/qstring.h>
#include <algorithm>

#include "BigNum.h"


CBigNum::CBigNum(QString numstr)
{
    for (auto i = numstr.begin(); i != numstr.end() && i->isDigit(); ++i) {
        mul_10();
        add(i->digitValue());
    }
}

CBigNum::CBigNum(const CBigNum& other)
{
    num = other.num;
}

CBigNum::~CBigNum()
{
}

QString CBigNum::toString()
{
    if (num.empty())
        return "0";

    QString result;
    CBigNum n{ *this };
    while (!n.num.empty()) {
        auto r = n.div_10();
        result.push_front(QString::number(r));
    }

    return result;
}

bool CBigNum::operator>(const CBigNum & other)
{
    if (num.size() > other.num.size())
        return true;
    if (num.size() == other.num.size() && num[num.size() - 1] > other.num[other.num.size() - 1])
        return true;
    return false;
}

CBigNum CBigNum::operator+(const CBigNum & other)
{
    CBigNum result;
    uint16_t r = 0;

    auto i = num.begin();
    auto j = other.num.begin();
    for (; i != num.end() && j != other.num.end(); ++i, ++j) {
        uint32_t n = static_cast<uint32_t>(*i) + static_cast<uint32_t>(*j) + r;
        result.num.push_back(n & 0xFFFF);
        r = n >> 16;
    }
    while (i != num.end()) {
        uint32_t n = static_cast<uint32_t>(*i) + r;
        result.num.push_back(n & 0xFFFF);
        r = n >> 16;
        ++i;
    }
    while (j != other.num.end()) {
        uint32_t n = static_cast<uint32_t>(*j) + r;
        result.num.push_back(n & 0xFFFF);
        r = n >> 16;
        ++j;
    }

    if (r != 0)
        result.num.push_back(r);

    return result;
}

void CBigNum::mul_10()
{
    uint16_t r = 0;

    for (auto i = num.begin(); i != num.end(); ++i) {
        uint32_t n = static_cast<uint32_t>(*i) * 10 + r;
        *i = n & 0xFFFF;
        r = n >> 16;
    }
    if (r != 0)
        num.push_back(r);
}

uint16_t CBigNum::div_10()
{
    if (num.empty())
        return 0;

    std::vector<uint16_t> q;
    uint32_t r = 0;
    for (auto i = num.rbegin(); i != num.rend(); ++i) {
        uint32_t n = (r << 16) + static_cast<uint32_t>(*i);
        r = n % 10;
        n = n / 10;
        if (!q.empty() || n != 0)
            q.push_back(n);
    }

    auto i = q.begin();
    while (i != q.end()) {
        if (*i != 0)
            break;
    }

    if (i == q.end())
        num = std::vector<uint16_t>();
    else {
        num = std::vector<uint16_t>(i, q.end());
        std::reverse(num.begin(), num.end());
    }

    return r;
}

void CBigNum::add(uint16_t n)
{
    uint16_t r = n;

    for (auto i = num.begin(); i != num.end() && r != 0; ++i) {
        uint32_t sum = static_cast<uint32_t>(*i) + r;
        *i = sum & 0xFFFF;
        r = sum >> 16;
    }
    if (r != 0)
        num.push_back(r);
}
