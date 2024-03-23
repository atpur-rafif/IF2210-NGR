#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "Item.hpp"
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Storage {
private:
	int width;
	int height;
	vector<T> storage;
	int flat(int x, int y) { return y * this->width + x; };
	static int stringToInt(string value) {
		int result = 0;
		int length = value.length();
		while (length > 0) {
			result = result * 26 + (tolower(value.at(--length)) - 'a');
		}
		return result;
	}
	T &get(string x, int y) {
		return this->storage.at(this->flat(this->stringToInt(x), y));
	}

public:
	Storage() : Storage(0, 0){};

	Storage(int width, int height) : width(width), height(height) {
		this->storage.resize(width * height);
	};

	T &getItem(string x, int y) {
		return this->get(x, y);
	};

	void setItem(string x, int y, T item) {
		this->get(x, y) = item;
	};

	void print() {
		for (int y = 0; y < this->height; ++y) {
			cout << "| ";
			for (int x = 0; x < this->width; ++x) {
				int i = this->flat(x, y);
				cout << this->storage.at(i).getCode() << " | ";
			}
			cout << endl;
		}
	}

	friend istream &operator>>(istream &inputStream, Storage<T> templateStorage);
};

#endif
