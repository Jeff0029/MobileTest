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
        if (cocos2d::Director::getInstance()->getOpenGLView()->isRetinaDisplay())
        {
            // Load retina graphics
            
            cocos2d::Image slingImage;
            slingImage.initWithImageFile("bottom-hd.png");
            m_slingShotTexture.initWithImage(&slingImage);
        }
        else
        {
            // Load standard graphics
            
        }
        
    }
    
    TextureBank::~TextureBank()
    {
        
        
    }
    
    TextureBank& TextureBank::GetInstance()
    {
        static TextureBank singleton;
        return singleton;
    }
    
}