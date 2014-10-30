//
//  EnemyGenerator.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-05.
//
//

#ifndef __ArcticTest__EnemyGenerator__
#define __ArcticTest__EnemyGenerator__

#include <cocos2d.h>
#include <map>
#include <vector>
#include <iostream>

#include "OrangeEnemy.h"
#include "GreenEnemy.h"
#include "RedEnemy.h"
#include "TextureBank.h"
#include "Constants.h"

namespace ArcticTest
{
    using namespace cocos2d;
    
    class EnemyGenerator : cocos2d::Layer
    {
    public:
        
        EnemyGenerator(TextureBank* textBank);
        virtual ~EnemyGenerator();
        
        void SpeedUpGenerationScheduler(float dt);
        void GenerateEnemiesScheduler(float dt);
        
    private:
        void GenerateEnemy();
        float GetEnumKey(vector<float> keys, float ranNum);
        
        template<typename T>
        vector<float> KeysInVector(map<float, T> map );
        static float randomPourcentageGenerator();
        
        // time it takes to spawn the next enemy
        float generationRate = 15;
        
        TextureBank* textBank;
        Layer* enemyLayer;
        
        // pourcentages paired with enums that determine how each Shape/Color type is likely to be picked
        std::map <float, Enemy::ShapeType> allShapeTypeChances;
        std::map <float, Enemy::ColorType> allColorTypeChances;
    };
    
}

#endif /* defined(__ArcticTest__EnemyGenerator__) */
