#pragma once

#include <cstdint>
#include <vector>

class BigNumber
{
public:
    BigNumber() {}
    BigNumber(QString numstr);
    BigNumber(const BigNumber&);
    ~BigNumber();
    QString toString() const;
    BigNumber operator+(const BigNumber&) const;

private:

    void mul_10();
    uint16_t div_10();
    void add(uint16_t);

    std::vector<uint16_t> num;
};

