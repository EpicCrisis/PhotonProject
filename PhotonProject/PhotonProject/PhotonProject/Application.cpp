
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

void Application::SetMousePos(float x, float y)
{
	mousePos[0] = x;
	mousePos[1] = y;
}

void Application::CheckClickBoxPosition()
{
	// Check position, check player turn, check have marked, check array align, check win.
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (mousePos[0] >= 300.0f + (j * offset) - halfBoxSize &&
				mousePos[0] <= 300.0f + (j * offset) + halfBoxSize &&
				mousePos[1] >= 400.0f + (i * -offset) - halfBoxSize &&
				mousePos[1] <= 400.0f + (i * -offset) + halfBoxSize)
			{
				int k = (i * 3) + j;

				if (playerTurn == 0 && currentPlayer == 1)
				{
					if (alignArray[k] == 0)
					{
						alignArray[k] = 1;

						network->sendData(packer->Pack(k + 1, 4));
						std::cout << k << std::endl;
						//std::cout << packer->Pack(boardIndex, 4) << std::endl;

						UpdateBoard(k);
						UpdateTurn();
					}
				}
				else if (playerTurn == 1 && currentPlayer == 2)
				{
					if (alignArray[k] == 0)
					{
						alignArray[k] = 2;

						network->sendData(packer->Pack(k + 1, 4));
						std::cout << k << std::endl;
						//std::cout << packer->Pack(boardIndex, 4) << std::endl;

						UpdateBoard(k);
						UpdateTurn();
					}
				}
			}
		}
	}
}

void Application::CheckPlayerWin()
{
	if (
		// horizontal
		alignArray[0] == 1 && alignArray[1] == 1 && alignArray[2] == 1 ||
		alignArray[3] == 1 && alignArray[4] == 1 && alignArray[5] == 1 ||
		alignArray[6] == 1 && alignArray[7] == 1 && alignArray[8] == 1 ||
		// vertical
		alignArray[0] == 1 && alignArray[3] == 1 && alignArray[6] == 1 ||
		alignArray[1] == 1 && alignArray[4] == 1 && alignArray[7] == 1 ||
		alignArray[2] == 1 && alignArray[5] == 1 && alignArray[8] == 1 ||
		// diagonal
		alignArray[0] == 1 && alignArray[4] == 1 && alignArray[8] == 1 ||
		alignArray[2] == 1 && alignArray[4] == 1 && alignArray[6] == 1
		)
	{
		if (currentPlayer == 1)
		{
			// always last to spawn
			GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
			GO->SetSprite(spr_youWin);
			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

			std::cout << "YOU WIN!" << std::endl;
		}
		else if (currentPlayer == 2)
		{
			// always last to spawn
			GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
			GO->SetSprite(spr_youLose);
			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

			std::cout << "YOU LOSE!" << std::endl;
		}
		SetGameState(STATE_GAMEOVER);
	}
	else if (
		// horizontal
		alignArray[0] == 2 && alignArray[1] == 2 && alignArray[2] == 2 ||
		alignArray[3] == 2 && alignArray[4] == 2 && alignArray[5] == 2 ||
		alignArray[6] == 2 && alignArray[7] == 2 && alignArray[8] == 2 ||
		// vertical
		alignArray[0] == 2 && alignArray[3] == 2 && alignArray[6] == 2 ||
		alignArray[1] == 2 && alignArray[4] == 2 && alignArray[7] == 2 ||
		alignArray[2] == 2 && alignArray[5] == 2 && alignArray[8] == 2 ||
		// diagonal
		alignArray[0] == 2 && alignArray[4] == 2 && alignArray[8] == 2 ||
		alignArray[2] == 2 && alignArray[4] == 2 && alignArray[6] == 2
		)
	{
		if (currentPlayer == 1)
		{
			// always last to spawn
			GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
			GO->SetSprite(spr_youLose);
			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

			std::cout << "YOU LOSE!" << std::endl;
		}
		else if (currentPlayer == 2)
		{
			// always last to spawn
			GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
			GO->SetSprite(spr_youWin);
			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

			std::cout << "YOU WIN!" << std::endl;
		}
		SetGameState(STATE_GAMEOVER);
	}
	else if (
		// horizontal
		alignArray[0] != 0 && alignArray[1] != 0 && alignArray[2] != 0 &&
		alignArray[3] != 0 && alignArray[4] != 0 && alignArray[5] != 0 &&
		alignArray[6] != 0 && alignArray[7] != 0 && alignArray[8] != 0 &&
		// vertical													   
		alignArray[0] != 0 && alignArray[3] != 0 && alignArray[6] != 0 &&
		alignArray[1] != 0 && alignArray[4] != 0 && alignArray[7] != 0 &&
		alignArray[2] != 0 && alignArray[5] != 2 && alignArray[8] != 0 &&
		// diagonal													   
		alignArray[0] != 0 && alignArray[4] != 0 && alignArray[8] != 0 &&
		alignArray[2] != 0 && alignArray[4] != 0 && alignArray[6] != 0
		)
	{
		GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
		GO->SetSprite(spr_gameDraw);
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

		std::cout << "Game Draw!" << std::endl;
		SetGameState(STATE_GAMEOVER);
	}
}

