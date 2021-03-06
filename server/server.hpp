#pragma once
#include <iostream>
#include <future>
#include <string>
#include <unordered_map>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

#include "../libs/simple-web-sockets/server_ws.hpp"
#include "../libs/simple-web-sockets/client_ws.hpp"
#include "../libs/json/single_include/nlohmann/json.hpp"

using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;
using WsClient = SimpleWeb::SocketClient<SimpleWeb::WS>;
using WsEndpoint = SimpleWeb::SocketServerBase<SimpleWeb::WS>::Endpoint;
using json = nlohmann::json;

namespace WsChess
{
class Server
{

public:
  void Start();

private:
  void Configure();
  void Listen();
  WsEndpoint &AddGenericEndpoint(const std::string endpoint);
  WsEndpoint &AddGameEndpoint();
  void LogPlayers();
  void NotifyPlayersOfChanges();

private:
  WsServer mWsServer;
};

std::string GetConnectionId(const WsServer::Connection &conn);
void HandleError(const SimpleWeb::error_code &ec);

} // namespace WsChess