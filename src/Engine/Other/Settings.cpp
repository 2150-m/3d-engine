#include "Engine/Other/Settings.hpp"

using namespace MyEngine::Settings;

// APP
constexpr int windowWidth = 1280;
constexpr int windowHeight = 720;

// PLAYER
constexpr float fov = 70, nearPlane = 0.1f, farPlane = 1000;
constexpr float mouseSensitivity = 0.1f;

constexpr float gravity = -0.01;

constexpr float runSpeed = 0.2, turnSpeed = 3, jumpPower = 0.2;

// SHADERS
constexpr float WAVE_SPEED = 0.0003f;
