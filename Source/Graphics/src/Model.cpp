#include "Graphics/Model.h"

#include "Graphics/BufferLayout.h"

#include <Core/Logger.h>
#include <tiny_obj_loader.h>

#define TINYOBJLOADER_IMPLEMENTATION

using namespace an::gfx;

namespace
{

an::gfx::Mesh processNode(
    const tinyobj::mesh_t &mesh, const tinyobj::attrib_t &attrib, std::size_t &indexOffset)
{
    constexpr std::size_t vertInFace = 3U;

    std::vector<an::gfx::BufferElement> elements;
    elements.emplace_back("a_Position", an::gfx::ShaderDataType::FLOAT3);
    if(attrib.normals.size() > 0)
        elements.emplace_back("a_Normal", an::gfx::ShaderDataType::FLOAT3);
    if(attrib.texcoords.size() > 0)
        elements.emplace_back("aTextCoord", an::gfx::ShaderDataType::FLOAT2);
    an::gfx::BufferLayout bufferLayout(std::move(elements));

    const int faceCount = mesh.num_face_vertices.size();
    std::vector<float> vertices;
    vertices.reserve(faceCount * vertInFace * bufferLayout.componentCount());

    const auto &tindices = mesh.indices;
    std::vector<unsigned int> indices;
    indices.reserve(tindices.size());

    for(std::size_t faceIdx = 0; faceIdx < faceCount; faceIdx++)
    {
        std::size_t faceVerticesCount = static_cast<std::size_t>(mesh.num_face_vertices[faceIdx]);
        assert(faceVerticesCount == vertInFace);

        for(std::size_t faceVertIdx = 0; faceVertIdx < faceVerticesCount; faceVertIdx++)
        {
            tinyobj::index_t tinyObjIdx = mesh.indices[indexOffset + faceVertIdx];
            std::size_t vertIdx = vertInFace * static_cast<std::size_t>(tinyObjIdx.vertex_index);

            tinyobj::real_t vx = attrib.vertices[vertIdx + 0U];
            tinyobj::real_t vy = attrib.vertices[vertIdx + 1U];
            tinyobj::real_t vz = attrib.vertices[vertIdx + 2U];
            vertices.push_back(vx);
            vertices.push_back(vy);
            vertices.push_back(vz);

            if(tinyObjIdx.normal_index >= 0)
            {
                std::size_t normIdx =
                    vertInFace * static_cast<std::size_t>(tinyObjIdx.normal_index);
                tinyobj::real_t nx = attrib.normals[normIdx + 0U];
                tinyobj::real_t ny = attrib.normals[normIdx + 1U];
                tinyobj::real_t nz = attrib.normals[normIdx + 2U];
                vertices.push_back(nx);
                vertices.push_back(ny);
                vertices.push_back(nz);
            }

            if(tinyObjIdx.texcoord_index >= 0)
            {
                std::size_t textCoordIdx = 2U * static_cast<std::size_t>(tinyObjIdx.texcoord_index);
                tinyobj::real_t tx = attrib.texcoords[textCoordIdx + 0U];
                tinyobj::real_t ty = attrib.texcoords[textCoordIdx + 1U];
                vertices.push_back(tx);
                vertices.push_back(ty);
            }
        }

        indices.push_back(indexOffset);
        indices.push_back(indexOffset + 1U);
        indices.push_back(indexOffset + 2U);
        indexOffset += faceVerticesCount;
    }

    auto vertexBuffer = std::make_unique<an::gfx::VertexBuffer>(
        vertices.data(), vertices.size(), std::move(bufferLayout));

    std::vector<std::unique_ptr<an::gfx::VertexBuffer>> vertBuffers;
    vertBuffers.push_back(std::move(vertexBuffer));

    auto m_vertArray = std::make_unique<an::gfx::VertexArray>();
    m_vertArray->bind();
    auto indexBuffer = std::make_unique<an::gfx::IndexBuffer>(indices.data(), indices.size());

    m_vertArray->setVertexBuffers(std::move(vertBuffers));
    m_vertArray->setIndexBuffer(std::move(indexBuffer));

    return an::gfx::Mesh(std::move(m_vertArray));
}

} // namespace

Model::Model(std::string const &path)
{
    load(path);
}

void Model::load(std::string const &path)
{
    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;

    if(!reader.ParseFromFile(path, reader_config))
    {
        AN_ERROR("[TinyObjReader] Can't pars from file: {}", path);
        if(!reader.Error().empty())
            AN_ERROR("[TinyObjReader] {}", reader.Error());

        return;
    }

    if(!reader.Warning().empty())
        AN_ERROR("[TinyObjReader] {}", reader.Warning());

    const auto &attrib = reader.GetAttrib();
    const auto &shapes = reader.GetShapes();
    const auto &materials = reader.GetMaterials();

    std::size_t indexOffset = 0;
    for(const auto &shape : shapes)
    {
        m_meshes.push_back(processNode(shape.mesh, attrib, indexOffset));
    }
}
