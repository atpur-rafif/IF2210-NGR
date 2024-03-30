#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "Heapify.hpp"
#include <optional>
#include <vector>
using namespace std;

/*
 * This class can only be used with Item as T
 * */
template <class T>
class Storage {
protected:
	int width;
	int height;
	vector<optional<T>> storage;
	int flat(int x, int y) { return y * this->width + x; };
	static int stringToInt(string value) {
		int result = 0;
		int length = value.length();
		while (length > 0) {
			result = result * 26 + (tolower(value.at(--length)) - 'a');
		}
		return result;
	}

public:
	Storage() : Storage(0, 0){};

	Storage(int width, int height) : width(width), height(height) {
		this->storage.resize(width * height);
	};

	T *getItem(string x, int y) {
		auto val = this->storage[this->flat(this->stringToInt(x), y)];
		if (val.has_value()) return &val.value();
		else return NULL;
	};

	void setItem(string x, int y, T item) {
		int ix = this->stringToInt(x);
		int i = this->flat(ix, y);
		this->storage[i] = item;
	};

	void addItem(T item) {
		for (int y = 0; y < this->height; ++y) {
			for (int x = 0; x < this->width; ++x) {
				int i = this->flat(x, y);
				if (!this->storage[i].has_value()) {
					this->storage[i] = item;
					return;
				}
			}
		}
	}

	pair<int, int> getSize() {
		return {this->width, this->height};
	}

	void print() {
		for (int y = 0; y < this->height; ++y) {
			cout << "| ";
			for (int x = 0; x < this->width; ++x) {
				int i = this->flat(x, y);
				auto &val = this->storage[i];
				if (!val.has_value()) cout << "   ";
				else cout << val->getCode();
				cout << " | ";
			}
			cout << endl;
		}
	}
};

template <class T>
class HeapifyStorage : public Storage<Heapify<T>> {
public:
	HeapifyStorage() : HeapifyStorage(0, 0){};
	HeapifyStorage(int width, int height) : Storage<Heapify<T>>(width, height){};

	T *getItem(string x, int y) {
		auto val = this->storage[this->flat(this->stringToInt(x), y)];
		if (val.has_value()) return val->getRaw();
		else return NULL;
	};

	void print() {
		for (int y = 0; y < this->height; ++y) {
			cout << "| ";
			for (int x = 0; x < this->width; ++x) {
				int i = this->flat(x, y);
				auto val = this->storage[i];
				if (!val.has_value()) cout << "   ";
				else cout << val.value()->getCode();
				cout << " | ";
			}
			cout << endl;
		}
	}
};

#endif
