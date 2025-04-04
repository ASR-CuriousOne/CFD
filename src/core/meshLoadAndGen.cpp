#include "core.hpp"
#include <cstdint>
#include <cstdio>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "../../lib/TinyObjLoader/tiny_obj_loader.h"
#include "../../lib/stb/stb_image.h"

namespace Core{

    
    
    void CalculateTangents(std::vector<Vertex>& vertices,const std::vector<uint32_t>& indices){
        for (int i = 0; i < indices.size(); i+=3) {
            uint32_t i0 = indices[i];
            uint32_t i1 = indices[i+1];
            uint32_t i2 = indices[i+2];

            glm::vec3 e1 = vertices[i1].pos - vertices[i0].pos;
            glm::vec3 e2 = vertices[i2].pos - vertices[i0].pos;

            float deltaU1 = vertices[i1].texCoord.x - vertices[i0].texCoord.x;
            float deltaV1 = vertices[i1].texCoord.y - vertices[i0].texCoord.y;

            float deltaU2 = vertices[i2].texCoord.x - vertices[i0].texCoord.x;
            float deltaV2 = vertices[i2].texCoord.y - vertices[i0].texCoord.y;

            float divider = 1.0f/(deltaU1 * deltaV2 - deltaU2 * deltaV1);

            glm::vec3 tangent = glm::normalize(divider * (deltaV2 * e1 - deltaV1 * e2));

            vertices[i0].tangent = tangent;
            vertices[i1].tangent = tangent;
            vertices[i2].tangent = tangent;


        }
    }

    void Application::loadModel(){
        std::ifstream settings("settings.txt");

        std::getline(settings,MODEL_PATH);
        std::getline(settings,TEXTURE_PATH);
        std::getline(settings,NORMAL_PATH);

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str())) {
            throw std::runtime_error(warn + err);
        }

        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex{};

                vertex.pos = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };
                
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
                };
                
                vertex.color = {1.0f, 1.0f, 1.0f};
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]

                };          

                m_vertices.push_back(vertex);
                m_indices.push_back(m_indices.size());
            }
        }

        CalculateTangents(m_vertices, m_indices);

    }

}
