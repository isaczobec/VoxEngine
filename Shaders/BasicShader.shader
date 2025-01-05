#shader vertex
#version 440

layout(location = 0) in vec3 trow0;
layout(location = 1) in vec3 trow1;
layout(location = 2) in vec3 trow2;
out vec4 fragPosition;

// uniform mat4 u_projectionMatrix;
uniform vec2 u_vertexPositions[4];

void main()
{
   vec3 pos = vec3(u_vertexPositions[gl_VertexID % 3],1.0);
   mat3 transformMat = mat3(trow0, trow1, trow2)
   vec3 transformed = transformMat * pos;
  
   gl_Position =  vec4(pos,1.0);
   fragPosition = vec4(pos,1.0);
};


#shader fragment
#version 440

in vec4 fragPosition;
layout(location = 0) out vec4 color;

void main()
{
   color = vec4(1,fragPosition.x,fragPosition.y,1);
};