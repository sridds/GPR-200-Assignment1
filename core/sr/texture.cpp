#include "texture.h"

Texture2D::Texture2D(const char* filePath, int filterMode, int wrapMode, bool flipOnLoad) {
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
    // load image, create texture and generate mipmapsa

    int nrChannels;

    stbi_set_flip_vertically_on_load(flipOnLoad);
    unsigned char* data = stbi_load(filePath, &m_width, &m_height, &nrChannels, 0);
    if (data) 
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture: " << filePath << std::endl;
        exit(-1);
    }

    stbi_image_free(data);
}

// Binds to a specific texture unit
void Texture2D::Bind(unsigned int slot) {
    glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

Texture2D::~Texture2D() {

}

// Returns the private m_id variable to the user
int Texture2D::GetID() {
	return m_id;
}

int Texture2D::GetWidth() {
    return m_width;
}

int Texture2D::GetHeight() {
    return m_height;
}