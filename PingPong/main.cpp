#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Ball.hpp"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Ping Pong", sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);

	sf::RectangleShape line({ 15.f, 600.f });
	line.setFillColor({ 255,255,255,127 });
	line.setPosition({ (800.f - 15.f) / 2.f, 0.f });

	Player p1(0.f, 600.f, sf::Keyboard::Scancode::W, sf::Keyboard::Scancode::S);
	Player p2(800.f - PLAYER_WIDTH, 600.f, sf::Keyboard::Scancode::Up, sf::Keyboard::Scancode::Down);

	Ball ball(window.getSize());
	ball.resetBall(Goal::None);

	sf::Clock clock;
	unsigned int counter[2] = { 0,0 };

	sf::Font font;
	if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf")) return -1;

	sf::Text text(font);
	text.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		while (const std::optional<sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) window.close();
		}

		p1.update(dt);
		p2.update(dt);

		Goal goal = ball.update(dt, p1.getY(), p2.getY());

		if (goal == Goal::Left)
		{
			++counter[0];
			ball.resetBall(goal);
		}
		else if (goal == Goal::Right)
		{
			++counter[1];
			ball.resetBall(goal);
		}

		window.clear();

		text.setString(std::to_string(counter[0]));
		text.setPosition({ 800.f / 2.f - 100.f - text.getGlobalBounds().size.x, 100.f });
		window.draw(text);

		text.setString(std::to_string(counter[1]));
		text.setPosition({ 800.f / 2.f + 100.f, 100.f });
		window.draw(text);

		window.draw(line);
		window.draw(p1);
		window.draw(p2);
		window.draw(ball);
		window.display();
	}
}
