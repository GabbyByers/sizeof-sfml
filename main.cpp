#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "mouse.h"
using std::cout;
using std::vector;
using std::string;

int main() {
	int screen_width = 1920;
	int screen_height = 1080;
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Hello SFML", sf::Style::Fullscreen | sf::Style::Close);
	Mouse mouse(screen_width, screen_height);
	sf::Event event;

	vector<sf::Vertex> single_quad;
	float w = static_cast<float>(screen_width);
	float h = static_cast<float>(screen_height);
	single_quad.push_back(sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
	single_quad.push_back(sf::Vertex(sf::Vector2f(w, 0), sf::Vector2f(w, 0)));
	single_quad.push_back(sf::Vertex(sf::Vector2f(w, h), sf::Vector2f(w, h)));
	single_quad.push_back(sf::Vertex(sf::Vector2f(0, h), sf::Vector2f(0, h)));

	sf::Image image;
	image.loadFromFile("1920x1080_.png");
	sf::Texture texture;
	texture.loadFromImage(image);

	uint8_t* pixels_ptr = const_cast<uint8_t*>(image.getPixelsPtr());
	sf::Vector2u pixels_dim = image.getSize();
	size_t pixels_len = pixels_dim.x * pixels_dim.y;
	cout << "pixels_dim.x = " << pixels_dim.x << "\n";
	cout << "pixels_dim.y = " << pixels_dim.y << "\n";
	cout << "pixels_len   = " << pixels_len << "\n";

	for (int i = 0; i < 100; i++) {
		if (i % 4 == 0) { cout << "\n"; }
		cout << unsigned(*(pixels_ptr + i)) << " ";
	}

	vector<sf::Vertex> pixels;
	for (int i = 0; i < screen_width; i++) {
		for (int j = 0; j < screen_height; j++) {
			sf::Vertex vertex = sf::Vertex(sf::Vector2f(i, j), sf::Color(0, 255, 255));
			pixels.push_back(vertex);
		}
	}

	bool isImage = true;

	while (window.isOpen()) {
		mouse.setMouseProperties(sf::Mouse::getPosition(window));
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == sf::Keyboard::A) {
					isImage = !isImage;
				}
			}
		}

		window.clear(sf::Color(0, 0, 0));

		if (isImage) {
			texture.loadFromImage(image);
			window.draw(&single_quad[0], single_quad.size(), sf::Quads, &texture);
		}
		else {
			window.draw(&pixels[0], pixels.size(), sf::Points);
		}
		
		window.display();
	} return 0;
}

