#include "ShaderProgram.h"

namespace Renderer {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER compile error" << std::endl;
			return;
		}

		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER compile error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}

		shaderProgramID = glCreateProgram();
		glAttachShader(shaderProgramID, vertexShaderID);
		glAttachShader(shaderProgramID, fragmentShaderID);
		glLinkProgram(shaderProgramID);

		GLint success;
		glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[512];
			glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER: Link time error:\n" << infoLog << std::endl;
		}
		else
		{
			isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(shaderProgramID);
	}

	void ShaderProgram::use() const
	{
		glUseProgram(shaderProgramID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(shaderProgramID);
		shaderProgramID = shaderProgram.shaderProgramID;
		isCompiled = shaderProgram.isCompiled;
		
		shaderProgram.shaderProgramID = 0;
		shaderProgram.isCompiled = false;
		
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		shaderProgramID = shaderProgram.shaderProgramID;
		isCompiled = shaderProgram.isCompiled;

		shaderProgram.shaderProgramID = 0;
		shaderProgram.isCompiled = false;
	}

	bool ShaderProgram::createShader(const std::string& shaderSource, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* source = shaderSource.c_str();
		glShaderSource(shaderID, 1, &source, NULL);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[512];
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
			std::cerr << "ERROR::Shader: Compile time error:\n" << infoLog << std::endl;
			return false;
		}

		return true;
	}
}

