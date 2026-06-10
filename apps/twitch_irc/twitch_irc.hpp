#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "lumino_logger/lumino_logger.h"

std::unique_ptr<Lumino::Logger> _logger = std::make_unique<Lumino::Logger>();
using boost::asio::ip::tcp;
boost::asio::io_context _io_context;
tcp::resolver _resolver(_io_context);
tcp::socket _socket(_io_context);

const std::string TWITCH_SERVER = "irc.chat.twitch.tv";
const std::string TWITCH_PORT = "6667"; // 6667 for non-SSL / 6697 for SSL
const std::string TWITCH_NICK = "";
const std::string TWITCH_OAUTH = ""; // figure out a way to put this into an environment variable
const std::string TWITCH_CHANNEL = "";
