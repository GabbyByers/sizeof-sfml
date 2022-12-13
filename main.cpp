#include "SFML/Graphics.hpp"
#include <bitset>
#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::vector;
using std::string;

int main() {
	int screen_width = 1920;
	int screen_height = 1080;
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Hello SFML", sf::Style::Fullscreen | sf::Style::Close);
	sf::Event event;

	cout << "sizeof(sf::Vertex) = " << sizeof(sf::Vertex) << "\n";

	uint8_t* vertex_bytes = new uint8_t[sizeof(sf::Vertex)];

	sf::Vector2f position = sf::Vector2f(0.2, 0.0);
	sf::Color color = sf::Color(255, 255, 255, 255);
	sf::Vector2f texCoords = sf::Vector2f(0.0, 0.2);

	sf::Vertex vertex = sf::Vertex(position, color, texCoords);

	*(reinterpret_cast<sf::Vertex*>(&vertex_bytes[0])) = vertex;

	cout << sizeof(std::bitset<8>) << "\n";
	
	for (int i = 0; i < sizeof(sf::Vertex); i++) {
		uint8_t& byte = vertex_bytes[i];
		std::bitset<8> bit(byte);
		cout << bit.to_string() << " | " << unsigned(byte) << "\n";
	}

	vector<sf::Vertex> pixels;
	for (int i = 0; i < screen_width; i++) {
		for (int j = 0; j < screen_height; j++) {
			sf::Vertex pixel = sf::Vertex(sf::Vector2f(i, j), sf::Color(255, 0, 255));
			pixels.push_back(pixel);
		}
	}

	vector<sf::Vertex> single_quad;
	single_quad.push_back(sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0.0, 0.0)));
	single_quad.push_back(sf::Vertex(sf::Vector2f(screen_width, 0), sf::Vector2f(1.0, 0.0)));
	single_quad.push_back(sf::Vertex(sf::Vector2f(screen_width, screen_height), sf::Vector2f(1.0, 1.0)));
	single_quad.push_back(sf::Vertex(sf::Vector2f(0, screen_height), sf::Vector2f(0.0, 1.0)));

	sf::Texture texture;
	//texture.create(screen_width, screen_height);
	texture.loadFromFile("1920x1080_test_texture.png");

	cout << "Texture is size = " << sizeof(texture) << "\n";

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
		}

		window.clear(sf::Color(0, 0, 0));
		//window.draw(&pixels[0], pixels.size(), sf::Points);
		window.draw(&single_quad[0], single_quad.size(), sf::Quads, &texture);
		window.display();
	} return 0;
}

