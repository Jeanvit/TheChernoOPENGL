/*
 * VertexBuffer.cpp
 *
 *  Created on: 13 de dez de 2017
 *      Author: Casa
 */
#include "VertexBuffer.hpp"
#include "Renderer.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	GLCall(glGenBuffers(1,&m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1,&m_RendererID));
}

void VertexBuffer::Bind()const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind()const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
