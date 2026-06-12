#include "twitch_irc/twitch_irc.hpp"

std::unique_ptr<Lumino::Logger> _logger = std::make_unique<Lumino::Logger>();

boost::asio::io_context _io_context;
tcp::resolver _resolver(_io_context);
tcp::socket _socket(_io_context);

const std::string TWITCH_SERVER = "irc.chat.twitch.tv";
const std::string TWITCH_PORT = "6667";
const std::string TWITCH_NICK = "";
const std::string TWITCH_OAUTH = "";
const std::string TWITCH_CHANNEL = "";

void send_message(tcp::socket& socket, const std::string& msg)
{
    std::string formatted_msg = msg + "\r\n";
    boost::asio::write(socket, boost::asio::buffer(formatted_msg));
}

void messageHandler(boost::asio::streambuf& buffer)
{
    while (true)
    {
        boost::asio::read_until(_socket, buffer, "\r\n");

        std::istream stream(&buffer);
        std::string line;
        std::getline(stream, line);

        if (line.rfind("PING :", 0) == 0)
        {
            send_message(_socket, "PONG :tmi.twitch.tv");
        }
    }
}

void irc_handler()
{
    try
    {
        _logger->log("Connecting to " + TWITCH_SERVER, Lumino::LogLevel::DEBUG);

        boost::asio::connect(
            _socket,
            _resolver.resolve(TWITCH_SERVER, TWITCH_PORT)
        );

        _logger->log("Successfully connected!", Lumino::LogLevel::DEBUG);

        send_message(_socket, "PASS " + TWITCH_OAUTH);
        send_message(_socket, "NICK " + TWITCH_NICK);
        send_message(_socket, "JOIN " + TWITCH_CHANNEL);

        _logger->log(
            "Successfully authenticated to twitch irc servers as " + TWITCH_NICK,
            Lumino::LogLevel::DEBUG
        );

        boost::asio::streambuf buffer;
        messageHandler(buffer);
    }
    catch (boost::system::system_error& e)
    {
        _logger->log(
            "Error connecting to irc server: " + std::string(e.what()),
            Lumino::LogLevel::CRITICAL
        );
    }
}