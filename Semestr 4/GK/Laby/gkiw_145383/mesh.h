#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shaderprogram.h"


struct Vertex {
    glm::vec4 Position;
    glm::vec4 Normal;
    glm::vec2 TexCoord;
};

struct Texture {
    GLuint id;
    std::string type;
    aiString path;
};


class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        this->SetupMesh();
    }

    void Draw(ShaderProgram shader) {
        GLuint diffuseNr =1;
        GLuint specularNr =1;

        for(GLuint i=0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            std::stringstream ss;
            std::string number;
            std::string name = this->textures[i].type;

            if(name == "texture_diffuse") {
                ss << diffuseNr++;
            }
            else if(name == "texture_specular") {
                ss << specularNr++;
            }

            number = ss.str();

            glUniform1i( glGetUniformLocation(shader.shaderProgram, (name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, this->textures[i].id);

        }

        glUniform1f(glGetUniformLocation(shader.shaderProgram, "material.shininess"), 16.0f);

        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        for(GLuint i=0; i<this->textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
private:
    GLuint VAO, VBO, EBO;

    void SetupMesh() {
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);


        //vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

        //vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

        //vertex texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));

        glBindVertexArray(0);
    }
};