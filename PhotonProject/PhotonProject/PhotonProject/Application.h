
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

	int currentPlayer = 0; // Set this based on who created the room.
	int playerTurn = 0;
	int alignArray[9];

public:
	~Application();

	GameObject* GO;

	Sprite spr_title;
	Sprite spr_yourTurn;
	Sprite spr_otherTurn;
	Sprite spr_pleaseWait;
	Sprite spr_youWin;
	Sprite spr_youLose;
	Sprite spr_gameDraw;
	Sprite spr_boxSprite;
	Sprite spr_circleSprite;
	Sprite spr_crossSprite;
	Sprite spr_resetSprite;

	MyPhoton* network;
	UCharPacker* packer = new UCharPacker;


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
	void SetMousePos(float x, float y);

	void OnMouseClickBox();
	void ReceiveData(unsigned char data, int bitCount);

	void SetCurrentPlayer(int player);
	void CheckPlayerWin();
	void UpdatePlayerTurn();

	void CreateBoard();
	void UpdateBoardData(int index);
	void UpdateBoardSprite();

	void ResetGame();

	void SetGameState(GameState state);
	GameState GetGameState();

	// create singleton
	static Application& Instance();
	float time;

	void Start();
	void Update(float deltaTime);
	void Draw();
};

