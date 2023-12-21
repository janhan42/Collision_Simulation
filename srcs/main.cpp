/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:57:42 by janhan            #+#    #+#             */
/*   Updated: 2023/12/22 04:45:26 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Export.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include <SFML/Graphics.hpp>
#include <regex>
#include <string>
#include <vector>
#include <thread>
#include <sstream>
#include <iostream>
#include "Ball.hpp"
#include "Button.hpp"

int	main()
{
	// Window Setting
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Collision");
	window.setFramerateLimit(60);

	// Object Setting
	std::vector<Ball> vecBall;
	const int maxBallCount = 600; // Max Ball Setting
	int	currentBallCount = 0;
	float buttonSizeRatio = 0.05; // 버튼 크기를 창의 5%로 설정
	float buttonPositionRatioX = 0.1; // 버튼 X 위치를 창의 10%로 설정
	float buttonPositionRatioY = 0.1; // 버튼 Y 위치를 창의 10%로 설정

	// 창 크기에 따라 버튼의 크기와 위치 계산
	sf::Vector2f buttonSize = sf::Vector2f(window.getSize().x * buttonSizeRatio, window.getSize().y * buttonSizeRatio);
	sf::Vector2f buttonPosition = sf::Vector2f(window.getSize().x * buttonPositionRatioX, window.getSize().y * buttonPositionRatioY);

	Button button(buttonPosition, buttonSize, "Clear", sf::Color::Green);
	Button trajectoryButton(sf::Vector2f(buttonPosition.x + 60, buttonPosition.y), buttonSize, "Trajectory", sf::Color::Red);
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Font loading failed!" << std::endl;
		return -1;
	}
	// flag Setting
	bool trajectoryFlag = false;
	// Text Setting
	sf::Text ballcountText;
	ballcountText.setFont(font);
	ballcountText.setCharacterSize(20);
	ballcountText.setFillColor(sf::Color::White);
	ballcountText.setPosition(buttonPosition.x + 10, buttonPosition.y + 60);

	// Window open event
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) // 이벤트 감지
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !trajectoryButton.isMouseOver(window)) // Mouse Left Button Pressed Event
			{
				if (button.isMouseOver(window))
				{
					vecBall.clear();
					currentBallCount = 0;
				}
				else if (vecBall.size() < maxBallCount)
				{
					sf::Color randomColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
					vecBall.push_back(Ball(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, -1, -1, randomColor));
					currentBallCount++;
				}
				else
				{
					vecBall.erase(vecBall.begin());
					sf::Color randomColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
					vecBall.push_back(Ball(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, -1, -1, randomColor));
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && trajectoryButton.isMouseOver(window))
			{
				trajectoryFlag = !trajectoryFlag;
			}
			if (event.type == sf::Event::MouseButtonReleased == sf::Mouse::Left) // Mouse Left Released Event
			{

			}
		}
		window.clear(); // clear window
		button.draw(window);
		trajectoryButton.draw(window);
	// update and draw all objects
		for (int i = 0; i < vecBall.size(); i++)
		{
			vecBall[i].updatePhysics(vecBall, window);
			if (trajectoryFlag)
				vecBall[i].renderTrajectory(window);
			vecBall[i].draw(window);
		}
		std::stringstream ss;
		ss << "Ball Count (MAX: " << maxBallCount << "): " << currentBallCount;
		ballcountText.setString(ss.str());
		window.draw(ballcountText);
		window.display(); // draw complete -> display
	}
	return 0;
}
