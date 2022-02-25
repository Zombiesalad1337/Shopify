#version 120 

attribute vec3 position;
//want to interpolate this and send this to fragment shader

//a varying variable can be shared between shaders

//uniform, attribute - a variable that can be set by the cpu
//attribute used for data that is different for different vertices, like position
//uniform is used for data that is same for all vertices, like time
uniform mat4 transform;


//executes for each vertex
void main(){
    //1.0 controls the degree of translation 
    //if 0.0 - no translation, only rotation and scaling?
    gl_Position = transform * vec4(position, 1.0);
}
