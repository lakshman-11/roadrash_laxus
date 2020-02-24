#include<SFML\Graphics.hpp>
#include<iostream>
#include"rdtrack.h"

int width = 1920, height = 1080;
int roadW = 2000;
int segL = 200; //segment length
float camD = 0.84; //camera depth
int speed = 200;



int main()
{ 
	sf::RenderWindow window(sf::VideoMode(width, height), "my test", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);
	sf::Texture bg;
	bg.loadFromFile("back.png",sf::IntRect(0,0,1920,1080));
	bg.setRepeated(true);
	sf::Sprite sBackground(bg);
	float obsposx=1000, obsposy=700;
	int obssize = 20;
	sf::RectangleShape obs1(sf::Vector2f(obssize, obssize));
	obs1.setFillColor(sf::Color::Blue);
	
	//sf::Texture playerTexture;
	//playerTexture.loadFromFile("kaido.png");
	//player.setTexture(&playerTexture);*/
	std::vector<Line>lines;
	for (int i = 0; i < 1600; i++)
	{
		Line line;
		line.z = i * segL;
		if (i > 300 && i < 700) line.curve = 0.5;
		if (i > 750)line.y = sin(i / 30.0) * 1500;
		lines.push_back(line);

	}
	int N = lines.size(); 
	int pos = 0;
	
	while (window.isOpen())
	{
		std::cout << obsposy << std::endl;
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == evnt.Closed)
			{
				window.close();
			}
		}
		obs1.setPosition(obsposx, obsposy);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			pos += speed;
			obsposy = obsposy + 2;
			obssize += 5;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			pos -= speed;
			obsposy = obsposy - 2;
			obssize -= 5;
		} 
		while (pos >= N * segL) pos -= N * segL;
		while (pos < 0) pos += N * segL;
		window.clear();
		
		window.draw(sBackground);
		int startPos = pos / segL;
		float x = 0, dx = 0;
		int maxy = height;
		float camH = 1500 + lines[startPos].y; 
		 
		//roadtrack::drawQuad(window, sf::Color::Blue, 960, 900, 300, 960,100, 200);
		///draw road///
		
		for (int n =startPos ; n < startPos+300; n++)
		{
			Line& l = lines[n % N];
			l.project(-x,camH, pos-(n>=N?N*segL:0));
			x += dx;
			dx += l.curve;
			if (l.Y >= maxy) continue;
			maxy = l.Y;
			sf::Color grass = (n / 3) % 2 ? sf::Color(16, 200, 16) : sf::Color(0, 150, 0);


			
			
			sf::Color rumble;
			if ((n / 2)%3==0) rumble = sf::Color(237, 188, 0);
			else if((n/2)%3==1) rumble = sf::Color(0, 76, 153);
			else rumble = sf::Color(169, 0, 69);

			//sf::Color rumble= (n / 3) % 2 ? sf::Color(255, 255, 255) : sf::Color(0, 0, 0);
			sf::Color road  = (n / 3) % 2 ? sf::Color(107, 107, 107) : sf::Color(150, 150, 150);
			 
			Line p = lines[(n - 1) % N]; //previous line
			roadtrack::drawQuad(window, grass, 0, p.Y, width, 0, l.Y, width);
			roadtrack::drawQuad(window, rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2); 
			roadtrack::drawQuad(window, road, p.X, p.Y, p.W, l.X, l.Y, l.W); 
			
			obs1.setOrigin(sf::Vector2f(obssize / 2, obssize / 2));
			obs1.setSize(sf::Vector2f(obssize, obssize));
		}
		window.draw(obs1);
		window.display();
	}
}