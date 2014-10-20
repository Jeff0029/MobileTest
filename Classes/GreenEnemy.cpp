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
    
    GreenEnemy* GreenEnemy::Create(string spriteName)
    {
        GreenEnemy* greenEnemy = new GreenEnemy();
        
        return greenEnemy;
    }
    
    void GreenEnemy::Activate()
    {
        float finalPos = Director::getInstance()->getVisibleSize().height;
        auto moveDown = MoveBy::create(timeToTravelScreenHeight, Vec2(0, -finalPos));
        this->moveDown = moveDown;
        
        CallFunc *callSelectorAction = CallFunc::create(this, callfunc_selector(Enemy::ApplyPunishement) );
        
        enemySprite->runAction(Sequence::create(moveDown, callSelectorAction, NULL));
    }
}