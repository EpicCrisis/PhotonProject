
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
	mousePos[1] = y;
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
					
				if (!isMark && alignArray[k] == 0)
				{
					if (playerTurn == 0 && currentPlayer == 1)
					{
						FindGameObject(k).SetSprite(circleSprite);
						GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
						alignArray[k] = 1;

						packer->Pack(alignArray[k], 8);
						isMark = true;
					}
					else if (playerTurn == 1 && currentPlayer == 2)
					{
						FindGameObject(k).SetSprite(crossSprite);
						GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
						alignArray[k] = 2;

						packer->Pack(alignArray[k], 8);
						isMark = true;
					}
				}
			}
		}
	}

	// Make sure there is a mark before switching player.
	if (isMark)
	{
		CheckPlayerWin();

		++playerTurn;
		if (playerTurn % 2 == 0)
		{
			playerTurn = 0;
		}
		isMark = false;

		UpdatePlayerTurn();
		PackData();
	}
}

void Application::CheckPlayerWin()
{
	//for (int i = 0; i < 9; ++i)
	//{
	//	for (int j = 0; j < 9; ++j)
	//	{
	//		if (
	//			alignArray[i] == 1 || alignArray[j] == 1 ||
	//			alignArray[0] == 1 && alignArray[4] == 1 && alignArray[8] == 1 ||
	//			alignArray[2] == 1 && alignArray[4] == 1 && alignArray[6] == 1
	//			)
	//		{
	//			if (currentPlayer == 1 && playerTurn == 0 ||
	//				currentPlayer == 2 && playerTurn == 1)
	//			{
	//				// always last to spawn
	//				GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
	//				GO->GetSprite().SetFilePath("../media/YouWin.bmp");
	//				GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
	//
	//				std::cout << "YOU WIN!" << std::endl;
	//			}
	//		}
	//		else if (
	//			alignArray[i] == 2 || alignArray[j] == 2 ||
	//			alignArray[0] == 2 && alignArray[4] == 2 && alignArray[8] == 2 ||
	//			alignArray[2] == 2 && alignArray[4] == 2 && alignArray[6] == 2
	//			)
	//		{
	//			if (currentPlayer == 1 && playerTurn == 1 ||
	//				currentPlayer == 2 && playerTurn == 0)
	//			{
	//				// always last to spawn
	//				GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
	//				GO->GetSprite().SetFilePath("../media/YouLose.bmp");
	//				GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
	//
	//				std::cout << "YOU LOSE!" << std::endl;
	//			}
	//
	//			SetGameState(STATE_GAMEOVER);
	//		}
	//		else if (
	//			alignArray[i] != 0 || alignArray[j] != 0 ||
	//			alignArray[0] != 0 && alignArray[4] != 0 && alignArray[8] != 0 ||
	//			alignArray[2] != 0 && alignArray[4] != 0 && alignArray[6] != 0
	//			)
	//		{
	//			GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
	//			GO->GetSprite().SetFilePath("../media/GameDraw.bmp");
	//			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
	//
	//			std::cout << "Game Draw!" << std::endl;
	//			SetGameState(STATE_GAMEOVER);
	//		}
	//	}
	//}

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
		if (currentPlayer == 1 && playerTurn == 0 ||
			currentPlayer == 2 && playerTurn == 1)
		{
			// always last to spawn
			GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
			GO->GetSprite().SetFilePath("../media/YouWin.bmp");
			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

			std::cout << "YOU WIN!" << std::endl;
		}
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
		if (currentPlayer == 1 && playerTurn == 1 ||
			currentPlayer == 2 && playerTurn == 0)
		{
			// always last to spawn
			GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
			GO->GetSprite().SetFilePath("../media/YouLose.bmp");
			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

			std::cout << "YOU LOSE!" << std::endl;
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
		GO->GetSprite().SetFilePath("../media/GameDraw.bmp");
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
			GO->GetSprite().SetFilePath("../media/Box.bmp");
			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
		}
	}
	// 9
	GO = Spawn(Vector2(60.0f, 550.0f), 0.0f, Vector2(1.0f, 1.0f));
	GO->GetSprite().SetFilePath("../media/TicTacToeTitle.bmp");
	GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
}

void Application::UpdatePlayerTurn()
{
	if (currentPlayer == 1 && playerTurn == 0 ||
		currentPlayer == 2 && playerTurn == 1)
	{
		// 10, will change between sprites!
		FindGameObject(10).GetSprite().SetFilePath("../media/YourTurn.bmp");
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
	}
	else if (currentPlayer == 1 && playerTurn == 1 ||
			currentPlayer == 2 && playerTurn == 0)
	{
		// 10, will change between sprites!
		FindGameObject(10).GetSprite().SetFilePath("../media/OtherTurn.bmp");
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
	}
	else if (GetGameState() == STATE_WAITGAME)
	{
		// 10, will change between sprites!
		FindGameObject(10).GetSprite().SetFilePath("../media/OtherTurn.bmp");
	}
}

void Application::PackData()
{
	//for (int i = 0; i < 9; ++i)
	//{

	//	//unsigned int value = packer->Extract(32);

	//	//std::cout << "Extract Value " << value << std::endl;
	//}

	packer->Pack(alignArray[1], 32);

	std::cout << "Pack Value " << packer->GetData() << std::endl;

	unsigned int value = packer->Extract(32);

	std::cout << "Extract Value " << value << std::endl;
}

void Application::SetCurrentPlayer(int player)
{
	currentPlayer = player;
	std::cout << currentPlayer << std::endl;
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

	boxSprite.SetFilePath("../media/Box.bmp");
	circleSprite.SetFilePath("../media/BoxCircle.bmp");
	crossSprite.SetFilePath("../media/BoxCross.bmp");

	SpawnGrid();

	// 10, spawn game object to show player turn
	GO = Spawn(Vector2(420.0f, 500.0f), 0.0f, Vector2(3.0f, 0.35f));

	SetGameState(STATE_WAITGAME);

	UpdatePlayerTurn();
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
