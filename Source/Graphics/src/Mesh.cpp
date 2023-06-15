#include "Graphics/Mesh.h"

#include "Graphics/VertexBuffer.h"

using namespace an::gfx;

Mesh::Mesh(std::unique_ptr<VertexArray> vertArray) : m_vertArray(std::move(vertArray)) {}
