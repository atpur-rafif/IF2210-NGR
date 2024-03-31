#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "Container/Heapify.hpp"
#include <iostream>
#include <optional>
#include <string>
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

	static pair<int, int> parseCoordinate(string str) {
		int len = str.length();

		string x = "";
		string y = "";
		for (int i = 0; i < len; ++i) {
			auto ch = str.at(i);
			if (
					('A' <= ch && ch <= 'Z') ||
					('a' <= ch && ch <= 'z')
			) x += ch;
			else if (
					('0' <= ch && ch <= '9')
			) y += ch;
		}

		if (x.length() == 0 || y.length() == 0) throw "Invalid coordinate";

		return {stringToInt(x), stoi(y) - 1};
	}

public:
	Storage() : Storage(0, 0){};

	Storage(int width, int height) : width(width), height(height) {
		this->storage.resize(this->width * this->height);
	};

	optional<T> &getItem(string coordinate) {
		auto c = this->parseCoordinate(coordinate);
		return this->storage[this->flat(c.first, c.second)];
	};

	void getAllItem(vector<T *> &vec) {
		for (int i = 0; i < this->width * this->height; ++i) {
			if (this->storage[i].has_value())
				vec.push_back(&this->storage[i].value());
		}
	}

	void setItem(string coordinate, T &item) {
		auto c = this->parseCoordinate(coordinate);
		int i = this->flat(c.first, c.second);
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

// TODO: This is temporary solution, will be refactored
template <class T>
class HeapifyStorage : public Storage<Heapify<T>> {
public:
	HeapifyStorage() : HeapifyStorage(0, 0){};
	HeapifyStorage(int width, int height) : Storage<Heapify<T>>(width, height){};

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
