/*
 * Renderer.cpp
 *
 *  Created on: 13 de dez de 2017
 *      Author: Casa
 */
#include "Renderer.hpp"
#include <iostream>

void GLClearError(){
	while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line){
	while (GLenum error = glGetError()){
		std::cout<<"[OpenGL Error] (" << error << ") " << function <<" "<< file << " " << line << std::endl;
		return false;
	}
	return true;
}



void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES,ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

}
