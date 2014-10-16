//
//  TextureBank.h
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-05.
//
//

#ifndef __ArcticTest__TextureBank__
#define __ArcticTest__TextureBank__

#include <cocos2d.h>

namespace ArcticTest
{
    class TextureBank
    {
        

    public:
        
        TextureBank();
        virtual ~TextureBank();
        
        TextureBank(TextureBank const&); // Prevent copy-constructor
        TextureBank& operator=(TextureBank const&); // Prevent assignment
        
        static TextureBank& GetInstance();
        
        cocos2d::Texture2D m_slingShotTexture;
        cocos2d::Texture2D m_reticleTexture;
        cocos2d::Texture2D m_projectileTexture;
        cocos2d::Texture2D m_enemyTexture;

    };
}

#endif /* defined(__ArcticTest__TextureBank__) */
