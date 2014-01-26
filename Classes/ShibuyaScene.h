//
//  ShibuyaScene.h
//  cocos2dx-space-game
//
//  Created by cocos2d-x on 14/01/26.
//
//

#ifndef __cocos2dx_space_game__ShibuyaScene__
#define __cocos2dx_space_game__ShibuyaScene__

#include <iostream>
#include "cocos2d.h"
#include "StageScene.h"

class ShibuyaScene : public StageScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    virtual void update(float dt);

    // implement the "static node()" method manually
    CREATE_FUNC(ShibuyaScene);

    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
private:
    PlayerShip*  _playerShip;
    bool    _touchFlag;
    cocos2d::CCPoint _startTouchPos;
    cocos2d::CCPoint _lastTouchPos;
    cocos2d::CCPoint _moveShipPos;

};

#endif /* defined(__cocos2dx_space_game__ShibuyaScene__) */
