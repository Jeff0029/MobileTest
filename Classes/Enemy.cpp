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
        cout << "Enemy destroyed!! " << endl;
    }
    
    void Enemy::Activate()
    {}
    
    void Enemy::onExit()
    {
        
    }
    
    void Enemy::SetStartingPos(Sprite* sprite)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Size spriteSize = sprite->getContentSize();
        
        sprite->setPosition(Vec2(RandomScreenWidthPosition(spriteSize.width) + origin.x, visibleSize.height + spriteSize.height/2));
    }
    
    float Enemy::RandomScreenWidthPosition(float spriteWidth)
    {
        // Smallest Possible number = sprite.getContentSize().width/2
        // Largest Possible number = screen Width - sprite.getContentSize().width/2
        float screenWidth = Director::getInstance()->getVisibleSize().width;
        
        return (rand()%static_cast<int>(screenWidth - spriteWidth)) + spriteWidth/2;
    }
    
    void Enemy::SetupEnemySpriteRect(Enemy* enemy)
    {
        int col = enemy->color;
        int shape = enemy->shape;
        int offset = col + shape * numOfDifColors;
        
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
        
        CCASSERT(physicsBody != NULL, "Create \'physicsbody\' before continuing");
        physicsBody->setCollisionBitmask(ENEMY_CONTACT_LAYER);
        physicsBody->setContactTestBitmask(true);
        physicsBody->setDynamic(false);
        physicsBody->setGravityEnable(false);
    }
    
    void Enemy::ApplyPunishement()
    {
        Destroy(this);
        cout << "Enemy reached the lower section of the screen" << endl;
    }
    
    void Enemy::Destroy(Enemy* enemy)
    {
        enemy->enemySprite->getScheduler()->unscheduleAllForTarget(enemy->enemySprite);
        enemy->enemySprite->getActionManager()->removeAllActionsFromTarget(enemy->enemySprite);
        enemy->enemySprite->getPhysicsBody()->setEnable(false);
        enemy->enemySprite->setVisible(false);
        
        enemy->removeFromParentAndCleanup(false);
    }
}