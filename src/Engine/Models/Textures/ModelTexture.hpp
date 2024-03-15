#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include <GL/gl.h>

namespace MyEngine {
    namespace Textures {
        class ModelTexture {
            private:
                GLuint m_id;
                float m_shineDamper;
                float m_reflectivity;

                bool m_hasTransparency;
                bool m_useFakeLighting;

            public:
                ModelTexture(GLuint id, float shineDamp, float reflectivity, bool hasTransparency, bool fakeLighting);
                GLuint GetID() const;

                float GetShineDamper() const { return m_shineDamper; }
                float GetReflectivity() const { return m_reflectivity; }
                bool GetHasTransparency() const { return m_hasTransparency; }
                bool GetUseFakeLighting() const { return m_useFakeLighting; }

                // void SetShineDamper(float value) { m_shineDamper = value; }
                // void SetReflectivity(float value) { m_reflectivity = value; }
        };
    }
}

#endif
