#include "MySexyVector.h"
#include <assert.h>

MySexyVector::MySexyVector(const MySexyVector & source)
{
	*this = source;
}

MySexyVector & MySexyVector::operator=(const MySexyVector & source)
{
	delete[] container;

	currentCapacity = source.currentCapacity;
	currentSize = source.currentSize;

	if (currentCapacity > 0) {
		container = new int[currentCapacity];

		for (int i = 0; i < currentSize; i++) {
			container[i] = source[i];
		}
	}	
	return *this;
}

MySexyVector::~MySexyVector()
{
	delete[] container;
	container = nullptr;
}

// operators

int& MySexyVector::operator[](int pos)
{
	assert(pos < currentSize);
	return container[pos];
}

const int MySexyVector::operator[](int pos) const
{
	assert(pos < currentSize);
	return container[pos];
}

// capacity

bool MySexyVector::empty() const
{
	return currentSize == 0;
}

int MySexyVector::size() const
{
	return currentSize;
}

void MySexyVector::reserve(int new_cap)
{
	if (new_cap <= currentCapacity) {
		return;
	}
	reallocate(new_cap);
}

int MySexyVector::capacity() const
{
	return currentCapacity;
}

void MySexyVector::shrink_to_fit()
{
	reallocate(currentSize);
}

void MySexyVector::clear()
{
	currentSize = 0;
}

void MySexyVector::push_back(int value)
{
	if (currentCapacity == 0) {
		reallocate(1);
	}
	else if (currentSize == currentCapacity) {
		reallocate(currentCapacity * 2);
	}
	container[currentSize] = value;
	currentSize++;
}

void MySexyVector::pop_back()
{
	assert(currentSize > 0);
	currentSize -= 1;
}

void MySexyVector::reallocate(int new_cap)
{
	assert(new_cap >= 0);
	int* newContainer = new int[new_cap];
	for (int i = 0; (i < currentCapacity) && (i < new_cap); i++) {
		newContainer[i] = container[i];
	}
	delete[] container;
	container = newContainer;
	currentCapacity = new_cap;
}
