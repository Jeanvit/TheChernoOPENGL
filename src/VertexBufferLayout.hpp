/*
 * VertexBufferLayout.hpp
 *
 *  Created on: 22 de dez de 2017
 *      Author: Casa
 */

#ifndef SRC_VERTEXBUFFERLAYOUT_HPP_
#define SRC_VERTEXBUFFERLAYOUT_HPP_

#include <vector>
#include "Renderer.hpp"
#include <GL/glew.h>

struct VertexBufferElement{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type){
		switch(type){
			case GL_FLOAT: 			return 4;
			case GL_UNSIGNED_INT: 	return 4;
			case GL_UNSIGNED_BYTE: 	return 1;
		}
		ASSERT(false);
		return 0;
	}

};

class VertexBufferLayout{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout():
		m_Stride(0){};



	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride;}
	template<typename T> void Push(unsigned int count){	ASSERT(false);}

};

/* I had to inline all the code so it could work*/
/* GCC doesn't seem to accept template specialization inside the class*/

	template<> inline void VertexBufferLayout::Push<float>(unsigned int count){
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride+=count * VertexBufferElement::GetSizeOfType(GL_FLOAT);

	}

	template<> inline void VertexBufferLayout::Push<unsigned int>(unsigned int count){
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride+=count *VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);

	}

	template<> inline void VertexBufferLayout::Push<unsigned char>(unsigned int count){
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride+=count *VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);

	}





#endif /* SRC_VERTEXBUFFERLAYOUT_HPP_ */
