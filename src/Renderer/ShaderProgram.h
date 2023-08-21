#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>

namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool checkCompiled() const { return isCompiled; };
		void use() const;
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

	private:
		bool createShader(const std::string& shaderSource, const GLenum shaderType, GLuint& shaderID);
		bool isCompiled = false;
		GLuint shaderProgramID;
	};
}