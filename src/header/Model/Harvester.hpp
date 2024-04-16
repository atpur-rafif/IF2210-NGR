#ifndef MODEL_HARVESTER_HPP
#define MODEL_HARVESTER_HPP

#include "Container/Storage.hpp"
#include "Controller/GameContext.hpp"
#include "Model/GameObject.hpp"
#include "Model/Player.hpp"

template <class T>
class Harvester : public Player {
protected:
	Storage<T> field;

public:
	Storage<T> &getField() {
		return this->field;
	};

	void place(string inventoryLocation, string fieldLocation) {
		auto opt = this->inventory.getItem(inventoryLocation);
		if (!opt.has_value())
			throw GameException("Empty inventory slot");

		shared_ptr<Item> item = opt.value();
		T *newAnimal = dynamic_cast<T *>(item.get());
		if (newAnimal == nullptr)
			throw GameException("Invalid harvestable item");

		if (this->field.getItem(fieldLocation).has_value())
			throw GameException("Field slot not empty");

		this->field.setItem(fieldLocation, *newAnimal);
		this->inventory.clearItem(inventoryLocation);
	}

	void harvest(string coordinate) {
		auto &ctx = this->getContext();
		auto &itemFactory = ctx.getItemFactory();

		optional<T> harvestedAnimal = this->field.getItem(coordinate);
		if (!harvestedAnimal.has_value())
			throw GameException("Empty slot when harvesting");

		T &item = harvestedAnimal.value();
		vector<string> results = itemFactory.getProductResults(item.getName());

		if (this->inventory.getEmptySpaceCount() < (int)results.size())
			throw GameException("Inventory full when harvesting");

		this->field.clearItem(coordinate);
		for (auto name : results) {
			shared_ptr<Item> item = itemFactory.createBaseItemByName(name);
			this->inventory + item;
		}
	};

	void readFieldFromStream(istream &inputStream) {
		auto &ctx = this->getContext();
		int barnCount;
		inputStream >> barnCount;
		while (barnCount--) {
			string location, name;
			inputStream >> location >> name;
			T item;
			ctx.getItemFactory().createItemByName(name, item);
			item.readHarvestState(inputStream);
			this->field.setItem(location, item);
		}
	};

	void writeFieldToStream(ostream &outputStream) {
		auto items = this->field.getAllItemWithCoordinate();
		outputStream << items.size() << endl;
		for (auto &[location, item] : items) {
			outputStream << location << ' ' << item->getName() << ' ';
			item->writeHarvestState(outputStream);
			outputStream << endl;
		}
	}
};

#endif
