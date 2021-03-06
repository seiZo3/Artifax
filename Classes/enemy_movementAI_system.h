#ifndef _ENEMY_MOVEMENT_AI_SYSTEM_H__
#define _ENEMY_MOVEMENT_AI_SYSTEM_H__

#include <functional>
#include <map>
#include <math.h>
#include "cocos2d.h"
#include "entityx/entityx.h"
#include "components.h"
#include "constants.h"

USING_NS_CC;
using namespace entityx;

namespace PathFunctions
{
    //static float w = Director::getInstance()->getWinSize().width;
	//static float h = Director::getInstance()->getWinSize().height;

	static float const side1(float x)
	{
		auto winSize = Director::getInstance()->getWinSize();
		float e = M_E;
		float coeff = (x * 6.5f) / winSize.width;
		return pow(e, coeff) + (winSize.height / 2);
	}

	static float const cos1(float x)
	{
		auto winSize = Director::getInstance()->getWinSize();
		return (winSize.height / 2.f - 60.f) * cosf((x * 10) / winSize.width) + winSize.height / 2;
	}

	static float const straight_mid1(float x)
	{
		auto winSize = Director::getInstance()->getWinSize();
		return (winSize.height / 100) * sinf((x * 70) / winSize.width) + winSize.height / 2;
	}

	static float const sin1(float x)
	{
		auto winSize = Director::getInstance()->getWinSize();
		return ((winSize.height / 2) - 60) * sinf((x * 10) / winSize.width - M_PI / 2) + winSize.height / 2;
	}

	static float const sin2(float x)
	{
		auto winSize = Director::getInstance()->getWinSize();
		return ((winSize.height / 2) - 60) * sinf((x*25) / winSize.width) + winSize.height / 2;
	}
    
    static float const hill1(float x)
    {
        auto winSize = Director::getInstance()->getWinSize();
        return (winSize.height * 0.33) * pow(M_E, sinf((x*10) / winSize.width));
    }
}


//because c++ does not support reflection
static std::map<std::string, EnemyPath> enemyPathMap =
{
	{ "cos1", EnemyPath(PathType::FUNCTION, PathFunctions::cos1) },
	{ "sin1", EnemyPath(PathType::FUNCTION, PathFunctions::sin1) },
	{ "side1", EnemyPath(PathType::FUNCTION, PathFunctions::side1) },
	{ "straight_mid1", EnemyPath(PathType::FUNCTION, PathFunctions::straight_mid1) },
	{ "sin2", EnemyPath(PathType::FUNCTION, PathFunctions::sin2) },
    { "hill1", EnemyPath(PathType::FUNCTION, PathFunctions::hill1) }
};

class EnemyMovementAISystem : public entityx::System < EnemyMovementAISystem >
{
public:
	void configure(EventManager &events);
	void update(EntityManager &es, EventManager &events, double dt) override;
};

#endif