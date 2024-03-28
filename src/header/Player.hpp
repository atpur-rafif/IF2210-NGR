#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Heapify.hpp"
#include "Item.hpp"
#include "Storage.hpp"

enum PlayerType {
	Farmer,
	Breeder,
	Mayor
};

class Player {
	friend class PlayerController;

protected:
	string username;
	PlayerType type;
	int weight;
	int money;
	Storage<ProductItem> inventory;

public:
	Player(string username, PlayerType type, int weight, int money);
	virtual Player *clone() const = 0;
	virtual ~Player();
	// virtual int calculateTax() = 0;
	// virtual void eat() = 0;
	// virtual void turn() = 0;
	PlayerType getType();
	string getUsername();
	int getWeight();
	int getMoney();
	void readProductFromStream(istream &inputStream, ItemFactory<ProductItem> productFactory);
};

class PlayerFarmer : public Player {
private:
	Storage<FarmItem> farm;

public:
	PlayerFarmer(string username, int weight, int money);
	PlayerFarmer *clone() const override;
	virtual ~PlayerFarmer();
	// virtual int calculateTax();
	// virtual void eat();
	// virtual void turn();

	void harvest();
	void readFarmFromStream(istream &inputStream, ItemFactory<FarmItem> farmFactory);
};

class PlayerBreeder : public Player {
private:
	Storage<BarnItem> barn;

public:
	PlayerBreeder(string username, int weight, int money);
	PlayerBreeder *clone() const override;
	virtual ~PlayerBreeder();
	// virtual int calculateTax();
	// virtual void eat();
	// virtual void turn();

	void harvest();
	void readBarnFromStream(istream &inputStream, ItemFactory<BarnItem> barnFactory);
	void feed();
};

class PlayerMayor : public Player {
private:
public:
	PlayerMayor(string username, int weight, int money);
	PlayerMayor *clone() const override;
	virtual ~PlayerMayor();
	// virtual int calculateTax();
	// virtual void eat();
	// virtual void turn();

	void build();
};

class PlayerController {
private:
	vector<Heapify<Player>> players;
	void rearrangePosition();

public:
	void addPlayer(Heapify<Player> player);
	vector<Heapify<Player>> *getPlayers();
};

#endif
