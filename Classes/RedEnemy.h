//
//  RedEnemy.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-10.
//
//

#ifndef __ArcticTest__RedEnemy__
#define __ArcticTest__RedEnemy__

#include "Enemy.h"
#include <iostream>
#include "OrangeEnemy.h"

namespace ArcticTest
{
    class RedEnemy : public Enemy, cocos2d::Node
    {
        RedEnemy();
        virtual ~RedEnemy();
    protected:
        virtual void Activate();
    public:
        static RedEnemy* Create(string spriteName);
    };
}

#endif /* defined(__ArcticTest__RedEnemy__) */
