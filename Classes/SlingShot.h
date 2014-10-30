/*
 * SlingShot.h
 *
 *  Created on: Oct 3, 2014
 *      Author: jean-francoisvienneau
 */

#ifndef SLINGSHOT_H_
#define SLINGSHOT_H_

#include <iostream>

#include "cocos2d.h"
#include "TextureBank.h"
#include "Constants.h"
#include "Projectile.h"

namespace ArcticTest
{
    using namespace cocos2d;
    class SlingShot : cocos2d::Layer
    {
    public:
        SlingShot(TextureBank* textBank);
        virtual ~SlingShot();
        
        // Setup the physicsbody that delemit the projectile's environment
        void SetupScreenBorder(Size sizeOffset);
        
    private:
        
        // Simple touch event with the whole screen to trigger
        bool onTouchedStarted(Touch * touch, Event * event);
        void onTouchedMoved(Touch * touch, Event * event);
        void onTouchedEnded(Touch * touch, Event * event);
        
        // Activate the projectile and give it an impulse
        void ReleaseProjectile(float force, Vec2 direction);
        
        // fetch a reusable projectile
        void UnpoolProjectile(Projectile* projectile);
        
        Layer* slingLayer;
        
        Sprite* slingshotSprite;
        Sprite* reticleSprite;
        
        // First touch when onTouchedStarted is called
        Vec2 initialTouch = Vec2::ZERO;
        
        // Location where the reticle is when no touch is detected
        Vec2 reticleRestingPos = Vec2::ZERO;
        
        // radius where the reticle can move (in pixels)
        float reticleMovementRadius = 150;
        
        // speed of which the reticle moves back to the resting position (in px/s)
        float reticleMovingSpeed = 10;
        
        // How much force the slingshot apply to the projectiles
        float slingshotForce = 160000;
        
        bool isFirstShotFired = false;
        
        // Stored name of the texture to apply to the sprites
        string projectileTextureName;
        
        Projectile* projectileInSling;
        
        // List of projectiles that have been used and are not currently active
        list<Projectile *> usedProjectiles;
    };

} /* namespace ArcticTest */

#endif /* SLINGSHOT_H_ */
