//
//  ConfigEnemyPopData.h
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/03.
//
//

#ifndef __cocos2dx_space_game__ConfigEnemyPopData__
#define __cocos2dx_space_game__ConfigEnemyPopData__

#include "cocos2d.h"

class ConfigEnemyPopData
{
public:
    ConfigEnemyPopData(cocos2d::CCDictionary* dict);
    virtual ~ConfigEnemyPopData();
    virtual void setup(cocos2d::CCDictionary* dict);
    
public:
    float               time;
    int                 type;
    int                 moveIndex;
};

#endif /* defined(__cocos2dx_space_game__ConfigEnemyPopData__) */
