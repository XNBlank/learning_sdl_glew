#pragma once
#include <SDL.h>
#include <glew.h>
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <vector>

enum class GameState {PLAY, EXIT};

class MainGame{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
    float _fps;
    float _maxFPS;
    float _frameTime;

    void initSystems();
    void InitShaders();

    void CalculateFPS();

    void Input();
    void Draw();
    void Update();

    std::vector <Sprite*> _sprites;
    GLSLProgram _colorProgram;
};

