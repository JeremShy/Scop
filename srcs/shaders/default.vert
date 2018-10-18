#version 400
// in vec3 vp;
// void main() {
//   gl_Position = vec4(vp, 1.0);
// }

// Input vertex data, different for all executions of this shader.
// layout(location = 0) in vec3 vertexPosition_modelspace;

in vec3 vp;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(vp,1);
    // gl_Position = vec4(vp, 1.0);

}
