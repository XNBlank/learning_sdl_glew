#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace Engine {

    enum class GlyphSortType
    {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE
    };

    struct Glyph
    {
        GLuint texture;
        float depth;

        Color color;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;
    };

    class RenderBatch {
    public:
        RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
            numVertices(NumVertices), texture(Texture) {
        }
        GLuint offset;
        GLuint numVertices;
        GLuint texture;
    };

    class SpriteBatch
    {
        public:
            SpriteBatch();
            ~SpriteBatch();

            void Init();
            void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
            void End();
            void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint texture, const float depth, const Color color);
            void Render();

        private:
            void createRenderBatches();
            void createVertexArray();
            void sortGlyphs();

            static bool compareFrontToBack(Glyph* a, Glyph* b);
            static bool compareBackToFront(Glyph* a, Glyph* b);
            static bool compareTexture(Glyph* a, Glyph* b);

            GlyphSortType _sortType;
            GLuint _vbo;
            GLuint _vao;
            std::vector<Glyph*> _glyphs;
            std::vector<RenderBatch> _renderBatches;
    };

}
