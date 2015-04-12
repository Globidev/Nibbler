#include "Canvas.hpp"

#include <unordered_map>
#include <iterator>

SFMLCanvas::SFMLCanvas(unsigned width, unsigned height):
    window_ {
        sf::VideoMode {
            gui::WINDOW_WIDTH,
            gui::WINDOW_HEIGHT
        },
        gui::WINDOW_TITLE_PREFIX + "SFML",
        sf::Style::Titlebar | sf::Style::Close
    },
    boxWidth_ { (float)gui::WINDOW_WIDTH / width },
    boxHeight_ { (float)gui::WINDOW_HEIGHT / height } {

    headImg_.create(1, 1, sf::Color { 32, 128, 32 });
    bodyImg_.create(1, 1, sf::Color::Green);
    foodImg_.create(1, 1, sf::Color::Yellow);

    headTx_.loadFromImage(headImg_);
    bodyTx_.loadFromImage(bodyImg_);
    foodTx_.loadFromImage(foodImg_);

    headSp_.setTexture(headTx_);
    bodySp_.setTexture(bodyTx_);
    foodSp_.setTexture(foodTx_);

    headSp_.scale(boxWidth_, boxHeight_);
    bodySp_.scale(boxWidth_, boxHeight_);
    foodSp_.scale(boxWidth_, boxHeight_);
}

void SFMLCanvas::draw(const gui::GameInfo & info) {
    window_.clear();

    drawSpriteAt(info.food, foodSp_);
    for (const auto & snake: info.snakes) {
        drawSpriteAt(snake.front(), headSp_);
        for (auto it = std::next(snake.begin()); it != snake.end(); ++it)
            drawSpriteAt(*it, bodySp_);
    }

    window_.display();
}

void SFMLCanvas::drawSpriteAt(const Position & pos, sf::Sprite & sprite) {
    sprite.setPosition(
        pos.x * boxWidth_,
        pos.y * boxHeight_
    );
    window_.draw(sprite);
}

using KeyMap = std::unordered_map<sf::Keyboard::Key, gui::Input>;
static const KeyMap KEY_MAP = {
    { sf::Keyboard::Up,     gui::Input::Up    },
    { sf::Keyboard::Down,   gui::Input::Down  },
    { sf::Keyboard::Left,   gui::Input::Left  },
    { sf::Keyboard::Right,  gui::Input::Right },
    { sf::Keyboard::W,      gui::Input::W     },
    { sf::Keyboard::S,      gui::Input::S     },
    { sf::Keyboard::A,      gui::Input::A     },
    { sf::Keyboard::D,      gui::Input::D     },
    { sf::Keyboard::Escape, gui::Input::Exit  },
    { sf::Keyboard::Num1,   gui::Input::Key1  },
    { sf::Keyboard::Num2,   gui::Input::Key2  },
    { sf::Keyboard::Num3,   gui::Input::Key3  },
};

gui::Inputs SFMLCanvas::getInputs(void) {
    gui::Inputs inputs;
    sf::Event event;
    KeyMap::const_iterator inputIt;

    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                inputs.push_back(gui::Input::Exit);
                break ;
            case sf::Event::KeyPressed:
                inputIt = KEY_MAP.find(event.key.code);
                if (inputIt != KEY_MAP.end())
                    inputs.push_back(inputIt->second);
                break ;
            default:
                break ;
        }
    }
    return inputs;
}
