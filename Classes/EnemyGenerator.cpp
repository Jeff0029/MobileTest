//
//  EnemyGenerator.cpp
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-05.
//
//

#include "EnemyGenerator.h"
namespace ArcticTest
{ 
    EnemyGenerator::EnemyGenerator(TextureBank* textBank)
    {
        auto enemyLayer = EnemyGenerator::create();
        this->enemyLayer = enemyLayer;
        
        //enemyLayer->setph(Director::getInstance()->getRunningScene()->getPhysicsWorld());
        Director::getInstance()->getRunningScene()->addChild(enemyLayer);
        
        this->textBank = textBank;
        allShapeTypeChances[TRIANGLE_TYPE_CHANCE] = Enemy::triangle;
        allShapeTypeChances[CIRCLE_TYPE_CHANCE] = Enemy::circle;
        
        allColorTypeChances[GREEN_TYPE_CHANCE] = Enemy::green;
        allColorTypeChances[ORANGE_TYPE_CHANCE] = Enemy::orange;
        allColorTypeChances[RED_TYPE_CHANCE] = Enemy::red;
        
        // Spawn the first one
        GenerateEnemy();
        Director::getInstance()->getScheduler()->schedule(schedule_selector(EnemyGenerator::GenerateEnemiesScheduler), this, 2, false);
        
        Director::getInstance()->getScheduler()->schedule(schedule_selector(EnemyGenerator::SpeedUpGenerationScheduler), this, 2, false);
    }
    
    EnemyGenerator::~EnemyGenerator()
    {
        // Delete the content the pointers is pointing at.
        for (int i = 0; i < allEnemies.size(); i++)
            delete &allEnemies.at(i);
        
        // Clear the pointers
        allEnemies.clear();
        allEnemies.shrink_to_fit(); 
    }
    
    void EnemyGenerator::GenerateEnemy()
    {
        Enemy* enemy;

        allEnemies.push_back(enemy);
        
        vector<float> allColorKeys = KeysInVector(allColorTypeChances);
        float colorTypeChance = randomPourcentageGenerator();
        Enemy::ColorType color = allColorTypeChances[GetEnumKey(allColorKeys, colorTypeChance)];

        switch (color)
        {
            case Enemy::green:
                enemy = GreenEnemy::Create(textBank->enemyTexture);
                break;
            case Enemy::orange:
                enemy = OrangeEnemy::Create(textBank->enemyTexture);
                break;
            case Enemy::red:
                enemy = RedEnemy::Create(textBank->enemyTexture);
                break;
            default:
                break;
        }
        enemy->color = color;
        
        vector<float> allShapeKeys = KeysInVector(allShapeTypeChances);
        float shapeTypeChance = randomPourcentageGenerator();
        enemy->shape = allShapeTypeChances[GetEnumKey(allShapeKeys, shapeTypeChance)];
        
        enemy->enemySprite = Sprite::create(textBank->enemyTexture);
        
        enemy->SetupEnemySpriteRect(enemy);
        
        enemy->SetupCollisionShape(enemy);
        
        enemy->SetStartingPos(enemy->enemySprite);
        
        enemyLayer->addChild(enemy->enemySprite);
        
        enemy->Activate();
    }
    
    void EnemyGenerator::SpeedUpGenerationScheduler(float dt)
    {
        generationRate -= (generationRate * generationRateIncrease);
    }
    
    void EnemyGenerator::GenerateEnemiesScheduler(float dt)
    {
        GenerateEnemy();
    }
    
    float EnemyGenerator::GetEnumKey(vector<float> allKeys, float ranNum)
    {
        float currentNum = 0.0f;
        for (int i = 0; allKeys.size(); i++)
        {
            currentNum += allKeys[i];
            if (ranNum < currentNum)
                return allKeys[i];
        }
        // Something went wrong
        return  NULL;
    }
    

    float EnemyGenerator::randomPourcentageGenerator()
    {
        return (rand()%100) / 100.0f;
    }
    
    template <typename T>
    vector<float> EnemyGenerator::KeysInVector(map<float, T> mapping )
    {
        // Tutorial used:  http://stackoverflow.com/questions/110157/how-to-retrieve-all-keys-or-values-from-a-stdmap
        vector<float> allKeys;
        for( typename map<float, T>::iterator it = mapping.begin(); it != mapping.end(); ++it )
            allKeys.push_back( it->first );
        
        return allKeys;
        
    }
}
