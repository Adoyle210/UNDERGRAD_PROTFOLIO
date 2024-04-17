#version 110

uniform float	uTime;		// "Time", from Animate( )
uniform float   uA;
uniform float   uB;
uniform bool	uVertex;
varying vec2  	vST;		// texture coords

const float PI = 	3.14159265;
const float AMP = 	0.2;		// amplitude
const float W = 	2.;		// frequency

void
main( )
{ 
	vST = gl_MultiTexCoord0.st;
	vec3 vert = gl_Vertex.xyz;
	if(uVertex == false){
		vert.x = vert.x / uA; //??? something fun of your own design
		vert.y = vert.y / uB; //??? something fun of your own design
		vert.z = vert.z * 1; //??? something fun of your own design
	}
	else{
		vert.x = vert.x * sin(uB); //??? something fun of your own design
		vert.y = vert.y * cos(vert.x); //??? something fun of your own design
		vert.z = vert.z * cos(vert.y); //??? something fun of your own design
	}

	gl_Position = gl_ModelViewProjectionMatrix * vec4( vert, 1. );
}