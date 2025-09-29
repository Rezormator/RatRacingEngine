#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shininess;
};

struct TextureMaterial {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define DIRECTIONAL_LIGHTS_COUNT 1
#define POINT_LIGHTS_COUNT 1
#define SPOT_LIGHTS_COUNT 1

uniform DirectionalLight directionalLights[DIRECTIONAL_LIGHTS_COUNT];
uniform PointLight pointLights[POINT_LIGHTS_COUNT];
uniform SpotLight spotLights[SPOT_LIGHTS_COUNT];

uniform vec3 viewPos;

uniform Material material;
uniform TextureMaterial textureMaterial;
uniform bool isLight;
uniform bool isTextureMaterial;

vec3 CalculateAllLights(Material materialParts);
vec3 CalculateDirectionalLight(Material materialParts, DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(Material materialParts, PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos);
vec3 CalculateSpotLight(Material materialParts, SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos);

void main() {
    vec3 result;

    if (isLight) {
        result = vec3(1.0f, 1.0f, 1.0f);
    }
    else {
        if (isTextureMaterial) {
            Material texMaterial;
            texMaterial.ambient = vec3(texture(textureMaterial.diffuse, TexCoords));
            texMaterial.diffuse = vec3(texture(textureMaterial.diffuse, TexCoords));
            texMaterial.specular = vec3(texture(textureMaterial.specular, TexCoords));
            texMaterial.shininess = textureMaterial.shininess;
            texMaterial.emission = vec3(texture(textureMaterial.emission, TexCoords));
            result = CalculateAllLights(texMaterial);
        }
        else {
            result = CalculateAllLights(material);
        }
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalculateAllLights(Material materialParts) {
    vec3 result;

    if (materialParts.emission != vec3(0.0)) {
        return materialParts.emission;
    }

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    for (int i = 0; i < DIRECTIONAL_LIGHTS_COUNT; i++) {
        if (directionalLights[i].ambient == vec3(0.0)) {
            continue;
        }
        result += CalculateDirectionalLight(materialParts, directionalLights[i], norm, viewDir);
    }

    for (int i = 0; i < POINT_LIGHTS_COUNT; i++) {
        if (pointLights[i].ambient == vec3(0.0)) {
            continue;
        }
        result += CalculatePointLight(materialParts, pointLights[i], norm, viewDir, FragPos);
    }

    for (int i = 0; i < SPOT_LIGHTS_COUNT; i++) {
        if (spotLights[i].ambient == vec3(0.0)) {
            continue;
        }
        result += CalculateSpotLight(materialParts, spotLights[i], norm, viewDir, FragPos);
    }

    return result;
}

vec3 CalculateDirectionalLight(Material materialParts, DirectionalLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.direction);

    vec3 ambient = light.ambient * materialParts.ambient;

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * materialParts.diffuse;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialParts.shininess);
    vec3 specular = light.specular * spec * materialParts.specular;

    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(Material materialParts, PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos) {
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * materialParts.ambient;

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * materialParts.diffuse;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialParts.shininess);
    vec3 specular = light.specular * spec * materialParts.specular;

    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalculateSpotLight(Material materialParts, SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos) {
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    if (theta <= light.outerCutOff) {
        return light.ambient * materialParts.ambient * attenuation;
    }

    vec3 ambient = light.ambient * materialParts.diffuse;

    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * materialParts.diffuse;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialParts.shininess);
    vec3 specular = light.specular * spec * materialParts.specular;

    return (ambient + diffuse * intensity + specular * intensity) * attenuation;
}
