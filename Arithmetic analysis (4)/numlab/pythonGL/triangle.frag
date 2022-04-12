varying vec3 normal;
varying float distance;
varying float cos_angle;

uniform sampler2D text1;
varying vec2 uv;


void main()
{

    vec3 base_color = texture2D(text1, uv);

    float distance_coeff = (2/distance) * (2/distance) ;
    vec3 diffuse = distance_coeff * base_color;

    vec3 specular = vec3(0,0,0);


    if(cos_angle<0){
        float cos_angle_coeff = -cos_angle/1.5;
        specular = cos_angle_coeff * vec3(0.6,0.6,0.6);
        //float cos_angle_coeff = (-cos_angle/5);
        //specular = cos_angle_coeff * vec3(1, 1, 1);
    }


    vec3 final_color = diffuse + specular;

    //texture testing
    //final_color = texture2D(text1, position.xz);

    gl_FragColor = vec4(final_color, 1.0);
    
}