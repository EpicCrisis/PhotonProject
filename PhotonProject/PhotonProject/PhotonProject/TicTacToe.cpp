
#include "TicTacToe.h"

TicTacToe* TicTacToe::instance = 0;

TicTacToe* TicTacToe::Instance()
{
	if (instance == 0)
	{
		instance = new TicTacToe();
	}

	return instance;
}

TicTacToe::TicTacToe()
{
	box_width = 150;
	box_drawPoint = Vector2(280, 525);

	m_ID = -1;
	m_gameState = STATE_LOADING;
}

TicTacToe::~TicTacToe()
{
}

void TicTacToe::Start()
{
	//Load texture
	spr_Title = new Sprite("../media/title.bmp");
	spr_Connecting = new Sprite("../media/connecting.bmp");
	spr_Connected = new Sprite("../media/connected.bmp");
	spr_Empty = new Sprite("../media/empty.bmp");
	spr_YourTurn = new Sprite("../media/player01.bmp");
	spr_OtherTurn = new Sprite("../media/player02.bmp");
	spr_Box_Empty = new Sprite("../media/box.bmp");
	spr_Box_Circle = new Sprite("../media/box_orange.bmp");
	spr_Box_Cross = new Sprite("../media/box_blue.bmp");

	//Load game object
	GO = new GameObject;

	//Initialize game board
	InitializeBoard();
}

void TicTacToe::Update()
{

}

void TicTacToe::Draw()
{
}

void TicTacToe::SetID(int ID)
{
}

int TicTacToe::GetID()
{
	return 0;
}

void TicTacToe::SetGameState(GameState state)
{
}

GameState & TicTacToe::GetGameState()
{
	// TODO: insert return statement here
}

void TicTacToe::InitializeBoard()
{
}

void TicTacToe::UpdateBoard(int index, bool isOrange)
{
}

int TicTacToe::GetIndex(Vector3 mousePos)
{
	return 0;
}
