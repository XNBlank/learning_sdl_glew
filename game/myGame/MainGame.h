#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <Engine/Sprite.h>
#include <Engine/SpriteBatch.h>
#include <Engine/GLSLProgram.h>
#include <Engine/GLTexture.h>
#include <Engine/Window.h>
#include <Engine/Engine.h>
#include <Engine/Camera2D.h>
#include <Engine/InputManager.h>
#include <Engine/Timing.h>
#include <vector>

    enum class GameState {PLAY, EXIT};

    class MainGame{
    public:
        MainGame();
        ~MainGame();

        void run();

    private:
        Engine::Window _window;
        int _screenWidth;
        int _screenHeight;
        GameState _gameState;
        float _fps;
        float _maxFPS;

        void InitSystems();
        void InitShaders();

        void CalculateFPS();

        void Input();
        void Draw();
        void Update();

        Engine::GLSLProgram _colorProgram;
        Engine::Camera2D _camera2D;
        Engine::SpriteBatch _spriteBatch;
        Engine::InputManager _inputManager;
        Engine::FPSLimiter _fpsLimiter;
    };

