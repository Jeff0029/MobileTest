//
//  Projectile.cpp
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-18.
//
//

#include "Projectile.h"
#include <iostream>

namespace ArcticTest
{
    Projectile::Projectile(string projectileName, Layer* projectileLayer)
    {
        projectileSprite = Sprite::create(projectileName);
        
        auto projectilePhysic = PhysicsBody::createBox(projectileSprite->getContentSize());
        projectilePhysic->setEnable(false);
        
        projectileSprite->setPhysicsBody(projectilePhysic);
        
        projectileLayer->addChild(projectileSprite);
    }
    
    Projectile::~Projectile()
    {
        
    }
    
    void Projectile::LookAt(Vec2 target)
    {
        Vec2 up = Vec2(0,1);
        Vec2 deltaProjectileTarget = target - projectileSprite->getPosition();
        deltaProjectileTarget.normalize();
        
        float angle = ccpAngle(up, deltaProjectileTarget);
        angle *= (180/3.14);
        
        projectileSprite->setRotation(-angle);
    }
    
    void Projectile::SetPos(Vec2 position)
    {
        projectileSprite->cocos2d::Node::setPosition(position);
    }
    
    Vec2 Projectile::GetNormalizedDirection()
    {
        float x = sin(projectileSprite->getRotation() * 3.14/180);
        float y = cos(projectileSprite->getRotation() * 3.14/180);
        Vec2 direction = Vec2(x, y);
        direction.normalize();
        return direction;
    }
}