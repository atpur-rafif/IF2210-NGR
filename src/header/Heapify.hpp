#ifndef HEAPIFY_HPP
#define HEAPIFY_HPP

template <class T>
class Heapify {
	T *pointer;

public:
	Heapify(T *value) {
		this->pointer = value->clone();
	}

	Heapify(const Heapify<T> &from) {
		this->pointer = from->clone();
	}

	Heapify &operator=(Heapify<T> &from) {
		this->pointer = from->clone();
		return *this;
	}

	T *operator->() {
		return this->pointer;
	}
};

#endif
