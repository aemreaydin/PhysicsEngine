#version 430
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 ObjectPosition;
in vec3 LightPosition;

uniform vec4 AmbientColor;
uniform vec4 DiffuseColor;
uniform vec4 SpecularColor;
uniform vec3 Attenuation;
uniform vec3 LightDirection;
uniform vec2 Cutoff;
uniform int LightType;
uniform vec3 eyePos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height;

void main()
{    
	if(LightType == 0)
	{
		float AmbientStr = 0.0;
		vec3 ambientColor;
		ambientColor = AmbientColor.xyz * AmbientStr;
		
		vec3 normalizedNormal = normalize(Normal);
		vec3 lightDir = normalize(-LightDirection);
		float diffuseRatio = max(dot(normalizedNormal, lightDir), 0.0);
		vec3 diffuseColor;
		diffuseColor = diffuseRatio * DiffuseColor.xyz;
		
		float specularStr = 0.9;
		vec3 viewDir = normalize(eyePos - LightPosition);
		vec3 reflectDir = reflect(-lightDir, normalizedNormal);
		float specularRatio = pow(max(dot(viewDir, reflectDir), 0.0), 64);
		vec3 specularColor;
		specularColor = specularRatio * specularStr * SpecularColor.xyz;
		
		vec3 lightColor = ambientColor + diffuseColor + specularColor;
		//vec3 lightColor = ambientColor + diffuseColor; // + specularColor;
		FragColor = vec4(lightColor, 1.0) * (texture(texture_diffuse1, TexCoords));
										  //+ texture(texture_specular1, TexCoords));
										  //+ texture(texture_normal1, TexCoords));
	}
	else if(LightType == 1)
	{
		float distance = length(LightPosition - ObjectPosition);
		float attenuation = 1.0 / (Attenuation.x + Attenuation.y * distance + Attenuation.z * (distance * distance));
	
		float AmbientStr = 0.0;
		vec3 ambientColor;
		ambientColor = AmbientColor.xyz * AmbientStr;
		ambientColor *= attenuation;
		
		vec3 normalizedNormal = normalize(Normal);
		vec3 lightDir = normalize(LightPosition - ObjectPosition);
		float diffuseRatio = max(dot(normalizedNormal, lightDir), 0.0);
		vec3 diffuseColor;
		diffuseColor = diffuseRatio * DiffuseColor.xyz;
		diffuseColor *= attenuation;
		
		float specularStr = 0.9;
		vec3 viewDir = normalize(eyePos - LightPosition);
		vec3 reflectDir = reflect(-lightDir, normalizedNormal);
		float specularRatio = pow(max(dot(viewDir, reflectDir), 0.0), 64);
		vec3 specularColor;
		specularColor = specularRatio * specularStr * SpecularColor.xyz;
		specularColor *= attenuation;
		
		vec3 lightColor = ambientColor + diffuseColor + specularColor;
		//vec3 lightColor = ambientColor + diffuseColor; // + specularColor;
		FragColor = vec4(lightColor, 1.0) * (texture(texture_diffuse1, TexCoords));
										  //+ texture(texture_specular1, TexCoords));
										  //+ texture(texture_normal1, TexCoords));
	}
	else if(LightType == 2)
	{
		float distance = length(LightPosition - ObjectPosition);
		float attenuation = 1.0 / (Attenuation.x + Attenuation.y * distance + Attenuation.z * (distance * distance));
	
		float AmbientStr = 0.0;
		vec3 ambientColor;
		ambientColor = AmbientColor.xyz * AmbientStr;
		
		
		vec3 normalizedNormal = normalize(Normal);
		vec3 lightDir = normalize(LightPosition - ObjectPosition);
		float diffuseRatio = max(dot(normalizedNormal, lightDir), 0.0);
		vec3 diffuseColor;
		diffuseColor = diffuseRatio * DiffuseColor.xyz;
		
		
		float specularStr = 0.9;
		vec3 viewDir = normalize(eyePos - LightPosition);
		vec3 reflectDir = reflect(-lightDir, normalizedNormal);
		float specularRatio = pow(max(dot(viewDir, reflectDir), 0.0), 64);
		vec3 specularColor;
		specularColor = specularRatio * specularStr * SpecularColor.xyz;
		
		float theta = dot(lightDir, normalize(-LightDirection));
		float epsilon = -(Cutoff.x - Cutoff.y);
		float intensity = clamp((theta - Cutoff.y) / epsilon, 0.0, 1.0);
		diffuseColor *= intensity;
		specularColor *= intensity;	
		
		
		ambientColor *= attenuation;
		diffuseColor *= attenuation;
		specularColor *= attenuation;		
		vec3 lightColor = ambientColor + diffuseColor + specularColor;
		//vec3 lightColor = ambientColor + diffuseColor; // + specularColor;
		FragColor = vec4(lightColor, 1.0) * (texture(texture_diffuse1, TexCoords));
										  //+ texture(texture_specular1, TexCoords));
										  //+ texture(texture_normal1, TexCoords));
	}
}

