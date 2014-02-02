//
//  TimeUtils.cpp
//  SpaceGame
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#include "TimeUtils.h"
#include "cocos2d.h"

double TimeUtils::getMSecTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000.0+tv.tv_usec/1000.0;
}

double TimeUtils::getTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)(tv.tv_sec) + (double)((tv.tv_usec)* 0.001 * 0.001);
}

