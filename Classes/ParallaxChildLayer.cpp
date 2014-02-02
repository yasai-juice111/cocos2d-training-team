//
//  ParallaxChildLayer.cpp
//  SpaceGame
//
//  Created by Shinji Hiramatsu on H.26/02/02.
//
//

#include "ParallaxChildLayer.h"
#include "cocos2d.h"

USING_NS_CC;


ParallaxChildLayer::ParallaxChildLayer()
{
    
}

ParallaxChildLayer::~ParallaxChildLayer()
{
    
}

void ParallaxChildLayer::initWithData(const char* pzFileName,
                                      unsigned int z, float scale,
                                     const cocos2d::CCPoint& ratio, const cocos2d::CCPoint& offset,
                                      cocos2d::CCNode* container)
{
    // 初期化
    _z = z;
    _scale = scale;
    _ratio = ratio;
    _offset = offset;
    
    // ベースとなる画像を追加
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* sprite = CCSprite::create(pzFileName);
    _childList.push_back(sprite);
    
    // 画面サイズにフィットする背景のスケーリングを取得
    _scale = winSize.width / sprite->getContentSize().width;
    
    sprite->setScale(_scale);
    sprite->setAnchorPoint(ccp(0,0));
    sprite->setPosition(_offset);
    container->addChild(sprite);
    
    float   width = sprite->getContentSize().width*_scale;
    int numContent = 2;
    if (winSize.width > width)
        numContent++;
    
    for (int i = 1; i < numContent; i++)
    {
        sprite = CCSprite::create(pzFileName);
        _childList.push_back(sprite);
        CCPoint     offs = _offset;
        offs.x = width*i;
        sprite->setScale(_scale);
        sprite->setAnchorPoint(ccp(0,0));
        sprite->setPosition(ccp(_offset.x + width*i, _offset.y));
        container->addChild(sprite);
    }
}


void ParallaxChildLayer::update(CCPoint& movePt)
{
    int i = 0;
    std::vector<CCSprite *>::iterator iter = _childList.begin();
    while (iter != _childList.end())
    {
        CCSprite* sp = (CCSprite *)(*iter);
        if (sp)
        {
            sp->setPosition(ccp(sp->getPosition().x + (movePt.x * _ratio.x), sp->getPosition().y + (movePt.y * _ratio.y)));
            float   dispWidth = sp->getContentSize().width*_scale;
            float   rightPos = sp->getPosition().x + dispWidth;
            if (rightPos < 0)
            {
                sp->setPosition(ccp(sp->getPosition().x+dispWidth*_childList.size(), sp->getPosition().y));
            }
        }
        i++;
        iter++;
    }
}
