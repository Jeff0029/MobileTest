//
//  Enemy.cpp
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-07.
//
//

#include "Enemy.h"

namespace ArcticTest
{
    Enemy::Enemy()
    {
        
    }
    
    Enemy::~Enemy()
    {

    }
    
    void Enemy::Activate()
    {}
    
    void Enemy::SetStartingPos(Sprite* sprite)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Size spriteSize = sprite->getContentSize();
        
        // Put the sprite above the screen with a random X coordinate that
        sprite->setPosition(Vec2(RandomScreenWidthPosition(spriteSize.width, visibleSize.width) + origin.x, visibleSize.height + spriteSize.height/2));
    }
    
    float Enemy::RandomScreenWidthPosition(float spriteWidth, float screenWidth)
    {
        return (rand()%static_cast<int>(screenWidth - spriteWidth)) + spriteWidth/2;
    }
    
    void Enemy::SetupEnemySpriteRect(Enemy* enemy)
    {
        // Using the order of the enum as they appear on the spritesheat
        int col = enemy->color;
        int shape = enemy->shape;
        int offset = col + shape * numOfDifColors;

        // Rect splicing the horizontal set the spritesheat to only include one enemy Texture
        enemy->enemySprite->setTextureRect(Rect(enemy->enemySprite->getContentSize().width / enemySpriteAmount * offset,
                                                0,
                                                enemy->enemySprite->getContentSize().width / enemySpriteAmount,
                                                enemy->enemySprite->getContentSize().height));
    }
    
    void Enemy::SetupCollisionShape(Enemy* enemy)
    {
        PhysicsBody* physicsBody;
        if (enemy->shape == circle)
        {
            // Circle
            physicsBody = PhysicsBody::createCircle(enemySprite->getContentSize().height/2, PhysicsMaterial(0,1,0));
            enemySprite->setPhysicsBody(physicsBody);
        }
        else if (enemy->shape == triangle)
        {
            float x = enemySprite->getContentSize().width;
            float y = enemySprite->getContentSize().height;
            //Triangle
            Vec2 triangleVerts[3] = { Vec2(0, y/2), Vec2(x/2,-y/2), Vec2(-x/2,-y/2) };
            physicsBody = PhysicsBody::createPolygon(triangleVerts, 3);
            enemySprite->setPhysicsBody(physicsBody);
        }
        
        CCASSERT(physicsBody != NULL, "Create physicsbody before continuing");
        physicsBody->setCollisionBitmask(ENEMY_CONTACT_LAYER);
        physicsBody->setContactTestBitmask(true);
        physicsBody->setDynamic(false);
        physicsBody->setGravityEnable(false);
    }
    
    void Enemy::ApplyPunishement()
    {
        Destroy(this);
    }
    
    void Enemy::Destroy(Enemy* enemy)
    {
        // Cleanup the moving action of the enemy before Cleanup
        enemy->enemySprite->getScheduler()->unscheduleAllForTarget(enemy->enemySprite);
        enemy->enemySprite->getActionManager()->removeAllActionsFromTarget(enemy->enemySprite);
        enemy->enemySprite->getPhysicsBody()->setEnable(false);
        enemy->enemySprite->setVisible(false);
        
        enemy->enemySprite->removeAllChildrenWithCleanup(true);
        enemy->removeFromParentAndCleanup(true);
    }
}