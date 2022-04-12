attribute vec3 vPosition;
attribute vec3 vNormal;
attribute vec2 vUV;

varying vec3 normal;
varying float distance;
varying float cos_angle;
varying vec2 uv;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(vPosition, 1.0f);


    vec3 light_origin = vec3(0.3, 2, 0.3);
    distance = length(gl_Position - light_origin);
    cos_angle = dot(vNormal, normalize(light_origin - vPosition));
    uv = vUV;
    normal = vNormal;
}