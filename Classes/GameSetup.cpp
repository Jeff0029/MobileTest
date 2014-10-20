//
//  GameSetup.cpp
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-05.
//
//

#include "GameSetup.h"

namespace ArcticTest
{

    GameSetup::GameSetup()
    {
        
        textureBank = new TextureBank();
        
        // Create all initial Game assets to start the game
        enemyGen = new EnemyGenerator(textureBank);
        
        slingshot = new SlingShot(textureBank);
        
    }
    
    GameSetup::~GameSetup()
    {
        if (textureBank != NULL)
        {
            delete textureBank;
            textureBank = 0;
        }
        
        if (enemyGen != NULL)
        {
            delete enemyGen;
            enemyGen = 0;
        }
        
        if (slingshot != NULL)
        {
            delete slingshot;
            slingshot = 0;
        }
        
    }
}