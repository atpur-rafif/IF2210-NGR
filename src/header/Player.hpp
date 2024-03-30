#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Game.hpp"
#include "Heapify.hpp"
#include "Item.hpp"
#include "ItemFactory.hpp"
#include "Storage.hpp"

class PlayerSpecialization {
private:
public:
	PlayerSpecialization();
	virtual PlayerSpecialization *clone() const = 0;
	virtual ~PlayerSpecialization();

	virtual void readSpecializationFromStream(istream &inputStream, MiscConfig &miscConfig, ItemFactory &itemFactory) = 0;
};

enum SpecializationType {
	Farmer,
	Breeder,
	Mayor
};

class Player {
protected:
	string username;
	SpecializationType type;
	int weight;
	int money;
	Storage<Heapify<Item>> inventory;

	Heapify<PlayerSpecialization> specialization;

public:
	Player();

	SpecializationType getType();
	int getWeight();
	int getMoney();
	string getUsername();
	Storage<Heapify<Item>> &getInventory();

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

	virtual void readSpecializationFromStream(istream &inputStream, MiscConfig &miscConfig, ItemFactory &itemFactory);
};

class BreederSpecialization : public PlayerSpecialization {
private:
	Storage<BarnItem> barn;

public:
	BreederSpecialization();
	virtual BreederSpecialization *clone() const;
	virtual ~BreederSpecialization();

	virtual void readSpecializationFromStream(istream &inputStream, MiscConfig &miscConfig, ItemFactory &itemFactory);
};

class MayorSpecialization : public PlayerSpecialization {
private:
public:
	MayorSpecialization();
	virtual MayorSpecialization *clone() const;
	virtual ~MayorSpecialization();

	virtual void readSpecializationFromStream(istream &inputStream, MiscConfig &miscConfig, ItemFactory &itemFactory);
};

#endif
