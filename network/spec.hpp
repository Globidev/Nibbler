#pragma once

#include <vector>
#include <boost/variant/variant.hpp>

#include "../gui/spec.hpp"
#include "../audio/spec.hpp"
#include "../tools/Direction.hpp"

namespace network {

    using Port = unsigned short;

    struct ChangeDirection {
        size_t id;
        Direction direction;
    };

    struct Left {
        size_t id;
    };

    using ClientMessage = boost::variant<
        ChangeDirection,
        Left
    >;

    using ClientMessages = std::vector<ClientMessage>;

    using ServerMessage = boost::variant<
        audio::Sound,
        gui::GameState
    >;
    using ServerMessages = std::vector<ServerMessage>;

    struct Server {

        struct SharedObjectInfo {
            using Getter = Server * (*)(unsigned, unsigned);
            static constexpr const char * getterName = "getServer";
        };

        virtual bool            listen(Port port)                           = 0;
        virtual void            waitFor(unsigned players)                   = 0;
        virtual void            sendMessage(const ServerMessage & message)  = 0;
        virtual ClientMessages  getMessages(void)                           = 0;

    };

    struct Client {

        using Dimensions = std::pair<unsigned, unsigned>;

        struct SharedObjectInfo {
            using Getter = Client * (*)(void);
            static constexpr const char * getterName = "getClient";
        };

        virtual bool            connect(const std::string & host, Port port)    = 0;
        virtual Dimensions      getDimensions(void)                             = 0;
        virtual ServerMessages  getMessages(void)                               = 0;
        virtual void            sendDirection(Direction direction)              = 0;
        virtual bool            isConnected(void)                               = 0;

    };

}
