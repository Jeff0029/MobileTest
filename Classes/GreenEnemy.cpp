//
//  GreenEnemy.cpp
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-10.
//
//

#include "GreenEnemy.h"

namespace ArcticTest
{
    GreenEnemy::GreenEnemy()
    {
        
    }
    
    GreenEnemy::~GreenEnemy()
    {
        
    }
    
    GreenEnemy* GreenEnemy::Create()
    {
        return new GreenEnemy();
    }
    
    void GreenEnemy::Activate()
    {
        float finalPos = Director::getInstance()->getVisibleSize().height;
        auto moveDown = MoveBy::create(timeToTravelScreenHeight, Vec2(0, -finalPos));
        
        // Apply the CallFunc if the action was able to finish
        CallFunc *callPunishement = CallFunc::create(CC_CALLBACK_0(Enemy::ApplyPunishement, this));
        enemySprite->runAction(Sequence::create(moveDown, callPunishement, NULL));
    }
}