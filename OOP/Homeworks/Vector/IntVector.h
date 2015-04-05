#ifndef INT_VECTOR_H_
#define INT_VECTOR_H_

class IntVector {

public:

	explicit IntVector(size_t);
	IntVector();
	IntVector(const IntVector&);

	~IntVector();

	IntVector& operator=(const IntVector&);

	void push_back(const int&);

	void pop_back();

	int& front();
	const int& front() const;
	int& back();
	const int& back() const;

	void clear();
	void resize(size_t);
	void reserve(size_t);
	void shrink_to_fit();

	size_t size() const;
	size_t capacity() const;
	bool empty() const;

private:

	// This part is just a tip, nothing obligatory
	int* mData;
	size_t mSize;
	size_t mCapacity;

	void copy(const IntVector&);
	void del();
	size_t getNextSize() const;
};

#endif