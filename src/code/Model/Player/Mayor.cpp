#include "Model/Player/Mayor.hpp"
#include "Controller/GameContext.hpp"
#include "Exception/GameException.hpp"
#include "Model/Item/BuildingItem.hpp"
#include <sstream>

#define MINIMUM_MONEY 50

Mayor::Mayor() { this->type = MayorType; }
Mayor::~Mayor() {}
Mayor *Mayor::clone() { return new Mayor(*this); }

vector<pair<shared_ptr<Player>, int>> Mayor::collectTax() {
	vector<pair<shared_ptr<Player>, int>> result;
	pair<shared_ptr<Player>, int> inserter;
	auto players = this->getContext().getPlayerController().getPlayers();
	int size = players.size();
	for (int i = 0; i < size; ++i) {
		auto &income = players[i];
		if (income->getType() == MayorType) continue;
		int tax = income->calculateTax();
		income->setMoney(income->getMoney() - tax);
		this->setMoney(this->getMoney() + tax);
		inserter.first = income;
		inserter.second = tax;
		result.push_back(inserter);
	}
	sort(result.begin(), result.end(), [](const pair<shared_ptr<Player>, int> &elOne, const pair<shared_ptr<Player>, int> &elTwo) {
		if (elTwo.second != elOne.second) {
			return elTwo.second < elOne.second;
		} else {
			return (elTwo.first.get()->getUsername() > elOne.first.get()->getUsername() || PlayerController::toLower(elTwo.first.get()->getUsername()) > PlayerController::toLower(elOne.first.get()->getUsername()));
		}
	});
	return result;
}

int Mayor::calculateTax() {
	return 0;
}

void Mayor::buildBuilding(string name, vector<string> &ingredientLocation) {
	auto &itemFactory = this->getContext().getItemFactory();
	auto building = dynamic_pointer_cast<BuildingItem>(itemFactory.getItemByName(name));
	if (building == nullptr)
		throw GameException("Parameter " + name + " isn't a building");

	if (building->getPrice() > this->getMoney())
		throw GameException("Insufficient funds when building");

	auto &counter = building->getIngredients();
	for (auto &location : ingredientLocation) {
		auto &opt = this->inventory.getItem(location);
		if (!opt.has_value())
			throw GameException("Empty supplied location when building");

		auto itemName = opt.value()->getName();
		if (!counter.contains(itemName)) throw GameException("Supplied ingredient include unused item");
		if (counter[itemName] == 1) counter.erase(itemName);
		else counter[itemName] -= 1;

		this->inventory.clearItem(location);
	}

	if (counter.size() != 0)
		throw GameException("Insufficient supplied ingredient location");

	shared_ptr<Item> newBuilding = itemFactory.createBaseItemByName(building->getName());
	this->inventory.addItem(newBuilding);
}

pair<vector<string>, map<string, int>> Mayor::checkInventory(map<string, int> items) {
	vector<string> locations;
	(void)items;
	for (auto &[coordinate, item] : this->inventory.getAllItemWithCoordinate()) {
		auto name = (*item)->getName();
		if (!items.contains(name)) continue;

		locations.push_back(coordinate);

		if (items[name] == 1) items.erase(name);
		else items[name] -= 1;
	}

	return {locations, items};
};

const int startWeight = 0;
const int startMoney = 50;
void Mayor::addPlayer(string username, string type) {
	auto &playerController = this->getContext().getPlayerController();
	if (startMoney > this->getMoney()) throw GameException("Insufficient funds when creating new player");
	this->money -= startMoney;

	string stream = username + " " + type + " " + to_string(startWeight) + " " + to_string(startMoney) + " 0 0"; // Last part for empty inventory
	istringstream inputStream(stream);
	shared_ptr<Player> player = playerController.readPlayerFromStream(inputStream);
	playerController.addPlayer(player);

	// TODO: Create util for string
	if (this->username > username || PlayerController::toLower(this->username) > PlayerController::toLower(username)) {
		this->getContext().getPlayerController().nextPlayer();
	}
}

void Mayor::isEnoughMoney() {
	if (this->money < MINIMUM_MONEY) throw GameException("Not enought money");
}

void Mayor::readSpecializedConfig(istream &inputStream) {
	(void)inputStream;
}

void Mayor::writeSpecializedConfig(ostream &outputStream) {
	(void)outputStream;
}
