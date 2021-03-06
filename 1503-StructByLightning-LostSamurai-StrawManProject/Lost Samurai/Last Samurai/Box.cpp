#include "Box.h"


Box::Box()
{
}


Box::~Box()
{
}

void Box::CalculateVelocity(SGD::Vector v)
{
	if (isHeavy)
		SetVelocity({ v.x *2 ,v.y}) ;
	else
		SetVelocity({ v.x*2, v.y });

}

void Box::Update(float elapsedTime)
{
	if (!GetIsTriggered())
		m_vtVelocity.y = 500.0f;
	else
		m_vtVelocity.y = 0.0f;

	if (GetHeavy())
		SetWeight(100.0f);
	else
		SetWeight(50.0f);


	Actor::Update(elapsedTime);
	SetVelocity({ 0.0, 0.0 });
	SetTriggered(false);
}

void Box::Render(void)
{
	/*SGD::Rectangle rect = GetRect();
	rect.top -= Game::GetInstance()->GetCameraPosition().y;
	rect.left -= Game::GetInstance()->GetCameraPosition().x;
	rect.bottom -= Game::GetInstance()->GetCameraPosition().y;
	rect.right -= Game::GetInstance()->GetCameraPosition().x;

	SGD::GraphicsManager::GetInstance()->DrawRectangle(rect, SGD::Color{ 255, 0, 255, 0 });*/
	SGD::Point pt = GetPosition();
	pt.x -= Game::GetInstance()->GetCameraPosition().x;
	pt.y -= Game::GetInstance()->GetCameraPosition().y;
	SGD::GraphicsManager::GetInstance()->DrawTexture(GetImage(), pt);
}
SGD::Rectangle Box::GetRect(void)	const
{
	SGD::Rectangle rect = { GetPosition(), GetSize() };
	 return rect;
}
void Box::HandleCollision(IEntity* pOther)
{
	if (pOther->GetType() == ENT_TILES)
	{
		SetTriggered(true);
	}
}