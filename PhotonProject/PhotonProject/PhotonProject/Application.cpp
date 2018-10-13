
#include "Application.h"
#include <iostream>

Application::Application()
{

}

Application::~Application()
{

}

void Application::SetMousePos(float x, float y)
{
	mousePos[0] = x;
	mousePos[1] = -y; // Display start position and mouse start position is inverse.
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

Application & Application::Instance()
{
	// return singleton
	static Application instance;
	return instance;
}

void Application::Start()
{
	std::cout << "APPLICATION STARTED" << std::endl; 
	
	network = new MyPhoton();

	network->connect();

	GO = Spawn(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f));
	GO->GetSprite().SetFilePath("../media/NomadAvatar.bmp");

	GO = Spawn(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f));
	GO->GetSprite().SetFilePath("../media/Jake.bmp");
}

void Application::Update(float deltaTime)
{
	time += deltaTime;

	network->run();

	// Set this to follow the mouse position
	Transform2D m_transform0;
	m_transform0 = FindGameObject(0).GetTransform();
	m_transform0.position =
		Vector2
		(
			mousePos[0], mousePos[1]
		);
	FindGameObject(0).SetTransform(m_transform0);

	// Set this to follow the OTHER mouse position
	Transform2D m_transform1;
	m_transform1 = FindGameObject(1).GetTransform();
	m_transform1.position =
		Vector2
		(
			network->cursorPos[1], network->cursorPos[2]
		);
	FindGameObject(1).SetTransform(m_transform1);
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
