#ifndef ITEM_FACTORY_HPP
#define ITEM_FACTORY_HPP

#include "GameObject.hpp"
#include "Heapify.hpp"
#include "Item.hpp"
#include <functional>

class ItemFactory : public GameObject {
private:
	map<string, Heapify<Item>> repository;
	string codeFinder(function<bool(Item *)> &lambda);

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
		result.setContext(this->getContext());
	}

	Heapify<Item> createBaseItem(string code);

	string getCodeByName(const string name);
};

#endif
