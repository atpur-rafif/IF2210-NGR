#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Heapify.hpp"
#include "Item.hpp"
#include "Storage.hpp"

class GameContext;

enum SpecializationType {
	Farmer,
	Breeder,
	Mayor
};

class PlayerSpecialization : public GameObject {
	friend class Player;

protected:
	PlayerSpecialization();

public:
	virtual PlayerSpecialization *clone() const = 0;
	virtual ~PlayerSpecialization();

	virtual void readSpecializationFromStream(istream &inputStream) = 0;
};

class Player : public GameObject {
	friend class PlayerController;

protected:
	Player();
	string username;
	SpecializationType specializationType;
	int weight;
	int money;
	HeapifyStorage<Item> inventory;

	Heapify<PlayerSpecialization> specialization;

public:
	virtual ~Player();

	SpecializationType getType();
	int getWeight();
	int getMoney();
	string getUsername();
	HeapifyStorage<Item> &getInventory();

	PlayerSpecialization &getSpecialization();
	void specialize(SpecializationType type);

	friend istream &operator>>(istream &inputStream, Player &player);
	void readInventoryFromStream(istream &inputStream);
};

class FarmerSpecialization : public PlayerSpecialization {
private:
	Storage<FarmItem> farm;

public:
	FarmerSpecialization();
	virtual FarmerSpecialization *clone() const;
	virtual ~FarmerSpecialization();

	Storage<FarmItem> &getFarm();
	virtual void readSpecializationFromStream(istream &inputStream);
};

class BreederSpecialization : public PlayerSpecialization {
private:
	Storage<BarnItem> barn;

public:
	BreederSpecialization();
	virtual BreederSpecialization *clone() const;
	virtual ~BreederSpecialization();

	Storage<BarnItem> &getBarn();
	virtual void readSpecializationFromStream(istream &inputStream);
};

class MayorSpecialization : public PlayerSpecialization {
private:
public:
	MayorSpecialization();
	virtual MayorSpecialization *clone() const;
	virtual ~MayorSpecialization();

	virtual void readSpecializationFromStream(istream &inputStream);
};

#endif
