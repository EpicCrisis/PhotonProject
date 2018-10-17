
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

	if (mousePos[0] >= 300.0f + (0 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (0 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (0 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (0 * -offset) + halfBoxSize)
	{
		if (playerTurn == 0)
		{
			FindGameObject(0).SetSprite(circleSprite);
		}
		else
		{
			FindGameObject(0).SetSprite(crossSprite);
		}
	}
	else if (mousePos[0] >= 300.0f + (1 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (1 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (0 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (0 * -offset) + halfBoxSize)
	{
		if (playerTurn == 0)
		{
			FindGameObject(1).SetSprite(circleSprite);
		}
		else
		{
			FindGameObject(1).SetSprite(crossSprite);
		}
	}
	else if (mousePos[0] >= 300.0f + (2 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (2 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (0 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (0 * -offset) + halfBoxSize)
	{
		if (playerTurn == 0)
		{
			FindGameObject(2).SetSprite(circleSprite);
		}
		else
		{
			FindGameObject(2).SetSprite(crossSprite);
		}
	}
	else if (mousePos[0] >= 300.0f + (0 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (0 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (1 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (1 * -offset) + halfBoxSize)
	{
		if (playerTurn == 0)
		{
			FindGameObject(3).SetSprite(circleSprite);
		}
		else
		{
			FindGameObject(3).SetSprite(crossSprite);
		}
	}
	else if (mousePos[0] >= 300.0f + (1 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (1 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (1 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (1 * -offset) + halfBoxSize)
	{
		if (playerTurn == 0)
		{
			FindGameObject(4).SetSprite(circleSprite);
		}
		else
		{
			FindGameObject(4).SetSprite(crossSprite);
		}
	}
	else if (mousePos[0] >= 300.0f + (2 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (2 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (1 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (1 * -offset) + halfBoxSize)
	{
		if (playerTurn == 0)
		{
			FindGameObject(5).SetSprite(circleSprite);
		}
		else
		{
			FindGameObject(5).SetSprite(crossSprite);
		}
	}
	else if (mousePos[0] >= 300.0f + (0 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (0 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (2 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (2 * -offset) + halfBoxSize)
	{
		if (playerTurn == 0)
		{
			FindGameObject(6).SetSprite(circleSprite);
		}
		else
		{
			FindGameObject(6).SetSprite(crossSprite);
		}
	}
	else if (mousePos[0] >= 300.0f + (1 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (1 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (2 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (2 * -offset) + halfBoxSize)
	{
		if (playerTurn == 0)
		{
			FindGameObject(7).SetSprite(circleSprite);
		}
		else
		{
			FindGameObject(7).SetSprite(crossSprite);
		}
	}
	else if (mousePos[0] >= 300.0f + (2 * offset) - halfBoxSize &&
		mousePos[0] <= 300.0f + (2 * offset) + halfBoxSize &&
		mousePos[1] >= 400.0f + (2 * -offset) - halfBoxSize &&
		mousePos[1] <= 400.0f + (2 * -offset) + halfBoxSize)
	{
		if (playerTurn == 0)
		{
			FindGameObject(8).SetSprite(circleSprite);
		}
		else
		{
			FindGameObject(8).SetSprite(crossSprite);
		}
	}

	// Make sure there is a mark before switching player.
	++playerTurn;
	if (playerTurn % 2 == 0)
	{
		playerTurn = 0;
	}
}

void Application::UpdateArray(int index)
{

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

	network->connect();

	boxSprite.SetFilePath("../media/Box.bmp");
	circleSprite.SetFilePath("../media/BoxCircle.bmp");
	crossSprite.SetFilePath("../media/BoxCross.bmp");

	SpawnGrid();

	// 10
	GO = Spawn(Vector2(0.0f, 0.0f), 0.0f, Vector2(0.5f, 0.5f));
	GO->GetSprite().SetFilePath("../media/CrosshairRed.bmp");
	GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);

	// 11
	GO = Spawn(Vector2(0.0f, 0.0f), 0.0f, Vector2(0.5f, 0.5f));
	GO->GetSprite().SetFilePath("../media/CrosshairBlue.bmp");
	GO->GetSprite().SetBlendingMode(BLEND_ADDITIVE);
}

void Application::Update(float deltaTime)
{
	time += deltaTime;

	// Set this to follow the mouse position
	Transform2D m_transform0;
	m_transform0 = FindGameObject(10).GetTransform();
	m_transform0.position =
		Vector2
		(
			mousePos[0], mousePos[1]
		);
	FindGameObject(10).SetTransform(m_transform0);

	// Set this to follow the OTHER mouse position
	Transform2D m_transform1;
	m_transform1 = FindGameObject(11).GetTransform();
	m_transform1.position =
		Vector2
		(
			network->cursorPos[0], network->cursorPos[1]
		);
	FindGameObject(11).SetTransform(m_transform1);

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
