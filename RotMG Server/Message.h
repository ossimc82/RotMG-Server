#ifndef MESSAGE_H_
#define MESSAGE_H_

#define NULLTERMINATESTRING(input, fulllength) (input[fulllength-1] = '\0')

#define FAILURE 0
#define CREATE_SUCCESS 31
#define CREATE 36
#define PLAYERSHOOT 38
#define MOVE 7
#define PLAYERTEXT 69
#define TEXT 25
#define SERVERPLAYERSHOOT 13
#define DAMAGE 47
#define UPDATE 26
#define UPDATEACK 11
#define NOTIFICATION 63
#define NEWTICK 62
#define INVSWAP 65
#define USEITEM 30
#define SHOWEFFECT 56
#define HELLO 17
#define GOTO 52
#define INVDROP 35
#define INVRESULT 4
#define RECONNECT 39
#define PING 6
#define PONG 16
#define MAPINFO 60
#define LOAD 45
#define PIC 28
#define SETCONDITION 10
#define TELEPORT 49
#define USEPORTAL 3
#define DEATH 41
#define BUY 50
#define BUYRESULT 27
#define AOE 68
#define GROUNDDAMAGE 64
#define PLAYERHIT 24
#define ENEMYHIT 76
#define AOEACK 59
#define SHOOTACK 22
#define OTHERHIT 66
#define SQUAREHIT 51
#define GOTOACK 14
#define EDITACCOUNTLIST 53
#define ACCOUNTLIST 46
#define QUESTOBJID 34
#define CHOOSENAME 33
#define NAMERESULT 20
#define CREATEGUILD 15
#define GUILDRESULT 58
#define GUILDREMOVE 78
#define GUILDINVITE 8
#define ALLYSHOOT 74
#define ENEMYSHOOT 19
#define REQUESTTRADE 21
#define TRADEREQUESTED 61
#define TRADESTART 67
#define CHANGETRADE 37
#define TRADECHANGED 23
#define ACCEPTTRADE 57
#define CANCELTRADE 1
#define TRADEDONE 12
#define TRADEACCEPTED 18
#define CLIENTSTAT 75
#define CHECKCREDITS 48
#define ESCAPE 42
#define FILE 55
#define INVITEDTOGUILD 77
#define JOINGUILD 5
#define CHANGEGUILDRANK 40
#define PLAYSOUND 44
#define GLOBAL_NOTIFICATION 9
#define RESKIN 79
#define FAMEPRICEMULTIPLIER 80
#define PACKETLOSS 81
#define STATVALIDATION 82
#define CHANGESERVERSTAT 2
#define VAULTUPGRADEREQUEST 29

class GameClient;
class Message
{
public:
	Message(){}
	~Message(){}
	virtual unsigned char getMessageId() = 0;
private:

};
#endif // !MESSAGE_H_