#include "GameplayState.h"
#include"Father.h"
#include "Game.h"
#include "Son.h"
#include "Actor.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_Message.h"
#include"MainMenuState.h"
#include "Message.h"
#include "EntityManager.h"
#include"../Last Samurai/TileSystem.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_Geometry.h"
GameplayState* GameplayState::GetInstance()
{
	static GameplayState m_Instance;
	return &m_Instance;
}

Actor* GameplayState::CreateFather(void)
{
		Player* father = new Father;
		father->SetPosition(SGD::Point{ 100.0f, 480.0f });
		father->SetAlive(true);
		father->SetImage(m_FatherImage);
		father->SetSize(SGD::Size{ -1.5f,1.5f });
		father->SetVelocity({ 0.0f, 0.0f });
		return father;
}

Actor* GameplayState::CreateSon(void)
{
	Player* son = new Son;
	son->SetPosition(SGD::Point{ 700.0f, 540.0f });
	son->SetAlive(true);
	son->SetImage(m_FatherImage);
	son->SetSize(SGD::Size{ -0.75f, 0.75f });
	son->SetVelocity({ 0.0f, 0.0f });
	return son;
}
void GameplayState::Enter()
{
	m_FatherImage = SGD::GraphicsManager::GetInstance()->LoadTexture("../resource/graphics/Father.png");
	m_pEntities = new EntityManager;
	father = CreateFather();
	m_pEntities->AddEntity(father, 0);
	son = CreateSon();
	m_pEntities->AddEntity(son, 1);
//	Game::GetInstance()->SetCameraPosition({ father->GetPosition().x, father->GetPosition().y });
	Load = new TileSystem();
	Load->LoadTileXml();
}


void GameplayState::Exit()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_FatherImage);
	father->Release();
	father = nullptr;
	son->Release();
	son = nullptr;
	if (m_pEntities != nullptr)
	{
		m_pEntities->RemoveAll();
		delete m_pEntities;
		m_pEntities = nullptr;
		delete Load;
	}
}

bool GameplayState::Update(float _ElapsedTime)
{
	

	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Escape))
	{
		Game::GetInstance()->ChangeState(MainMenuState::GetInstance());
		return true;
	}
	
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::J))
	{
		if (dynamic_cast<Father*>(father)->GetCurrCharacter())
		{
			if (dynamic_cast<Son*>(son)->GetBackPack())
			{
				dynamic_cast<Son*>(son)->SetPosition(SGD::Point{ dynamic_cast<Father*>(father)->GetPosition().x-16.0f, dynamic_cast<Father*>(father)->GetPosition().y-16.0f });
				dynamic_cast<Son*>(son)->SetBackPack(false);
				dynamic_cast<Father*>(father)->SetBackPack(false);
			}
			dynamic_cast<Father*>(father)->SetCurrCharacter(false);
			dynamic_cast<Son*>(son)->SetCurrCharacter(true);
		}
		else if (dynamic_cast<Son*>(son)->GetCurrCharacter())
		{
			dynamic_cast<Father*>(father)->SetCurrCharacter(true);
			dynamic_cast<Son*>(son)->SetCurrCharacter(false);
			if (dynamic_cast<Son*>(son)->GetPosition().y!=540)
			{
				dynamic_cast<Son*>(son)->SetPosition(SGD::Point{ dynamic_cast<Father*>(father)->GetPosition().x-16.0f, 540 });//16.0 because while backack i had to reset the x
			}
			
		}
	}
	
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::K) && dynamic_cast<Father*>(father)->GetCurrCharacter() && !dynamic_cast<Father*>(father)->GetBackPack())
	{
		m_pEntities->CheckCollisions(0, 1);
	}

	m_pEntities->UpdateAll(_ElapsedTime);

	if (dynamic_cast<Father*>(father)->GetCurrCharacter())
	{
		Game::GetInstance()->SetCameraPosition(SGD::Point{ father->GetPosition().x - Game::GetInstance()->GetScreenSize().width / 2, father->GetPosition().y - Game::GetInstance()->GetScreenSize().height / 2 });

	}
	else if (dynamic_cast<Son*>(son)->GetCurrCharacter())
	{
		Game::GetInstance()->SetCameraPosition(SGD::Point{ son->GetPosition().x - Game::GetInstance()->GetScreenSize().width / 2, son->GetPosition().y - Game::GetInstance()->GetScreenSize().height / 2 });

	}

	//reset son after backpacing is activated
	if (dynamic_cast<Father*>(father)->GetBackPack())
	{
		dynamic_cast<Son*>(son)->SetFacing(dynamic_cast<Father*>(father)->GetFacing());
		dynamic_cast<Son*>(son)->SetPosition(SGD::Point{ dynamic_cast<Father*>(father)->GetPosition().x - 16.0f, dynamic_cast<Father*>(father)->GetPosition().y - 16.0f });
	}
		
	return true;
}


