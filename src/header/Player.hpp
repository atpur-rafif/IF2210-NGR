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

	PlayerType getType();
	string getUsername();
	int getWeight();
	int getMoney();
};

class PlayerFarmer : public Player {
private:
	Storage<FarmItem> farm;

public:
	PlayerFarmer(string username, int weight, int money);
	PlayerFarmer *clone() const override;
	virtual ~PlayerFarmer();

	void harvest();
};

class PlayerBreeder : public Player {
private:
	Storage<BarnItem> barn;

public:
	PlayerBreeder(string username, int weight, int money);
	PlayerBreeder *clone() const override;
	virtual ~PlayerBreeder();

	void harvest();
	void feed();
};

class PlayerMayor : public Player {
private:
public:
	PlayerMayor(string username, int weight, int money);
	PlayerMayor *clone() const override;
	virtual ~PlayerMayor();

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
