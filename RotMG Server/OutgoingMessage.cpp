#include "OutgoingMessage.h"
#include "MessageDataWriter.h"

void FailureMessage::writeToOutput(MessageDataWriter* wtr) {
	wtr->writeInt32(errorId);
	wtr->writeUTF(errorMessage);
}

void MapInfoMessage::writeToOutput(MessageDataWriter* wtr) {
	wtr->writeInt32(width);
	wtr->writeInt32(height);
	wtr->writeUTF(name);
	wtr->writeUTF(displayName);
	wtr->writeUInt32(fp);
	wtr->writeInt32(background);
	wtr->writeInt32(difficulty);
	wtr->writeBoolean(allowPlayerTeleport);
	wtr->writeBoolean(showDisplays);

	wtr->writeInt16(clientXML.size());
	for each (std::string xml in clientXML) {
		wtr->writeUTF32(xml.c_str());
	}

	wtr->writeInt16(extraXML.size());
	for each (std::string xml in extraXML) {
		wtr->writeUTF32(xml.c_str());
	}
}
