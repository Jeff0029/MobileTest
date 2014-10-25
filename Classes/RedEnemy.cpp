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
        cout << "Red Enemy Destroyed" << endl;
    }
    
    RedEnemy* RedEnemy::Create()
    {
        return new RedEnemy();
    }
    
    void RedEnemy::Activate()
    {
        OrangeEnemy::Activate();
        Director::getInstance()->getScheduler()->schedule(schedule_selector(RedEnemy::SwitchSide), this, switchingIntervalTime, false);
    }

    void RedEnemy::SwitchSide(float dt)
    {
        CCASSERT(enemySprite->getActionManager() != NULL, "Action manager needs to be non-NULL to get the actions");
        Action* currentMovingAction = enemySprite->getActionByTag(MOVE_DOWN_ACTION_TAG);
        enemySprite->stopAllActions();
        
        if (currentMovingAction == MoveDownLeft)
            enemySprite->runAction(MoveDownRight);
        else if (currentMovingAction == MoveDownRight)
            enemySprite->runAction(MoveDownLeft);
    }
}