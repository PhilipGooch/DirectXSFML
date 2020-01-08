// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	// Loading textures.
	textureMgr->loadTexture(L"red", L"res/red.png");
	textureMgr->loadTexture(L"green", L"res/green.png");
	textureMgr->loadTexture(L"blue", L"res/blue.png");
	textureMgr->loadTexture(L"yellow", L"res/yellow.png");
	textureMgr->loadTexture(L"magenta", L"res/magenta.png");
	textureMgr->loadTexture(L"cyan", L"res/cyan.png");
	textureMgr->loadTexture(L"white", L"res/white.png");
	textureMgr->loadTexture(L"orange", L"res/orange.png");
	textureMgr->loadTexture(L"black", L"res/black.png");
	textureMgr->loadTexture(L"concrete", L"res/concreteWall.png");
	textureMgr->loadTexture(L"water", L"res/water.jpg");
	textureMgr->loadTexture(L"camel", L"res/camel.jpg");

	// Creating shader handler classes.
	colourShader = new ColourShader(renderer->getDevice(), hwnd);

	// Creating sphere mesh for light indicators.
	sphereMesh = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());

	// Setting up the camera.
	camera->setPosition(0, 0, -10);

	///////////////////////

	// Reading the IP address of the server from a text file, set by the user.
	std::ifstream inFile;
	inFile.open("IP.txt");
	if (!inFile)
	{
		printf("Error loading IP file.");
		assert(false);
	}
	inFile >> serverIP;
	inFile.close();

	// Binding th UDP socket to the specified port and setting it to non blocking mode.
	udpSocket.bind(sf::Socket::AnyPort);
	udpSocket.setBlocking(false);

	// Setting to blocking mode for the initial conversation. Could cause other players to lag if there is a problem with the connection phase of a client. not idea...
	tcpSocket.setBlocking(true);

	connect();
}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

}

bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}

	
	camera->update();
	

	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

void App1::connect()
{
	// Attempting to connect to the server.
	sf::Socket::Status status = tcpSocket.connect(serverIP, serverPortTCP);
	// Error handling / debugging.
	if (status != sf::Socket::Done)
	{
		printf("ERROR: connect()");
		assert(false);
	}
}

bool App1::render()
{
	finalPass();
	return true;
}

bool App1::finalPass()
{
	// Clear the scene. 
	renderer->beginScene(1.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = camera->getViewMatrix();	
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix(); 

	sphereMesh->sendData(renderer->getDeviceContext());
	colourShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, XMFLOAT4(0, 1, 0, 1));
	colourShader->render(renderer->getDeviceContext(), sphereMesh->getIndexCount());

	// Render GUI
	gui();

	// Swap the buffers
	renderer->endScene();
	return true;
}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	// ImGui::

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

