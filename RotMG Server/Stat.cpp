#include "Stat.h"
#include "MessageDataWriter.h"

bool Stat::isStringStat() {
	switch (statType) {
	case NAME_STAT:
	case GUILD_NAME_STAT:
		return true;
	}
	return false;
}

void Stat::writeToOutput(MessageDataWriter* wtr) {
	wtr->writeInt8(statType);
	if (isStringStat()) {
		wtr->writeUTF(stringValue.c_str());
	}
	else {
		wtr->writeInt32(intValue);
	}
}
