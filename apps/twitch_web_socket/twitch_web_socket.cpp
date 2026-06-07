#include <ixwebsocket/IXWebSocket.h>
#include "lumino_logger.h"
#include <iostream>

std::unique_ptr<ix::WebSocket> webSocketPtr;
std::unique_ptr<Lumino::Logger> logger;

void connectToTwitch() {
	std::string url("wss://eventsub.wss.twitch.tv/ws");
	webSocketPtr = std::make_unique<ix::WebSocket>();
	logger = std::make_unique<Lumino::Logger>();
	webSocketPtr->setUrl(url);

	webSocketPtr->setOnMessageCallback([](const ix::WebSocketMessagePtr& msg) {
		switch (msg->type) {
		case ix::WebSocketMessageType::Message :
			logger->log("Message Reccieved!", Lumino::LogLevel::DEBUG);
		case ix::WebSocketMessageType::Open :
			logger->log("Connection opened!", Lumino::LogLevel::DEBUG);
		case ix::WebSocketMessageType::Close :
			logger->log("Connection closed!", Lumino::LogLevel::DEBUG);
		case ix::WebSocketMessageType::Error :
			logger->log("Error connection to ws server", Lumino::LogLevel::ERROR);
		}
	});
	webSocketPtr->start();
}