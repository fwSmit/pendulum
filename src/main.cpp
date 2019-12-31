#include <iostream>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <deque>

struct variables{
	double angle1 = 35.f;
	double angle2 = 45.f;
	double angle1_acc = 0;
	double angle2_acc = 0;
	double angle1_vel = 0;
	double angle2_vel = 0;
	double length1 = 0.1;
	double length2 = 0.1;
	double maxMass = 1;
	double mass1 = 100;
	double mass2 = 0.2;
	double scale = 1000;
	double timeScale = 1.0/5;
	double maxLenght = 0.2;
	double minLenght = 0.02;
	float lineThickness = 5;
	std::deque<sf::Vector2f> positions;
	unsigned int maxPositions = 2000;

	// constants
	constexpr static double g{ 9.81 };

};

void reset(variables& _var){
	_var = variables();
}

int main()
{
	variables var;
	

	sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML Double pendulum");
	sf::Vector2u windowSize = window.getSize();
	tgui::Gui gui(window);
	// tgui::TextBox::Ptr test = tgui::TextBox::create();
	// test->setPosition(0, 0);
	// test->setSize(100, 50);
	// gui.add(test);


	sf::CircleShape trailCircle;
	int a = 60;
	trailCircle.setFillColor(sf::Color(a, a, a));
	trailCircle.setRadius(3);
	trailCircle.setOrigin(trailCircle.getRadius(), trailCircle.getRadius());
	trailCircle.setPointCount(10);

	
	sf::Font font;
	if(!font.loadFromFile("resources/Mermaid1001.ttf")){
		std::cout << "Could not load font" << std::endl;
	}
	
	auto pendulum_position = tgui::Slider::create();
	pendulum_position->setPosition("50%", "250");
	pendulum_position->setEnabled(0);
	pendulum_position->setVisible(0);
	gui.add(pendulum_position);
	

	auto horLayout1 = tgui::HorizontalLayout::create();
	horLayout1->setSize("90%", 50);
	horLayout1->setPosition("5%", "&.height - 100");
	// gui.add(horLayout1);
	
	auto horLayout2 = tgui::HorizontalLayout::create();
	horLayout2->setSize("90%", 50);
	horLayout2->setPosition("5%", "&.height - 200");
	// gui.add(horLayout2);
	
	auto vertLayout = tgui::VerticalLayout::create();
	vertLayout->setSize("90%", 200);
	vertLayout->setPosition("5%", "&.height - 200");
	vertLayout->add(horLayout1);
	vertLayout->add(horLayout2);
	gui.add(vertLayout);
	
	// sf::Text massText;
	// massText.setFont(font);
	// massText.setString("Mass");
	// massText.setPosition(50, windowSize.y - 150);
	// massText.setFillColor(sf::Color::Black);
	// tgui::Font tguiFont(font);
	// tgui::Text::Ptr massText;
	// massText->setFont(tguiFont);
	// massText->setString("test");
	// gui.add(massText);
	
	auto massLabel = tgui::Label::create();
	massLabel->setText("Mass");
	massLabel->setTextSize(35);
	massLabel->setPosition("19%", "&.height - 250");
	gui.add(massLabel);
	
	auto sizeLabel = tgui::Label::create();
	sizeLabel->setText("Size");
	sizeLabel->setTextSize(35);
	sizeLabel->setPosition("65%", "&.height - 250");
	gui.add(sizeLabel);

	// horLayout1->add(massText);
	auto massSlider1 = tgui::Slider::create(.1f, var.maxMass);
	// massSlider1->setPosition({"10%", "80%"});
	// massSlider1->setSize("20%", 15);
	massSlider1->setStep(0.005);
	// gui.add(massSlider1);
	tgui::Slider::Ptr massSlider2 = tgui::Slider::create(0.01f, var.maxMass);
	// massSlider2->setPosition({"10%", "85%"});
	// massSlider2->setSize("20%", 15);
	massSlider2->setStep(0.005);
	// gui.add(massSlider2);
	
	// sf::Text lengthText;
	// lengthText.setFont(font);
	// lengthText.setString("Length");
	// lengthText.setPosition(270, windowSize.y - 150);
	// lengthText.setFillColor(sf::Color::Black);
	tgui::Slider::Ptr lengthSlider1 = tgui::Slider::create(var.minLenght, var.maxLenght);
	lengthSlider1->setPosition(270, windowSize.y - 100);
	lengthSlider1->setSize(180, 15);
	lengthSlider1->setStep(0.0005);
	lengthSlider1->setValue(var.length1);
	// gui.add(lengthSlider1);
	tgui::Slider::Ptr lengthSlider2	= tgui::Slider::create(var.minLenght, var.maxLenght);
	lengthSlider2->setPosition(270, windowSize.y - 50);
	lengthSlider2->setSize(180, 15);
	lengthSlider2->setStep(0.0005);
	lengthSlider2->setValue(var.length2);
	// gui.add(lengthSlider2);

	horLayout1->add(massSlider1);
	horLayout1->add(lengthSlider1);
	horLayout2->add(massSlider2);
	horLayout2->add(lengthSlider2);
	// sf::Texture pause_tex;
	// if(!pause_tex.loadFromFile("resources/icon_pause.png")){
		// std::cout << "Pause icon could not be found" << std::endl;
	// }

	bool paused = false;
	tgui::Texture pause_tex("resources/icon_pause.png");
	tgui::Picture::Ptr pause_img = tgui::Picture::create(pause_tex);
	pause_img->setPosition(20, 20);
	pause_img->connect("clicked", [& paused](){
			paused = !paused;
			if (paused){
				std::cout << "pause" << std::endl;
			}
			else{
				std::cout << "play" << std::endl;
			}
			});
	gui.add(pause_img);
	
	
	// Icon made by Google from https://www.flaticon.com
	tgui::Texture reset_tex("resources/icon_reset.png");
	tgui::Picture::Ptr reset_img = tgui::Picture::create(reset_tex);
	reset_img->setPosition(20, 50);
	reset_img->connect("clicked", [& var](){
			reset(var);
			});
	gui.add(reset_img);
	// pause_img->connect("MouseEntered", [window](){});
	// pause_img->connect("MouseLeft", shadeButton);

	// tgui::Button::Ptr pause_button = tgui::Button::create();
	// pause_button->setPosition(20, 20);
	// pause_button->setSize(pause_img->getSize());

	// gui.add(pause_button);
	// sf::Sprite pause_sprite;
	// pause_sprite.setTexture(pause_tex);
	// pause_sprite.setPosition(20, 20);
	
	

	sf::Clock timer;
	double deltaTime;
	while (window.isOpen())
	{

		
		// masses
		var.mass1 = massSlider1->getValue();
		var.mass2 = massSlider2->getValue();
		double mass1Percent = var.mass1/var.maxMass;
		double mass2Percent = var.mass2/var.maxMass;
		sf::CircleShape weight1(std::max(10., var.mass1/var.maxMass * 15.));
		sf::Color weigth1Color(100*mass1Percent, 255 * (1-mass1Percent), 255 * (1-mass1Percent));
		weight1.setFillColor(weigth1Color);
		weight1.setOrigin(weight1.getRadius(), weight1.getRadius());
		weight1.setPointCount(100);

		sf::CircleShape weight2(std::max(10., var.mass2/var.maxMass * 15.));
		sf::Color weigth2Color(100*mass2Percent, 255 * (1-mass2Percent), 255 * (1-mass2Percent));
		weight2.setFillColor(weigth2Color);
		weight2.setOrigin(weight2.getRadius(), weight2.getRadius());
		weight2.setPointCount(100);

		//lenghts
		var.length1 = lengthSlider1->getValue();
		var.length2 = lengthSlider2->getValue();
		sf::RectangleShape firstLine (sf::Vector2f(var.lineThickness, var.length1*var.scale));
		firstLine.setOrigin(var.lineThickness / 2., 0);
		firstLine.setPosition(pendulum_position->getPosition().x, pendulum_position->getPosition().y);
		firstLine.setFillColor(sf::Color::Black);

		sf::RectangleShape secondLine (sf::Vector2f(var.lineThickness, var.length2*var.scale));
		secondLine.setOrigin(var.lineThickness / 2., 0);
		secondLine.setFillColor(sf::Color::Black);

		
		// std::stringstream mousePos;
		// mousePos << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y;
		// test->setText(mousePos.str());
		deltaTime = var.timeScale * timer.restart().asSeconds();
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
		if(!paused){
			// from myphsicslab
			double top1 = -var.g *(2*var.mass1 + var.mass2)* sin(var.angle1) - var.mass2*var.g*sin(var.angle1 - 2*var.angle2)
				- 2 * sin(var.angle1-var.angle2)*var.mass2*(var.angle2_vel*var.angle2_vel*var.length2 + var.angle1_vel*var.angle1_vel*var.length1*cos(var.angle1-var.angle2));
			double top2 = 2*sin(var.angle1-var.angle2)*( (var.angle1_vel*var.angle1_vel*var.length1*(var.mass1+var.mass2))
					+ var.g*(var.mass1+var.mass2)*cos(var.angle1) + var.angle2_vel*var.angle2_vel*var.length2*var.mass2*cos(var.angle1-var.angle2) );
			double bottomPart = (2*var.mass1 + var.mass2 - var.mass2*cos(2*(var.angle1 - var.angle2)));
			var.angle1_acc = top1 / (var.length1 * bottomPart);
			var.angle2_acc = top2 / (var.length2 * bottomPart);
			var.angle1 += deltaTime * var.angle1_vel;
			var.angle2 += deltaTime * var.angle2_vel;
			var.angle1_vel = var.angle1_vel + deltaTime * var.angle1_acc;
			var.angle2_vel = var.angle2_vel + deltaTime * var.angle2_acc;
		}
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
		sf::Vector2f firstEndPos (pendulum_position->getPosition().x + var.length1 * var.scale * sin(var.angle1), pendulum_position->getPosition().y + var.length1 * var.scale * cos(var.angle1));
		sf::Vector2f secondEndPos (firstEndPos.x + var.length2 * var.scale * sin(var.angle2), firstEndPos.y + var.length2 * var.scale * cos(var.angle2));
		firstLine.setRotation(-var.angle1/M_PI*180.f);
		secondLine.setRotation(-var.angle2/M_PI*180.f);
		secondLine.setPosition(firstEndPos.x, firstEndPos.y);
		weight1.setPosition(firstEndPos);
		weight2.setPosition(secondEndPos);


		
		// take care of the trail
		var.positions.push_back(secondEndPos);
		if(var.positions.size() > var.maxPositions){
			var.positions.pop_front();
		}

		for(auto pos : var.positions){
			trailCircle.setPosition(pos);
			window.draw(trailCircle);
		}
		
		window.draw(firstLine);
		window.draw(secondLine);
		window.draw(weight1);
		window.draw(weight2);
		// window.draw(massText);
		// window.draw(lengthText);
		gui.draw();
		window.display();
	}
}
