#include <Hadouken/Http/DefaultRequestHandlerFactory.hpp>

#include <Hadouken/Http/JsonRpcRequestHandler.hpp>
#include <Hadouken/Http/WebSocketRequestHandler.hpp>

#include <Hadouken/Http/JsonRpc/SessionAddTorrentFileMethod.hpp>
#include <Hadouken/Http/JsonRpc/SessionGetTorrentsMethod.hpp>
#include <Hadouken/Http/JsonRpc/TorrentPauseMethod.hpp>
#include <Hadouken/Http/JsonRpc/TorrentResumeMethod.hpp>

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>

using namespace Hadouken::Http;
using namespace Hadouken::Http::JsonRpc;
using namespace Poco::Net;

DefaultRequestHandlerFactory::DefaultRequestHandlerFactory()
{
    methods_.insert(std::make_pair("session.addTorrentFile", new SessionAddTorrentFileMethod()));
    methods_.insert(std::make_pair("session.getTorrents", new SessionGetTorrentsMethod()));
    methods_.insert(std::make_pair("torrent.pause", new TorrentPauseMethod()));
    methods_.insert(std::make_pair("torrent.resume", new TorrentResumeMethod()));
}

DefaultRequestHandlerFactory::~DefaultRequestHandlerFactory()
{
    // Delete all registered RPC methods. 
    for (auto item : methods_)
    {
        delete item.second;
    }
}

HTTPRequestHandler* DefaultRequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    if (request.getURI() == "/api"
        && request.getMethod() == "POST")
    {
        return new JsonRpcRequestHandler(methods_);
    }

    if (request.getURI() == "/events"
        && request.find("Upgrade") != request.end()
        && Poco::icompare(request["Upgrade"], "websocket") == 0)
    {
        return new WebSocketRequestHandler();
    }

    return 0;
}
