//
//  KawabataEnemy.h
//  cocos2dx-space-game
//
//  Created by kwst_mac on 2014/02/01.
//
//

#ifndef __cocos2dx_space_game__KawabataEnemy__
#define __cocos2dx_space_game__KawabataEnemy__

#include "EnemyShip.h"

class KawabataEnemy : public EnemyShip
{
public:
	KawabataEnemy();
	virtual ~KawabataEnemy();
	
	virtual void update(float dt);
	virtual void shotBullet();
	
public:
    static KawabataEnemy* createShip(const char* filename);
    static KawabataEnemy* createShipFrame(const char* filename, int numFrame);
};



#endif /* defined(__cocos2dx_space_game__KawabataEnemy__) */
