#include "Player.hpp"

Player::Player() {}

SpecializationType Player::getType() { return this->type; }
int Player::getWeight() { return this->weight; }
int Player::getMoney() { return this->money; }
string Player::getUsername() { return this->username; }
HeapifyStorage<Item> &Player::getInventory() { return this->inventory; }

PlayerSpecialization::PlayerSpecialization() {}
FarmerSpecialization::FarmerSpecialization() {}
BreederSpecialization::BreederSpecialization() {}
MayorSpecialization::MayorSpecialization() {}

PlayerSpecialization::~PlayerSpecialization() {}
FarmerSpecialization::~FarmerSpecialization() {}
BreederSpecialization::~BreederSpecialization() {}
MayorSpecialization::~MayorSpecialization() {}

FarmerSpecialization *FarmerSpecialization::clone() const { return new FarmerSpecialization(*this); }
BreederSpecialization *BreederSpecialization::clone() const { return new BreederSpecialization(*this); }
MayorSpecialization *MayorSpecialization::clone() const { return new MayorSpecialization(*this); }

Storage<FarmItem> & ::FarmerSpecialization::getFarm() { return this->farm; };
Storage<BarnItem> & ::BreederSpecialization::getBarn() { return this->barn; };

PlayerSpecialization &Player::getSpecialization() { return *this->specialization.getRaw(); };
void Player::specialize(PlayerSpecialization &specialization) { this->specialization = Heapify(&specialization); }

istream &operator>>(istream &inputStream, Player &player) {
	inputStream >> player.username;

	string type;
	inputStream >> type;
	if (type == "Petani") player.type = Farmer;
	else if (type == "Peternak") player.type = Breeder;
	else if (type == "Walikota") player.type = Mayor;

	inputStream >> player.weight;
	inputStream >> player.money;

	return inputStream;
};

void Player::readInventoryFromStream(istream &inputStream, MiscConfig &miscConfig, ItemFactory &itemFactory) {
	auto size = miscConfig.getInventorySize();
	this->inventory = HeapifyStorage<Item>(size.first, size.second);

	int count;
	inputStream >> count;
	while (count--) {
		string name;
		inputStream >> name;
		string code = itemFactory.getCodeByName(name);
		Heapify<Item> item = itemFactory.createBaseItem(code);
		this->inventory.addItem(item);
	}
};

// TODO: Set item attribute
void FarmerSpecialization::readSpecializationFromStream(istream &inputStream, MiscConfig &miscConfig, ItemFactory &itemFactory) {
	auto size = miscConfig.getFarmSize();
	this->farm = Storage<FarmItem>(size.first, size.second);

	int count;
	inputStream >> count;
	while (count--) {
		string location, name, age;
		inputStream >> location >> name >> age;

		FarmItem item;
		string code = itemFactory.getCodeByName(name);
		itemFactory.createItem(code, item);
		this->farm.addItem(item);
	}
};

// TODO: Set item attribute
void BreederSpecialization::readSpecializationFromStream(istream &inputStream, MiscConfig &miscConfig, ItemFactory &itemFactory) {
	auto size = miscConfig.getBarnSize();
	this->barn = Storage<BarnItem>(size.first, size.second);

	int count;
	inputStream >> count;
	while (count--) {
		string location, name, weight;
		inputStream >> location >> name >> weight;

		BarnItem item;
		string code = itemFactory.getCodeByName(name);
		itemFactory.createItem(code, item);
		this->barn.addItem(item);
	}
};

void MayorSpecialization::readSpecializationFromStream(istream &inputStream, MiscConfig &config, ItemFactory &itemFactory) {
	(void)inputStream;
	(void)config;
	(void)itemFactory;
};
