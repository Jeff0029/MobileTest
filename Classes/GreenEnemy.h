//
//  GreenEnemy.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-10.
//
//

#ifndef __ArcticTest__GreenEnemy__
#define __ArcticTest__GreenEnemy__

#include <iostream>

#include "Enemy.h"

namespace ArcticTest
{
    
    class GreenEnemy : public Enemy
    {
        GreenEnemy();
        virtual ~GreenEnemy();

    protected:
        virtual void Activate();
    public:
        static GreenEnemy* Create();
    };
}

#endif /* defined(__ArcticTest__GreenEnemy__) */
