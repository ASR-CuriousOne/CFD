#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec3 fragPos;

layout(location = 0) out vec4 outColor;

const vec3 lightPos = vec3(1000,0,0);
const vec3 lightColor = vec3(1.0, 1.0, 1.0);
const float lightPower = 1000000;


const vec3 specColor = vec3(1.0, 1.0, 1.0);
const float shininess = 10.0;
const float screenGamma = 1.0; // Assume the monitor is calibrated to the sRGB color space

void main() {
    vec3 diffuseColor = texture(texSampler,fragTexCoord).rgb;
    vec3 ambientColor = diffuseColor * 0.00001;
    vec3 normal = fragNormal;
    vec3 lightDir = lightPos - fragPos;
    float distance = dot(lightDir,lightDir);
    lightDir = normalize(lightDir);
    float lambertian = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;

    if (lambertian > 0.0) {

        vec3 viewDir = normalize(-fragPos);

        // this is blinn phong
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, shininess);
       
    
    }
    vec3 colorLinear = ambientColor +
                     diffuseColor * lambertian * lightColor * lightPower / distance +
                     specColor * specular * lightColor * lightPower / distance ;
    // apply gamma correction (assume ambientColor, diffuseColor and specColor
    // have been linearized, i.e. have no gamma correction in them)
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / screenGamma));
    // use the gamma corrected color in the fragment
    outColor = vec4(colorGammaCorrected, 1.0);
}
