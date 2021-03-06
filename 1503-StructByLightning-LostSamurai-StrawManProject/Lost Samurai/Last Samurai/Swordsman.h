#pragma once
#include "Actor.h"
#include <vector>
#include "AnimationSystem.h"
#include "../SGD Wrappers/SGD_IListener.h"
#include "Player.h"
class Swordsman :
	public Actor, public SGD::IListener
{
public:
	Swordsman();
	~Swordsman();
	SGD::Point m_LeftMax = {};
	SGD::Point m_RightMax = {};

	void	Update(float elapsedTime);
	void	Render(void);
	int		GetType(void)	const				{ return ENT_SWORDSMAN; }
	SGD::Rectangle GetRect(void)	const;
	void	HandleCollision(IEntity* pOther);
	void SetDestination(float _dest){ destination = _dest; }
	float GetDestination(){ return destination; }
	bool toRight = true;
	bool toLeft = false;

	void SetTarget(Actor * _target){ m_Target = _target; }
	Actor * GetEnemyTarget(){ return m_Target; }
	void HandleEvent(const SGD::Event* pEvent);

private:
	int direction = 0;
	float frameswitch = 0.0f;
	float destination = 0.0f;
	bool m_facingRight = true;
	Actor* m_Target = nullptr;
	AnimationTimestamp m_Timestamp;
	bool Debug = false;
	//SGD::Point m_Original = m_ptPosition;
	bool isAlerted = false;
	float AlertTimer = 0.0f;
	float ChangeFaceTimer = 0.0f;
	SGD::Vector EnemyDistance = {};
	SGD::HTexture m_AlertedImage = SGD::INVALID_HANDLE;
};

