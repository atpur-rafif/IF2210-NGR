#ifndef ITEM_FACTORY_HPP
#define ITEM_FACTORY_HPP

#include "Container/Heapify.hpp"
#include "Model/GameObject.hpp"
#include "Model/Item.hpp"
#include "Model/Item/ProductItem.hpp"
#include <functional>
#include <map>

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
		if (clone->getType()==result.getType()){
			T *ptr = dynamic_cast<T *>(clone);
			result = *ptr;
			result.setContext(this->getContext());
		}
		else{
			throw;
		}
	}

	Heapify<Item> createBaseItem(string code) const;
	string getCodeByName(const string name) const;

	template<class T>
	string getProductResult(T item) {
		for (const auto &repo_el:this->repository)
		{
			auto tempRepoItem = repo_el.second;
        	ProductItem* product = dynamic_cast<ProductItem*>(tempRepoItem.getRaw());
			if (product != nullptr)
			{
				if (product->getOrigin() == item->getName())
				{
					return repo_el.first;
				}
			}
		}
		return NULL;
	}
};

#endif
