enum ServerSignals
{
	OPERATION_SUCCESS,
	INVALID_USERNAME,
	SENDER_NOT_RECOGNIZED,
	SERVER_OVERFLOW,
	UNAVAILABLE,
	BANNED,
	NEW_CHANNEL,
	NO_CHANNEL
};

enum ClientSignals
{
	CONNECTION,
	LOGIN,
	LOGOUT,
	SUBSCRIBE,
	UNSUBSCRIBE,
	MESSAGE,
	MSGREG,
	BLOCK,
	UNBLOCK,
	USERS,
	SUBSLIST,
	CHANNELLIST,
	BANS,
	QUIT
};

struct Message
{
	long receiver;
	int sender;

	int type;

	char shortText[16];
	char longText[256];
};

struct Client
{
	int id;
	char name[16];
};

struct Subscription
{
	int id;
	int channel;
	int quantity;
};

struct Blockade
{
	int blocker;
	int blocked;
};