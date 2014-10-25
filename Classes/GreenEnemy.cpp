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
        cout << "Green Enemy Destroyed" << endl;
    }
    
    GreenEnemy* GreenEnemy::Create()
    {
        return new GreenEnemy();
    }
    
    void GreenEnemy::Activate()
    {
        float finalPos = Director::getInstance()->getVisibleSize().height;
        auto moveDown = MoveBy::create(timeToTravelScreenHeight, Vec2(0, -finalPos));
        this->moveDown = moveDown;
        
        CallFunc *callPunishement = CallFunc::create(CC_CALLBACK_0(Enemy::ApplyPunishement, this));
        enemySprite->runAction(Sequence::create(moveDown, callPunishement, NULL));
    }
}