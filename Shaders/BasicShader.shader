#shader vertex
#version 440

layout(location = 0) in vec4 trow0;
layout(location = 1) in vec4 trow1;
layout(location = 2) in vec4 trow2;
layout(location = 3) in vec4 trow3;
out vec4 fragPosition;

// uniform mat4 u_projectionMatrix;
uniform vec2 u_vertexPositions[6];

void main()
{
   vec4 pos = vec4(u_vertexPositions[gl_VertexID % 6],1.0,1.0);
   mat4 transformMat = mat4(trow0, trow1, trow2, trow3);
   vec4 transformed = transformMat * pos;
   transformed[2] = 0;
  
   gl_Position =  transformed;
   fragPosition = transformed;
};


#shader fragment
#version 440

in vec4 fragPosition;
layout(location = 0) out vec4 color;

void main()
{
   color = vec4(1,0,1,1);
};