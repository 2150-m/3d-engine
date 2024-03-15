#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <glm/glm.hpp>

#include "Engine/ECS/EntityManagement.hpp"
#include "Engine/ECS/ComponentManagement.hpp"

#include "Engine/Other/Input.hpp"

#include "Engine/Physics/Physics.hpp"

#include "Engine/Utilities/SaveSystem.hpp"

#include "Engine/Rendering/DisplayManager.hpp"
#include "Engine/Rendering/MasterRenderer.hpp"
#include "Engine/Rendering/OBJLoader.hpp"

#include "Engine/Shaders/Water/WaterRenderer.hpp"
#include "Engine/Shaders/Water/WaterTile.hpp"

#include "Engine/Other/Math.hpp"
#include "Engine/Other/Printer.hpp"
#include "Engine/Other/MouseRay.hpp"

#include "Engine/Other/Input.hpp"

#include "Engine/Globals.hpp"

#include <array>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

#endif
