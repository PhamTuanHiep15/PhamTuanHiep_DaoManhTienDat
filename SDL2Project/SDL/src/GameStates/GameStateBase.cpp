#include "GameStateBase.h"
#include "GameStates/GSIntro.h"
#include "GameStates/GSMenu.h"
#include "GameStates/GSPlay.h"
#include "GameStates/GSOption.h"
#include "GameStates/GSCredit.h"
GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		//GSINTRO;
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		//GSMENU
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		//GSPLAY
		break;
	case StateType::STATE_OPTION:
		gs = std::make_shared<GSOption>();
		//GSOption
		break;
	case StateType::STATE_CREDIT:
		gs = std::make_shared<GSCredit>();
		//GSCredit
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}
