#include "Lever.h"


Lever::Lever()
{
	m_Timestamp.SetCurrAnim("Lever");
	m_Timestamp.SetCurrFrame(0);
	m_Timestamp.SetElapsedTime(0);
	m_Timestamp.SetOwner(this);
}


Lever::~Lever()
{


}

void Lever::Update(float elapsedTime)
{
}

void Lever::Render(void)
{
	SGD::Rectangle rect = GetRect();
	rect.top -= Game::GetInstance()->GetCameraPosition().y;
	rect.left -= Game::GetInstance()->GetCameraPosition().x;
	rect.bottom -= Game::GetInstance()->GetCameraPosition().y;
	rect.right -= Game::GetInstance()->GetCameraPosition().x;
	SGD::Point pt = m_ptPosition;
	pt.x -= Game::GetInstance()->GetCameraPosition().x;
	pt.y -= Game::GetInstance()->GetCameraPosition().y;

	//SGD::GraphicsManager::GetInstance()->DrawRectangle(rect, SGD::Color{ 255, 255, 0, 255 });
	AnimationSystem::GetInstance()->Render(m_Timestamp, pt.x, pt.y, { -1, 1 });
}

SGD::Rectangle Lever::GetRect(void) const
{
	return AnimationSystem::GetInstance()->GetRect(m_Timestamp, m_ptPosition.x, m_ptPosition.y);
}

void Lever::HandleCollision(IEntity* pOther)
{
	if (pOther->GetType() == ENT_FATHER )
	{
		SGD::Event* event = new SGD::Event("Levers", nullptr, this);
		event->QueueEvent();
	}
	if (pOther->GetType() == ENT_SON)
	{
		SGD::Event* event = new SGD::Event("Levers", nullptr, this);
		event->QueueEvent();
	}
}
