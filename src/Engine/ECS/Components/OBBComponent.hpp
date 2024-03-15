#ifndef OBBHEADER
#define OBBHEADER

#include "Engine/Models/TexturedModel.hpp"

namespace MyEngine {
    namespace Components {
        class OBBComponent {
        public:
            OBBComponent(unsigned entityID, bool debug = false);
            void GenerateModel();

            unsigned GetEntityID() const { return m_entityID; }
            Models::TexturedModel& GetModel() { return m_model; }
            bool GetVisualDebugging() const { return m_visualDebugging; }
            bool IsColliding() const { return m_isColliding; }

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
