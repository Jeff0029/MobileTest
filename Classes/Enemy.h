//
//  Enemy.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-07.
//
//

#ifndef __ArcticTest__Enemy__
#define __ArcticTest__Enemy__

#include <stdio.h>
#include <cocos2d.h>
#include <iostream>

#include "TextureBank.h"
#include "Constants.h"

namespace ArcticTest
{
    using namespace cocos2d;
    class Enemy : public cocos2d::Node
    {
    public:
        
        enum ShapeType
        {
            circle = 0,
            triangle
        };
        
        enum ColorType
        {
            green = 0,
            orange,
            red
        };
        
        Enemy();
        virtual ~Enemy();
        
        virtual void Activate();
        virtual void onExit();
        void SetStartingPos(Sprite* sprite);
        static float RandomScreenWidthPosition(float spriteWidth);
        void SetupEnemySpriteRect(Enemy* enemy);
        void SetupCollisionShape(Enemy* enemy);
        void ApplyPunishement();
        static void MarkedAsPoolable(Enemy* enemy);
        
        // Amount of sprites in the spritesheat
        int enemySpriteAmount = 6;
        // amount of diffrent kinds of colors
        int numOfDifColors = 3;
        
        float timeToTravelScreenHeight = 5;
        
        ShapeType shape;
        ColorType color;
        Sprite* enemySprite;
        
        bool isPoolable = false;
    };
}

#endif /* defined(__ArcticTest__Enemy__) */
