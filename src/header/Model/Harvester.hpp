#ifndef MODEL_HARVESTER_HPP
#define MODEL_HARVESTER_HPP

#include "Container/Storage.hpp"
#include "Model/GameObject.hpp"
#include "Model/Player.hpp"

// TODO: Add constraint
template <class T>
class Harvester : public Player {
protected:
	Storage<T> field;

public:
	void place(string &inventoryLocation, string &fieldLocation) {
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

	void harvest(){};

	Storage<T> &getField() {
		return this->field;
	};

	void readFieldFromStream(istream &inputStream) {
		auto &ctx = this->getContext();
		auto &misc = ctx.getMiscConfig();
		this->field = Storage<T>(misc.getBarnWidth(), misc.getFarmHeight());
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
