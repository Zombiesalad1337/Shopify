#version 120 

attribute vec3 position;
//want to interpolate this and send this to fragment shader
attribute vec2 texCoord;

//a varying variable can be shared between shaders
varying vec2 texCoord0;

void main(){
    gl_Position = vec4(position, 1.0);
    //now fragment shader has access to texCoord0
    texCoord0 = texCoord;
}
