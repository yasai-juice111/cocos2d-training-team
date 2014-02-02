//
//  JSONToDictConverter.h
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#ifndef __cocos2dx_space_game__JSONToDictConverter__
#define __cocos2dx_space_game__JSONToDictConverter__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "Json.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN

class JSONToDictConverter   : public CCObject
{
public:
    static CCDictionary * queryDictionary(const char * str);
   
private:
    static CCDictionary *dictWithJson(Json *pJson);
    static CCObject *parseObject(Json *pJson);
    static CCArray *parseArray(Json *pJson);
    static CCObject *parseValue(Json *pJson);

};

NS_CC_EXT_END

#endif /* defined(__cocos2dx_space_game__JSONToDictConverter__) */
