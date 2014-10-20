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
#include <string>
#include <iostream>

#include "OrangeEnemy.h"
#include "GreenEnemy.h"
#include "RedEnemy.h"

#include "TextureBank.h"

namespace ArcticTest
{
    using namespace std;
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
        
        float generationRate = 15;
        const float SPEEDUP_INTERVAL_TIME = 25.0f;
        float generationRateIncrease = 0.1f;
        
        TextureBank* textBank;
        Layer* enemyLayer;
        
        vector<Enemy*> allEnemies;
        
        // These pourcentages needs to equal 1
        const float TRIANGLE_TYPE_CHANCE = 0.7f;
        const float CIRCLE_TYPE_CHANCE = 0.3f;
        
        // These pourcentages needs to equal 1
        const float GREEN_TYPE_CHANCE = 0.45f;
        const float ORANGE_TYPE_CHANCE = 0.3f;
        const float RED_TYPE_CHANCE = 0.25f;

        std::map <float, Enemy::ShapeType> allShapeTypeChances;
        std::map <float, Enemy::ColorType> allColorTypeChances;
    };
    
}

#endif /* defined(__ArcticTest__EnemyGenerator__) */
