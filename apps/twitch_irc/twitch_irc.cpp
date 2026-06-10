#include "twitch_irc/twitch_irc.hpp"

void send_message(tcp::socket& socket, const std::string& msg) {
	std::string formatted_msg = msg + "\r\n";
	boost::asio::write(socket, boost::asio::buffer(formatted_msg));
}
void messageHandler(boost::asio::streambuf& buffer) {
	while (true) {
		// We are going to read until the IRC newline delimiter (\r\n)
		boost::asio::read_until(_socket, buffer, "\r\n");

		std::istream stream(&buffer);
		std::string line;
		std::getline(stream, line);

		// Twitch ping/pong to keep the connection alive
		if (line.rfind("PING: ", 0) == 0) {
			send_message(_socket, "PONG :tmi.twitch.tv");
		}
	}
}

void irc_handler() {
	try {
		_logger->log("Connecting to " + TWITCH_SERVER, Lumino::LogLevel::DEBUG);
		boost::asio::connect(_socket, _resolver.resolve(TWITCH_SERVER, TWITCH_PORT));
		_logger->log("Successfully connected!", Lumino::LogLevel::DEBUG);

		// Authenticate 
		send_message(_socket, "PASS " + TWITCH_OAUTH);
		send_message(_socket, "NICK " + TWITCH_NICK);
		send_message(_socket, "JOIN " + TWITCH_CHANNEL); // eventually this is going to be dynamic

		_logger->log("Successfully authenticated to twitch irc servers as " + TWITCH_NICK, Lumino::LogLevel::DEBUG);
		boost::asio::streambuf buffer;
		messageHandler(buffer);
	}
	catch (boost::system::system_error& e) {
		_logger->log("Error connecting to irc server:" + std::string(e.what()), Lumino::LogLevel::CRITICAL);
	}
}