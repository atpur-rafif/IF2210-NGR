#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Item.hpp"
#include "Storage.hpp"

enum PlayerType {
	Farmer,
	Breeder,
	Mayor
};

class Player {
	friend class PlayerController;

private:
	string username;
	PlayerType type;
	int weight;
	int money;
	Storage<InventoryItem> inventory;

public:
	Player(string username, PlayerType type, int weight, int money);
	virtual ~Player();
	// virtual int calculateTax() = 0;
	// virtual void eat() = 0;
	// virtual void turn() = 0;
	PlayerType getType();
	string getUsername();
	int getWeight();
	int getMoney();
	void readInventoryFromStream(istream &inputStream, ItemFactory<InventoryItem> inventoryFactory);
};

class PlayerFarmer : public Player {
	friend class Player;

private:
	Storage<FarmItem> farm;

public:
	PlayerFarmer(string username, int weight, int money);
	virtual ~PlayerFarmer();
	// virtual int calculateTax();
	// virtual void eat();
	// virtual void turn();

	void harvest();
	void readFarmFromStream(istream &inputStream, ItemFactory<FarmItem> farmFactory);
};

class PlayerBreeder : public Player {
	friend class Player;

private:
	Storage<BarnItem> barn;

public:
	PlayerBreeder(string username, int weight, int money);
	virtual ~PlayerBreeder();
	// virtual int calculateTax();
	// virtual void eat();
	// virtual void turn();

	void harvest();
	void readBarnFromStream(istream &inputStream, ItemFactory<BarnItem> barnFactory);
	void feed();
};

class PlayerMayor : public Player {
	friend class Player;

private:
public:
	PlayerMayor(string username, int weight, int money);
	virtual ~PlayerMayor();
	// virtual int calculateTax();
	// virtual void eat();
	// virtual void turn();

	void build();
};

class PlayerController {
private:
	vector<Player *> players;
	vector<PlayerFarmer> farmer;
	vector<PlayerBreeder> breeder;
	vector<PlayerMayor> mayor;
	void rearrangePosition();

public:
	void addFarmer(PlayerFarmer farmer);
	void addBreeder(PlayerBreeder breeder);
	void addMayor(PlayerMayor mayor);
	vector<Player *> *getPlayers();
};

#endif
