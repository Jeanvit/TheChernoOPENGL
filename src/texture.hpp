/*
 * texture.hpp
 *
 *  Created on: 20 de fev de 2018
 *      Author: Casa
 */

#ifndef SRC_TEXTURE_HPP_
#define SRC_TEXTURE_HPP_
#include "Renderer.hpp"

class Texture{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char * m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};


#endif /* SRC_TEXTURE_HPP_ */
