#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
using namespace std;

class Rational {
private:
	int numer;
    int denom;
	int gcd(int, int);

public:
	Rational(int = 0, int = 1);
	Rational(Rational const&);
	int setNumerator(int);
	int setDenominator(int);
	int getNumerator() const { return numer; }
	int getDenominator() const { return denom; }
	//void read();
	Rational& operator=(Rational const&);
	Rational operator+(Rational const&);
	Rational operator-(Rational const&);
	Rational operator*(Rational const&);
	Rational operator/(Rational const&);
	Rational& operator+=(Rational const&);
	friend bool operator!=(Rational const&, Rational const&);
	friend ostream& operator<<(ostream&, Rational const&);
	friend istream& operator>>(istream&, Rational&);
};


class Matrix {
    int rows;
    int columns;
    Rational** A;
public:
    Matrix();
    Matrix(int, int);
    Matrix(const Matrix&);
    ~Matrix();
    void setRows(int _rows){rows=_rows;}
    void setColumns(int _columns){columns=_columns;}
    //void setMatrix();
    int getRows(){return rows;}
    int getColumns(){return columns;}
    bool IsAppropriateForSum(Matrix const&)const;
    bool IsAppropriateForMult(Matrix const&) const;
    bool CanTransformToIdentityM()const;
    bool HasReverse()const;
    Rational Determinant()const;
    Matrix Transposition();
    Rational Cofactor(int , int);
    Matrix InverseMatrix();
    Matrix operator+(Matrix const&);
    Matrix operator-(Matrix const&);
    Matrix operator*(Matrix const&);
    Matrix operator*(Rational const&);
    Matrix operator/(Matrix const&);
    Matrix& operator=(Matrix const&);
    Rational* operator[](int);
    friend ostream& operator<<(ostream&, Matrix const&);
	friend istream& operator>>(istream&, Matrix&);
};

#endif // MATRIX_H_INCLUDED
