#pragma once

#include "Sprite.hpp"

#include "spec.hpp"

#include <memory>

class SDLCanvas: public gui::Canvas {

public:
                        SDLCanvas(unsigned width, unsigned height);
    virtual             ~SDLCanvas(void);

    virtual void        draw(const gui::GameState & info);
    virtual gui::Inputs getInputs(void);

private:
    struct GraphicSnake { Sprite head, body; };
    using GraphicSnakes = std::vector<std::unique_ptr<GraphicSnake>>;
    using SpritePtr     = std::unique_ptr<Sprite>;

    void                drawSprite(const Position &, const Sprite & sprite);
    void                drawBackground(void);

    float               boxWidth_, boxHeight_;

    SDL_Window          *window_;
    SDL_Renderer        *renderer_;
    SpritePtr           food_, obstacle_, background_;
    GraphicSnakes       snakes_;
};
