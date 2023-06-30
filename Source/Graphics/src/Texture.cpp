#include "Graphics/Texture.h"

#include <Core/Core.h>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


using namespace an::gfx;



Texture::Texture(const std::string &_path) : path(_path)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc *data = stbi_load(_path.c_str(), &width, &height, &channels, 0);
    AN_ASSERT(data, "Failed to load texture.");
    this->width = width;
    this->height = height;

    GLenum internalFormat = 0, dataFormat = 0;
    if(channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if(channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    this->internalFormat = internalFormat;
    this->dataFormat = dataFormat;

    glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
    glTextureStorage2D(rendererID, 1, internalFormat, width, height);

    glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_LINEAR);

    glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &rendererID);
}

void Texture::Bind(uint32_t _slot /*= 0*/) const
{
    glBindTextureUnit(_slot, rendererID);
}
