
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

	Vector2 boxCoords[9];
	float mousePos[2];
	float halfBoxSize = 50.0f;
	float offset = 120.0f;

	int playerTurn = 0;
	int alignArray[9];
	bool markArray[9];
	bool isMark = false;
	bool isGameOver = false;

public:
	~Application();

	GameObject* GO;

	Sprite boxSprite;
	Sprite circleSprite;
	Sprite crossSprite;

	MyPhoton* network;

	void SetMousePos(float x, float y);
	bool GetGameOverState() { return isGameOver; };

	// overload spawn gameobject function
	GameObject* Spawn();
	GameObject* Spawn(GameObject* duplicate);
	GameObject* Spawn(Transform2D transform);
	GameObject* Spawn(Vector2 position, float rotation, Vector2 scale);
	GameObject& FindGameObject(int index);
	void Destroy(GameObject* gameObject);

	// First is to detect player left mouse click.
	// Then you need to get the mouse coordinates and box coordinates.
	// Check for the current player turn, then change the box to either 
	// a cross or circle depending on player turn.
	void CheckClickBoxPosition();
	void CheckPlayerWin();
	void SpawnGrid();

	// create singleton
	static Application& Instance();
	float time;

	void Start();
	void Update(float deltaTime);
	void Draw();
};

