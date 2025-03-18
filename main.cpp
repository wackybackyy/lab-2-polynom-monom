#include <iostream>
#include "Polynom.h"

int main() {
    // �������� �������
    Monom m1(3, 2), m2(5, 2), m3(2, 1);

    // �������� �������� � ���������� �������
    Polynom p;
    p.addMonom(m1);
    p.addMonom(m2);
    p.addMonom(m3);

    // ����� ��������
    p.print();

    // �������� ������� ��������
    Monom m4(2, 1);
    Polynom p2;
    p2.addMonom(m4);
    p2.print();

    // �������� ���� ���������
    Polynom sum = p + p2;
    sum.print();

    return 0;
}
