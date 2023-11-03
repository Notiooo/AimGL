#include "VertexBuffer.h"
#include "Renderer3D/OpenglUtils.h"
#include "pch.h"

VertexBuffer::VertexBuffer()
{
    GLCall(glGenBuffers(1, &mBufferId));
}

VertexBuffer::VertexBuffer(const void* data, unsigned size)
    : VertexBuffer()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mBufferId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &mBufferId));
}

void VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mBufferId));
}

void VertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::setBuffer(const void* data, unsigned size)
{
    bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
