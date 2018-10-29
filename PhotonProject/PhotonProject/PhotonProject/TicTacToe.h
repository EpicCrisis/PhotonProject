
#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "GameObjectContainer.h"
#include "Vector.h"
#include "Vector3.h"

enum GameState
{
	STATE_LOADING,
	STATE_STARTGAME,
	STATE_GAMEOVER,
};

class TicTacToe
{
private:
	static TicTacToe* instance;

	Sprite* spr_Title;
	Sprite* spr_Connecting;
	Sprite* spr_Connected;
	Sprite* spr_Empty;
	Sprite* spr_YourTurn;
	Sprite* spr_OtherTurn;
	Sprite* spr_Box_Empty;
	Sprite* spr_Box_Circle;
	Sprite* spr_Box_Cross;

	GameObject* GO;

	Vector2 box_drawPoint;
	float box_width;

	int m_ID;
	GameState m_gameState;

public:
	static TicTacToe* Instance();

	TicTacToe();
	~TicTacToe();

	void Start();
	void Update();
	void Draw();

	void SetID(int ID);
	int GetID();
	void SetGameState(GameState state);
	GameState& GetGameState();

	void InitializeBoard();
	void UpdateBoard(int index, bool isOrange);

	int GetIndex(Vector3 mousePos);
};

