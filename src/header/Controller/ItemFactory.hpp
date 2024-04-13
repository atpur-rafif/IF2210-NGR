#ifndef ITEM_FACTORY_HPP
#define ITEM_FACTORY_HPP

#include "Exception/DowncastException.hpp"
#include "Model/GameObject.hpp"
#include "Model/Item.hpp"
#include "Model/Item/ProductItem.hpp"
#include "Exception/DowncastException.hpp"
#include "Exception/StorageException.hpp"
#include <functional>
#include <map>
#include <memory>

class ItemFactory : public GameObject {
	friend class GameContext;

protected:
	ItemFactory();
	map<string, shared_ptr<Item>> repository;
	string codeFinder(function<bool(shared_ptr<Item>)> &lambda) const;

public:
	/*
	 * From the name of it, isn't it obvious you can only use Item instance here?
	 * */
	template <class T>
	void addTemplateItem(T item) {
		shared_ptr<Item> ptr{item.clone()};
		this->repository[item.getCode()] = ptr;
	}

	template <class T>
	void createItem(string code, T &result) const {
		auto base = this->repository.at(code);
		shared_ptr<Item> clone{base->clone()};
		if (clone->getType() == result.getType()) {
			shared_ptr<T> ptr = dynamic_pointer_cast<T>(clone);
			result = *ptr;
			result.setContext(this->getContext());
		} else {
			throw InvalidDowncastException();
		}
	}

	shared_ptr<Item> createBaseItem(string code) const;
	string getCodeByName(const string name) const;
	
	string getProductResult(string Code, string obtainedProduct) {
		for (const auto &repo_el:this->repository){
			auto tempRepoItem = repo_el.second;
			ProductItem* product = dynamic_cast<ProductItem*>(&*tempRepoItem);
			if (product != nullptr){
				if (product->getOrigin() == Code && repo_el.first != obtainedProduct){
					return repo_el.first;
				}
			}
		}
		return "";
	}
};
#endif