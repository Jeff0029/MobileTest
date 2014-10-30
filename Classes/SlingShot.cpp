/*
 * SlingShot.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: jean-francoisvienneau
 */

#include "SlingShot.h"

namespace ArcticTest
{
    USING_NS_CC;
    
	SlingShot::SlingShot(TextureBank* textBank)
	{
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        // Stores string for pojectile sprite creation
        projectileTextureName = textBank->projectileTexture;
        
        // Create Sprites
        slingshotSprite = Sprite::create(textBank->slingShotTexture);
        reticleSprite = Sprite::create(textBank->reticleTexture);
        
        // position Sprites
        slingshotSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, slingshotSprite->getContentSize().height/2 + origin.y));
        reticleSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, slingshotSprite->getContentSize().height + origin.y));
        reticleRestingPos = reticleSprite->getPosition();
        
        // Create layer
        auto slingLayer = SlingShot::create();
        // Store layer
        this->slingLayer = slingLayer;
        
        // Setup slingShot Listner
        auto listner = EventListenerTouchOneByOne::create();
        listner->setSwallowTouches(true);
        listner->onTouchBegan = CC_CALLBACK_2(SlingShot::onTouchedStarted, this);
        listner->onTouchMoved = CC_CALLBACK_2(SlingShot::onTouchedMoved, this);
        listner->onTouchEnded = CC_CALLBACK_2(SlingShot::onTouchedEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listner, reticleSprite);
        
        // add sprites to layer and adds the layer to the scene
        slingLayer->addChild(reticleSprite);
        slingLayer->addChild(slingshotSprite);
        Director::getInstance()->getRunningScene()->addChild(slingLayer);
        
	}

	SlingShot::~SlingShot()
	{
        if (projectileInSling != NULL)
        {
            delete projectileInSling;
            projectileInSling = 0;
        }
	}
    
    void SlingShot::SetupScreenBorder(Size sizeOffset)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        // Create size of the screen plus the offset Size param
        Size BorderSize = *new Size(visibleSize.width + (sizeOffset.width * 2), visibleSize.height + visibleSize.height);
        auto screenBorder = PhysicsBody::createEdgeBox(BorderSize);
        
        // Setup PhysicsBody
        screenBorder->setTag(BORDER_PHYSICBODY_TAG);
        screenBorder->setPositionOffset(Vec2(visibleSize.width/2, visibleSize.height/2));
        screenBorder->setCollisionBitmask(BORDER_CONTACT_LAYER);
        screenBorder->setContactTestBitmask(true);
        
        // Add border to the layer
        auto borderNode = Node::create();
        borderNode->setPhysicsBody(screenBorder);
        slingLayer->addChild(borderNode);
    }
        
    bool SlingShot::onTouchedStarted(Touch* touch, Event* event)
    {
        if (usedProjectiles.size() == 0)
        {
            // Creating a new projectile
            projectileInSling = new Projectile(projectileTextureName, slingLayer);
            projectileInSling->usedProjectiles = &usedProjectiles;
        }
        else
        {
            // Taking a projectile from the pool
            projectileInSling = usedProjectiles.front();
            UnpoolProjectile(usedProjectiles.front());
        }
        
        // Refurbrish the projectile
        projectileInSling->projectileSprite->getPhysicsBody()->resetForces();
        projectileInSling->projectileSprite->setRotation(0);
        projectileInSling->SetPos(reticleSprite->getPosition());
        
        if (!isFirstShotFired)
        {
            // CREATED ONCE*
            //setup the border for the projectiles to mark them as poolable
            float maxDimension = MAX(projectileInSling->projectileSprite->getContentSize().height, projectileInSling->projectileSprite->getContentSize().width);
            SetupScreenBorder(Size(maxDimension, maxDimension));
            isFirstShotFired = true;
        }
        
        initialTouch = touch->getLocation();
        return true;
    }
    
    void SlingShot::onTouchedMoved(Touch* touch, Event* event)
    {
        projectileInSling->SetPos(reticleSprite->getPosition());
        projectileInSling->LookAt(reticleRestingPos);
        
        // This prevent the player from going too high on the screen and moving the finger with the Sling doing nothing
        if (initialTouch.y < touch->getLocation().y)
            initialTouch.y = touch->getLocation().y;
        
        // If we are within the movement circle
        if (initialTouch.distance(touch->getLocation()) < reticleMovementRadius)
            reticleSprite->setPosition(reticleRestingPos + (touch->getLocation() - initialTouch));
        // If we are outside the circle
        else
            reticleSprite->setPosition(initialTouch.lerp(touch->getLocation(), reticleMovementRadius / initialTouch.distance(touch->getLocation())) + (reticleRestingPos - initialTouch));
        
        //Clamp to only be able to shoot up
        reticleSprite->setPosition(reticleSprite->getPosition().x ,clampf(reticleSprite->getPosition().y, 0, reticleRestingPos.y));
    }
    
    void SlingShot::onTouchedEnded(Touch* touch, Event* event)
    {
        // get a number between 0 & 1 to apply to the final force
        float stretchAmount = reticleRestingPos.distance(reticleSprite->getPosition()) / reticleMovementRadius;
        ReleaseProjectile(slingshotForce * stretchAmount, projectileInSling->GetNormalizedDirection());
        
        // Reset the reticle's position
        float distance = reticleSprite->getPosition().distance(reticleRestingPos);
        auto moveToRestingLocation = MoveTo::create(reticleMovingSpeed / distance, reticleRestingPos);
        reticleSprite->runAction(moveToRestingLocation);
    }
    
    void SlingShot::ReleaseProjectile(float force, Vec2 direction)
    {
        // Release Projectile
        PhysicsBody* ProjectileBody = projectileInSling->projectileSprite->getPhysicsBody();
        ProjectileBody->setEnable(true);
        ProjectileBody->applyImpulse(Vect(direction.x * force, direction.y * force));
    }
    
    void SlingShot::UnpoolProjectile(Projectile* projectile)
    {
        // take a used projectile from the pool
        projectile->projectileSprite->setVisible(true);
        usedProjectiles.remove(projectile);
    }

} /* namespace ArcticTest */
