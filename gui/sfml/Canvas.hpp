#pragma once

#include "Sprite.hpp"

#include "spec.hpp"

#include <memory>

class SFMLCanvas: public gui::Canvas {

public:
                        SFMLCanvas(unsigned width, unsigned height);

    virtual void        draw(const gui::GameState & info);
    virtual gui::Inputs getInputs(void);

private:
    struct GraphicSnake { Sprite head, body; };
    using GraphicSnakes = std::vector<std::unique_ptr<GraphicSnake>>;

    sf::RenderWindow    window_;

    float               boxWidth_, boxHeight_;
    GraphicSnakes       snakes_;
    Sprite              food_, obstacle_;
    sf::Font            font_;

    void                drawSnake(const gui::GameState::Snake & snake);
    void                drawSpriteAt(const Position & pos, sf::Sprite & sprite);
};
