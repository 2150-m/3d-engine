#ifndef GAMEINCLUDE
#define GAMEINCLUDE

#include "Engine/Engine.hpp"

using namespace MyEngine;

class Game {
    public:
        void Start();

    private:
        void DemoLvl_InitVars();
        void DemoLvl_StartingState();

    private:
        Engine engine;

};

#endif
