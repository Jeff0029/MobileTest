//
//  OrangeEnemy.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-10.
//
//

#ifndef __ArcticTest__OrangeEnemy__
#define __ArcticTest__OrangeEnemy__

#include "Enemy.h"
#include <iostream>

namespace ArcticTest
{
    class OrangeEnemy : public Enemy
    {
        OrangeEnemy();
        virtual ~OrangeEnemy();
    protected:
        virtual void Activate();
    public:
        static OrangeEnemy* Create(string spriteName);
        virtual void update(float dt);
        
        Size screenSize;
        
        Action* MoveDownLeft;
        Action* MoveDownRight;
    };
}

#endif /* defined(__ArcticTest__OrangeEnemy__) */
