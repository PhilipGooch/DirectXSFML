// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework

#include "ColourShader.h"

#include <SFML/Network.hpp>

#include "Player.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool finalPass();
	bool render();
	void gui();

	// Attempting to connect to the server.
	void connect();

private:
	ColourShader* colourShader;

	SphereMesh* sphereMesh;
	

	// Variables to hold temporary information generated from socket functions.
	sf::Socket::Status status;
	std::size_t bytes;

	// Setting up IP and port address'
	sf::IpAddress  serverIP;
	unsigned short serverPortTCP = 4444;
	unsigned short serverPortUDP = 4445;

	// Declaring sockets.
	sf::UdpSocket udpSocket;
	sf::TcpSocket tcpSocket;


	// Map of all the players in the game.
	std::map<int, Player*> players;

	int target = -1;
};

#endif