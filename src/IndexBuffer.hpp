/*
 * VertexBuffer.hpp
 *
 *  Created on: 13 de dez de 2017
 *      Author: Casa
 */

#ifndef SRC_INDEXBUFFER_HPP_
#define SRC_INDEXBUFFER_HPP_

class IndexBuffer{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const {
		return m_Count;
	}


};







#endif /* SRC_VERTEXBUFFER_HPP_ */
