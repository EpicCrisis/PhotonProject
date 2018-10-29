
#pragma once

#include <GLFW/glfw3.h>
#include "MyPhoton.h"
#include "GameObject.h"
#include "GameObjectContainer.h"
#include "UIntPacker.h"

enum GameState
{
	STATE_WAITGAME = 0,
	STATE_STARTGAME = 1,
	STATE_GAMEOVER
};

class Application
{
private:
	Application();

	GameObjectContainer<GameObject> m_GOs;
	std::list<GameObject*>::iterator iteGO;

	GameState m_gameState;

	float mousePos[2];
	float halfBoxSize = 50.0f;
	float offset = 120.0f;

	int currentPlayer; // Set this based on who created the room.
	int playerTurn = 0;
	int alignArray[9];
	bool isMark = false;

public:
	~Application();

	GameObject* GO;

	Sprite boxSprite;
	Sprite circleSprite;
	Sprite crossSprite;

	MyPhoton* network;
	UCharPacker* packer = new UCharPacker;

	void SetMousePos(float x, float y);

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
	void UpdatePlayerTurn();
	void PackData();
	void SetCurrentPlayer(int player);

	void SetGameState(GameState state);
	GameState GetGameState();

	// create singleton
	static Application& Instance();
	float time;

	void Start();
	void Update(float deltaTime);
	void Draw();
};

