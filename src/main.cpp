#include <iostream>
#include <armadillo>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Double pendulum");
	tgui::Gui gui(window);
	tgui::Button::Ptr button;
	arma::fvec2 circlePos {250, 250};
	sf::CircleShape shape(200.f);
	shape.setPointCount(300);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(circlePos[0], circlePos[1]);

	double angle1 = 90;
	double angle2 = 45;
	double angle1_acc = 0;
	double angle2_acc = 0;
	double angle1_vel = 0;
	double angle2_vel = 0;
	double length1 = 0.1;
	double length2 = 0.1;
	double mass1 = 0.1;
	double mass2 = 0.1;
	double g = 9.81;
	double scale = 1000;
	double timeScale = 1.0/5;
	sf::Vector2f startPos(250, 200);

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
		window.clear();
		sf::Vector2f firstPos (startPos.x + length1 * scale * sin(angle1), startPos.y + length1 * scale * cos(angle1));
		sf::Vector2f secondPos (firstPos.x + length2 * scale * sin(angle2), firstPos.y + length2 * scale * cos(angle2));
		std::vector<sf::Vertex> line =
		{
			sf::Vertex(startPos),
			sf::Vertex(firstPos),
			sf::Vertex(secondPos)
		};
		window.draw(&line[0], line.size(), sf::LineStrip);
		window.display();
	}
}
