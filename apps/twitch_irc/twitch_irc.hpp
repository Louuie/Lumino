#pragma once
#include <string>
#include <cstdlib>
#include <boost/asio.hpp>
#include "lumino_logger/lumino_logger.h"

using boost::asio::ip::tcp;

extern boost::asio::io_context _io_context;
extern tcp::resolver _resolver;
extern tcp::socket _socket;

extern const std::string TWITCH_SERVER;
extern const std::string TWITCH_PORT;
extern const std::string TWITCH_NICK;
extern const std::string TWITCH_OAUTH;
extern const std::string TWITCH_CHANNEL;

void irc_handler();