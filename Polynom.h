#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// �����, �������������� ���� ����� (��������) ��������
class Monom {
public:
    double coef; // ����������� ������
    int degree; // ������� ������

    // ����������� � ����������� �� ���������
    Monom(double c = 0, int d = 0) : coef(c), degree(d) {}

    // ������� ��� ������ ������ �� �����
    void print() const {
        cout << coef << "x^" << degree;
    }

    // �������� �������� ���� ������� (�������� ������ ���� ������� �����)
    Monom operator+(const Monom& other) const {
        if (degree == other.degree)
            return Monom(coef + other.coef, degree);
        throw invalid_argument("Degrees must be the same for addition"); // ������, ���� ������� �� �����
    }

    // �������� ��������� ���� ������� (�������� ������ ���� ������� �����)
    Monom operator-(const Monom& other) const {
        if (degree == other.degree)
            return Monom(coef - other.coef, degree);
        throw invalid_argument("Degrees must be the same for subtraction"); // ������, ���� ������� �� �����
    }

    // �������� ��������� ���� ������� (������������ �������������, ������� ������������)
    Monom operator*(const Monom& other) const {
        return Monom(coef * other.coef, degree + other.degree);
    }

    // �������� ������� ���� ������� (������������ �������, ������� ����������)
    Monom operator/(const Monom& other) const {
        if (other.coef == 0)
            throw invalid_argument("Division by zero"); // ������ ��� ������� �� ����
        return Monom(coef / other.coef, degree - other.degree);
    }
};

// �����, �������������� ������� (���������) ��� ������ �������
class Polynom {
public:
    std::vector<Monom> monoms; // ������ �������, ������������ �������

    // ���������� ������ ������ � �������
    void addMonom(const Monom& m) {
        monoms.push_back(m);
        simplify(); // ����� ���������� ������ ����������� ���������
    }

    // ������� ������ �������� �� �����
    void print() const {
        for (size_t i = 0; i < monoms.size(); i++) {
            monoms[i].print();
            if (i != monoms.size() - 1) cout << " + ";
        }
        cout << endl;
    }

    // �������� �������� ���� ���������
    Polynom operator+(const Polynom& other) const {
        Polynom result = *this;
        for (const auto& m : other.monoms)
            result.addMonom(m);
        return result;
    }

    // �������� ��������� ���� ���������
    Polynom operator-(const Polynom& other) const {
        Polynom result = *this;
        for (const auto& m : other.monoms)
            result.addMonom(Monom(-m.coef, m.degree)); // ���������� ������ � ��������������� ������
        return result;
    }

    // �������� ��������� ���� ��������� (������������� ��� ������)
    Polynom operator*(const Polynom& other) const {
        Polynom result;
        for (const auto& m1 : monoms)
            for (const auto& m2 : other.monoms)
                result.addMonom(m1 * m2);
        return result;
    }

    // ������� ��������� �������� (���������� ������ � ����������� ���������)
    void simplify() {
        // ���������� ������� �� �������� �������
        sort(monoms.begin(), monoms.end(), [](const Monom& a, const Monom& b) {
            return a.degree > b.degree;
            });

        // ����������� ������� � ����������� ���������
        for (size_t i = 0; i < monoms.size() - 1; i++) {
            if (monoms[i].degree == monoms[i + 1].degree) {
                monoms[i].coef += monoms[i + 1].coef; // ��������� ������������
                monoms.erase(monoms.begin() + i + 1); // ������� ������ �����
                i--; // ������������ �����, ����� �����������
            }
        }
    }
};
