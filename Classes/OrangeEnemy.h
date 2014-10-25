//
//  OrangeEnemy.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-10.
//
//

#ifndef __ArcticTest__OrangeEnemy__
#define __ArcticTest__OrangeEnemy__

#include <iostream>

#include "Enemy.h"

namespace ArcticTest
{
    class OrangeEnemy : public Enemy
    {   
    protected:
        OrangeEnemy();
        virtual ~OrangeEnemy();
        virtual void Activate();
    public:
        static OrangeEnemy* Create();
        virtual void update(float dt);
        
        Size screenSize;
        
        Action* MoveDownLeft;
        Action* MoveDownRight;
    };
}

#endif /* defined(__ArcticTest__OrangeEnemy__) */
