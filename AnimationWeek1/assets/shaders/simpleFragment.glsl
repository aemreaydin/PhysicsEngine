#version 430
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords)
			  + texture(texture_specular1, TexCoords);
			  //+ texture(texture_normal1, TexCoords);
			  //+ texture(texture_height, TexCoords);
}