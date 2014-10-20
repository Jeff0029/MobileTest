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
    using namespace std;
    class TextureBank
    {
        
    public:
        
        TextureBank();
        virtual ~TextureBank();
        
        void RenameRetina(string* name);
        
        
        string slingShotTexture = "bottom.png";
        string reticleTexture = "sling.png";
        string projectileTexture = "projectile.png";
        string enemyTexture = "pieces.png";
    };
}

#endif /* defined(__ArcticTest__TextureBank__) */
