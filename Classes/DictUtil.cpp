//
//  DictUtil.cpp
//  cocos2dx-space-game
//
//  Created by CyberAgent on H.26/02/02.
//
//

#include "DictUtil.h"
#include "CCJSONConverter.h"
#include "cocos2d.h"
#include <typeinfo>

USING_NS_CC;

int DictUtil::getIntForKey(CCDictionary* dict, const std::string& keyId)
{
    int     value = 0;
    if (dict)
    {
        CCObject*   cobj = dict->objectForKey(keyId);
        if (cobj)
        {
            
            if (typeid(*cobj) == typeid(CCNumber))
            {
                CCNumber* numObj = (CCNumber *)cobj;
                value = numObj->getIntValue();
            }
            else if (typeid(*cobj) == typeid(CCString))
            {
                CCString*   numStr = (CCString *)cobj;
                value = numStr->intValue();
            }
            else
            {
                CCLOG("cobj != CCString && cobj == CCNumber");
            }
        }
    }
    return value;
}

float DictUtil::getFloatForKey(CCDictionary* dict, const std::string& keyId)
{
    float     value = 0;
    if (dict)
    {
        CCObject*   cobj = dict->objectForKey(keyId);
        if (cobj)
        {
            if (typeid(*cobj) == typeid(CCNumber))
            {
                CCNumber* numObj = (CCNumber *)cobj;
                value = numObj->getDoubleValue();
            }
            else if (typeid(*cobj) == typeid(CCString))
            {
                CCString*   numStr = (CCString *)cobj;
                value = numStr->floatValue();
            }
        }
    }
    return value;
}

