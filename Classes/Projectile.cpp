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
        
        // Physicsbody of the projectile
        auto projectilePhysic = PhysicsBody::createBox(projectileSprite->getContentSize());
        
        // Projectile spawns in the sling and are not active until shot
        projectilePhysic->setEnable(false);
        projectilePhysic->setCollisionBitmask(PROJECTILE_CONTACT_LAYER);
        projectilePhysic->setContactTestBitmask(true);
        
        // Contact Listener for when it collides with enemies or the screen border
        collisionListner = EventListenerPhysicsContact::create();
        collisionListner->onContactBegin = CC_CALLBACK_1(Projectile::OnContactBegin, this);
        
        // Used for storing the projectiles in the pool instead of the sprite (who has the physicsbody)
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
        
        // Finds the angle between the two Vec2
        float angle = ccpAngle(up, deltaProjectileTarget);
        
        //Rad to Deg
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
            
            // De-activate both objects
            MarkAsPoolable(projectile);
            Enemy::Destroy(enemy);
            
        }
        // If any shape is a wall
        else if ((a->getBody()->getTag() == BORDER_PHYSICBODY_TAG) || (b->getBody()->getTag() == BORDER_PHYSICBODY_TAG))
        {
            Projectile *projectile;
            if (a->getBody()->getTag() == BORDER_PHYSICBODY_TAG)
                //b is the projectile
                projectile = static_cast<Projectile *>(b->getBody()->getNode()->getUserData());
            else
                //a is the projectile
                projectile = static_cast<Projectile *>(a->getBody()->getNode()->getUserData());

            // Projectile is out of bound and should be pooled
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
        // Hide projectile
        projectile->projectileSprite->setVisible(false);
        
        // Since the projectile is a dynamic physicsObject we need to reset all the forces applied on the body
        PhysicsBody* ProjectileBody = projectile->projectileSprite->getPhysicsBody();
        ProjectileBody->resetForces();
        ProjectileBody->setVelocity(Vect(0,0));
        ProjectileBody->setAngularVelocity(0);
        ProjectileBody->setEnable(false);
        
        //Maked as re-usable again
        usedProjectiles->push_back(projectile);
    }
}