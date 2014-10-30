//
//  OrangeEnemy.cpp
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-10.
//
//

#include "OrangeEnemy.h"

namespace ArcticTest
{
    OrangeEnemy::OrangeEnemy()
    {
        screenSize = Director::getInstance()->getVisibleSize();
    }
    
    OrangeEnemy::~OrangeEnemy()
    {

    }
    
    OrangeEnemy* OrangeEnemy::Create()
    {
        return new OrangeEnemy();
    }
    
    void OrangeEnemy::Activate()
    {
        float finalPos = screenSize.height;
        
        // Create both directions
        MoveDownRight  = MoveBy::create(timeToTravelScreenHeight, Vec2(finalPos, -finalPos));
        MoveDownLeft  = MoveBy::create(timeToTravelScreenHeight, Vec2(-finalPos, -finalPos));
        
        // Setup
        MoveDownLeft->setTag(MOVE_DOWN_ACTION_TAG);
        MoveDownLeft->retain();
        MoveDownLeft->setTarget(enemySprite);
        
        MoveDownRight->setTag(MOVE_DOWN_ACTION_TAG);
        MoveDownRight->retain();
        MoveDownRight->setTarget(enemySprite);
        
        // Randomly pick between left or right direction to start
        if (rand() & 1)
            enemySprite->runAction(MoveDownRight);
        else
            enemySprite->runAction(MoveDownLeft);
        
        Director::getInstance()->getScheduler()->schedule(schedule_selector(OrangeEnemy::update), this, 0, false);
    }
    
    void OrangeEnemy::update(float dt)
    {
        CCASSERT(enemySprite->getActionManager() != NULL, "Action manager needs to be non-NULL to get the actions");
        
        
        if (enemySprite->getPosition().x > screenSize.width - enemySprite->getContentSize().width/2 && enemySprite->getActionByTag(MOVE_DOWN_ACTION_TAG) == MoveDownRight)
        {
            // Check if we are moving right and touching the right screen border
            // TODO: use stopaction with proper cleanup
            enemySprite->stopAllActions();
            enemySprite->runAction(MoveDownLeft);
        }
        else if (enemySprite->getPosition().x < enemySprite->getContentSize().width/2 && enemySprite->getActionByTag(MOVE_DOWN_ACTION_TAG) == MoveDownLeft)
        {
            // Check if we are moving left and touching the left screen border
            // TODO: use stopaction with proper cleanup
            enemySprite->stopAllActions();
            enemySprite->runAction(MoveDownRight);
        }
        
        if (enemySprite->getPosition().y < enemySprite->getContentSize().height/2)
        {
            // If we reached the lower area
            ApplyPunishement();
            enemySprite->stopAllActions();
            Director::getInstance()->getScheduler()->unschedule(schedule_selector(OrangeEnemy::update), this);
        }
    }
}