#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <iostream>

#include "BigNum.h"

const QString str2 = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";

int main(int argc, char *argv[])
{
    QString str;
    QTextStream input_stream(stdin);

    std::cout << "Enter the first long number: ";

    str = input_stream.readLine();
    BigNumber a{ str };

    std::cout << "Enter the second long number: ";
    str = input_stream.readLine();
    BigNumber b{ str };

    auto c = a + b;

    std::cout << "You entered the following numbers (input data terminated by first non-digit symbol):" << std::endl;
    std::cout << a.toString().toUtf8().constData() << std::endl;
    std::cout << b.toString().toUtf8().constData() << std::endl;
    std::cout << "The sum is:" <<std::endl << c.toString().toUtf8().constData() << std::endl;

    return 0;
}
