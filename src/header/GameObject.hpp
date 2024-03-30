#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

class GameContext;

class GameObject {
private:
	GameContext *context;

public:
	GameContext &getContext();
	virtual void setContext(GameContext &context);
};

#endif
