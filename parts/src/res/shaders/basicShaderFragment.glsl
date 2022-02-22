#version 120 

//opengl itself interpolates the texture coordinate when
//it sends it to the fragment shader
varying  vec2 texCoord0;
//uniform means both cpu and gpu can access it?
//sampler? diffuse - a type of texture?
uniform sampler2D diffuse;

void main(){
    // gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);

    //reads a pixel from the texture
    gl_FragColor = texture2D(diffuse, texCoord0);
}