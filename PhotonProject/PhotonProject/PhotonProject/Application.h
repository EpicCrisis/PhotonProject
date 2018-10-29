
#pragma once

#include <GLFW/glfw3.h>
#include "MyPhoton.h"
#include "GameObject.h"
#include "GameObjectContainer.h"
#include "UIntPacker.h"
#include "Vector3.h"

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

	GameObject* GO;

	Sprite* spr_Title;
	Sprite* spr_Connecting;
	Sprite* spr_Connected;
	Sprite* spr_Empty;
	Sprite* spr_YourTurn;
	Sprite* spr_OtherTurn;
	Sprite* spr_BoxEmpty;
	Sprite* spr_BoxCircle;
	Sprite* spr_BoxCross;

	GameState m_gameState;

	Vector2 box_drawPoint;

	float box_width;

	int m_ID;

public:
	~Application();

	MyPhoton* network;
	UCharPacker* packer = new UCharPacker;

	// overload spawn gameobject function
	GameObject* Spawn();
	GameObject* Spawn(GameObject* duplicate);
	GameObject* Spawn(Transform2D transform);
	GameObject* Spawn(Vector2 position, float rotation, Vector2 scale);
	GameObject& FindGameObject(int index);
	void Destroy(GameObject* gameObject);
	
	void SetID(int ID);
	int GetID();

	void SetGameState(GameState state);
	GameState& GetGameState();

	void InitializeBoard();
	void UpdateBoard(int index, bool isOrange);
	int GetIndex(Vector3 mousePos);

	// create singleton
	static Application& Instance();
	float time;

	void Start();
	void Update(float deltaTime);
	void Draw();
};

