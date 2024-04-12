#include "Controller/ItemFactory.hpp"

ItemFactory::ItemFactory(){};

string ItemFactory::codeFinder(function<bool(Item *)> &lambda) const {
	for (const auto &i : this->repository) {
		auto item = i.second.getRaw();
		if (lambda(item)) return item->getCode();
	}
	throw InvalidItemNotFoundException();
}

Heapify<Item> ItemFactory::createBaseItem(string code) const {
	Heapify<Item> item = Heapify(this->repository.at(code));
	item->setContext(this->getContext());
	return item;
}

string ItemFactory::getCodeByName(const string name) const {
	function<bool(Item *)> fn = [name](Item *item) {
		return item->getName() == name;
	};
	return this->codeFinder(fn);
}