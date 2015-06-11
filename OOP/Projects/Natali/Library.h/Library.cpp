#include "stdafx.h"
#include "Book.h"

using namespace std;

namespace Books{

	Book::Book(string i, string t, string a, Genre g, int cp, bool ch /* = false */)
		: ISBN(i), title(t), author(a), gnr(g), cpyrghtDate(cp), chkout(ch)
	{
		if(!(isalpha(i[i.size()-1])) && !(isdigit(i[i.size()-1]))) throw Invalid();
		for(int j=0;j<i.size()-1;++j)
		{
			if(!(isdigit(i[j]))) throw Invalid();
		}
	}

	void Book::_chkout()
	{
		chkout = true;		
	}

	void Book::_chkin()
	{
		chkout = false;
	}

	bool operator==(const Book& a, const Book& b)
	{
		return a._ISBN()==b._ISBN();
	}

	bool operator!=(const Book& a, const Book& b)
	{
		return !(a==b);
	}	

	ostream& operator<<(ostream& os, const Book& b)
	{
		return os << b._title() << "\n" <<  b._author() << "\n" << b._ISBN() << "\n" << b._gnr() << "\n\n";
	}

	void Patron::set_fee(double x)
	{
		lib_fee = x;
	}

	bool Patron::chk_fee()
	{
		if(_lib_fee()==0) return false;
			else return true;
	}
}


int _tmain(int argc, _TCHAR* argv[])
try{
	Books::Book b1("123S", "Pod igoto", "Ivan Vazov", Books::Book::periodical, 1880, true);
	Books::Book b2("123S", "Nova zemq", "Ivan Vazov", Books::Book::fiction, 1885/*, true*/);
	cout << /*b1._gnr() <<*/ b1 << b2 << endl;

	Books::Patron p1("Natali", 358, 0);
	p1.set_fee(20.5);

	system("pause");
	return p1.chk_fee();
}
catch(Books::Book::Invalid&) {
	cerr << "Invalid ISBN!";
	system("pause");
	return 1;
}

