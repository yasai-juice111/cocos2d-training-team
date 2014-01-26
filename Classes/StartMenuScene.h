//
//  StartMenuScene.h
//  SpaceGame
//
//  Created by shiramat on H.26/01/15.
//
//

#ifndef __SpaceGame__StartMenuScene__
#define __SpaceGame__StartMenuScene__

#include "cocos2d.h"

class StartMenuScene : public cocos2d::CCLayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuSelectGameLevel1(cocos2d::CCObject* pSender);
    void menuSelectGameLevel2(cocos2d::CCObject* pSender);
    void menuSelectGameLevel3(cocos2d::CCObject* pSender);
    void menuSelectGameLevel4(cocos2d::CCObject* pSender);
    void menuSelectGameLevel5(cocos2d::CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(StartMenuScene);
};

#endif /* defined(__SpaceGame__StartMenuScene__) */
