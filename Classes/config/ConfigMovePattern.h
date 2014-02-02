//
//  ConfigMovePattern.h
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#ifndef __cocos2dx_space_game__ConfigMovePattern__
#define __cocos2dx_space_game__ConfigMovePattern__

#include "cocos2d.h"

class ConfigMovePattern
{
public:
    ConfigMovePattern(cocos2d::CCDictionary* dict);
    virtual ~ConfigMovePattern();
    virtual void setup(cocos2d::CCDictionary* dict);
    
public:
    float       x;
    float       y;
    float       speed;
};

#endif /* defined(__cocos2dx_space_game__ConfigMovePattern__) */