void GameplayState::Render(float _ElapsedTime)
{


	for (int X = 0; X < Load->m_Grid->m_GridWidth; X++)
	{
		for (int Y = 0; Y < Load->m_Grid->m_GridHeight; Y++)
		{
			SGD::Rectangle DestinationRectangle;
			DestinationRectangle.top = X * Load->m_Tile->m_TileWidth;
			DestinationRectangle.left = Y * Load->m_Tile->m_TileHeight;
			DestinationRectangle.right = DestinationRectangle.left + Load->m_Grid->m_GridWidth;
			DestinationRectangle.bottom = DestinationRectangle.top + Load->m_Grid->m_GridHeight;
			//SGD::GraphicsManager::GetInstance()->DrawRectangle(DestinationRectangle, SGD::Color{ 255, 0, 255, 255 }, SGD::Color{ 255, 255, 0, 0 }, 5);

			SGD::Rectangle SourceRectangle;
			SourceRectangle.left = Load->Map[X][Y]->m_TileID % (int)(Load->Map[X][Y]->m_Image.width / Load->Map[X][Y]->m_TileWidth) * Load->Map[X][Y]->m_TileWidth;
			SourceRectangle.top = Load->Map[X][Y]->m_TileID / (int)(Load->Map[X][Y]->m_Image.height / Load->Map[X][Y]->m_TileHeight) * Load->Map[X][Y]->m_TileHeight;


			SourceRectangle.right = SourceRectangle.left + Load->Map[X][Y]->m_TileHeight;
			SourceRectangle.bottom = SourceRectangle.top + Load->Map[X][Y]->m_TileWidth;
			SGD::GraphicsManager::GetInstance()->DrawTextureSection(Load->GetTileImage(), SGD::Point{ ((float)X * Load->Map[X][Y]->m_TileWidth - Game::GetInstance()->GetScreenSize().width / 2) - Game::GetInstance()->GetCameraPosition().x, (float)Y * Load->Map[X][Y]->m_TileHeight  - Game::GetInstance()->GetCameraPosition().y }, SourceRectangle);
			//SGD::GraphicsManager::GetInstance()->DrawTextureSection(Load->GetTileImage(), SGD::Point{ 0, 0}, SGD::Rectangle(Load->Map[X][Y]->m_TileID % (512 / Load->m_Tile->m_TileWidth), Load->Map[X][Y]->m_TileID % (512 / Load->m_Tile->m_TileWidth), 32, 32));


		}
	}
	m_pEntities->RenderAll();
}
void GameplayState::MessageProc(const SGD::Message* pMsg)
{
	/* Show warning when a Message ID enumerator is not handled */
#pragma warning( push )
#pragma warning( 1 : 4061 )


	// What type of message?
	switch (pMsg->GetMessageID())
	{
	case MessageID::MSG_BACKPACK:
		SGD_PRINT(L"BackPack Done");
		break;
	case MessageID::MSG_UNKNOWN:
		SGD_PRINT(L"GameplayState::MessageProc - unknown message id\n");
		break;
	default:
		break;
	}


	/* Restore previous warning levels */
#pragma warning( pop )
}
