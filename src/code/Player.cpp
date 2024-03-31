#include "Player.hpp"
#include "GameContext.hpp"

Player::Player() {}
Player::~Player() {}

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
void Player::specialize(PlayerSpecialization &specialization) {
	this->specialization = Heapify(&specialization);
	this->specialization->setContext(this->getContext());
}

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

void Player::readInventoryFromStream(istream &inputStream) {
	GameContext *context = &this->getContext();
	auto size = context->miscConfig.getInventorySize();
	this->inventory = HeapifyStorage<Item>(size.first, size.second);

	int count;
	inputStream >> count;
	while (count--) {
		string name;
		inputStream >> name;
		string code = context->itemFactory.getCodeByName(name);
		Heapify<Item> item = context->itemFactory.createBaseItem(code);
		this->inventory.addItem(item);
	}
};

void FarmerSpecialization::readSpecializationFromStream(istream &inputStream) {
	GameContext *context = &this->getContext();
	auto size = context->miscConfig.getFarmSize();
	this->farm = Storage<FarmItem>(size.first, size.second);

	int count;
	inputStream >> count;
	while (count--) {
		int age;
		string location, name;
		inputStream >> location >> name >> age;

		FarmItem item;
		string code = context->itemFactory.getCodeByName(name);
		context->itemFactory.createItem(code, item);
		item.setAge(age);
		this->farm.setItem(location, item);
	}
};

void BreederSpecialization::readSpecializationFromStream(istream &inputStream) {
	GameContext *context = &this->getContext();
	auto size = context->miscConfig.getBarnSize();
	this->barn = Storage<BarnItem>(size.first, size.second);

	int count;
	inputStream >> count;
	while (count--) {
		int weight;
		string location, name;
		inputStream >> location >> name >> weight;

		BarnItem item;

		string code = context->itemFactory.getCodeByName(name);
		context->itemFactory.createItem(code, item);
		item.setWeight(weight);
		this->barn.setItem(location, item);
	}
};

void MayorSpecialization::readSpecializationFromStream(istream &inputStream) {
	(void)inputStream;
};
