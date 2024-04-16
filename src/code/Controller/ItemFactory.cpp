#include "Controller/ItemFactory.hpp"

ItemFactory::ItemFactory(){};

string ItemFactory::nameFinder(function<bool(shared_ptr<Item>)> &lambda) const {
	for (const auto &[code, item] : this->repository)
		if (lambda(item)) return item->getName();
	throw GameException("Item not found using codeFinder");
}

shared_ptr<Item> ItemFactory::createBaseItemByName(string name) const {
	shared_ptr<Item> item{this->repository.at(name)->clone()};
	item->setContext(this->getContext());
	return item;
}

string ItemFactory::getNameByCode(string code) {
	function<bool(shared_ptr<Item>)> fn = [&](shared_ptr<Item> item) {
		if (item->getCode() == code) return true;
		return false;
	};
	return this->nameFinder(fn);
};

shared_ptr<Item> &ItemFactory::getItemByName(string name) {
	return this->repository[name];
};

map<string, shared_ptr<Item>> &ItemFactory::getRepository() {
	return this->repository;
}
