#version 120 

//opengl itself interpolates the texture coordinate when
//it sends it to the fragment shader
//uniform means both cpu and gpu can access it?
//sampler? diffuse - a type of texture?
//sampler is used to sample images
uniform vec4 u_color;
void main(){
    // gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);

    //reads a pixel from the texture
    gl_FragColor = u_color;
}
