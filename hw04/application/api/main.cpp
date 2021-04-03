//
// Created by Andrey Kuzmickiy group BS20-03.
//

#include "gateways/MainHandler.cpp"

using namespace std;

int main() {
    Address addr(Ipv4::any(), Port(9080));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<MainHandler>());

    cout << "Server connected to " << addr.host() << ":" << addr.port() << endl;
    server.serve();
}