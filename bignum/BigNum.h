#pragma once

#include <cstdint>
#include <vector>

class CBigNum
{
public:
    CBigNum() {}
    CBigNum(QString numstr);
    CBigNum(const CBigNum&);
    ~CBigNum();
    QString toString();
    bool operator>(const CBigNum&);
    CBigNum operator+(const CBigNum&);

private:

    void mul_10();
    uint16_t div_10();
    void add(uint16_t);

    std::vector<uint16_t> num;
};

