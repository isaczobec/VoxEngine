#shader vertex
#version 440

layout(location = 0) in vec2 pos;
layout(location = 1) in float rot;
layout(location = 2) in vec2 scale;
out vec4 fragPosition;

// uniform mat4 u_projectionMatrix;
uniform vec2 u_vertexPositions[6];

void main()
{

   vec2 vertpos = u_vertexPositions[gl_VertexID % 6];

   // perform transformations
   vertpos *= scale;
   float cosrot = cos(rot);
   float sinrot = sin(rot);
    vec2 rotatedpos = vec2(
        vertpos.x * cosrot - vertpos.y * sinrot,
        vertpos.x * sinrot + vertpos.y * cosrot  // Fix here
    );
   rotatedpos = rotatedpos + pos;

   vec4 transformedPos = vec4(rotatedpos, 0, 1);
  
   gl_Position =  transformedPos;
   fragPosition = transformedPos;
};


#shader fragment
#version 440

in vec4 fragPosition;
layout(location = 0) out vec4 color;

void main()
{
   color = vec4(1,0,1,1);
};