void Application::SpawnGrid()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			// 0 ~ 8
			GO = Spawn(Vector2(300.0f + (j * offset), 400.0f + (i * -offset)), 0.0f, Vector2(1.0f, 1.0f));
			GO->SetSprite(spr_boxSprite);
			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
		}
	}
	// 9
	GO = Spawn(Vector2(60.0f, 550.0f), 0.0f, Vector2(1.0f, 1.0f));
	GO->SetSprite(spr_title);
	GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
}

void Application::UpdateTurn()
{
	CheckPlayerWin();

	++playerTurn;
	if (playerTurn % 2 == 0)
	{
		playerTurn = 0;
	}

	CheckPlayerWin();

	if (GetGameState() == STATE_STARTGAME)
	{
		UpdateTurnSprite();
	}

	std::cout << "PLAYERTURN : " << playerTurn << std::endl;
}

void Application::UpdateTurnSprite()
{
	if (currentPlayer == 1 && playerTurn == 0 ||
		currentPlayer == 2 && playerTurn == 1)
	{
		// 10, will change between sprites!
		FindGameObject(10).SetSprite(spr_yourTurn);
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
	}
	else if (currentPlayer == 2 && playerTurn == 0 ||
			currentPlayer == 1 && playerTurn == 1)
	{
		// 10, will change between sprites!
		FindGameObject(10).SetSprite(spr_otherTurn);
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
	}
	else if (GetGameState() == STATE_WAITGAME)
	{
		// 10, will change between sprites!
		FindGameObject(10).SetSprite(spr_pleaseWait);
	}
}

void Application::SetCurrentPlayer(int player)
{
	if (currentPlayer == 0)
	{
		currentPlayer = player;
		std::cout << currentPlayer << std::endl;
	}
}

void Application::UpdateBoard(int index)
{	
	if (currentPlayer == 1 && playerTurn == 0)
	{
		FindGameObject(index).SetSprite(spr_circleSprite);
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

		alignArray[index] = 1;
	}
	else if (currentPlayer == 2 && playerTurn == 0)
	{
		FindGameObject(index).SetSprite(spr_circleSprite);
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

		alignArray[index] = 1;
	}

	if (currentPlayer == 1 && playerTurn == 1)
	{
		FindGameObject(index).SetSprite(spr_crossSprite);
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

		alignArray[index] = 2;
	}
	else if (currentPlayer == 2 && playerTurn == 1)
	{
		FindGameObject(index).SetSprite(spr_crossSprite);
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

		alignArray[index] = 2;
	}
}

void Application::ReceiveData(unsigned char data, int bitCount)
{
	UpdateBoard((packer->Extract(data, bitCount)) - 1);
	UpdateTurn();
}

void Application::SetGameState(GameState state)
{
	if (m_gameState == STATE_WAITGAME)
	{
		// Put image showing waiting player 2.
	}

	m_gameState = state;
}

GameState Application::GetGameState()
{
	return m_gameState;
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

	// Here is where you will determine which is the current player.
	network->connect();

	spr_title.SetFilePath("../media/TicTacToeTitle.bmp");
	spr_yourTurn.SetFilePath("../media/YourTurn.bmp");
	spr_otherTurn.SetFilePath("../media/OtherTurn.bmp");
	spr_pleaseWait.SetFilePath("../media/PleaseWait.bmp");
	spr_youWin.SetFilePath("../media/YouWin.bmp");
	spr_youLose.SetFilePath("../media/YouLose.bmp");
	spr_gameDraw.SetFilePath("../media/GameDraw.bmp");
	spr_boxSprite.SetFilePath("../media/Box.bmp");
	spr_circleSprite.SetFilePath("../media/BoxCircle.bmp");
	spr_crossSprite.SetFilePath("../media/BoxCross.bmp");

	SpawnGrid();

	// 10, spawn game object to show player turn
	GO = Spawn(Vector2(420.0f, 500.0f), 0.0f, Vector2(3.0f, 0.35f));

	SetGameState(STATE_WAITGAME);

	UpdateTurnSprite();
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
