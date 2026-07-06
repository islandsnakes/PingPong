#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include "Config.hpp"

class Player : public sf::Drawable {
private:
    sf::VertexArray m_va;
    sf::Keyboard::Scancode m_keyUp;
    sf::Keyboard::Scancode m_keyDown;

    void setY(float y)
    {
        m_va[0].position.y = { y };
        m_va[1].position.y = { y };
        m_va[2].position.y = { y + PLAYER_HEIGHT };
        m_va[3].position.y = { y + PLAYER_HEIGHT };
    }

public:
    Player(float x, float window_height, sf::Keyboard::Scancode keyUp, sf::Keyboard::Scancode keyDown)
        : m_va(sf::PrimitiveType::TriangleStrip, 4), m_keyUp(keyUp), m_keyDown(keyDown)
    {
        float y = (window_height - PLAYER_HEIGHT) / 2.f;
        m_va[0].position = { x, y };
        m_va[1].position = { x + PLAYER_WIDTH, y };
        m_va[2].position = { x, y + PLAYER_HEIGHT };
        m_va[3].position = { x + PLAYER_WIDTH, y + PLAYER_HEIGHT };

        for (int i = 0; i < 4; ++i) m_va[i].color = sf::Color::White;
    }

    void update(float dt)
    {
        float currentY = m_va[0].position.y;
        float direction = 0.f;

        if (sf::Keyboard::isKeyPressed(m_keyUp)) direction -= 1.f;
        if (sf::Keyboard::isKeyPressed(m_keyDown)) direction += 1.f;

        if (direction != 0.f)
        {
            float newY = currentY + direction * PLAYER_SPEED * dt;
            newY = std::clamp(newY, 0.f, 600.f - PLAYER_HEIGHT);
            setY(newY);
        }
    }

    float getY() const { return m_va[0].position.y; }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    { target.draw(m_va, states); }
};