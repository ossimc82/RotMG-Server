#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

class GameClient;

class Player : public GameObject {
public:
	Player(GameClient* client);
	~Player();

	GameClient* client;
private:

};

#endif // !PLAYER_H_
