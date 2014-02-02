//
//  ConfigMovePattern.cpp
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#include "ConfigMovePattern.h"
#include "DictUtil.h"
#include "cocos2d.h"

USING_NS_CC;

ConfigMovePattern::ConfigMovePattern(CCDictionary *dict)
{
    if (dict)
    {
        setup(dict);
    }
}

ConfigMovePattern::~ConfigMovePattern()
{
}

void ConfigMovePattern::setup(CCDictionary* dict)
{
    x = DictUtil::getFloatForKey(dict, "x");
    y = DictUtil::getIntForKey(dict, "y");
    speed = DictUtil::getFloatForKey(dict, "s");
}
