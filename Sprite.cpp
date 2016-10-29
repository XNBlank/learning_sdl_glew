#include <iostream>
#include "mainGame.h"

Sprite::Sprite(){
    _vboID = 0;
}

Sprite::~Sprite(){
    if(_vboID != 0){
        glDeleteBuffers(1, &_vboID);
    }
}

void Sprite::Init(float x, float y, float width, float height){
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    if(_vboID == 0){
        glGenBuffers(1, &_vboID);
    }

    float vertexData[12];

    //Triangle 1
    vertexData[0] = x + width;
    vertexData[1] = y + height;
    vertexData[2] = x;
    vertexData[3] = y + height;
    vertexData[4] = x;
    vertexData[5] = y;

    //Triangle 2
    vertexData[6] = x;
    vertexData[7] = y;
    vertexData[8] = x + width;
    vertexData[9] = y;
    vertexData[10] = x + width;
    vertexData[11] = y + height;

    //Bind the buffer. Only one at a time.
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    //Unbind Buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw(){
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}