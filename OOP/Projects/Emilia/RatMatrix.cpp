#include <iostream>
#include <cmath>
#include <stdio.h>
#include "Matrix.h"
using namespace std;

/*void read() {
	int n;
	cout << "Please enter a number: ";
	cin >> n;
	cout << "Thank you!" << std::endl;
}
*/
int Rational::gcd(int x, int y) { // съкращава рационалните числа
	if (x <= 0 || y <= 0) {
		return 1;
	}
	while (x != y)
		if (x > y)
			x -= y;
		else
			y -= x;

	return x;
}
Rational::Rational(Rational const& r){ //copy конструктор
    numer=r.numer;
    denom=r.denom;
}
Rational::Rational(int n, int d)
	: numer(n), denom(d) {
	if (denom == 0) {
		cout << "Опит за подаване на знаменател 0!" << std::endl;
		denom = 1;
	}
	if (numer != 0) {
		int g = gcd(numer, denom);
		numer /= g;
		denom /= g;
	}
	else
		denom = 1;
}
int Rational::setNumerator(int n){
    numer=n;
}
int Rational::setDenominator(int d){
    if(d!=0)
        denom=d;
    else
        cout<<"Error - the denominator can not be 0!";
}
void Rational::print() const {
	cout << getNumerator() << '/' << getDenominator();
}
void Rational::read() {
	cin >> numer;
	cin.ignore();
	cin >> denom;
}
double Rational::toDouble() const {
	return (double)getNumerator() / getDenominator();
}
Rational& Rational::operator=(Rational const& r){
    if(this!=&r)
    {
        numer=r.numer;
        denom=r.denom;
    }
    return *this;
}
Rational Rational::operator+(Rational const& r){
    return Rational(numer * r.getDenominator()
			        + denom * r.getNumerator(),
					denom * r.getDenominator());
}
Rational Rational::operator-(Rational const& r){
    return Rational(numer * r.getDenominator()
			        - denom * r.getNumerator(),
					denom * r.getDenominator());
}
Rational Rational::operator*(Rational const& r){
    return Rational(numer * r.getNumerator(),
					denom * r.getDenominator());
}
Rational Rational::operator/(Rational const& r){
    return Rational(numer * r.getDenominator(),
					denom * r.getNumerator());
}
Rational& Rational::operator+=(Rational const& r){
	int newNum = 0;
    int newDenom = 0;
	newNum = numer * r.denom + denom * r.numer;
	newDenom = denom * r.denom;
	numer = newNum;
	denom = newDenom;
	return *this;
}
bool operator!=(Rational const& r1, Rational const& r2) {
  return r1.getNumerator() != r2.getNumerator() &&
             r1.getDenominator() != r2.getDenominator();
}
ostream& operator<<(ostream& os, Rational const& r){
    return os<<r.getNumerator()<<"/"<<r.getDenominator();
}
istream& operator>>(istream& is, Rational& r) {
  return is>>r.numer>>r.denom;
}


