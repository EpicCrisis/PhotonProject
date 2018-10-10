
#pragma once

#include <GLFW/glfw3.h>
#include "MyPhoton.h"
#include "GameObject.h"
#include "GameObjectContainer.h"

class Application
{
private:
	Application();

	GameObjectContainer<GameObject> m_GOs;
	std::list<GameObject*>::iterator iteGO;

	float mousePos[2];

	int playerTurn;

public:
	~Application();

	GameObject* GO;

	MyPhoton* network;

	void SetMousePos(float x, float y);

	// overload spawn gameobject function
	GameObject* Spawn();
	GameObject* Spawn(GameObject* duplicate);
	GameObject* Spawn(Transform2D transform);
	GameObject* Spawn(Vector2 position, float rotation, Vector2 scale);
	GameObject& FindGameObject(int index);
	void Destroy(GameObject* gameObject);

	// create singleton
	static Application& Instance();
	float time;

	void Start();
	void Update(float deltaTime);
	void Draw();
};

