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
        // Create the layer which all enemies will exist
        auto enemyLayer = EnemyGenerator::create();
        this->enemyLayer = enemyLayer;
        Director::getInstance()->getRunningScene()->addChild(enemyLayer);
        
        // Store the textureBank to
        this->textBank = textBank;
        
        // Setup the maps for the colors and the shapes paired with % chance they are picked
        allShapeTypeChances[TRIANGLE_TYPE_CHANCE] = Enemy::triangle;
        allShapeTypeChances[CIRCLE_TYPE_CHANCE] = Enemy::circle;
        
        allColorTypeChances[GREEN_TYPE_CHANCE] = Enemy::green;
        allColorTypeChances[ORANGE_TYPE_CHANCE] = Enemy::orange;
        allColorTypeChances[RED_TYPE_CHANCE] = Enemy::red;
        
        // Spawn the first one
        GenerateEnemy();
        
        // Schedule for periodic enemy spawn
        Director::getInstance()->getScheduler()->schedule(schedule_selector(EnemyGenerator::GenerateEnemiesScheduler), this, 2, false);
        // Schedule for periodic enemy spawn rate increase
        Director::getInstance()->getScheduler()->schedule(schedule_selector(EnemyGenerator::SpeedUpGenerationScheduler), this, 2, false);
    }
    
    EnemyGenerator::~EnemyGenerator()
    {

    }
    
    void EnemyGenerator::GenerateEnemy()
    {
        Enemy* enemy;
        
        // Get all the % values for the colors
        vector<float> allColorKeys = KeysInVector(allColorTypeChances);
        float colorTypeChance = randomPourcentageGenerator();
        //Get a random key from the Vector of keys and use it to get it's paired color enum
        Enemy::ColorType color = allColorTypeChances[GetEnumKey(allColorKeys, colorTypeChance)];

        // Create proper enemy depending on color
        switch (color)
        {
            case Enemy::green:
                enemy = GreenEnemy::Create();
                break;
            case Enemy::orange:
                enemy = OrangeEnemy::Create();
                break;
            case Enemy::red:
                enemy = RedEnemy::Create();
                break;
            default:
                break;
        }
        enemy->color = color;
        
        // Same concept for color but with the shape
        vector<float> allShapeKeys = KeysInVector(allShapeTypeChances);
        float shapeTypeChance = randomPourcentageGenerator();
        enemy->shape = allShapeTypeChances[GetEnumKey(allShapeKeys, shapeTypeChance)];
        
        enemy->enemySprite = Sprite::create(textBank->enemyTexture);
        enemy->enemySprite->setTag(ENEMY_TAG);
        // Used for referencing object to delete
        enemy->enemySprite->setUserData(enemy);
        // Find the proper rect on the enemy spritesheat
        enemy->SetupEnemySpriteRect(enemy);
        // Apply proper collider geometry
        enemy->SetupCollisionShape(enemy);
        // Move above the screen with random X pos
        enemy->SetStartingPos(enemy->enemySprite);
        
        enemyLayer->addChild(enemy->enemySprite);
        
        enemy->Activate();
    }
    
    void EnemyGenerator::SpeedUpGenerationScheduler(float dt)
    {
        // Take a pourcentage off the regenRate
        generationRate -= (generationRate * GENERATION_RATE_INCREASE);
    }
    
    void EnemyGenerator::GenerateEnemiesScheduler(float dt)
    {
        GenerateEnemy();
    }
    
    float EnemyGenerator::GetEnumKey(vector<float> allKeys, float ranNum)
    {
        // Return the value from the vector AllKeys that was choosen by random
        float currentNum = 0.0f;
        for (int i = 0; allKeys.size(); i++)
        {
            currentNum += allKeys[i];
            if (ranNum < currentNum)
                return allKeys[i];
        }
        CCASSERT(true, "No value in allKeys has been greater than the ranNum, Make sure that the sum of allKeys and the highest ranNum number possible are the same");
        return  NULL;
    }
    

    float EnemyGenerator::randomPourcentageGenerator()
    {
        // Generate number between 0.0f and 1.0f
        srand(arc4random());
        return (rand() % 100) / 100.0f;
    }
    
    template <typename T>
    vector<float> EnemyGenerator::KeysInVector(map<float, T> mapping )
    {
        // Return all the keys in the map
        // Tutorial used:  http://stackoverflow.com/questions/110157/how-to-retrieve-all-keys-or-values-from-a-stdmap
        vector<float> allKeys;
        for( typename map<float, T>::iterator it = mapping.begin(); it != mapping.end(); ++it )
            allKeys.push_back( it->first );
        
        return allKeys;
        
    }
}
