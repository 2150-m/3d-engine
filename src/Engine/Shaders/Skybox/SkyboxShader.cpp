#include "Engine/Shaders/Skybox/SkyboxShader.hpp"
#include "Engine/Other/Math.hpp"

namespace MyEngine {
	using namespace Skybox;

	const std::string SkyboxShader::VERTEX_SOURCE = "src/Engine/Shaders/Skybox/SkyboxVertex.glsl";
	const std::string SkyboxShader::FRAGMENT_SOURCE = "src/Engine/Shaders/Skybox/SkyboxFragment.glsl";

	SkyboxShader::SkyboxShader() : ShaderProgram(VERTEX_SOURCE.c_str(), FRAGMENT_SOURCE.c_str()) {
		BindAttributes();
		GetAllUniformLocations();
	}

	void SkyboxShader::BindAttributes() {
		BindAttribute(0, "position");
	}

	void SkyboxShader::GetAllUniformLocations() {
		location_projectionMat = ShaderProgram::GetUniformLocation("projectionMat");
		location_viewMat = ShaderProgram::GetUniformLocation("viewMat");
	}

	void SkyboxShader::LoadProjectionMat(const glm::mat4& matrix) {
		ShaderProgram::LoadMatrix(location_projectionMat, matrix);
	}

	void SkyboxShader::LoadViewMat(const Entities::Camera& camera) {
		glm::mat4 matrix = Other::Maths::CreateViewMatrix(camera);
		matrix[3][0] = 0;
		matrix[3][1] = 0;
		matrix[3][2] = 0;
		// Since the skybox doesn't have a transformation matrix, the view matrix is used as a replacement.
		// The translation values of the matrix need to be set to 0 in order for the skybox to "follow" the camera
		// (it stays at the center of the world, because the camera doesn't actually move - the world around it does)

		ShaderProgram::LoadMatrix(location_viewMat, matrix);
	}
}
