//
//  KWPlayer.h
//  cocos2dx-space-game
//
//  Created by kwst_mac on 2014/02/01.
//
//

#ifndef __cocos2dx_space_game__KWPlayer__
#define __cocos2dx_space_game__KWPlayer__

#include "PlayerShip.h"

class KWPlayer : public PlayerShip
{
public:
	KWPlayer();
	virtual ~KWPlayer();
public:
    static KWPlayer* createShip(const char* filename);
    static KWPlayer* createShipFrame(const char* filename, int numFrame);
private:
};

#endif /* defined(__cocos2dx_space_game__KWPlayer__) */
