#shader vertex
#version 440

layout(location = 0) in vec2 pos;
layout(location = 1) in float rot;
layout(location = 2) in vec2 scale;
layout(location = 3) in float animationFrame;

out vec4 fragPosition;
out vec2 uvCoord;

// uniform mat4 u_projectionMatrix;
uniform vec2 u_vertexPositions[4];
uniform vec2 u_animationSlices;

vec2 uvCoords[4] = vec2[4](
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

   // modify UV-coord based on id and the animationFrame
   uvCoord = uvCoords[gl_VertexID % 4];
   //uvCoord.x /= 3;
   //uvCoord.y /= 3;
   uvCoord.x /= u_animationSlices.x;
   uvCoord.y /= u_animationSlices.y;
   uvCoord.x += mod(animationFrame, u_animationSlices.x) / u_animationSlices.x;
   //uvCoord.y += float(animationFrame / float(u_animationSlices.x)) / float(u_animationSlices.y);
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
   //color = vec4(uvCoord, 0, 1);
};