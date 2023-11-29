#version 330 core

out vec4 FragColor;

in vec3 FragmentNormal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 lightPos = vec3(3, 3, 3);
uniform vec3 cameraPosition;
uniform vec3 lightColor = vec3(1,1,1);

struct Material {
    bool isDiffusePresent;
    bool isSpecularPresent;
    sampler2D diffuse;
    sampler2D specular; // not used yet
};

uniform Material material;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambientColor = vec3(1.0, 1.0, 1.0);
    vec3 ambient = ambientStrength * ambientColor;

    // diffuse
    vec3 norm = normalize(FragmentNormal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseLight = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine texture color with lighting
    vec3 textureColor = vec3(1,1,1);
    if(material.isDiffusePresent)
    {
        textureColor = vec3(texture(material.diffuse, TexCoords));
    }
    vec3 result = textureColor * (ambient + diffuseLight) + specular;
    FragColor = vec4(result, 1.0);
}