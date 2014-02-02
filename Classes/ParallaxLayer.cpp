//
//  ParallaxLayer.cpp
//  SpaceGame
//
//  Created by Shinji Hiramatsu on 2014/01/24.
//
//

#include "ParallaxLayer.h"
#include "ParallaxChildLayer.h"
#include "cocos2d.h"

USING_NS_CC;

ParallaxLayer::ParallaxLayer()  :
    CCNode()
{
    
}

ParallaxLayer::~ParallaxLayer()
{
    
}

ParallaxLayer* ParallaxLayer::createLayer()
{
    ParallaxLayer *pRet = new ParallaxLayer();
    pRet->autorelease();
    return pRet;
}


void ParallaxLayer::addChildLayer(const char* pzFileName, unsigned int z, float scale,
                                  const cocos2d::CCPoint& ratio, const cocos2d::CCPoint& offset)
{
    ParallaxChildLayer* childLayer = new ParallaxChildLayer();
    childLayer->initWithData(pzFileName, z, scale, ratio, offset, this);
    childLayer->setScale(scale);
    childLayer->setAnchorPoint(ccp(0, 0));
    
    _parallaxList.push_back(childLayer);
}


void ParallaxLayer::update(float dt)
{
    CCPoint backgroundScrollVert = ccp(-640,0);
    CCPoint movePt = ccpAdd(this->getPosition(), ccpMult(backgroundScrollVert, dt));
//    this->setPosition(ccpAdd(this->getPosition(), ccpMult(backgroundScrollVert, dt)));

    std::vector<ParallaxChildLayer *>::iterator iter = _parallaxList.begin();
    while (iter != _parallaxList.end())
    {
        (*iter)->update(movePt);
        iter++;
    }
}
