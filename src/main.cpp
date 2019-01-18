#include <iostream>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Double pendulum");
	tgui::Gui gui(window);
	tgui::Button::Ptr button;
	sf::CircleShape shape(200.f);
	shape.setPointCount(300);
	shape.setOrigin(shape.getRadius(), shape.getRadius());

	double angle1 = 90.f;
	double angle2 = 45.f;
	double angle1_acc = 0;
	double angle2_acc = 0;
	double angle1_vel = 0;
	double angle2_vel = 0;
	double length1 = 0.15;
	double length2 = 0.1;
	double maxMass = 1;
	double mass1 = 1;
	double mass1Percent = mass1/maxMass;
	double mass2 = 0.2;
	double mass2Percent = mass2/maxMass;
	double g = 9.81;
	double scale = 1000;
	double timeScale = 1.0/5;
	float lineThickness = 5;
	sf::Vector2f startPos(250, 100);
	sf::RectangleShape firstLine (sf::Vector2f(lineThickness, length1*scale));
	firstLine.setOrigin(lineThickness / 2., 0);
	firstLine.setPosition(startPos.x, startPos.y);
	firstLine.setFillColor(sf::Color::Black);
	
	sf::RectangleShape secondLine (sf::Vector2f(lineThickness, length2*scale));
	secondLine.setOrigin(lineThickness / 2., 0);
	secondLine.setFillColor(sf::Color::Black);
	
	sf::CircleShape weight1(std::max(10., mass1/maxMass * 15.));
	sf::Color weigth1Color(100*mass1Percent, 255 * (1-mass1Percent), 255 * (1-mass1Percent));
	weight1.setFillColor(weigth1Color);
	weight1.setOrigin(weight1.getRadius(), weight1.getRadius());
	weight1.setPointCount(100);
	
	sf::CircleShape weight2(std::max(10., mass2/maxMass * 50.));
	sf::Color weigth2Color(100*mass2Percent, 255 * (1-mass2Percent), 255 * (1-mass2Percent));
	weight2.setFillColor(weigth2Color);
	weight2.setOrigin(weight2.getRadius(), weight2.getRadius());
	weight2.setPointCount(100);

	sf::Clock timer;
	double deltaTime;
	while (window.isOpen())
	{
		deltaTime = timeScale * timer.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type){
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}
		// from myphsicslab
		double top1 = -g *(2*mass1 + mass2)* sin(angle1) - mass2*g*sin(angle1 - 2*angle2)
			- 2 * sin(angle1-angle2)*mass2*(angle2_vel*angle2_vel*length2 + angle1_vel*angle1_vel*length1*cos(angle1-angle2));
		double top2 = 2*sin(angle1-angle2)*( (angle1_vel*angle1_vel*length1*(mass1+mass2))
				+ g*(mass1+mass2)*cos(angle1) + angle2_vel*angle2_vel*length2*mass2*cos(angle1-angle2) );
		double bottomPart = (2*mass1 + mass2 - mass2*cos(2*(angle1 - angle2)));
		angle1_acc = top1 / (length1 * bottomPart);
		angle2_acc = top2 / (length2 * bottomPart);
		angle1 += deltaTime * angle1_vel;
		angle2 += deltaTime * angle2_vel;
		angle1_vel = angle1_vel + deltaTime * angle1_acc;
		angle2_vel = angle2_vel + deltaTime * angle2_acc;
		//angle1 = 0;
		//angle2 = 45.0 / 180.0 * 3.14;
		window.clear(sf::Color(193, 193, 193));
		// sf::Vector2f firstPos (startPos.x + length1 * scale * sin(angle1), startPos.y + length1 * scale * cos(angle1));
		// sf::Vector2f secondPos (firstPos.x + length2 * scale * sin(angle2), firstPos.y + length2 * scale * cos(angle2));
		// std::vector<sf::Vertex> line =
		// {
			// sf::Vertex(startPos),
			// sf::Vertex(firstPos),
			// sf::Vertex(secondPos)
		// };
		// window.draw(&line[0], line.size(), sf::LineStrip);
		sf::Vector2f firstEndPos (startPos.x + length1 * scale * sin(angle1), startPos.y + length1 * scale * cos(angle1));
		sf::Vector2f secondEndPos (firstEndPos.x + length2 * scale * sin(angle2), firstEndPos.y + length2 * scale * cos(angle2));
		firstLine.setRotation(-angle1/M_PI*180.f);
		secondLine.setRotation(-angle2/M_PI*180.f);
		secondLine.setPosition(firstEndPos.x, firstEndPos.y);
		weight1.setPosition(firstEndPos);
		weight2.setPosition(secondEndPos);
		window.draw(firstLine);
		window.draw(secondLine);
		window.draw(weight1);
		window.draw(weight2);
		window.display();
	}
}
