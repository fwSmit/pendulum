#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

int main(){
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Double pendulum");
	tgui::Gui gui(window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
					gui.setView(window.getView());
				break;

				default:
					break;
			}
			gui.handleEvent(event);
		}
		window.clear();
		window.display();
	}
}
