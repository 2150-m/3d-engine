#include "Engine/Shaders/Water/WaterShader.hpp"
#include "Engine/ECS/Components/LightComponent.hpp"
#include "Engine/Globals.hpp"
#include "Engine/Other/Math.hpp"
#include "Engine/Other/Settings.hpp"

namespace MyEngine {
	using namespace Water;

	const std::string WaterShader::VERTEX_SOURCE = "src/Engine/Shaders/Water/WaterVertex.glsl";
	const std::string WaterShader::FRAGMENT_SOURCE = "src/Engine/Shaders/Water/WaterFragment.glsl";

	WaterShader::WaterShader() : ShaderProgram(VERTEX_SOURCE.c_str(), FRAGMENT_SOURCE.c_str()) {
		BindAttributes();
		GetAllUniformLocations();
	}

	void WaterShader::BindAttributes() {
		BindAttribute(0, "position");
	}

	void WaterShader::GetAllUniformLocations() {
		location_projectionMat = GetUniformLocation("projectionMat");
		location_viewMat = GetUniformLocation("viewMat");
		location_modelMat = GetUniformLocation("modelMat");
		location_reflectionTex = GetUniformLocation("reflectionTex");
		location_refractionTex = GetUniformLocation("refractionTex");
		location_dudvMap = GetUniformLocation("dudvMap");
		location_moveFactor = GetUniformLocation("moveFactor");
		location_cameraPosition = GetUniformLocation("cameraPosition");
		location_normalMap = GetUniformLocation("normalMap");
		location_lightPosition = GetUniformLocation("lightPosition");
		location_lightColor = GetUniformLocation("lightColor");
		location_depthMap = GetUniformLocation("depthMap");
		location_cameraNearPlane = GetUniformLocation("cameraNearPlane");
		location_cameraFarPlane = GetUniformLocation("cameraFarPlane");
	}

	void WaterShader::LoadMoveFactor(float factor) {
		LoadFloat(location_moveFactor, factor);
	}

	void WaterShader::LoadProjectionMat(const glm::mat4& matrix) {
		ShaderProgram::LoadMatrix(location_projectionMat, matrix);
	}

	void WaterShader::LoadViewMat(const Entities::Camera& camera) {
		ShaderProgram::LoadMatrix(location_viewMat, Other::Maths::CreateViewMatrix(camera));
		LoadVector(location_cameraPosition, camera.GetPosition());

		LoadFloat(location_cameraNearPlane, Settings::nearPlane);
		LoadFloat(location_cameraFarPlane, Settings::farPlane);
	}

	void WaterShader::LoadModelMat(const glm::mat4& matrix) {
		ShaderProgram::LoadMatrix(location_modelMat, matrix);
	}

	void WaterShader::ConnectTextureUnits() {
		LoadInt(location_reflectionTex, 0);
		LoadInt(location_refractionTex, 1);
		LoadInt(location_dudvMap, 2);
		LoadInt(location_normalMap, 3);
		LoadInt(location_depthMap, 4);
	}

	// TODO: add multilight support
	void WaterShader::LoadLight(const Components::LightComponent& light) {
		LoadVector(location_lightColor, light.GetColor());
		LoadVector(location_lightPosition, Globals::entityMap.at(light.GetEntityID()).GetPosition());
	}
}
