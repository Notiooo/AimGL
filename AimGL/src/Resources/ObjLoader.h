#pragma once
#include <Renderer/Graphics/3D/Core/Vertex.h>
#include <fstream>

/**
 * \brief A .obj object loader to read an object and return vertices,
 * indices and additional information about the 3D object.
 *
 * \warning At this point ObjLoader duplicates the vertices, and the indexes are
 * a sequence of numbers 1 ... x. In the future, you should make the vertices
 * unique and the indexes determine their drawing order.
 */
class ObjLoader
{
public:
    /**
     * \brief Flags to change the way 3D objects are loaded.
     */
    enum class Flags
    {
        ForceCenterAtOrigin
    };

    /**
     * \brief Constructor of ObjLoader class
     * \param objFilePath The path to the .obj file to read
     * \param flags Flags to modify object loading behavior
     */
    explicit ObjLoader(const std::string& objFilePath, std::vector<Flags> flags = {});

    /**
     * \brief Returns the vertices from which the loaded object is constructed
     * \return Vertices from which the loaded object is constructed
     */
    [[nodiscard]] std::vector<Vertex> vertices() const;

    /**
     * \brief Returns the indexes that determine the order in which the vertices are drawn
     * \return Indexes that determine the order in which the vertices are drawn
     */
    [[nodiscard]] std::vector<unsigned int> indices() const;

    /**
     * \brief Returns the dimensions of the loaded object
     * \return The dimensions of the loaded object
     */
    [[nodiscard]] glm::vec3 dimensions() const;

    /**
     * \brief Returns the MidPoint of the object, which is the point
     * placed after the center of the object.
     * \return MidPoint of the object, which is the point placed after the center of the
     * object.
     */
    [[nodiscard]] glm::vec3 midPoint() const;

private:
    /**
     * \brief Loads a 3d object from an obj file
     * \param objFilePath Path to obj file
     */
    void loadObject(const std::string& objFilePath);

    /**
     * \brief Updates object dimension information based on the passed object vertex
     * \param vec New vertex on the basis of which the dimensions of the object should be updated
     */
    void updateDimensionsInformations(const glm::vec3& vec);

    /**
     * \brief Reads a vertex and writes it a vector of vertices
     * \param ss StringStream containing text with vertex representation in obj
     */
    void parseVertex(std::istringstream& ss);

    /**
     * \brief Reads a normal and writes it a vector of normal
     * \param ss StringStream containing text with normal representation in obj
     */
    void parseNormal(std::istringstream& ss);

    /**
     * \brief Reads a texture coordinate and writes it a vector of texture coordinates
     * \param ss StringStream containing text with texture coordinate representation in obj
     */
    void parseTextureCoordinate(std::istringstream& ss);

    /**
     * \brief Reads an indexes and returns a tuple of 3 indexes
     * \param faceText Textual representation of a set of three indices from inside an obj file
     * \return Three indexes read
     */
    std::tuple<int, int, int> parseIndices(const std::string& faceText);

    /**
     * \brief Reads a face and writes it a vector of indexes
     * \param ss StringStream containing text with face representation in obj
     */
    void parseFace(std::istringstream& ss);

    /**
     * \brief Reads the line from the obj file transforming it
     * into the appropriate vertex/index/normal etc.
     * \param line A line of text from the obj file
     */
    void parseLine(const std::string& line);

private:
    std::vector<Vertex> mVertices;
    std::vector<glm::vec3> mPositions;
    std::vector<glm::vec3> mNormals;
    std::vector<glm::vec2> mTextureCoordinates;
    std::vector<unsigned int> mIndices;

    std::vector<Flags> mFlags;
    glm::vec3 mDimensions;
    glm::vec3 mMidPoint;
    glm::vec3 mLowestDimensions{std::numeric_limits<float>::max(),
                                std::numeric_limits<float>::max(),
                                std::numeric_limits<float>::max()};
    glm::vec3 mBiggestDimensions{std::numeric_limits<float>::lowest(),
                                 std::numeric_limits<float>::lowest(),
                                 std::numeric_limits<float>::lowest()};
};
