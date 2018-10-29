
#include "Application.h"
#include <iostream>

Application::Application()
{

}

Application::~Application()
{

}

GameObject* Application::Spawn()
{
	return Spawn(new GameObject());
}

GameObject* Application::Spawn(GameObject* duplicate)
{
	m_GOs.GetList().push_back(duplicate);
	return duplicate;
}

GameObject* Application::Spawn(Transform2D transform)
{
	GameObject* GO = new GameObject();
	GO->SetTransform(transform);

	return Spawn(GO);
}

GameObject* Application::Spawn(Vector2 position, float rotation, Vector2 scale)
{
	Transform2D transform;
	transform.position = position;
	transform.rotation = rotation;
	transform.scale = scale;

	return Spawn(transform);
}

GameObject& Application::FindGameObject(int index)
{
	return m_GOs.GetItem(index);
}

void Application::Destroy(GameObject* gameObject)
{
	GameObject* storedGOs = gameObject;
	m_GOs.GetList().remove(gameObject);
	delete gameObject;
}

void Application::SetID(int ID)
{
}

int Application::GetID()
{
	return 0;
}

void Application::SetGameState(GameState state)
{
}

GameState & Application::GetGameState()
{
	// TODO: insert return statement here
}

void Application::InitializeBoard()
{
}

void Application::UpdateBoard(int index, bool isOrange)
{
}

int Application::GetIndex(Vector3 mousePos)
{
	return 0;
}

Application &Application::Instance()
{
	// return singleton
	static Application instance;
	return instance;
}

void Application::Start()
{
	std::cout << "APPLICATION STARTED" << std::endl;

	// Load sprites.
	spr_Title			= new Sprite("../media/TicTacToeTitle.bmp");
	spr_Connecting		= new Sprite("../media/");
	spr_Connected		= new Sprite("../media/");
	spr_Empty			= new Sprite("../media/");
	spr_YourTurn		= new Sprite("../media/YourTurn.bmp");
	spr_OtherTurn		= new Sprite("../media/OtherTurn.bmp");
	spr_BoxEmpty		= new Sprite("../media/Box.bmp");
	spr_BoxCircle		= new Sprite("../media/BoxCircle.bmp");
	spr_BoxCross		= new Sprite("../media/BoxCross.bmp");

	network = new MyPhoton();

	//Initialize game board
	InitializeBoard();

	// Here is where you will determine which is the current player.
	network->connect();
}

void Application::Update(float deltaTime)
{
	time += deltaTime;

	network->run();
}

void Application::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw function
	iteGO = m_GOs.GetList().begin();
	while (iteGO != m_GOs.GetList().end())
	{
		GameObject GO = **iteGO;
		GO.Draw();
		++iteGO;
	}
}
