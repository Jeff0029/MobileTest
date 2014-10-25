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
        cout << "Orange Enemy Destroyed" << endl;
    }
    
    OrangeEnemy* OrangeEnemy::Create()
    {
        return new OrangeEnemy();
    }
    
    void OrangeEnemy::Activate()
    {
        float finalPos = screenSize.height;
        MoveDownRight  = MoveBy::create(timeToTravelScreenHeight, Vec2(finalPos, -finalPos));
        MoveDownLeft  = MoveBy::create(timeToTravelScreenHeight, Vec2(-finalPos, -finalPos));
        
        
        MoveDownLeft->setTag(MOVE_DOWN_ACTION_TAG);
        MoveDownLeft->retain();
        MoveDownLeft->setTarget(enemySprite);
        
        MoveDownRight->setTag(MOVE_DOWN_ACTION_TAG);
        MoveDownRight->retain();
        MoveDownRight->setTarget(enemySprite);
        
        if (rand() & 1)
            enemySprite->runAction(MoveDownRight);
        else
            enemySprite->runAction(MoveDownLeft);
        
        // Check when it touches the screen
        Director::getInstance()->getScheduler()->schedule(schedule_selector(OrangeEnemy::update), this, 0, false);
    }
    
    void OrangeEnemy::update(float dt)
    {
        if (enemySprite->getPosition().x > screenSize.width - enemySprite->getContentSize().width/2 && enemySprite->getActionByTag(MOVE_DOWN_ACTION_TAG) == MoveDownRight)
        {
            // TODO: use stopaction with proper cleanup
            enemySprite->stopAllActions();
            enemySprite->runAction(MoveDownLeft);
        }
        else if (enemySprite->getPosition().x < enemySprite->getContentSize().width/2 && enemySprite->getActionByTag(MOVE_DOWN_ACTION_TAG) == MoveDownLeft)
        {
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