#include <iostream>
#include "Polynom.h"

int main() {
    // Создание мономов
    Monom m1(3, 2), m2(5, 2), m3(2, 1);

    // Создание полинома и добавление мономов
    Polynom p;
    p.addMonom(m1);
    p.addMonom(m2);
    p.addMonom(m3);

    // Вывод полинома
    p.print();

    // Создание второго полинома
    Monom m4(2, 1);
    Polynom p2;
    p2.addMonom(m4);
    p2.print();

    // Сложение двух полиномов
    Polynom sum = p + p2;
    sum.print();

    return 0;
}
