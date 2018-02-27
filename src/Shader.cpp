#include "Shader.hpp"

#include<iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.hpp"
using std::cout;
using std::endl;


Shader::Shader(const std::string& filepath)
 :m_FilePath(filepath), m_RendererID(0){
	ShaderProgramSource source = parseShader(filepath);
	m_RendererID = createShader(source.VertexSource, source.FragmentSource);

}

Shader::~Shader() {
	GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::parseShader (const std::string& filepath){
	std::ifstream stream (filepath);

	enum class ShaderType{
		NONE = -1, VERTEX =0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type =  ShaderType::NONE;

	while(getline(stream, line)){
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos){
				type = ShaderType::VERTEX;

			}
			else if (line.find("fragment") != std::string::npos) {
				type= ShaderType::FRAGMENT;
			}
		} else {
			ss[static_cast<int>(type)] << line << '\n';
		}

	}
	return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::compileShader (unsigned int type, const std::string& source){
	 unsigned int id = glCreateShader(type);
	 const char *src = source.c_str();
	 glShaderSource(id,1,&src,nullptr);
	 glCompileShader(id);

	 int result;
	 glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	 if (result == GL_FALSE){
		 int length;
		 glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		 char message[length];
		 glGetShaderInfoLog(id, length, &length,message);
		 cout<<"Failed to compile" << (type==GL_VERTEX_SHADER ? "vertex" : "fragment") <<"shader"<<endl;
		 cout<<message<<endl;
		 glDeleteShader(id);
		 return 0;
	 }

	 return id;
}


unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader){
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER,vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER,fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


void Shader::Bind() const {
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value) {
	GLCall(glUniform1i(GetUniformLocation(name),value));
}

void Shader::SetUniform1f(const std::string& name, float value) {
	GLCall(glUniform1f(GetUniformLocation(name),value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(GetUniformLocation(name),v0,v1,v2,v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4&  matrix) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) {
	if (m_UniformLocationCache.find(name)!= m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1 )
		std::cout<< "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	m_UniformLocationCache[name]= location;
	return location;
}
