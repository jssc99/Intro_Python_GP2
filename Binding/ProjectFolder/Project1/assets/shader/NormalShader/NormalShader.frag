#version 330 core
out vec4 FragColor;

#define NR_POINT_LIGHTS 10   
#define NR_SPOTH_LIGHTS 10   


// diffuse = 0
// specular = 1;



struct Material
{
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
};


struct DirLight {
    vec3 lightPos;
    vec3 direction;
    vec3 color;
};  

struct PointLight {    
    vec3 position;
    vec3 color;
        
    float constant;
    float linear;
    float quadratic;
};  

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 color;

};



in VS_OUT 
{
    vec3 Normal;
	vec2 TexCoords;
	vec3 FragPos;  
	vec3 LightPos;
    vec4 FragPosLightSpace;

	
} fs_in;
    


uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight[NR_POINT_LIGHTS];
uniform DirLight dirLight;


uniform  int nbrOfPointLight;
uniform  int nbrOfSpothLightLight;




uniform vec3 viewPos;
uniform Material material;

uniform sampler2D shadowMap;
uniform vec3 lightPos;

float ShadowCalculationDirectionnal(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}




vec3 CalculatePointLight(PointLight light , vec3 normal , vec3 fragPos , vec3 viewDir )
{
    // Determiante Light direction
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse 
    float diff = max(dot(normal, lightDir), 0.0);
    // specular 
    vec3 reflectDir = reflect(-lightDir, normal);
    // Calculate attenuation
    float Distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * Distance + light.quadratic  * Distance);    
    
    float spec = 0 ;
    
    vec3 halfwayDir = normalize(lightDir + viewDir);
     spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
  
    


    // result for eachType
    vec3 ambient = light.color * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 diffuse = light.color * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 specular = light.color * spec * vec3(texture(material.specular, fs_in.TexCoords));
    // end result
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}



vec3 Directionnal(DirLight light , vec3 normal , vec3 viewDir)
{
    vec3 lightdir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightdir,normal);

    // diffuse light
    float diff = max(dot(normal,lightdir),0);
    vec3 diffuse = light.color * diff * vec3(texture(material.diffuse, fs_in.TexCoords));


    // Specular Light
    float spec = 0 ;
    vec3 halfwayDir = normalize(lightdir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
   
    vec3 specular = light.color * spec * vec3(texture(material.specular, fs_in.TexCoords));

    // ambiant light
    vec3 ambient = light.color  * vec3(texture(material.diffuse, fs_in.TexCoords));
    
    float shadow = ShadowCalculationDirectionnal(fs_in.FragPosLightSpace);                      
    return (ambient + (1.0 - shadow) * (diffuse + specular));

   // return (ambient + (diffuse + specular));
}

vec3 SpothLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse Light
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 ambient = light.color * vec3(texture(material.diffuse, fs_in.TexCoords));
    // specular Light
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = 0;
    
    vec3 halfwayDir = normalize(lightDir + viewDir);    
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
   
    // attenuation
    float Distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * Distance + light.quadratic * Distance); 
    

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);


    // end result
    vec3 diffuse = light.color * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 specular = light.color * spec * vec3(texture(material.specular, fs_in.TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}


void main()
{


  
    vec3 endValue = vec3(0.0);
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    endValue = Directionnal(dirLight,norm,viewDir);

    /*
    for(int i = 0 ; i < nbrOfPointLight;i++)
    {
        endValue += CalculatePointLight(pointLights[i],norm,fs_in.FragPos,viewDir);

    } 

    for(int k = 0 ; k < nbrOfSpothLightLight;k++)
    {
     endValue += SpothLight(spotLight[k],norm,fs_in.FragPos,viewDir);
    } 

    */
    

    FragColor =  vec4(endValue,1) ;
}