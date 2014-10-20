/*
 * SlingShot.h
 *
 *  Created on: Oct 3, 2014
 *      Author: jean-francoisvienneau
 */

#ifndef SLINGSHOT_H_
#define SLINGSHOT_H_
#include "cocos2d.h"
#include "TextureBank.h"
#include "Projectile.h"
#include <iostream>

namespace ArcticTest
{
    using namespace cocos2d;
    class SlingShot : cocos2d::Layer
    {
    public:
        SlingShot(TextureBank* textBank);
        virtual ~SlingShot();
        void SetupSlingShot();
        
    private:
        
        bool onTouchedStarted(Touch * touch, Event * event);
        void onTouchedMoved(Touch * touch, Event * event);
        void onTouchedEnded(Touch * touch, Event * event);
        
        void ReleaseProjectile(float force, Vec2 direction);
        
        Layer* slingLayer;
        
        Sprite* slingshotSprite;
        Sprite* reticleSprite;
        
        Vec2 initialTouch = Vec2::ZERO;
        
        Vec2 reticleRestingPos = Vec2::ZERO;
        // radius where the reticle can move (in pixels)
        float reticleMovementRadius = 150;
        
        // speed of which the reticle moves back to the resting position (in px/s)
        float reticleMovingSpeed = 10;
        
        // How much force the slingshot apply to the projectiles
        float slingshotForce = 180000;
        
        string projectileName;
        Projectile* projectileInSling;
    };

} /* namespace ArcticTest */

#endif /* SLINGSHOT_H_ */
