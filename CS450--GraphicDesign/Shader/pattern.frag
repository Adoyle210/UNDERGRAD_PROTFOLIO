#version 110

uniform float	uTime;		// "Time", from Animate( )
uniform float   uC;
uniform float   uD;
uniform bool	uFragment;
varying vec2  	vST;		// texture coords

void
main( )
{
	vec3 myColor = vec3( 1,1,1);

	//regular fragment 
	if(uFragment == false){
		if(vST.s <= .2){
			myColor = vec3( 1,1,0 );
		}
		else if(vST.s <= .4){
			myColor = vec3( 1,0,0 );
		}
		else if(vST.s <= .6){
			myColor = vec3( 0,1,0 );
		}
		else if(vST.s <= .8){
			myColor = vec3( 0,1,1 );
		}
	}

	//animate fragment
	else{
		if(vST.s <= .2){
			myColor = vec3( 1,1,0 );
		}
		else if(vST.s <= uTime){
			myColor = vec3( 1,0,0 );
		}
		else if(vST.s <= .6){
			myColor = vec3( 0,1,0 );
		}
		else if(vST.s <= .8){
			myColor = vec3( 0,1,1 );
		}
	}
	
	gl_FragColor = vec4( myColor,  1. );
}