#include "TripWire.h"
#include "..\SGD Wrappers\SGD_Event.h"


TripWire::TripWire()
{
}


TripWire::~TripWire()
{
}

void TripWire::Update(float elapsedTime)
{

}

void TripWire::Render(void)
{
	SGD::Rectangle rect = GetRect();
	rect.top -= Game::GetInstance()->GetCameraPosition().y;
	rect.left -= Game::GetInstance()->GetCameraPosition().x;
	rect.bottom -= Game::GetInstance()->GetCameraPosition().y;
	rect.right -= Game::GetInstance()->GetCameraPosition().x;

	SGD::GraphicsManager::GetInstance()->DrawRectangle(rect, SGD::Color{ 255, 255, 0, 255 });
}

SGD::Rectangle TripWire::GetRect(void)	const
{
	SGD::Rectangle rect = { GetPosition(), GetSize() };
	return rect;
}

void TripWire::HandleCollision(IEntity* pOther)
{
	if (pOther->GetType() == ENT_FATHER || pOther->GetType() == ENT_SON)
	{
		SGD::Event* event = new SGD::Event("TripWire", nullptr, this);
		event->QueueEvent();
	}
}

//void TripWire::HandleEvent(const SGD::Event* pEvent)
//{
//
//
//}
