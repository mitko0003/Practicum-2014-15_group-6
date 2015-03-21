#ifndef _DOUBLE_H
#define _DOUBLE_H

class Double {

public:
	Double();
	Double(const double&);
	Double(const char*);

	double doubleValue() const;

	// Print with the given precision
	void print(const int& = 2) const;

	// Print the bits which represent the following
	void printMantissa() const;
	void printExponent() const;

	Double& increment() const;
	bool equals(const Double&) const;

	// The following operator
	Double& add(const Double&) const;
	Double& subtract(const Double&) const;
	Double& multiply(const Double&) const;
	Double& divide(const Double&) const;

private:
	// What ever you need

};

#endif