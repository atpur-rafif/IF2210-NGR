#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Storage.hpp"

enum PlayerType {
	Farmer,
	Breeder,
	Mayor
};

class PlayerSpecialization {};

class Player {
private:
	static int count;

	string username;
	PlayerType type;
	int weight;
	int money;

	PlayerSpecialization *specialization;

public:
	Player();
	~Player();
	virtual int calculateTax() = 0;
	virtual void eat() = 0;
	virtual void buy() = 0;
	virtual void sell() = 0;
	virtual void turn() = 0;
	PlayerType getType();
	friend istream &operator>>(istream &inputStream, Player &player);
};

class PlayerFarmer : public PlayerSpecialization {
private:
public:
	void harvest();
};

class PlayerBreeder : public PlayerSpecialization {
private:
public:
	void harvest();
	void feed();
};

class PlayerMayor : public PlayerSpecialization {
private:
public:
	void build();
};

#endif
