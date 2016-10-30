#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

TextureCache::TextureCache(){

}

TextureCache::~TextureCache(){

}

GLTexture TextureCache::getTexture(std::string filePath){
    // Lookup texture and see if it's in the map
    auto mit = _textureMap.find(filePath);

    //Check if it's not in the map
    if(mit == _textureMap.end()){
        //If it's not, load the texture
        GLTexture newTexture = ImageLoader::loadPNG(filePath);
        //Insert texture into the map.
        _textureMap.insert(make_pair(filePath, newTexture));

        std::cout << "Loaded new texture!\n";
        return newTexture;
    }
    std::cout << "Loaded cached texture!\n";
    return mit->second;
}