Matrix::Matrix():rows(1),columns(1){
        A=new Rational*[rows];
        for(int i=0; i<rows; i++)
            A[i]=new Rational[columns];
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<columns; j++)
                {
                    Rational temp(0);
                    A[i][j]=temp;
                }
        }
      //  Rational temp(0);
       // A[i][j]=temp;

}
Matrix::Matrix(int _rows, int _columns){
    rows=_rows;
    columns=_columns;
    A=new Rational*[_rows];
    for(int i=0; i<_rows; i++)
        {
            A[i]=new Rational[_columns];
            /*for(int j=0; j<_columns; j++){
                    Rational r;
                    cin>>r;
                    A[i][j]=r;
            }*/

        }
        //cin>>*this;

}
Matrix::Matrix(const Matrix& B){
    rows=B.rows;
    columns=B.columns;
    A=new Rational*[rows];
    for(int i=0; i<rows; i++)
        A[i]=new Rational[columns];
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
            A[i][j]=B.A[i][j];
    }
}
Matrix::~Matrix(){
   for(int i=0; i<rows; i++)
        delete[] A[i];
   delete[] A;
}
bool Matrix::IsAppropriateForSum(Matrix const& C)const{
    if(this->rows==C.rows && this->columns==C.columns)
        return true;
    return false;
}
bool Matrix::IsAppropriateForMult(Matrix const& C)const{
    if(this->columns==C.rows)
        return true;
    return false;
}
bool Matrix::CanTransformToIdentityM()const{
    if(rows==columns && Determinant()!=0)
        return true;
    return false;
}
bool Matrix::HasReverse()const{
    if(CanTransformToIdentityM())
        return true;
    return false;
}
Rational Matrix::Determinant()const{
    if(columns==rows){
    Rational det=0;
    Rational **B=A;
    switch(rows)
    {
        case 1: det=B[0][0]; return det; break;
        case 2: det=B[0][0]*B[1][1]-B[0][1]*B[1][0]; return det;break;
        case 3:
        {
            Rational a = B[0][0];
            Rational b = B[0][1];
            Rational c = B[0][2];
            Rational d = B[1][0];
            Rational e = B[1][1];
            Rational f = B[1][2];
            Rational g = B[2][0];
            Rational h = B[2][1];
            Rational i= B[2][2];
            Rational det = (a*e*i + b*f*g + c*d*h)-(a*f*h + b*d*i + c*e*g);
            return det;
        }break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        default:
        {
            int dim=rows;
            Matrix **temp=new Matrix*[dim];
            for(int i=0; i < dim; i++)
                temp[i]=new Matrix(dim- 1, dim- 1);
            for(int k=0; k<dim; k++)
            {
                for(int i=1; i<dim; i++)
                {
                    int j1 = 0;
                    for(int j=0; j<dim; j++)
                    {
                        if(k==j)
                            continue;
                        temp[k]->A[i-1][j1++] = this->A[i][j];
                    }
                }
            }
            Rational det=0;
            for(int k=0; k<dim; k++)
            {
                if( (k%2)==0)
                    det=det+(this->A[0][k] * temp[k]->Determinant());
                else
                    det=det-(this->A[0][k] * temp[k]->Determinant());
            }
            for(int i=0; i<dim; i++)
                delete temp[i];
            delete [] temp;
            return det;
        }
        break;
        }


    }
    else
        cout<<"Error! The rows must be the same number as the columns!"<<endl;
}
Matrix Matrix::Transposition(){
    Matrix trans(columns, rows);
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<columns; j++)
            {
                trans.A[j][i]=A[i][j];
            }
        }
        return trans;
}
Rational Matrix::Cofactor(int x, int y){
    if(rows!=columns)
        cout<<"Error!"<<endl;
    Matrix tmp(rows-1, columns-1);
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
        {
            if(x!=i && y!=j)
            {
               if(x>i && y>j)
                   tmp.A[i][j]=A[i][j];
               if(x>i&& y<j)
                    tmp.A[i][j-1]=A[i][j];
               if(x<i && y>j)
                    tmp.A[i-1][j]=A[i][j];
               if(x<i && y<j)
                    tmp.A[i-1][j-1]=A[i][j];

            }
        }
    }

    Rational t=pow(-1,x+y);
    return tmp.Determinant()*t;
}
Matrix Matrix::InverseMatrix(){
    Rational tmp(1);
    Rational det=Determinant();
    Matrix Tr(rows, columns);
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
            Tr.A[i][j]=Cofactor(i,j)/det;
    }
    return Tr;

}
Matrix Matrix::operator+(Matrix const& B){
    if(IsAppropriateForSum(B))
    {
        Matrix result(rows,columns);
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<columns; j++)
                result.A[i][j] = this->A[i][j] + B.A[i][j];
        }
        return result;
    }
    else
        cout<<"Unable to sum the matrices!"<<endl;
}
Matrix Matrix::operator-(Matrix const& B){
    if(IsAppropriateForSum(B))
    {
        Matrix result(rows,columns);
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<columns; j++)
                result.A[i][j] = this->A[i][j]-B.A[i][j];
        }
        return result;
    }
    else
        cout<<"Unable to subtract the matrices!"<<endl;
}
Matrix Matrix::operator*(Matrix const& B){
    if(IsAppropriateForMult(B))
    {
        Matrix result(this->rows, B.columns);
        for(int i=0; i<this->rows; i++)
        {
            for(int j=0; j<B.columns; j++)
            {
                for(int k=0; k<this->columns; k++)
                    result.A[i][j]+=this->A[i][k]*B.A[k][j];
            }
        }
        return result;
    }
    else
        cout<<"Unable to multiply the matrices!"<<endl;
}
Matrix Matrix::operator*(Rational const& r){
    Matrix result(this->rows, this->columns);
        for(int i=0; i<this->rows; i++)
        {
            for(int j=0; j<this->columns; j++)
            {
                    result.A[i][j]=this->A[i][j]*r;
            }
        }
        return result;
}
Matrix Matrix::operator/(Matrix const& B){
    if(IsAppropriateForMult(B))
    {
        Matrix result(this->rows, B.columns);
        for(int i=0; i<this->rows; i++)
        {
            for(int j=0; j<B.columns; j++)
            {
                for(int k=0; k<this->columns; k++)
                {
                    result.A[i][j]+=this->A[i][k]/B.A[k][j];
                    cout<<result.A[i][j];
                }
            }
        }
        return result;
    }
    else
        cout<<"Unable to multiply the matrices!"<<endl;
}
Matrix& Matrix::operator=(Matrix const& B){
    for(int i=0; i<rows; i++)
        delete[] A[i];
   delete[] A;
   A=new Rational*[B.rows];
   for(int i=0; i<rows; i++)
        A[i]=new Rational[B.columns];
   for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
            A[i][j]=B.A[i][j];
    }
}
Rational* Matrix::operator[](int x){
    if(x>this->rows && x>this->columns)
        cout<<"Error! No such position."<<endl;
   /* for(int i=0; i<this->rows; i++)
    {
        if(x==i)return A[i];
        for(int j=0; j<this->columns; j++)
            if(x==j)return A[i][j];
    }*/
    return *(A+x);
}
ostream& operator<<(ostream& os, Matrix const& B){
    os << "\nMatrix: "<<" rows: " <<B.rows<<" columns: "<<B.columns<<"\n";
    for(int i=0; i<B.rows; i++)
    {
        os<<" | ";
        for(int j=0; j<B.columns; j++)
        {
            //char buf[32];
            Rational data = B.A[i][j];
            os<<data<<"  ";
        }
        os << "|\n";
    }
    os<<"\n";
    return os;
}
istream& operator>>(istream& is, Matrix& B){
    cout << "\nEnter input for matrix: " <<" rows: " <<B.rows<<"columns: " <<B.columns<<"\n";
    for(int i=0; i<B.rows; i++)
    {
        for(int j=0; j<B.columns; j++)
        {
            cout <<"Input for row: "<<i+1<<" column: "<<j+1<<" = ";
            is>>B.A[i][j];
        }
        cout<<"\n";
    }
    cout <<"\n";
    return is;
}
