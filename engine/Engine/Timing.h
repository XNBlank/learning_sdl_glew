#pragma once

namespace Engine{

    class FPSLimiter{
        public:
            FPSLimiter();
            void SetMaxFPS(float maxFPS);
            void Init(float maxFPS);
            void Begin();
            float End(); //Will return FPS values

        private:
            void calculateFPS();
            float _fps;
            float _maxFPS;
            float _frameTime;
            unsigned int _startTicks;

    };

}
