#ifndef ITEM_FACTORY_HPP
#define ITEM_FACTORY_HPP

#include "GameObject.hpp"
#include "Heapify.hpp"
#include "Item.hpp"
#include <functional>

class ItemFactory : public GameObject {
	friend class GameContext;

protected:
	ItemFactory();
	map<string, Heapify<Item>> repository;
	string codeFinder(function<bool(Item *)> &lambda) const;

public:
	/*
	 * From the name of it, isn't it obvious you can only use Item instance here?
	 * */
	template <class T>
	void addTemplateItem(T item) {
		Item *base = &item;
		Heapify<Item> heap = Heapify(base);
		this->repository[item.getCode()] = heap;
	}

	template <class T>
	void createItem(string code, T &result) const {
		Item *base = this->repository.at(code).getRaw();
		Item *clone = base->clone();
		T *ptr = dynamic_cast<T *>(clone);
		result = *ptr;
		result.setContext(this->getContext());
	}

	Heapify<Item> createBaseItem(string code) const;

	string getCodeByName(const string name) const;
};

#endif
