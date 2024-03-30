#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Heapify.hpp"
#include "Item.hpp"
#include "ItemFactory.hpp"
#include "MiscConfig.hpp"
#include "Storage.hpp"

class GameContext;

enum SpecializationType {
	Farmer,
	Breeder,
	Mayor
};

class PlayerSpecialization {
private:
public:
	PlayerSpecialization();
	virtual PlayerSpecialization *clone() const = 0;
	virtual ~PlayerSpecialization();

	virtual void readSpecializationFromStream(istream &inputStream, GameContext &context) = 0;
};

class Player {
protected:
	string username;
	SpecializationType type;
	int weight;
	int money;
	HeapifyStorage<Item> inventory;

	Heapify<PlayerSpecialization> specialization;

public:
	Player();

	SpecializationType getType();
	int getWeight();
	int getMoney();
	string getUsername();
	HeapifyStorage<Item> &getInventory();

	PlayerSpecialization &getSpecialization();
	void specialize(PlayerSpecialization &specialization);

	friend istream &operator>>(istream &inputStream, Player &player);
	void readInventoryFromStream(istream &inputStream, MiscConfig &config, ItemFactory &itemFactory);
};

class FarmerSpecialization : public PlayerSpecialization {
private:
	Storage<FarmItem> farm;

public:
	FarmerSpecialization();
	virtual FarmerSpecialization *clone() const;
	virtual ~FarmerSpecialization();

	Storage<FarmItem> &getFarm();
	virtual void readSpecializationFromStream(istream &inputStream, GameContext &context);
};

class BreederSpecialization : public PlayerSpecialization {
private:
	Storage<BarnItem> barn;

public:
	BreederSpecialization();
	virtual BreederSpecialization *clone() const;
	virtual ~BreederSpecialization();

	Storage<BarnItem> &getBarn();
	virtual void readSpecializationFromStream(istream &inputStream, GameContext &context);
};

class MayorSpecialization : public PlayerSpecialization {
private:
public:
	MayorSpecialization();
	virtual MayorSpecialization *clone() const;
	virtual ~MayorSpecialization();

	virtual void readSpecializationFromStream(istream &inputStream, GameContext &context);
};

#endif
