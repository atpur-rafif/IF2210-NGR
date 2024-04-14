#include "Controller/ShopController.hpp"
#include "Controller/GameContext.hpp"
#include "Model/Item.hpp"
#include "Model/Player.hpp"

map<ItemType, bool> ShopController::infinity = {
		{Farm, true},
		{Barn, true}
};

map<PlayerType, set<ItemType>> ShopController::catalogue = {
		{FarmerType, {Product, Farm, Building}},
		{BreederType, {Product, Barn, Building}},
		{MayorType, {Product}}
};

map<PlayerType, set<ItemType>> ShopController::accept = {
		{FarmerType, {Product, Farm}},
		{BreederType, {Product, Barn}},
		{MayorType, {Product, Building}}
};

bool ShopController::getAccepted(PlayerType playerType, ItemType itemType) {
	return ShopController::accept[playerType].contains(itemType);
};

map<string, int> ShopController::getCatalogue(PlayerType playerType) {
	auto ctx = this->getContext();
	map<string, int> list;

	for (auto &it : ctx.getItemFactory().getRepository()) {
		auto &item = it.second;
		auto name = item->getName();
		auto itemType = item->getType();
		if (!ShopController::catalogue[playerType].contains(itemType))
			continue;

		if (ShopController::infinity[itemType]) {
			list[name] = -1;
		} else {
			list[name] = this->items[name];
		}
	}

	return list;
};

void ShopController::addItem(shared_ptr<Item> item) {
	this->addItem(item, 1);
};

void ShopController::addItem(shared_ptr<Item> item, int count) {
	if (!ShopController::infinity[item->getType()]) this->items[item->getName()] += count;
};

void ShopController::removeItem(shared_ptr<Item> item) {
	if (!ShopController::infinity[item->getType()]) this->items[item->getName()] -= 1;
};

void ShopController::readShopFromStream(istream &inputStream) {
	auto ctx = this->getContext();
	auto itemFactory = ctx.getItemFactory();
	int itemCount;
	inputStream >> itemCount;
	while (itemCount--) {
		int count;
		string name;
		inputStream >> name >> count;
		string code = itemFactory.getCodeByName(name);
		shared_ptr<Item> item = itemFactory.createBaseItem(code);
		this->addItem(item, count);
	}
};

void ShopController::writeShopToStream(ostream &outputStream) {
	outputStream << this->items.size() << endl;
	for (auto &it : this->items) {
		outputStream << it.first << ' ' << it.second << endl;
	}
};
