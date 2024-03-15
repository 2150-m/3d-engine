#ifndef BOXCOLCOMPH
#define BOXCOLCOMPH

#include "Engine/Models/TexturedModel.hpp"

namespace MyEngine {
    namespace Components
    {
        class AABBComponent
        {
        public:
            AABBComponent(unsigned entityID, bool debug = false);
            void GenerateModel();
            void RecalculateAABB();

            unsigned GetEntityID() const { return m_entityID; }
            Models::TexturedModel& GetModel() { return m_model; }
            bool IsColliding() const { return m_isColliding; }
            bool GetVisualDebugging() const { return m_visualDebugging; }

            void SetModel(const Models::TexturedModel& newModel) { m_model = newModel; }
            void SetIsColliding(bool value) { m_isColliding = value; }
            void SetVisualDebugging(bool value) { m_visualDebugging = value; }

        private:
            unsigned m_entityID;

            Models::TexturedModel m_model;

            bool m_isColliding = false;
            bool m_visualDebugging = false;
        };
    }
}

#endif
