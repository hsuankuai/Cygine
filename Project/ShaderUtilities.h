#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string readFile(const char* name) {
	std::ifstream file(name);
	std::string temp, ret;
	while (std::getline(file, temp)) {
		ret.append(temp + "\n");
	}
	if (!ret.empty()) ret.pop_back();
	return ret;
}

class Shader {
private:
	static int flag;
	static char infoLog[512];
	static std::string shaderSource;
	static std::unordered_map<unsigned int, std::set<unsigned int>> programRes;

public:
	static unsigned int CreateShader(const char* fileAddress, GLenum shaderType) {
		shaderSource = readFile(fileAddress);
		const char* shaderSource_cstr = shaderSource.c_str();
		unsigned int shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &shaderSource_cstr, nullptr);
		glCompileShader(shaderID);
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &flag);

		if (!flag) {
			glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n'
					  << "The source code is shown below:\n" << shaderSource << std::endl;
		}
		else {
			std::cout << "Shader compiled successfully." << std::endl;
		}

		return shaderID;
	}

	static unsigned int CreateShaderProgram(void) {
		return glCreateProgram();
	}

	static void AttachShader(GLuint program, GLuint shader) {
		glAttachShader(program, shader);
		glGetProgramiv(program, GL_LINK_STATUS, &flag);
		if (!flag) {
			glGetProgramInfoLog(program, 512, NULL, infoLog);

		}
	}

	static void LinkProgram(GLuint program, GLboolean reserveShaders = false) {
		glLinkProgram(program);
		if (!reserveShaders) {
			for (const auto& id : programRes[program]) {
				DeleteShader(id);
			}
			programRes.erase(program);
		}
	}

	static int DeleteShader(const int id) {
		glDeleteShader(id);
		return 0;
	}

	static int DeleteShaderProgram(const int id) {
		glDeleteProgram(id);
		return 0;
	}
};

int Shader::flag;
char Shader::infoLog[512];
std::string Shader::shaderSource;
std::unordered_map<unsigned int, std::set<unsigned int>> Shader::programRes;