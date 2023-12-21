/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ball.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:03:44 by janhan            #+#    #+#             */
/*   Updated: 2023/12/22 03:03:27 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ball.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <vector>

Ball::Ball(float pos_x, float pos_y, float vel_x, float vel_y, sf::Color color)
{
	pos.x = pos_x;
	pos.y = pos_y;
	vel.x = vel_x;
	vel.y = vel_y;


	ball.setPosition(pos);
	ball.setRadius(4);
	ball.setFillColor(color);
	ball.setOrigin(ball.getRadius(), ball.getRadius());

	mass = 10;
	dt = 0.07;
}

void	Ball::draw(sf::RenderWindow &window)
{
	ball.setPosition(pos);
	window.draw(ball);
}
void	Ball::setColor(sf::Color color)
{
	ball.setFillColor(color);
}

void	Ball::setVelocity(sf::Vector2f vel)
{
	this->vel = vel;
}

sf::Vector2f Ball::getPosition()
{
	return ball.getPosition();
}

void	Ball::setPosition(sf::Vector2f pos)
{
	this->pos = pos;
}

float Ball::getRadius()
{
	return ball.getRadius();
}
sf::Vector2f Ball::getVelocity()
{
	return this->vel;
}

float Ball::getMass()
{
	return this->mass;
}

float Ball::dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

void Ball::updatePhysics(std::vector<Ball>& vecBall, sf::RenderWindow& window)
{
	float numSteps = 2;  // 이동 경로를 샘플링하는 단계 수

	for (int step = 0; step < numSteps; ++step)
	{
		sf::Vector2f gravityForce = gravity * mass;
		sf::Vector2f acceleration = gravityForce / mass;
		vel += acceleration * dt / numSteps;  // 각 단계에서의 속도 갱신
		sf::Vector2f newPosition = pos + vel * dt / numSteps;  // 각 단계에서의 위치 갱신

		const float radius = ball.getRadius();
		const float screenWidth = static_cast<float>(window.getSize().x);
		const float screenHeight = static_cast<float>(window.getSize().y);
		const float restitution = 0.0f; // 탄성 1~0

		// CCD를 적용한 충돌 감지
		for (auto& otherBall : vecBall)
		{
			if (&otherBall != this)
			{
				sf::Vector2f distVector = otherBall.getPosition() - newPosition;
				float distance = std::sqrt(distVector.x * distVector.x + distVector.y * distVector.y);
				const float midDistance = radius + otherBall.getRadius();
				if (distance < midDistance)
				{
					// 충돌이 발생하는 경우, 충돌 지점과 충돌 시간을 찾아내어 위치 및 속도 조정
					sf::Vector2f normal = distVector / distance;
					sf::Vector2f relativeVelocity = otherBall.getVelocity() - vel;
					float inpulse = (2.0f * mass * otherBall.getMass()) /
									(mass + otherBall.getMass()) * dotProduct(relativeVelocity, normal);
					vel += (inpulse / mass) * normal;
					otherBall.setVelocity(otherBall.getVelocity() - (inpulse / otherBall.getMass()) * normal);

					// 충돌이 발생한 경우 위치 조정
					float overlap = midDistance - distance;
					sf::Vector2f correction = (overlap / 2.0f) * (distVector / distance);
					newPosition -= correction;
					otherBall.setPosition(otherBall.getPosition() + correction);

					// // 만약 충돌 후에 otherBall이 현재 공 위에 있다면
					// if (dotProduct(normal, sf::Vector2f(0.0f, -1.0f)) > 0.7f)
					// {
					// 	// 충돌 방향이 위쪽에 가까우면 다른 공을 넘어가지 않도록 위치를 아래로 조정
					// 	newPosition.y = otherBall.getPosition().y + midDistance;
					// }
				}
			}
		}
		// 벽과의 충돌 감지 및 응답
		if (newPosition.x - radius < 0.0f)
		{
			newPosition.x = radius;
			vel.x = -restitution * vel.x;
		}
		else if (newPosition.x + radius > window.getSize().x)
		{
			newPosition.x = window.getSize().x - radius;
			vel.x = -restitution * vel.x;
		}

		if (newPosition.y - radius < 0.0f)
		{
			newPosition.y = radius;
			vel.y = -restitution * vel.y;
		}
		else if (newPosition.y + radius > window.getSize().y)
		{
			newPosition.y = window.getSize().y - radius;
			vel.y = -restitution * vel.y;
		}

	// 현재 단계의 결과를 다음 단계로 반영
	pos = newPosition;
	}

	// 마지막 단계의 위치를 사용하여 물체의 실제 위치 갱신
	ball.setPosition(pos);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
}
