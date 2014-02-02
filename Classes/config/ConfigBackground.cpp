//
//  ConfigBackground.cpp
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#include "ConfigBackground.h"
#include "DictUtil.h"
#include "cocos2d.h"

USING_NS_CC;

ConfigBackground::ConfigBackground(CCDictionary *dict)
{
    if (dict)
    {
        setup(dict);
    }
}

ConfigBackground::~ConfigBackground()
{
    CC_SAFE_RELEASE(img);
}

void ConfigBackground::setup(CCDictionary* dict)
{
     bgId = DictUtil::getIntForKey(dict, "id");
     img = new CCString(dict->valueForKey("img")->getCString());
     ztag = DictUtil::getIntForKey(dict, "ztag");
     scale = DictUtil::getFloatForKey(dict, "scale");
     ratio.x = DictUtil::getFloatForKey(dict, "rx");
     ratio.y = DictUtil::getFloatForKey(dict, "ry");
     offset.x = DictUtil::getFloatForKey(dict, "offsx");
     offset.y = DictUtil::getFloatForKey(dict, "offsy");
}
