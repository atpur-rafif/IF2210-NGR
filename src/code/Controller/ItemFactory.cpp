#include "Controller/ItemFactory.hpp"
#include "Exception/ItemFactoryException.hpp"

ItemFactory::ItemFactory(){};

string ItemFactory::codeFinder(function<bool(shared_ptr<Item>)> &lambda) const {
	for (const auto &[code, item] : this->repository)
		if (lambda(item)) return item->getCode();
	throw ItemNotFoundException();
}

// TODO: Validate if not exist
shared_ptr<Item> ItemFactory::createBaseItemByName(string name) const {
	shared_ptr<Item> item{this->repository.at(name)->clone()};
	item->setContext(this->getContext());
	return item;
}

shared_ptr<Item> &ItemFactory::getItemByName(string name) {
	return this->repository[name];
};

map<string, shared_ptr<Item>> &ItemFactory::getRepository() {
	return this->repository;
}
