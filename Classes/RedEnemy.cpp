//
//  RedEnemy.cpp
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-10.
//
//

#include "RedEnemy.h"

namespace ArcticTest
{
    RedEnemy::RedEnemy()
    {
    }
    
    RedEnemy::~RedEnemy()
    {
    }
    
    RedEnemy* RedEnemy::Create()
    {
        return new RedEnemy();
    }
    
    void RedEnemy::Activate()
    {
        // Activate just like a OrangeEnemy
        OrangeEnemy::Activate();
        
        // Switch moving direction at given interval
        Director::getInstance()->getScheduler()->schedule(schedule_selector(RedEnemy::SwitchSide), this, switchingIntervalTime, false);
    }

    void RedEnemy::SwitchSide(float dt)
    {
        CCASSERT(enemySprite->getActionManager() != NULL, "Action manager needs to be non-NULL to get the actions");
        
        // Get current action to perform the opposite
        Action* currentMovingAction = enemySprite->getActionByTag(MOVE_DOWN_ACTION_TAG);
        enemySprite->stopAllActions();
        
        if (currentMovingAction == MoveDownLeft)
            enemySprite->runAction(MoveDownRight);
        else if (currentMovingAction == MoveDownRight)
            enemySprite->runAction(MoveDownLeft);
    }
}