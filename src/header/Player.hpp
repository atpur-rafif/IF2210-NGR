#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Storage.hpp"
class Player {
private:
	static int count;
	Storage storage;

public:
	virtual int calculateTax() = 0;
	virtual void eat();
	virtual void buy();
	virtual void sell();
	virtual void turn();
};

class Farmer : public Player {
private:
	static int count;
	Storage farm;

public:
	void harvest();
};

class Breeder : public Player {
private:
	static int count;
	Storage barn;

public:
	void harvest();
	void feed();
};

class Mayor : public Player {
private:
	static int count;

public:
	void build();
};

#endif
