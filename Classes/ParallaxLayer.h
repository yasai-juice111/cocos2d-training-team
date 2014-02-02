//
//  ParallaxLayer.h
//  SpaceGame
//
//  Created by Shinji Hiramatsu on 2014/01/24.
//
//

#ifndef __SpaceGame__ParallaxLayer__
#define __SpaceGame__ParallaxLayer__

#include "cocos2d.h"

class ParallaxChildLayer;

class ParallaxLayer    : public cocos2d::CCNode
{
public:
    ParallaxLayer();
    virtual ~ParallaxLayer();
    
    void addChildLayer(const char* pzFileName, unsigned int z, float scale,
                       const cocos2d::CCPoint& ratio, const cocos2d::CCPoint& offset);
    
    void update(float t);
    
public:
    static ParallaxLayer* createLayer();
    
private:
    std::vector<ParallaxChildLayer*>  _parallaxList;
};

#endif /* defined(__SpaceGame__ParallaxLayer__) */
