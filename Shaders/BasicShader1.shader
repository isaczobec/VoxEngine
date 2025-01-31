#shader vertex
#version 440

layout(location = 0) in vec2 pos;
layout(location = 1) in float rot;
layout(location = 2) in vec2 scale;

out vec4 fragPosition;
out vec2 uvCoord;

// uniform mat4 u_projectionMatrix;
uniform vec2 u_vertexPositions[4];

// the uv-coordinates will always be a uniform square, 
// since were only rendering sprites.
// predefine them here:

const vec2 uvCoords[4] = vec2[4](
    vec2(0, 1),
    vec2(1, 1),
    vec2(1, 0),
    vec2(0, 0)
);

void main()
{

   vec2 vertpos = u_vertexPositions[gl_VertexID % 4];

   // perform transformations
   vertpos *= scale;
   float cosrot = cos(rot);
   float sinrot = sin(rot);
    vec2 rotatedpos = vec2(
        vertpos.x * cosrot - vertpos.y * sinrot,
        vertpos.x * sinrot + vertpos.y * cosrot  
    );
   rotatedpos = rotatedpos + pos;

   vec4 transformedPos = vec4(rotatedpos, 0, 1);
  
   gl_Position =  transformedPos;
   fragPosition = transformedPos;

   // set uv-coord to the appropriate value based on the vertex id
   uvCoord = uvCoords[gl_VertexID % 4];
};


#shader fragment
#version 440

// texture
uniform sampler2D colorTexture;

in vec4 fragPosition;
in vec2 uvCoord;
layout(location = 0) out vec4 color;

void main()
{
   color = texture(colorTexture,uvCoord);
   
};