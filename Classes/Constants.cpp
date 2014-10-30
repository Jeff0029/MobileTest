//
//  Constants.cpp
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-24.
//
//

#include "Constants.h"

//PHYSICS TAGS
const int ENEMY_TAG = 1;
const int BORDER_PHYSICBODY_TAG = 3;

// PHYSICS LAYERS
const int ENEMY_CONTACT_LAYER = 1;
const int PROJECTILE_CONTACT_LAYER = 2;
const int BORDER_CONTACT_LAYER = 3;

// ACTIONS TAGS
const int MOVE_DOWN_ACTION_TAG = 1;

// ENEMY

// These pourcentages needs to equal 1
const float TRIANGLE_TYPE_CHANCE = 0.7f;
const float CIRCLE_TYPE_CHANCE = 0.3f;

// These pourcentages needs to equal 1
const float GREEN_TYPE_CHANCE = 0.45f;
const float ORANGE_TYPE_CHANCE = 0.3f;
const float RED_TYPE_CHANCE = 0.25f;

    // Time before the spawnrate increase
const float SPEEDUP_INTERVAL_TIME = 25.0f;
    // % off the enemy generation time
const float GENERATION_RATE_INCREASE = 0.1f;