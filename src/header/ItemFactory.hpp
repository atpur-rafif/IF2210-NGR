#ifndef ITEM_FACTORY_HPP
#define ITEM_FACTORY_HPP

#include "Heapify.hpp"
#include "Item.hpp"

class ItemFactory {
private:
public:
	map<string, Heapify<Item>> repository;
	// TODO: Item instance guard
	template <class T>
	void addItem(T item) {
		Item *base = &item;
		Heapify<Item> heap = Heapify(base);
		this->repository[item.getCode()] = heap;
	}

	template <class T>
	void createItem(string code, Heapify<T> &result) {
		cout << this->repository[code]->getCode();
		Item *base = this->repository[code].getRaw();
		Item *clone = base->clone();
		T *ptr = dynamic_cast<T *>(clone);
		result.set(ptr);
	}
};

#endif
