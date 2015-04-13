#pragma once

#include <SFML/network.hpp>

#include "spec.hpp"

class SFMLClient: public network::Client {

public:
                                SFMLClient(void);
    virtual                     ~SFMLClient(void);

    // 42 norme
                                SFMLClient(const SFMLClient &)  = delete;
    SFMLClient &                operator=(const SFMLClient &)   = delete;
    //

    virtual bool                connect(const std::string & host, network::Port port);
    virtual network::GameState  getGameState(void);
    virtual void                sendDirection(Direction direction);
    virtual bool                isConnected(void);

private:
    sf::TcpSocket               socket_;
    bool                        connected_;
};