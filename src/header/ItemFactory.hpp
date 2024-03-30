#ifndef ITEM_FACTORY_HPP
#define ITEM_FACTORY_HPP

#include "Heapify.hpp"
#include "Item.hpp"
#include <functional>

class ItemFactory {
private:
	map<string, Heapify<Item>> repository;
	string codeFinder(function<bool(Item *)> &lambda) {
		for (const auto &i : this->repository) {
			auto item = i.second.getRaw();
			if (lambda(item)) return item->getCode();
		}
		throw "Item not found";
	}

public:
	// TODO: Item instance guard
	template <class T>
	void addItem(T item) {
		Item *base = &item;
		Heapify<Item> heap = Heapify(base);
		this->repository[item.getCode()] = heap;
	}

	template <class T>
	void createItem(string code, T &result) {
		Item *base = this->repository[code].getRaw();
		Item *clone = base->clone();
		T *ptr = dynamic_cast<T *>(clone);
		result = *ptr;
	}

	string getCodeByName(const string name) {
		function<bool(Item *)> fn = [name](Item *item) {
			return item->getName() == name;
		};
		return this->codeFinder(fn);
	}
};

#endif
