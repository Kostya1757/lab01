#pragma once
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

#define pi 3.14159

class Ellipse
{

private:
    double h;
    double k;
    double a;
    double b;
    double c;
    bool XorY;
    double lr2;

public:
    Ellipse(double valueH, double valueK, double valueA, double valueB, bool valueXorY)
    {
        if (valueA > valueB) {
            h = valueH;
            k = valueK;
            a = valueA;
            b = valueB;
            XorY = valueXorY;
        }
        else {
            h = valueH;
            k = valueK;
            a = 0;
            b = 0;
            XorY = valueXorY;
            cout << "Поменяйте значения параметров a и b" << endl;
        }
    }

    Ellipse() : h(0), k(0), a(0), b(0), XorY(0) {}

    Ellipse(const Ellipse& other)
    {

    }

    double FindC() const
    {
        return sqrt(a * a - b * b);
    }

    void Vertex(double& v1x, double& v1y, double& v2x, double& v2y) const {
        if (XorY) {
            v1x = h - a; v1y = k;
            v2x = h + a; v2y = k;
        }
        else {
            v1x = h; v1y = k - a;
            v2x = h; v2y = k + a;
        }
    }

    void Focus(double& f1x, double& f1y, double& f2x, double& f2y) const {
        double c = FindC();
        if (XorY) {
            f1x = h - c; f1y = k;
            f2x = h + c; f2y = k;
        }
        else {
            f1x = h; f1y = k - c;
            f2x = h; f2y = k + c;
        }
    }

    double FindLR() const {
        return (2 * b * b) / a;
    }

    double Eccentricity() const {
        return FindC() / a;
    }

    string Position(double x, double y) const {
        double value;
        if (XorY) {
            value = pow(x - h, 2) / (a * a) + pow(y - k, 2) / (b * b);
        }
        else {
            value = pow(x - h, 2) / (b * b) + pow(y - k, 2) / (a * a);
        }

        if (abs(value - 1.0) < 1e-6) {
            return "На границе";
        }
        else if (value < 1.0) {
            return "Внутри";
        }
        else {
            return "Снаружи";
        }
    }

    double Perimeter() const {
        return pi * (3 * (a + b) - std::sqrt((3 * a + b) * (a + 3 * b)));
    }

    double Square() const {
        return pi * a * b;
    }

    double Second(double knownCoord, bool isXKnown) const {
        if (isXKnown) {
            double term = (1 - pow(knownCoord - h, 2) / (a * a)) * (b * b);
            if (term < 0) {
                throw invalid_argument("Заданная координата x находится за пределами эллипса.");
            }
            return k + sqrt(term);
        }
        else {
            double term = (1 - pow(knownCoord - k, 2) / (b * b)) * (a * a);
            if (term < 0) {
                throw invalid_argument("Заданная координата y находится за пределами эллипса.");
            }
            return h + sqrt(term);
        }
    }

    double GetH()
    {
        return h;
    }

    double GetK()
    {
        return k;
    }

    double GetA()
    {
        return a;
    }

    double GetB()
    {
        return b;
    }

    void SetH(double valueH)
    {
        h = valueH;
    }

    void SetK(double valueK)
    {
        k = valueK;
    }

    void SetA(double valueA)
    {
        a = valueA;
    }

    void SetB(double valueB)
    {
        b = valueB;
    }

    void Print()
    {
        cout << "Центр окружности находится в точке: (" << h << ", " << k << ")" << endl;
        cout << "a = " << a << ", b = " << b << endl;
        cout << lr2;
    }

    void printEllipseInfo() const {
        cout << "Общее уравнение эллипса: ";
        if (XorY) {
            cout << "(x - " << h << ")^2 / " << a * a << " + (y - " << k << ")^2 / " << b * b << " = 1" << std::endl;
        }
        else {
            cout << "(x - " << h << ")^2 / " << b * b << " + (y - " << k << ")^2 / " << a * a << " = 1" << std::endl;
        }

        double v1x, v1y, v2x, v2y;
        Vertex(v1x, v1y, v2x, v2y);
        cout << "Вершины: V1(" << v1x << ", " << v1y << "), V2(" << v2x << ", " << v2y << ")" << std::endl;

        double f1x, f1y, f2x, f2y;
        Focus(f1x, f1y, f2x, f2y);
        cout << "Фокусы: F1(" << f1x << ", " << f1y << "), F2(" << f2x << ", " << f2y << ")" << std::endl;

        cout << "Центр: C(" << h << ", " << k << ")" << std::endl;
        cout << "Длина фокальной хорды: " << Eccentricity() << std::endl;
        cout << "Эксцентриситет: " << Eccentricity() << std::endl;
    }
};