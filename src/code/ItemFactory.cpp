#include "ItemFactory.hpp"

ItemFactory::ItemFactory(){};

string ItemFactory::codeFinder(function<bool(Item *)> &lambda) {
	for (const auto &i : this->repository) {
		auto item = i.second.getRaw();
		if (lambda(item)) return item->getCode();
	}
	throw "Item not found";
}

Heapify<Item> ItemFactory::createBaseItem(string code) {
	Heapify<Item> item = Heapify(this->repository[code]);
	item->setContext(this->getContext());
	return item;
}

string ItemFactory::getCodeByName(const string name) {
	function<bool(Item *)> fn = [name](Item *item) {
		return item->getName() == name;
	};
	return this->codeFinder(fn);
}
