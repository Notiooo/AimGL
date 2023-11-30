#version 330 core

out vec4 FragColor;

in vec3 FragmentNormal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 lightPos = vec3(3, 3, 3);
vec3 lightAmbient = vec3(0.3f, 0.3f, 0.3f);
vec3 lightDiffuse = vec3(0.6f, 0.6f, 0.6f);
vec3 lightSpecular = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightColor = vec3(1,1,1);
uniform vec3 cameraPosition;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    bool isDiffusePresent;
    bool isSpecularPresent;
    sampler2D diffuse;
    sampler2D specular;
};

uniform Material material;

void main()
{
    // ambient
    vec3 ambient = lightAmbient;
    if(material.isDiffusePresent)
    {
        ambient = ambient * texture(material.diffuse, TexCoords).rgb;
    }

    // diffuse
    vec3 norm = normalize(FragmentNormal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightDiffuse * diff;
    if(material.isDiffusePresent)
    {
        diffuse = diffuse * texture(material.diffuse, TexCoords).rgb;
    }

    // specular
    vec3 viewDir = normalize(cameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.f);
    vec3 specular = lightSpecular * spec;
    if(material.isSpecularPresent)
    {
        specular = specular * texture(material.specular, TexCoords).rgb;
    }

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}