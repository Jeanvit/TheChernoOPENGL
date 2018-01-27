#ifndef SRC_VERTEXARRAY_HPP_
#define SRC_VERTEXARRAY_HPP_
#include "VertexBuffer.hpp"

class VertexBufferLayout;

class VertexArray{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};


#endif
