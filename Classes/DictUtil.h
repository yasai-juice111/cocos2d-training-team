//
//  DictUtil.h
//  cocos2dx-space-game
//
//  Created by CyberAgent on H.26/02/02.
//
//

#ifndef __cocos2dx_space_game__DictUtil__
#define __cocos2dx_space_game__DictUtil__

#include "cocos2d.h"

class DictUtil
{
public:
    static cocos2d::CCDictionary* cstrToDictionary(const char* chrs);
    static int getIntForKey(cocos2d::CCDictionary* dict, const std::string& keyId);
    static float getFloatForKey(cocos2d::CCDictionary* dict, const std::string& keyId);
    
};

#endif /* defined(__cocos2dx_space_game__DictUtil__) */
