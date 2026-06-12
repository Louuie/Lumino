#include "twitch_irc/twitch_irc.hpp"

std::unique_ptr<Lumino::Logger> _logger = std::make_unique<Lumino::Logger>();

boost::asio::io_context _io_context;
tcp::resolver _resolver(_io_context);
tcp::socket _socket(_io_context);
    
const std::string TWITCH_SERVER = "irc.chat.twitch.tv";
const std::string TWITCH_PORT = "6667";
const std::string TWITCH_NICK = "fincchbot";
const std::string TWITCH_OAUTH = "oauth:r7oehydtgfrwx56mcb6r82pzfxh0uw";
const std::string TWITCH_CHANNEL = "stableronaldo";

void send_message(tcp::socket& socket, const std::string& msg)
{
    std::string formatted_msg = msg + "\r\n";
    boost::asio::write(socket, boost::asio::buffer(formatted_msg));
}
//void messageHandler(boost::asio::streambuf& buffer)
//{
//    while (true)
//    {
//        // 1. Block and wait for network traffic to hit the socket
//        boost::asio::read_until(_socket, buffer, "\r\n");
//
//        std::istream stream(&buffer);
//        std::string line;
//
//        // 2. DRAIN THE ENTIRE BUFFER completely before calling read_until again
//        while (std::getline(stream, line))
//        {
//            // Clean up trailing carriage returns (\r)
//            if (!line.empty() && line.back() == '\r') {
//                line.pop_back();
//            }
//
//            // If the line is empty, skip it safely
//            if (line.empty()) continue;
//
//            // CRITICAL VERIFICATION: This will now catch 100% of live traffic
//            _logger->log("RAW SYSTEM: " + line, Lumino::LogLevel::DEBUG);
//
//            if (line.rfind("PING :", 0) == 0)
//            {
//                send_message(_socket, "PONG :tmi.twitch.tv");
//                continue;
//            }
//
//            // 3. Process the IRC command strings safely
//            size_t exclPosition = line.find("!");
//            size_t atPosition = line.find("@");
//            std::string targetCommand = "PRIVMSG #" + TWITCH_CHANNEL + " :";
//            size_t msgPosition = line.find(targetCommand);
//
//            if (exclPosition != std::string::npos &&
//                atPosition != std::string::npos &&
//                msgPosition != std::string::npos)
//            {
//                size_t nameStart = (line == ':') ? 1 : 0;
//                std::string twitchUser = line.substr(nameStart, exclPosition - nameStart);
//                std::string twitchUserMsg = line.substr(msgPosition + targetCommand.length());
//
//                _logger->log("[CHAT] " + twitchUser + ": " + twitchUserMsg, Lumino::LogLevel::DEBUG);
//            }
//        }
//    }
//}
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
        std::string rawIrcMessage = line.substr(line.rfind("!") + 1);
        size_t userNamePosition = rawIrcMessage.find("@");
        size_t userMsgPosition = rawIrcMessage.find(" PRIVMSG #" + TWITCH_CHANNEL + " :");
        if (userNamePosition != std::string::npos && userMsgPosition != std::string::npos) {
            std::string twitchUser = rawIrcMessage.substr(0, userNamePosition);
            std::string targetCommand = " PRIVMSG #" + TWITCH_CHANNEL + " :";

            std::string twitchUserMsg = rawIrcMessage.substr(userMsgPosition + targetCommand.length());
            _logger->log(twitchUser + ": " + twitchUserMsg, Lumino::LogLevel::DEBUG);
        }
       /* _logger->log(line, Lumino::LogLevel::DEBUG);*/
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
        send_message(_socket, "JOIN #" + TWITCH_CHANNEL);

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