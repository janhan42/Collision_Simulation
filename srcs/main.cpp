/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:57:42 by janhan            #+#    #+#             */
/*   Updated: 2023/12/22 03:12:31 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Export.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include "Ball.hpp"
#include "Button.hpp"

int	main()
{
	// Window Setting
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "TEST");
	window.setFramerateLimit(60);

	// Object Setting
	std::vector<Ball> vecBall;
	Button button(sf::Vector2f(100,100), sf::Vector2f(50,50), "", sf::Color::Green);

	// flag Setting

	// Window open event
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) // 이벤트 감지
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Mouse Left Button Pressed Event
			{
				if (button.isMouseOver(window))
					vecBall.clear();
				else
					vecBall.push_back(Ball(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, -1, -1, sf::Color::White));
			}
			if (event.type == sf::Event::MouseButtonReleased == sf::Mouse::Left) // Mouse Left Released Event
			{

			}
		}
		window.clear(); // clear window
		button.draw(window);
	// update and draw all objects
		for (int i = 0; i < vecBall.size(); i++)
		{
			vecBall[i].updatePhysics(vecBall, window);
			vecBall[i].draw(window);
		}

		window.display(); // draw complete -> display
	}
	return 0;
}
