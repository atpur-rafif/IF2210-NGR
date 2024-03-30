#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Storage {
private:
	int width;
	int height;
	vector<T> storage;
	vector<bool> filled;
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
		this->filled.resize(width * height);
		for (int i = 0; i < width * height; ++i)
			this->filled[i] = false;
	};

	T &getItem(string x, int y) {
		return this->storage[this->flat(this->stringToInt(x), y)];
	};

	void setItem(string x, int y, T item) {
		int ix = this->stringToInt(x);
		int i = this->flat(ix, y);
		this->filled[i] = true;
		this->storage[i] = item;
	};

	void addItem(T item) {
		for (int y = 0; y < this->height; ++y) {
			for (int x = 0; x < this->width; ++x) {
				int i = this->flat(x, y);
				if (!this->filled[i]) {
					this->filled[i] = true;
					this->storage[i] = item;
					return;
				}
			}
		}
	}

	// TODO: Generalize iterator
	void print() {
		for (int y = 0; y < this->height; ++y) {
			cout << "| ";
			for (int x = 0; x < this->width; ++x) {
				int i = this->flat(x, y);
				if (!this->filled[i]) cout << "   ";
				else cout << this->storage.at(i)->getCode();
				cout << " | ";
			}
			cout << endl;
		}
	}
};

#endif
