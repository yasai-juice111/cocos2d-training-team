//
//  ConfigEnemy.cpp
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#include "ConfigEnemy.h"
#include "DictUtil.h"
#include "cocos2d.h"

USING_NS_CC;

ConfigEnemy::ConfigEnemy(CCDictionary *dict)
{
    if (dict)
    {
        setup(dict);
    }
}

ConfigEnemy::~ConfigEnemy()
{
    CC_SAFE_RELEASE(img);
}

void ConfigEnemy::setup(CCDictionary* dict)
{
    enemyId = DictUtil::getIntForKey(dict, "id");
    img = new CCString(dict->valueForKey("img")->getCString());
    numFrame = DictUtil::getIntForKey(dict, "numFrame");
    scale = DictUtil::getFloatForKey(dict, "scale");
    if (scale <= 0)
        scale = 1.0;
    hp = DictUtil::getIntForKey(dict, "hp");
    attackPoint = DictUtil::getIntForKey(dict, "attackPoint");
}
