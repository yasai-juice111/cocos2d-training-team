//
//  ConfigPlayer.h
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#ifndef __cocos2dx_space_game__ConfigPlayer__
#define __cocos2dx_space_game__ConfigPlayer__

#include "cocos2d.h"

class ConfigPlayer
{
public:
    ConfigPlayer(cocos2d::CCDictionary* dict);
    virtual ~ConfigPlayer();
    virtual void setup(cocos2d::CCDictionary* dict);
    
public:
    cocos2d::CCString*  img;
    int                 numFrame;
    float               scale;
    int                 hp;
    int                 attackPoint;
};

#endif /* defined(__cocos2dx_space_game__ConfigPlayer__) */
