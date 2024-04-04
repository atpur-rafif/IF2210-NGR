#ifndef HEAPIFY_HPP
#define HEAPIFY_HPP

#include <cstddef>

// Make sure to use value with derived type, instead base type
// Somehow the compiler doesn't want to clone using derived virtual method with base type
template <class T>
class Heapify {
	T *pointer;

public:
	Heapify() : Heapify(NULL) {}

	Heapify(T value) {
		this->set(&value);
	}

	Heapify(T *value) {
		this->set(value);
	}

	Heapify(const Heapify<T> &from) {
		*this = from;
	}

	Heapify &operator=(const Heapify<T> &from) {
		this->set(from.getRaw());
		return *this;
	}

	template <class U>
	Heapify &operator=(const Heapify<U> &from) {
		T *ptr = from.getRaw();
		this->set(ptr);
		return *this;
	}

	~Heapify() {
		if (this->pointer != NULL) delete this->pointer;
	}

	T *operator->() const {
		return this->pointer;
	}

	T *getRaw() const {
		return this->pointer;
	}

	T &get() const {
		return *this->pointer;
	}

	void set(T *value) {
		if (value == NULL) {
			this->pointer = NULL;
			return;
		};
		pointer = value->clone();
	}
};

#endif
