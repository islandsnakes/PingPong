#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include "Config.hpp"

enum class Goal { Left, Right, None };

class Ball : public sf::Drawable {
private:
    sf::VertexArray m_va;
    sf::Vector2f m_speed;
    sf::Vector2f m_windowSize;
    sf::Vector2f m_position;

    void updateVertices()
    {
        m_va[0].position = m_position;
        m_va[0].color = sf::Color::White;

        const int pointsCount = 30;
        const float pi = 3.14159265f;
        const float angleStep = (2.f * pi) / pointsCount;

        for (int i = 0; i <= pointsCount; ++i)
        {
            float angle = i * angleStep;

            float x = m_position.x + BALL_R * std::cos(angle);
            float y = m_position.y + BALL_R * std::sin(angle);

            m_va[i + 1].position = { x, y };
            m_va[i + 1].color = sf::Color::White;
        }
    }

public:
    Ball(sf::Vector2u window_size)
        : m_va(sf::PrimitiveType::TriangleFan, 32),
        m_windowSize(static_cast<float>(window_size.x), static_cast<float>(window_size.y))
    {
        m_position = { m_windowSize.x / 2.f, m_windowSize.y / 2.f };
        updateVertices();
    }

    void move(sf::Vector2f offset)
    {
        m_position.x = std::clamp(m_position.x + offset.x, BALL_R, m_windowSize.x - BALL_R);
        m_position.y = std::clamp(m_position.y + offset.y, BALL_R, m_windowSize.y - BALL_R);

        updateVertices();
    }

    sf::Vector2f getPosition() const { return m_position; }
    void setPosition(sf::Vector2f position)
    {
        m_position = position;
        updateVertices();
    }

    Goal update(float dt, float py1, float py2)
    {
        float newX = m_position.x + dt * m_speed.x;
        float newY = m_position.y + dt * m_speed.y;

        if (newX <= BALL_R) return Goal::Left;
        else if (newX >= m_windowSize.x - BALL_R) return Goal::Right;

        if (newY <= BALL_R || newY >= m_windowSize.y - BALL_R)
        {
            m_speed.y = -m_speed.y;
            newY = std::clamp(newY, BALL_R, m_windowSize.y - BALL_R);
        }

        m_position.y = newY;
        m_position.x = newX;

        float p1_left = 0.f;
        float p1_right = p1_left + PLAYER_WIDTH;

        float p2_right = m_windowSize.x;
        float p2_left = p2_right - PLAYER_WIDTH;

        if (m_speed.x < 0.f)
        {
            if (m_position.x - BALL_R <= p1_right && m_position.x + BALL_R >= p1_left)
            {
                if (m_position.y >= py1 && m_position.y <= py1 + PLAYER_HEIGHT)
                {
                    m_speed.x = -m_speed.x;
                    m_speed.x *= 1.05f;
                    m_position.x = p1_right + BALL_R;
                }
            }
        }
        else if (m_speed.x > 0.f)
        {
            if (m_position.x + BALL_R >= p2_left && m_position.x - BALL_R <= p2_right)
            {
                if (m_position.y >= py2 && m_position.y <= py2 + PLAYER_HEIGHT)
                {
                    m_speed.x = -m_speed.x;
                    m_speed.x *= 1.05f;
                    m_position.x = p2_left - BALL_R;
                }
            }
        }

        updateVertices();
        return Goal::None;
    }

    void resetBall(Goal lastGoal)
    {
        m_position = { m_windowSize.x / 2.f, m_windowSize.y / 2.f };

        float tX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float tY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        m_speed.x = (22.4f + tX * (40.0f - 22.4f)) * 10.f;
        m_speed.y = (0.0f + tY * 22.4f) * 10.f;

        if (lastGoal == Goal::Left) m_speed.x = std::abs(m_speed.x);
        else if (lastGoal == Goal::Right) m_speed.x = -std::abs(m_speed.x);
        else if (rand() % 2 == 0) m_speed.x = -m_speed.x;

        if (rand() % 2 == 0) m_speed.y = -m_speed.y;

        updateVertices();
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(m_va, states); }
};