#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "Exception/StorageException.hpp"
#include <iostream>
#include <map>
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

public:
	Storage() : Storage(0, 0){};

	Storage(int width, int height) : width(width), height(height) {
		this->storage.resize(this->width * this->height);
	};

	optional<T> &getItem(int x, int y) {
		return this->storage[this->flat(x, y)];
	};

	optional<T> &getItem(string coordinate) {
		auto position = this->decodeCoordinate(coordinate);
		return this->getItem(position.first, position.second);
	};

	void clearItem(string coordinate) {
		auto position = this->decodeCoordinate(coordinate);
		this->clearItem(position.first, position.second);
	}

	void clearItem(int x, int y) {
		int i = this->flat(x, y);
		this->storage[i].reset();
	}

	vector<T *> getAllItem() {
		vector<T *> items;
		for (int i = 0; i < this->width * this->height; ++i) {
			if (this->storage[i].has_value())
				items.push_back(&this->storage[i].value());
		}
		return items;
	}

	vector<pair<string, T *>> getAllItemWithCoordinate() {
		vector<pair<string, T *>> items;
		for (int y = 0; y < this->height; ++y) {
			for (int x = 0; x < this->width; ++x) {
				int i = this->width * y + x;
				if (this->storage[i].has_value())
					items.push_back({Storage::encodeCoordinate(x, y), &this->storage[i].value()});
			}
		}
		return items;
	}

	void setItem(int x, int y, T &item) {
		int i = this->flat(x, y);
		this->storage[i] = item;
	};

	void setItem(string coordinate, T &item) {
		auto position = this->decodeCoordinate(coordinate);
		this->setItem(position.first, position.second, item);
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

	void removeItem(string name) {
		for (int y = 0; y < this->height; ++y) {
			for (int x = 0; x < this->width; ++x) {
				int i = this->flat(x, y);
				if (this->storage[i].has_value()) {
					if (this->storage[i].value()->getName() == name) {
						this->storage[i].reset();
						return;
					}
				}
			}
		}
	}

	int getEmptySpaceCount() {
		return (this->width * this->height) - this->getAllItem().size();
	}

	int getWidth() {
		return this->width;
	}

	int getHeight() {
		return this->height;
	}

	map<string, int> getItemFreq() {
		vector<T> vec;
		map<string, int> result;
		for (int i = 0; i < this->width * this->height; ++i) {
			if (this->storage[i].has_value())
				vec.push_back(this->storage[i].value());
		}
		for (auto const &item : vec) {
			++result[item.get()->getName()];
		}
		return result;
	}

	pair<int, int> decodeCoordinate(string str) {
		int len = str.length();

		string sx = "";
		string sy = "";
		for (int i = 0; i < len; ++i) {
			auto ch = str.at(i);
			if (
					('A' <= ch && ch <= 'Z') ||
					('a' <= ch && ch <= 'z')
			) sx += ch;
			else if (
					('0' <= ch && ch <= '9')
			) sy += ch;
		}

		if (sx.length() == 0 || sy.length() == 0) throw InvalidCoordinateStorageException();

		int x = stringToInt(sx);
		int y = stoi(sy) - 1;

		if (x < 0 || this->width < x || y < 0 || this->height < y) throw InvalidCoordinateStorageException();

		return {x, y};
	}

	string encodeCoordinate(int x, int y) {
		string str = "";
		if (x == 0) {
			str += "A";
		} else {
			while (x) {
				str += ('A' + (x % 26));
				x /= 26;
			}
		}

		str += to_string(y + 1);
		return str;
	}
};

#endif
