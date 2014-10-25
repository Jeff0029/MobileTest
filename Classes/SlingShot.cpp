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
        
        slingshotSprite = Sprite::create(textBank->slingShotTexture);
        reticleSprite = Sprite::create(textBank->reticleTexture);
        
        projectileTextureName = textBank->projectileTexture;
        
        auto slingLayer = SlingShot::create();
        this->slingLayer = slingLayer;
        
        slingshotSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, slingshotSprite->getContentSize().height/2 + origin.y));
        reticleSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, slingshotSprite->getContentSize().height + origin.y));
        
        reticleRestingPos = reticleSprite->getPosition();
        
        auto listner = EventListenerTouchOneByOne::create();
        listner->setSwallowTouches(true);
        
        listner->onTouchBegan = CC_CALLBACK_2(SlingShot::onTouchedStarted, this);
        listner->onTouchMoved = CC_CALLBACK_2(SlingShot::onTouchedMoved, this);
        listner->onTouchEnded = CC_CALLBACK_2(SlingShot::onTouchedEnded, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listner, reticleSprite);
        
        slingLayer->addChild(reticleSprite);
        slingLayer->addChild(slingshotSprite);
        
        Director::getInstance()->getRunningScene()->addChild(slingLayer);
        
	}

	SlingShot::~SlingShot()
	{
		// TODO Auto-generated destructor stub
	}
    
    void SlingShot::SetupScreenBorder(Size sizeOffset)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        Size BorderSize = *new Size(visibleSize.width + (sizeOffset.width * 2), visibleSize.height + visibleSize.height);
        auto screenBorder = PhysicsBody::createEdgeBox(BorderSize);
        screenBorder->setTag(BORDER_PHYSICBODY_TAG);
        screenBorder->setPositionOffset(Vec2(visibleSize.width/2, visibleSize.height/2));
        screenBorder->setCollisionBitmask(BORDER_CONTACT_LAYER);
        screenBorder->setContactTestBitmask(true);
        
        auto borderNode = Node::create();
        borderNode->setPhysicsBody(screenBorder);
        slingLayer->addChild(borderNode);
    }
        
    bool SlingShot::onTouchedStarted(Touch* touch, Event* event)
    {
        projectileInSling = new Projectile(projectileTextureName, slingLayer);
        projectileInSling->SetPos(reticleSprite->getPosition());
        if (!isFirstShotFired)
        {
            float maxDimension = MAX(projectileInSling->projectileSprite->getContentSize().height, projectileInSling->projectileSprite->getContentSize().width);
            cout << maxDimension << endl;
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
        float stretchAmount = reticleRestingPos.distance(reticleSprite->getPosition()) / reticleMovementRadius;
        ReleaseProjectile(slingshotForce * stretchAmount, projectileInSling->GetNormalizedDirection());
        
        float distance = reticleSprite->getPosition().distance(reticleRestingPos);
        auto moveToRestingLocation = MoveTo::create(reticleMovingSpeed / distance, reticleRestingPos);
        reticleSprite->runAction(moveToRestingLocation);
    }
    
    void SlingShot::ReleaseProjectile(float force, Vec2 direction)
    {
        //usedProjectiles.pushBack(projectileInSling);
        PhysicsBody* ProjectileBody = projectileInSling->projectileSprite->getPhysicsBody();
        ProjectileBody->setEnable(true);
        ProjectileBody->applyImpulse(Vect(direction.x * force, direction.y * force));
    }

} /* namespace ArcticTest */
