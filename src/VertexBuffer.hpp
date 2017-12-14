/*
 * VertexBuffer.hpp
 *
 *  Created on: 13 de dez de 2017
 *      Author: Casa
 */

#ifndef SRC_VERTEXBUFFER_HPP_
#define SRC_VERTEXBUFFER_HPP_

class VertexBuffer{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};







#endif /* SRC_VERTEXBUFFER_HPP_ */
