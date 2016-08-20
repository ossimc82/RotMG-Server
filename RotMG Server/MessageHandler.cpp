#include "MessageHandler.h"
#include "GameClient.h"
#include "OutgoingMessage.h"
#include "IncomingMessage.h"
#include "Player.h"
#include "RealmManager.h"

void HelloMessageHandler::handleMessage(HelloMessage* message) {
	client->player = new Player(client);
	MapInfoMessage* mapInfo = RealmManager::RegisterPlayerInWorld(message->gameId, client->player);
	if (mapInfo == NULL) {
		FailureMessage* failure = new FailureMessage();
		failure->errorId = 0;
		failure->errorMessage = "Invalid World";
		client->sendMessage(failure);
		client->disconnect("Invalid gameId", false);
		return;
	}
	client->sendMessage(mapInfo);
}
