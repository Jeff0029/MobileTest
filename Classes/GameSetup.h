//
//  GameSetup.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-05.
//
//

#ifndef __ArcticTest__GameSetup__
#define __ArcticTest__GameSetup__

#include <stdio.h>
#include "EnemyGenerator.h"
#include "SlingShot.h"


namespace ArcticTest
{
    
    class GameSetup
    {
    public:
        GameSetup();
        virtual ~GameSetup();
    private:
        
        TextureBank* textureBank;
        EnemyGenerator* enemyGen;
        SlingShot* slingshot;
    };
    
}






#endif /* defined(__ArcticTest__GameSetup__) */
