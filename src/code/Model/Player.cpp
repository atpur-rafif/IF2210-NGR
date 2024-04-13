#include "Model/Player.hpp"
#include "Controller/GameContext.hpp"

Player::Player() {}
Player::~Player() {}

int Player::getTaxBracket(int taxed) {
	if (taxed <= 6) return 5;
	else if (taxed <= 25) return 15;
	else if (taxed <= 50) return 25;
	else if (taxed <= 500) return 30;
	else return 35;
};

string Player::playerTypeToString(int type) {
	vector<string> typeString{"Petani", "Peternak", "Walikota"};
	return typeString[type];
}

int Player::countInventoryWealth() {
	vector<shared_ptr<Item> *> items = this->inventory.getAllItem();

	int wealth = 0;
	for (const auto &itemPtr : items)
		wealth += (*itemPtr)->getPrice();
	return wealth;
}

void Player::readInventory(istream &inputStream) {
	auto &ctx = this->getContext();
	auto &misc = ctx.miscConfig;
	this->inventory = Storage<shared_ptr<Item>>(misc.getInventoryWidth(), misc.getInventoryHeight());

	int inventoryCount;
	inputStream >> inventoryCount;
	while (inventoryCount--) {
		string name;
		inputStream >> name;
		string code = ctx.itemFactory.getCodeByName(name);
		shared_ptr<Item> item = ctx.itemFactory.createBaseItem(code);
		this->inventory.addItem(item);
	}
};

void Player::writeInventory(ostream &outputStream) {
	auto items = this->inventory.getAllItem();
	outputStream << items.size() << endl;
	for (auto item : items) {
		outputStream << (*item)->getName() << endl;
	}
};
