//
//  JSONToDictConverter.cpp
//  cocos2dx-space-game
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#include "JSONToDictConverter.h"
#include "cocos2d.h"
#include "cocos-ext.h"

#include "spine/Json.h"

USING_NS_CC;
USING_NS_CC_EXT;


CCDictionary * JSONToDictConverter::queryDictionary(const char * jsonStr)
{
    return JSONToDictConverter::dictWithJson(Json_create(jsonStr));
}

CCDictionary *JSONToDictConverter::dictWithJson(Json *pJson)
{
    if (pJson == NULL)
        return NULL;
    
    CCObject *obj = parseValue(pJson);
    if (!pJson->name)
    {
        return (CCDictionary *)obj;
    }

    CCDictionary *pRet = CCDictionary::create();
    if (obj)
    {
        pRet->setObject(obj, pJson->name);
    }
    return pRet;
}

CCObject *JSONToDictConverter::parseObject(Json *pJson)
{
    CCDictionary *root = CCDictionary::create();
    for (Json *item = pJson; item; item = item->next)
    {
        CCObject *value = parseValue(item);
        if (value)
            root->setObject(value, item->name);
    }
    return root;
}

CCArray *JSONToDictConverter::parseArray(Json *pJson)
{
    int arrayLength = Json_getSize(pJson);
    CCArray *array = CCArray::create();
    for (int i = 0; i < arrayLength; i++)
    {
        Json *item = Json_getItemAt(pJson, i);
        CCObject *object = parseValue(item);
        if (object)
            array->addObject(object);
    }
    return array;
}

CCObject *JSONToDictConverter::parseValue(Json *pJsonValue)
{
    if (!pJsonValue) {return NULL;}
    CCObject *object = NULL;
    switch (pJsonValue->type)
    {
        case Json_False:
            object = CCBool::create(false);
            break;
        case Json_True:
            object = CCBool::create(true);
            break;
        case Json_NULL:
            object = NULL;
            break;
        case Json_Number:
            object = CCFloat::create(pJsonValue->valuefloat);
            break;
        case Json_String:
            if (pJsonValue->valuestring)
                object = CCString::create(pJsonValue->valuestring);
            break;
        case Json_Array:
            object = parseArray(pJsonValue);
            break;
        case Json_Object:
            object = parseObject(pJsonValue->child);
            break;
        default:
            object = NULL;
            break;
    }
    return object;
}
