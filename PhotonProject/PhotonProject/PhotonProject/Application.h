
#pragma once

#include <GLFW/glfw3.h>
#include "GameObject.h"
#include "GameObjectContainer.h"

class Application
{
private:
	Application();

	GameObjectContainer<GameObject> m_GOs;
	std::list<GameObject*>::iterator iteGO;

	float xMousePos = 0.0f;
	float yMousePos = 0.0f;

public:
	~Application();

	GameObject* GO;

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

