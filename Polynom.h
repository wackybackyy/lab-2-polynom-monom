#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Класс, представляющий один моном (одночлен) полинома
class Monom {
public:
    double coef; // Коэффициент монома
    int degree; // Степень монома

    // Конструктор с параметрами по умолчанию
    Monom(double c = 0, int d = 0) : coef(c), degree(d) {}

    // Функция для вывода монома на экран
    void print() const {
        cout << coef << "x^" << degree;
    }

    // Оператор сложения двух мономов (возможен только если степени равны)
    Monom operator+(const Monom& other) const {
        if (degree == other.degree)
            return Monom(coef + other.coef, degree);
        throw invalid_argument("Degrees must be the same for addition"); // Ошибка, если степени не равны
    }

    // Оператор вычитания двух мономов (возможен только если степени равны)
    Monom operator-(const Monom& other) const {
        if (degree == other.degree)
            return Monom(coef - other.coef, degree);
        throw invalid_argument("Degrees must be the same for subtraction"); // Ошибка, если степени не равны
    }

    // Оператор умножения двух мономов (коэффициенты перемножаются, степени складываются)
    Monom operator*(const Monom& other) const {
        return Monom(coef * other.coef, degree + other.degree);
    }

    // Оператор деления двух мономов (коэффициенты делятся, степени вычитаются)
    Monom operator/(const Monom& other) const {
        if (other.coef == 0)
            throw invalid_argument("Division by zero"); // Ошибка при делении на ноль
        return Monom(coef / other.coef, degree - other.degree);
    }
};

// Класс, представляющий полином (многочлен) как список мономов
class Polynom {
public:
    std::vector<Monom> monoms; // Вектор мономов, составляющих полином

    // Добавление нового монома в полином
    void addMonom(const Monom& m) {
        monoms.push_back(m);
        simplify(); // После добавления монома выполняется упрощение
    }

    // Функция вывода полинома на экран
    void print() const {
        for (size_t i = 0; i < monoms.size(); i++) {
            monoms[i].print();
            if (i != monoms.size() - 1) cout << " + ";
        }
        cout << endl;
    }

    // Оператор сложения двух полиномов
    Polynom operator+(const Polynom& other) const {
        Polynom result = *this;
        for (const auto& m : other.monoms)
            result.addMonom(m);
        return result;
    }

    // Оператор вычитания двух полиномов
    Polynom operator-(const Polynom& other) const {
        Polynom result = *this;
        for (const auto& m : other.monoms)
            result.addMonom(Monom(-m.coef, m.degree)); // Добавление монома с противоположным знаком
        return result;
    }

    // Оператор умножения двух полиномов (перемножаются все мономы)
    Polynom operator*(const Polynom& other) const {
        Polynom result;
        for (const auto& m1 : monoms)
            for (const auto& m2 : other.monoms)
                result.addMonom(m1 * m2);
        return result;
    }

    // Функция упрощения полинома (объединяет мономы с одинаковыми степенями)
    void simplify() {
        // Сортировка мономов по убыванию степени
        sort(monoms.begin(), monoms.end(), [](const Monom& a, const Monom& b) {
            return a.degree > b.degree;
            });

        // Объединение мономов с одинаковыми степенями
        for (size_t i = 0; i < monoms.size() - 1; i++) {
            if (monoms[i].degree == monoms[i + 1].degree) {
                monoms[i].coef += monoms[i + 1].coef; // Суммируем коэффициенты
                monoms.erase(monoms.begin() + i + 1); // Удаляем лишний моном
                i--; // Возвращаемся назад, чтобы пересчитать
            }
        }
    }
};
