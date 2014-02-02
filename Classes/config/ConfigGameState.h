//
//  ConfigGameState.h
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#ifndef __cocos2dx_space_game__ConfigGameState__
#define __cocos2dx_space_game__ConfigGameState__

#include "cocos2d.h"

class ConfigGameState
{
public:
    ConfigGameState(cocos2d::CCDictionary* dict=NULL);
    virtual ~ConfigGameState();
    virtual void setup(cocos2d::CCDictionary* dict);
    
public:
    
    
};

#endif /* defined(__cocos2dx_space_game__ConfigGameState__) */
