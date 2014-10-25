//
//  Projectile.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-18.
//
//

#ifndef __ArcticTest__Projectile__
#define __ArcticTest__Projectile__

#include <cocos2d.h>

#include <stdio.h>
#include "Enemy.h"

namespace ArcticTest
{
    using namespace cocos2d;
    using namespace std;
    
    class Projectile
    {
    public:
        Projectile(string projectileName, Layer* projectileLayer);
        ~Projectile();
        
        void LookAt(Vec2 target);
        void SetPos(Vec2 position);
        bool OnContactBegin(PhysicsContact &physicBodyTouched);
        void Destroy();
        
        EventListenerPhysicsContact* collisionListner;
        Vec2 GetNormalizedDirection();
        static void MarkAsPoolable(Projectile* projectile);
        
        Sprite* projectileSprite;
        
        // If the projectile is ready to be reused
        bool isPoolable = false;
    };
}

#endif /* defined(__ArcticTest__Projectile__) */
