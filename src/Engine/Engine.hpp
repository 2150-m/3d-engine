#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Engine/Include.hpp"

namespace MyEngine {
    class Engine {
    public:
        Engine();
        void Run();

    private:
        void LoadDefaults();
        void SetMemberVars();

        void GameSystemsUpdate();

        void WaterRenderPasses(Rendering::MasterRenderer& renderer, Entities::Camera& camera, Water::WaterFrameBuffer& waterFBOs, std::vector<Water::WaterTile>& waterList);

        void UI_Init();
        void UI_CreateFrames();
        void UI_Update();

        void MainLoopEnd();
        void CleanUp(Water::WaterFrameBuffer&, Rendering::MasterRenderer&);

    private:
        Entities::Camera m_camera;
        Other::MouseRay m_mouseRay;

        // Water::WaterFrameBuffer waterFBOs;
        // Water::WaterShader waterShader;

    };
}

#endif
