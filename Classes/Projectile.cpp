//
//  Projectile.cpp
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-18.
//
//

#include "Projectile.h"

namespace ArcticTest
{
    Projectile::Projectile(string projectileName, Layer* projectileLayer)
    {
        projectileSprite = Sprite::create(projectileName);
        
        auto projectilePhysic = PhysicsBody::createBox(projectileSprite->getContentSize());
        projectilePhysic->setEnable(false);
        projectilePhysic->setCollisionBitmask(PROJECTILE_CONTACT_LAYER);
        projectilePhysic->setContactTestBitmask(true);
        
        collisionListner = EventListenerPhysicsContact::create();
        collisionListner->onContactBegin = CC_CALLBACK_1(Projectile::OnContactBegin, this);
        
        projectileSprite->setUserData(this);
        projectileSprite->setPhysicsBody(projectilePhysic);
        projectileSprite->getEventDispatcher()->addEventListenerWithFixedPriority(collisionListner, 1);
        
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
    
    bool Projectile::OnContactBegin(PhysicsContact &physicBodyTouched)
    {
        auto a = physicBodyTouched.getShapeA();
        auto b = physicBodyTouched.getShapeB();
        
        // If any of the shapes is an enemy
        if ((a->getCollisionBitmask() == ENEMY_CONTACT_LAYER) || (b->getCollisionBitmask() == ENEMY_CONTACT_LAYER ))
        {
            Enemy *enemy;
            Projectile *projectile;
            
            if (a->getCollisionBitmask() == ENEMY_CONTACT_LAYER)
            {
                // a is the enemy
                enemy = static_cast<Enemy *>(a->getBody()->getNode()->getUserData());
                projectile = static_cast<Projectile *>(b->getBody()->getNode()->getUserData());
            }
            else
            {
                // b is the enemy
                enemy = static_cast<Enemy *>(b->getBody()->getNode()->getUserData());
                projectile = static_cast<Projectile *>(a->getBody()->getNode()->getUserData());
            }
            
            MarkAsPoolable(projectile);
            Enemy::Destroy(enemy);
            
        }
        // If we collide with a wall
        else if ((a->getBody()->getTag() == BORDER_PHYSICBODY_TAG) || (b->getBody()->getTag() == BORDER_PHYSICBODY_TAG))
        {
            Projectile *projectile;
            if (a->getBody()->getTag() == BORDER_PHYSICBODY_TAG)
                //b is the projectile
                projectile = static_cast<Projectile *>(b->getBody()->getNode()->getUserData());
            else
                //a is the projectile
                projectile = static_cast<Projectile *>(a->getBody()->getNode()->getUserData());

            MarkAsPoolable(projectile);
        }
            
        return true;
    }

    Vec2 Projectile::GetNormalizedDirection()
    {
        float x = sin(projectileSprite->getRotation() * 3.14/180);
        float y = cos(projectileSprite->getRotation() * 3.14/180);
        Vec2 direction = Vec2(x, y);
        direction.normalize();
        return direction;
    }
    
    void Projectile::MarkAsPoolable(Projectile* projectile)
    {
        projectile->projectileSprite->setVisible(false);
        
        PhysicsBody* ProjectileBody = projectile->projectileSprite->getPhysicsBody();
        ProjectileBody->resetForces();
        ProjectileBody->setVelocity(Vect(0,0));
        ProjectileBody->setAngularVelocity(0);
        ProjectileBody->setEnable(false);
        usedProjectiles->push_back(projectile);
    }
}