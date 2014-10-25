//
//  RedEnemy.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-10.
//
//

#ifndef __ArcticTest__RedEnemy__
#define __ArcticTest__RedEnemy__

#include <iostream>

#include "Enemy.h"
#include "OrangeEnemy.h"

namespace ArcticTest
{
    class RedEnemy : public OrangeEnemy
    {
        RedEnemy();
        virtual ~RedEnemy();
        
    protected:
        virtual void Activate();
    public:
        static RedEnemy* Create();
    private:
        void SwitchSide(float dt);
        
        float switchingIntervalTime = 3;
    };
}

#endif /* defined(__ArcticTest__RedEnemy__) */
