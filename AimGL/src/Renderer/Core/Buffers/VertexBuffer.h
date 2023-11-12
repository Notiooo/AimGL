#pragma once
#include "Renderer/Core/Buffers/Buffer.h"
#include "Renderer/Core/OpenglUtils.h"

/**
 * Vertex buffer object (VBO) allows vertex array data to be stored
 * in high-performance graphics memory.
 */
class VertexBuffer : public Buffer
{
public:
    VertexBuffer();
    VertexBuffer(const void* data, unsigned int size);

    template<typename T>
    VertexBuffer(const std::vector<T>& vector);

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) noexcept = default;

    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) noexcept = default;

    ~VertexBuffer() override;

    /**
     * Binds a buffer object to the specific (GL_ARRAY_BUFFER) buffer binding point
     */
    void bind() const override;

    /**
     * Unbinds a buffer object (GL_ARRAY_BUFFER)
     */
    void unbind() const override;

    /**
     * \brief Creates and initializes a buffer object's data store
     * \param data Specifies a pointer to data that will be copied into the
     * data store for initialization, or NULL if no data is to be copied.
     * \param size Specifies the size in bytes of the buffer object's new data store
     */
    void setBuffer(const void* data, unsigned int size);

    /**
     * \brief Creates and initializes a buffer object's data store
     * \tparam T Data type inside the vector
     * \param vector Data that will be copied into the data store for initialization.
     */
    template<typename T>
    void setBuffer(const std::vector<T>& vector);
};

template<typename T>
VertexBuffer::VertexBuffer(const std::vector<T>& vector)
    : VertexBuffer(vector.data(), vector.size() * sizeof(vector[0]))
{
}

template<typename T>
void VertexBuffer::setBuffer(const std::vector<T>& vector)
{
    bind();
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mBufferId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, vector.size(), vector.data(), GL_STATIC_DRAW));
}
