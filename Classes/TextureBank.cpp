//
//  TextureBank.cpp
//  ArcticTest
//
//  Created by Jean-Francois Vienneau on 2014-10-05.
//
//

#include "TextureBank.h"
#include <iostream>
namespace ArcticTest
{
    TextureBank::TextureBank()
    {
        RenameRetina(& slingShotTexture);
        RenameRetina(& reticleTexture);
        RenameRetina(& projectileTexture);
        RenameRetina(& enemyTexture);
    }
    
    TextureBank::~TextureBank()
    {
        
        
    }
    
    void TextureBank::RenameRetina(string* name)
    {
        if (cocos2d::Director::getInstance()->getOpenGLView()->isRetinaDisplay())
            name->insert(name->find('.'), "-hd");
    }
}