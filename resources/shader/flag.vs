#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time=0;
uniform float center_x;
void main()
{
    
    FragPos = vec3(model * vec4(aPos, 1.0));
    if(time!=0.0)
    {
        FragPos.z += (center_x-FragPos.x) *0.15*cos(10*time - 3.0*2.0*FragPos.x + 1.5*2.0*FragPos.y);
        
    }
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoords = aTexCoords;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}