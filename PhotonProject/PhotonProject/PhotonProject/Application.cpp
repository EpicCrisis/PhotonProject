
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
	/*for (int k = 0; k < 9; ++k)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				boxCoords[k].x = 300.0f + (j * offset);
				boxCoords[k].y = 400.0f + (i * -offset);

				if (mousePos[0] >= boxCoords[k].x - halfBoxSize && mousePos[0] <= boxCoords[k].x + halfBoxSize &&
					mousePos[1] >= boxCoords[k].y - halfBoxSize && mousePos[1] <= boxCoords[k].y + halfBoxSize)
				{
					std::cout << "Click on box" << std::endl;
					FindGameObject(k).SetSprite(circleSprite);
				}
			}
		}
	}*/

	// Check position, check player turn, check have marked, check array align, check win.
	if (mousePos[0] >= 300.0f + (0 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (0 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (0 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (0 * -offset) + halfBoxSize)
	{
		if (!isMark && !markArray[0])
		{
			if (playerTurn == 0)
			{
				FindGameObject(0).SetSprite(circleSprite);
				GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
				alignArray[0] = 1;
			}
			else
			{
				FindGameObject(0).SetSprite(crossSprite);
				alignArray[0] = 2;
			}
			isMark = true;
			markArray[0] = true;
		}
	}
	else if (mousePos[0] >= 300.0f + (1 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (1 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (0 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (0 * -offset) + halfBoxSize)
	{
		if (!isMark && !markArray[1])
		{
			if (playerTurn == 0)
			{
				FindGameObject(1).SetSprite(circleSprite);
				alignArray[1] = 1;
			}
			else
			{
				FindGameObject(1).SetSprite(crossSprite);
				alignArray[1] = 2;
			}
			isMark = true;
			markArray[1] = true;
		}
	}
	else if (mousePos[0] >= 300.0f + (2 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (2 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (0 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (0 * -offset) + halfBoxSize)
	{
		if (!isMark && !markArray[2])
		{
			if (playerTurn == 0)
			{
				FindGameObject(2).SetSprite(circleSprite);
				alignArray[2] = 1;
			}
			else
			{
				FindGameObject(2).SetSprite(crossSprite);
				alignArray[2] = 2;
			}
			isMark = true;
			markArray[2] = true;
		}
	}
	else if (mousePos[0] >= 300.0f + (0 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (0 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (1 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (1 * -offset) + halfBoxSize)
	{
		if (!isMark && !markArray[3])
		{
			if (playerTurn == 0)
			{
				FindGameObject(3).SetSprite(circleSprite);
				alignArray[3] = 1;
			}
			else
			{
				FindGameObject(3).SetSprite(crossSprite);
				alignArray[3] = 2;
			}
			isMark = true;
			markArray[3] = true;
		}
	}
	else if (mousePos[0] >= 300.0f + (1 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (1 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (1 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (1 * -offset) + halfBoxSize)
	{
		if (!isMark && !markArray[4])
		{
			if (playerTurn == 0)
			{
				FindGameObject(4).SetSprite(circleSprite);
				alignArray[4] = 1;
			}
			else
			{
				FindGameObject(4).SetSprite(crossSprite);
				alignArray[4] = 2;
			}
			isMark = true;
			markArray[4] = true;
		}
	}
	else if (mousePos[0] >= 300.0f + (2 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (2 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (1 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (1 * -offset) + halfBoxSize)
	{
		if (!isMark && !markArray[5])
		{
			if (playerTurn == 0)
			{
				FindGameObject(5).SetSprite(circleSprite);
				alignArray[5] = 1;
			}
			else
			{
				FindGameObject(5).SetSprite(crossSprite);
				alignArray[5] = 2;
			}
			isMark = true;
			markArray[5] = true;
		}
	}
	else if (mousePos[0] >= 300.0f + (0 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (0 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (2 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (2 * -offset) + halfBoxSize)
	{
		if (!isMark && !markArray[6])
		{
			if (playerTurn == 0)
			{
				FindGameObject(6).SetSprite(circleSprite);
				alignArray[6] = 1;
			}
			else
			{
				FindGameObject(6).SetSprite(crossSprite);
				alignArray[6] = 2;
			}
			isMark = true;
			markArray[6] = true;
		}
	}
	else if (mousePos[0] >= 300.0f + (1 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (1 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (2 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (2 * -offset) + halfBoxSize)
	{
		if (!isMark && !markArray[7])
		{
			if (playerTurn == 0)
			{
				FindGameObject(7).SetSprite(circleSprite);
				alignArray[7] = 1;
			}
			else
			{
				FindGameObject(7).SetSprite(crossSprite);
				alignArray[7] = 2;
			}
			isMark = true;
			markArray[7] = true;
		}
	}
	else if (mousePos[0] >= 300.0f + (2 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (2 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (2 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (2 * -offset) + halfBoxSize)
	{
		if (!isMark && !markArray[8])
		{
			if (playerTurn == 0)
			{
				FindGameObject(8).SetSprite(circleSprite);
				alignArray[8] = 1;
			}
			else
			{
				FindGameObject(8).SetSprite(crossSprite);
				alignArray[8] = 2;
			}
			isMark = true;
			markArray[8] = true;
		}
	}

	// Make sure there is a mark before switching player.
	if (isMark)
	{
		++playerTurn;
		if (playerTurn % 2 == 0)
		{
			playerTurn = 0;
		}
		isMark = false;

		CheckPlayerWin();
		UpdatePlayerTurn();
		PackData();
	}
}

void Application::CheckPlayerWin()
{
	if (// horizontal win
		alignArray[0] == 1 && alignArray[1] == 1 && alignArray[2] == 1 ||
		alignArray[3] == 1 && alignArray[4] == 1 && alignArray[5] == 1 ||
		alignArray[6] == 1 && alignArray[7] == 1 && alignArray[8] == 1 ||
		// vertical win
		alignArray[0] == 1 && alignArray[3] == 1 && alignArray[6] == 1 ||
		alignArray[1] == 1 && alignArray[4] == 1 && alignArray[7] == 1 ||
		alignArray[2] == 1 && alignArray[5] == 1 && alignArray[8] == 1 ||
		// diagonal win
		alignArray[0] == 1 && alignArray[4] == 1 && alignArray[8] == 1 ||
		alignArray[2] == 1 && alignArray[4] == 1 && alignArray[6] == 1
		)
	{
		// always last to spawn
		GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
		GO->GetSprite().SetFilePath("../media/YouWin.bmp");
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

		std::cout << "YOU WIN!" << std::endl;

		isGameOver = true;
	}
	else if (// horizontal win
		alignArray[0] == 2 && alignArray[1] == 2 && alignArray[2] == 2 ||
		alignArray[3] == 2 && alignArray[4] == 2 && alignArray[5] == 2 ||
		alignArray[6] == 2 && alignArray[7] == 2 && alignArray[8] == 2 ||
		// vertical win
		alignArray[0] == 2 && alignArray[3] == 2 && alignArray[6] == 2 ||
		alignArray[1] == 2 && alignArray[4] == 2 && alignArray[7] == 2 ||
		alignArray[2] == 2 && alignArray[5] == 2 && alignArray[8] == 2 ||
		// diagonal win
		alignArray[0] == 2 && alignArray[4] == 2 && alignArray[8] == 2 ||
		alignArray[2] == 2 && alignArray[4] == 2 && alignArray[6] == 2
		)
	{
		// always last to spawn
		GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
		GO->GetSprite().SetFilePath("../media/YouLose.bmp");
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

		std::cout << "YOU LOSE!" << std::endl;

		isGameOver = true;
	}
	else if (// draw
		alignArray[0] != 0 && alignArray[1] != 0 && alignArray[2] != 0 &&
		alignArray[3] != 0 && alignArray[4] != 0 && alignArray[5] != 0 &&
		alignArray[6] != 0 && alignArray[7] != 0 && alignArray[8] != 0
		)
	{
		GO = Spawn(Vector2(420.0f, 50.0f), 0.0f, Vector2(3.0f, 0.5f));
		GO->GetSprite().SetFilePath("../media/GameDraw.bmp");
		GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

		std::cout << "Game Draw!" << std::endl;
		isGameOver = true;
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
	if (!isGameOver)
	{
		if (playerTurn == 0)
		{
			// 10, will change between sprites!
			FindGameObject(10).GetSprite().SetFilePath("../media/YourTurn.bmp");
			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
		}
		else if (playerTurn == 1)
		{
			// 10, will change between sprites!
			FindGameObject(10).GetSprite().SetFilePath("../media/OtherTurn.bmp");
			GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
		}
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
