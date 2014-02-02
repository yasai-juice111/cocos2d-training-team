//
//  ConfigBackground.h
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#ifndef __cocos2dx_space_game__ConfigBackground__
#define __cocos2dx_space_game__ConfigBackground__

#include "cocos2d.h"

class ConfigBackground
{
public:
    ConfigBackground(cocos2d::CCDictionary* dict=NULL);
    virtual ~ConfigBackground();
    virtual void setup(cocos2d::CCDictionary* dict);
    
public:
    int     bgId;
    cocos2d::CCString*  img;
    int     ztag;
    float   scale;
    cocos2d::CCPoint    ratio;
    cocos2d::CCPoint    offset;
};

#endif /* defined(__cocos2dx_space_game__ConfigBackground__) */
