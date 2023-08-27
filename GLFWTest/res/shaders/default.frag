#version 330 core

in vec2 textureCoord;
in vec3 Normal;
in vec3 worldPosition;

out vec4 color;

#define MAX_LIGHTS 128

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirLight
{
	vec3 Direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 Position;

	float a;
	float b;
	float c;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 Position;
	vec3 Direction;

	float a;
	float b;
	float c;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutOff;
	float outerCutOff;
};

uniform vec3 cameraPosition;
uniform Material material;

uniform int numDirLight;
uniform int numPointLight;
uniform int numSpotLight;

uniform DirLight[MAX_LIGHTS] dirLights;
uniform PointLight[MAX_LIGHTS] pointLights;
uniform SpotLight[MAX_LIGHTS] spotLights;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(worldPosition - cameraPosition);

	vec3 result = vec3(0, 0, 0);

	for (int i = 0; i < numDirLight; i++)
		result += CalcDirLight(dirLights[i], normal, viewDir);

	for (int i = 0; i < numPointLight; i++)
		result += CalcPointLight(pointLights[i], normal, viewDir);

	for (int i = 0; i < numSpotLight; i++)
		result += CalcSpotLight(spotLights[i], normal, viewDir);

	color = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.Direction);

	vec3 ambient = light.ambient * texture(material.diffuse, textureCoord).xyz;

	float diff = max(dot(-lightDir, normal), 0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, textureCoord).xyz;

	vec3 refLightDir = reflect(lightDir, normal);
	float spec = pow(max(dot(refLightDir, -viewDir), 0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, textureCoord);

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(worldPosition - light.Position);

	vec3 ambient = light.ambient * texture(material.diffuse, textureCoord).xyz;

	float diff = max(dot(-lightDir, normal), 0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, textureCoord).xyz;

	vec3 refLightDir = reflect(lightDir, normal);
	float spec = pow(max(dot(refLightDir, -viewDir), 0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, textureCoord);

	float distance = length(light.Position - worldPosition);
	float attenuation = 1.0 / (light.a * distance * distance + light.b * distance + light.c);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(worldPosition - light.Position);
	float theta = dot(lightDir, normalize(light.Direction));

	vec3 ambient = light.ambient * texture(material.diffuse, textureCoord).xyz;

	float diff = max(dot(-lightDir, normal), 0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, textureCoord).xyz;

	vec3 refLightDir = reflect(lightDir, normal);
	float spec = pow(max(dot(refLightDir, -viewDir), 0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, textureCoord);

	float distance = length(light.Position - worldPosition);
	float attenuation = 1.0 / (light.a * distance * distance + light.b * distance + light.c);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	diffuse *= intensity;
	specular *= intensity;

	return (ambient + diffuse + specular);
}