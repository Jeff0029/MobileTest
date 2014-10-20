//
//  GreenEnemy.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-10.
//
//

#ifndef __ArcticTest__GreenEnemy__
#define __ArcticTest__GreenEnemy__

#include "Enemy.h"
#include <iostream>

namespace ArcticTest
{
    
    class GreenEnemy : public Enemy
    {
        GreenEnemy();
        virtual ~GreenEnemy();
        
        Action* moveDown;
        
    protected:
        virtual void Activate();
    public:
        static GreenEnemy* Create(string spriteName);
    };
}

#endif /* defined(__ArcticTest__GreenEnemy__) */
