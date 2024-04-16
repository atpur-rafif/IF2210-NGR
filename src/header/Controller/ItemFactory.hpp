#ifndef ITEM_FACTORY_HPP
#define ITEM_FACTORY_HPP
#include "Exception/StorageException.hpp"
#include "Model/GameObject.hpp"
#include "Model/Item.hpp"
#include "Model/Item/ProductItem.hpp"
#include <functional>
#include <map>
#include <memory>

// TODO: Create iterator, like filter or so
class ItemFactory : public GameObject {
	friend class GameContext;

protected:
	ItemFactory();
	map<string, shared_ptr<Item>> repository;
	string nameFinder(function<bool(shared_ptr<Item>)> &lambda) const;

public:
	// Add new item from derived class, without the need to upcast
	template <class T>
	void addTemplateItem(T item) {
		shared_ptr<Item> ptr{item.clone()};
		this->repository[item.getName()] = ptr;
	}

	// Create item directly to derived class
	template <class T>
	void createItemByName(string name, T &result) const {
		auto base = this->repository.at(name);
		shared_ptr<Item> clone{base->clone()};
		if (clone->getType() == result.getType()) {
			shared_ptr<T> ptr = dynamic_pointer_cast<T>(clone);
			result = *ptr;
			result.setContext(this->getContext());
		} else {
			throw GameException("Can't create specified item because type mismatch");
		}
	}

	// Creating base item (shared pointer to Item)
	shared_ptr<Item> createBaseItemByName(string name) const;
	shared_ptr<Item> &getItemByName(string name);
	string getNameByCode(string code);

	vector<string> getProductResults(string name) {
		vector<string> results;
		for (const auto &repo_el : this->repository) {
			auto tempRepoItem = repo_el.second;
			ProductItem *product = dynamic_cast<ProductItem *>(&*tempRepoItem);
			if (product != nullptr) {
				if (product->getOrigin() == this->repository[name]->getName()) {
					results.push_back(product->getName());
				}
			}
		}
		return results;
	}

	string getProductResult(string Code, string obtainedProduct) {
		for (const auto &repo_el : this->repository) {
			auto tempRepoItem = repo_el.second;
			ProductItem *product = dynamic_cast<ProductItem *>(&*tempRepoItem);
			if (product != nullptr) {
				if (product->getOrigin() == Code && repo_el.first != obtainedProduct) {
					return repo_el.second->getName();
				}
			}
		}
		return "";
	}

	map<string, shared_ptr<Item>> &getRepository();
};
#endif
