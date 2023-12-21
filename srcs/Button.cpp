/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:06:40 by janhan            #+#    #+#             */
/*   Updated: 2023/12/22 04:40:51 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Button.hpp"
#include "SFML/System/Vector2.hpp"

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Color Color)
	: position(position), size(size), text(text) {
	font.loadFromFile("arial.ttf");
	buttonShape.setSize(size);
	buttonShape.setPosition(position);
	buttonShape.setFillColor(Color);
	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setCharacterSize(15);
	buttonText.setFillColor(sf::Color::Black);
	sf::FloatRect textBounds = buttonText.getGlobalBounds();
	buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
						textBounds.top + textBounds.height / 2.0f);
	buttonText.setPosition(position.x + size.x / 2.0f,
						position.y + size.y / 2.0f);
}

void	Button::setSize(sf::Vector2f size)
{
	buttonShape.setSize(size);
}

void	Button::setPosition(sf::Vector2f pos)
{
	buttonShape.setPosition(pos);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(buttonShape);
	window.draw(buttonText);
}

bool Button::isMouseOver(const sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return (buttonShape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))));
}
