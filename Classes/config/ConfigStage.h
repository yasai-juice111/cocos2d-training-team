//
//  ConfigStage.h
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#ifndef __cocos2dx_space_game__ConfigStage__
#define __cocos2dx_space_game__ConfigStage__

#include "cocos2d.h"

class ConfigStage
{
public:
    ConfigStage(cocos2d::CCDictionary* dict=NULL);
    virtual ~ConfigStage();
    virtual void setup(cocos2d::CCDictionary* dict);
    
public:
    
    
};

#endif /* defined(__cocos2dx_space_game__ConfigStage__) */
