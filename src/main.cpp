#include <iostream>
#include <armadillo>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

int main()
{
	int ab =10;
	if(!ab > 1){
		std::cout << "ab is " << ab << std::endl;
	}
	else{
		std::cout << "false" << std::endl;
	}
	std::cout << "Opening window" << std::endl;
	sf::RenderWindow window(sf::VideoMode(500, 500), "Template works!");
	tgui::Gui gui(window);
	tgui::Button::Ptr button;
	arma::fvec2 circlePos {250, 250};
	sf::CircleShape shape(200.f);
	shape.setPointCount(300);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(circlePos[0], circlePos[1]);
	sf::Texture img;
	if(!img.loadFromFile("resources/background.jpg")){
		// could not load image
		std::cout << "Could not find image" << std::endl;
		return -1;
	}
	shape.setTexture(&img);

	while (window.isOpen())
	{
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

		window.clear();
		window.draw(shape);
		//window.draw(img);
		window.display();
	}
}
