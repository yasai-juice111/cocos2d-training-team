//
//  ConfigEnemyPopData.cpp
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/03.
//
//

#include "ConfigEnemyPopData.h"
#include "DictUtil.h"
#include "cocos2d.h"

USING_NS_CC;

ConfigEnemyPopData::ConfigEnemyPopData(CCDictionary *dict)
{
    if (dict)
    {
        setup(dict);
    }
}

ConfigEnemyPopData::~ConfigEnemyPopData()
{
}

void ConfigEnemyPopData::setup(CCDictionary* dict)
{
    time = DictUtil::getFloatForKey(dict, "t");
    type = DictUtil::getIntForKey(dict, "type");
    moveIndex = DictUtil::getIntForKey(dict, "mid");
}
