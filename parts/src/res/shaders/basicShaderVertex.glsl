#version 120 

attribute vec3 position;
//want to interpolate this and send this to fragment shader
attribute vec2 texCoord;

//a varying variable can be shared between shaders
varying vec2 texCoord0;

//uniform - a variable that can be set by the cpu
uniform mat4 transform;

void main(){
    //1.0 controls the degree of translation 
    //if 0.0 - no translation, only rotation and scaling?
    gl_Position = transform * vec4(position, 1.0);
    //now fragment shader has access to texCoord0
    texCoord0 = texCoord;
}
