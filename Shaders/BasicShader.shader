#shader vertex
#version 440

layout(location = 0) in vec3 pos;

uniform mat4 mvp;
out vec3 uvPos;

void main()
{
   vec4 pos4d = vec4(pos, 1);
   uvPos = pos;
   gl_Position =  mvp * pos4d;
};


#shader fragment
#version 440

layout(location = 0) out vec4 color;
in vec3 uvPos;

void main()
{

   color = vec4(uvPos,1);
};