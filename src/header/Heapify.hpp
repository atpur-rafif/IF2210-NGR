#ifndef HEAPIFY_HPP
#define HEAPIFY_HPP

#include <cstddef>

// Make sure to use value with derived type, instead base type
// Somehow the compiler doesn't want to clone using derived virtual method with base type
template <class T>
class Heapify {
	T *pointer;

public:
	Heapify(T *value) {
		this->set(value);
	}

	Heapify(const Heapify<T> &from) {
		pointer = from->clone();
	}

	Heapify &operator=(const Heapify<T> &from) {
		pointer = from->clone();
		return *this;
	}

	T *operator->() const {
		return pointer;
	}

	void set(T *value) {
		if (value == NULL) return;
		pointer = value->clone();
	}
};

#endif
