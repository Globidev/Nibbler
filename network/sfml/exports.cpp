#include "spec.hpp"

#include "Server.hpp"
#include "Client.hpp"

extern "C" {

    network::Server * getServer(unsigned width, unsigned height) {
        return new SFMLServer { width, height };
    }

    network::Client * getClient(void) {
        return new SFMLClient;
    }

}

static_assert(
    std::is_same<
        decltype(&getServer),
        network::Server::SharedObjectInfo::Getter
    >::value &&
    std::is_same<
        decltype(&getClient),
        network::Client::SharedObjectInfo::Getter
    >::value,
    "Invalid exported function"
);
