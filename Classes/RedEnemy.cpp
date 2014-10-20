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
    
    RedEnemy* RedEnemy::Create(string spriteName)
    {
        RedEnemy* redEnemy = new RedEnemy();
        
        return redEnemy;
    }
    
    void RedEnemy::Activate()
    {
        //Director::getInstance()->getScheduler()->schedule(schedule_selector(OrangeEnemy::update), this, 0, false);

    }
}