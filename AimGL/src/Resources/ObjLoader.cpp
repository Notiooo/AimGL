#include "ObjLoader.h"
#include "pch.h"

ObjLoader::ObjLoader(const std::string& objFilePath, std::vector<Flags> flags)
    : mFlags(flags)
{
    loadObject(objFilePath);
}

std::vector<Vertex> ObjLoader::vertices() const
{
    return mVertices;
}

std::vector<unsigned> ObjLoader::indices() const
{
    return mIndices;
}

glm::vec3 ObjLoader::dimensions() const
{
    return mDimensions;
}

glm::vec3 ObjLoader::midPoint() const
{
    return mMidPoint;
}

void ObjLoader::loadObject(const std::string& objFilePath)
{
    std::ifstream file(objFilePath);
    std::string line;
    while (std::getline(file, line))
    {
        parseLine(line);
    }

    mDimensions = {mBiggestDimensions.x - mLowestDimensions.x,
                   mBiggestDimensions.y - mLowestDimensions.y,
                   mBiggestDimensions.z - mLowestDimensions.z};

    mMidPoint = {((mBiggestDimensions.x + mLowestDimensions.x) / 2.f),
                 ((mBiggestDimensions.y + mLowestDimensions.y) / 2.f),
                 ((mBiggestDimensions.z + mLowestDimensions.z) / 2.f)};

    if (std::find(mFlags.begin(), mFlags.end(), Flags::ForceCenterAtOrigin) != mFlags.end())
    {
        for (auto& vertex: mVertices)
        {
            vertex.position.x -= mMidPoint.x;
            vertex.position.y -= mMidPoint.y;
            vertex.position.z -= mMidPoint.z;
        }
    }

    mPositions.clear();
    mNormals.clear();
    mTextureCoordinates.clear();
}

void ObjLoader::updateDimensionsInformations(const glm::vec3& vec)
{
    if (vec.x > mBiggestDimensions.x)
    {
        mBiggestDimensions.x = vec.x;
    }
    if (vec.y > mBiggestDimensions.y)
    {
        mBiggestDimensions.y = vec.y;
    }
    if (vec.z > mBiggestDimensions.z)
    {
        mBiggestDimensions.z = vec.z;
    }

    if (vec.x < mLowestDimensions.x)
    {
        mLowestDimensions.x = vec.x;
    }
    if (vec.y < mLowestDimensions.y)
    {
        mLowestDimensions.y = vec.y;
    }
    if (vec.z < mLowestDimensions.z)
    {
        mLowestDimensions.z = vec.z;
    }
}

void ObjLoader::parseVertex(std::istringstream& ss)
{
    glm::vec3 position;
    ss >> position.x >> position.y >> position.z;
    updateDimensionsInformations(position);
    mPositions.push_back(position);
}

void ObjLoader::parseNormal(std::istringstream& ss)
{
    glm::vec3 normal;
    ss >> normal.x >> normal.y >> normal.z;
    mNormals.push_back(normal);
}

void ObjLoader::parseTextureCoordinate(std::istringstream& ss)
{
    glm::vec2 textureCoordinate;
    ss >> textureCoordinate.x >> textureCoordinate.y;
    mTextureCoordinates.push_back(textureCoordinate);
}

std::tuple<int, int, int> ObjLoader::parseIndices(const std::string& faceText)
{
    std::istringstream vertexStream(faceText);
    std::string index;
    std::vector<int> indices;

    while (std::getline(vertexStream, index, '/'))
    {
        if (!index.empty())
        {
            indices.push_back(std::stoi(index) - 1);
        }
    }

    return {indices[0], indices[1], indices[2]};
}

void ObjLoader::parseFace(std::istringstream& ss)
{
    std::string vertex;
    while (ss >> vertex)
    {
        // TODO: Index buffer is useless and vertices are duplicated this way. Should be fixed later
        auto [positionIndex, textureIndex, normalIndex] = parseIndices(vertex);
        Vertex v{mPositions[positionIndex], mNormals[normalIndex],
                 mTextureCoordinates[textureIndex]};
        mVertices.push_back(v);
        mIndices.push_back(mIndices.size());
    }
}

void ObjLoader::parseLine(const std::string& line)
{
    std::istringstream ss(line);
    std::string prefix;
    ss >> prefix;

    if (prefix == "v")
    {
        parseVertex(ss);
    }
    else if (prefix == "vn")
    {
        parseNormal(ss);
    }
    else if (prefix == "vt")
    {
        parseTextureCoordinate(ss);
    }
    else if (prefix == "f")
    {
        parseFace(ss);
    }
}
