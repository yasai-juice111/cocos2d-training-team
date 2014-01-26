//
//  GameTitleScene.h
//  SpaceGame
//
//  Created by GCREST on 2014/01/24.
//
//

#ifndef __SpaceGame__GameTitleScene__
#define __SpaceGame__GameTitleScene__

#include "cocos2d.h"

class GameTitleScene : public cocos2d::CCLayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

    // implement the "static node()" method manually
    CREATE_FUNC(GameTitleScene);
};

#endif /* defined(__SpaceGame__GameTitleScene__) */
