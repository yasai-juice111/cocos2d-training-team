//
//  ConfigEnemy.h
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#ifndef __cocos2dx_space_game__ConfigEnemy__
#define __cocos2dx_space_game__ConfigEnemy__

#include "cocos2d.h"

class ConfigEnemy
{
public:
    ConfigEnemy(cocos2d::CCDictionary* dict);
    virtual ~ConfigEnemy();
    virtual void setup(cocos2d::CCDictionary* dict);
    
public:
    int                 enemyId;
    cocos2d::CCString*  img;
    int                 numFrame;
    float               scale;
    int                 hp;
    int                 attackPoint;
};

#endif /* defined(__cocos2dx_space_game__ConfigEnemy__) */
