#include "Controller/ItemFactory.hpp"
#include "Exception/ItemFactoryException.hpp"

ItemFactory::ItemFactory(){};

string ItemFactory::codeFinder(function<bool(shared_ptr<Item>)> &lambda) const {
	for (const auto &i : this->repository) {
		auto item = i.second;
		if (lambda(item)) return item->getCode();
	}
	throw ItemNotFoundException();
}

shared_ptr<Item> ItemFactory::createBaseItem(string code) const {
	shared_ptr<Item> item{this->repository.at(code)->clone()};
	item->setContext(this->getContext());
	return item;
}

string ItemFactory::getCodeByName(const string name) const {
	function<bool(shared_ptr<Item>)> fn = [name](shared_ptr<Item> item) {
		return item->getName() == name;
	};
	return this->codeFinder(fn);
}

map<string, shared_ptr<Item>> ItemFactory::getRepository() {
	return this->repository;
}
