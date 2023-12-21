/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:05:55 by janhan            #+#    #+#             */
/*   Updated: 2023/12/22 03:08:04 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <SFML/Graphics.hpp>

class Button
{
	public:
		Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Color Color);
		void	draw(sf::RenderWindow& window);
		bool isMouseOver(const sf::RenderWindow& window);
	private:
		sf::Vector2f position;
		sf::Vector2f size;
		std::string text;
		sf::RectangleShape buttonShape;
		sf::Text buttonText;
		sf::Font font;
};
