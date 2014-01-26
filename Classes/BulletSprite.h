//
//  BulletSprite.h
//  SpaceGame
//
//  Created by GCREST on 2014/01/24.
//
//

#ifndef __SpaceGame__BulletSprite__
#define __SpaceGame__BulletSprite__

#include "cocos2d.h"

class BulletSprite    : public cocos2d::CCSprite
{
public:
    BulletSprite();
    virtual ~BulletSprite();
    
    bool initWithFileName(const char* pszFileName);
    
public:
    static BulletSprite* createBullet(const char* filename);
    static BulletSprite* createWithSpriteFrameName(const char* filename, int numFrames=0);
    
private:
    bool    _flag;
};


#endif /* defined(__SpaceGame__BulletSprite__) */
