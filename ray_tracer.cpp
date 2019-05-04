#include "ray_tracer.h"
ray ray_tracer::reflect(ray ray_in, vector normal,vector reflected_point){
    vector ray_o_start = reflected_point;
    normal = (1.0f/normal.norm()) * normal;
    vector ray_o_direction = ray_in.direction - (2 *(ray_in.direction & normal))* normal;
    ray output = ray(ray_o_start, ray_o_direction);
    return output;
}
ray ray_tracer::refract(ray ray_in, vector normal, 
            vector refracted_point,
            float refraction_coefficient_1,
            float refraction_coefficient_2){
    
    vector ray_o_start = refracted_point;
    float r = refraction_coefficient_1/refraction_coefficient_2;
    normal = (1.0f/normal.norm()) * normal;
    ray_in.direction = (1.0f / ray_in.direction.norm()) * ray_in.direction;
    float c = - normal & ray_in.direction;
    vector ray_o_direction = r * ray_in.direction + (r * c - sqrtf(1 - r * r * (1 - c * c))) * normal;
    ray output = ray(ray_o_start, ray_o_direction);
    return output;
}
color ray_tracer::phong_illumination(ray ray_in, vector normal, vector point, phong coefficients, light& light_in, bool not_shadowed){
    color output = coefficients.ambient_coeff & 
       ( (1.0f - coefficients.refraction_coefficient) * 
                light_in.ambient_intensity); 
    float epsilon = 5e-2;
    if(not_shadowed){
        vector L_m = light_in.position - point; L_m = (1.0f / L_m.norm()) * L_m;
        vector N = normal; N = (1.0f / N.norm()) * N;
        if((L_m&N) < epsilon){
            N = -N;
        }
        if((L_m & N) > epsilon){
        color i_md = light_in.intensity_atdist((point - light_in.position).norm());
        color i_ms = i_md;
        color k_d = coefficients.diffuse_coeff; 
        color k_s = coefficients.specular_coeff;
        float alpha = coefficients.shininess_coeff;
        vector V = -ray_in.direction; V = (1.0f / V.norm()) * V;
        vector R_m = (2 * (L_m & N) ) * N - L_m; R_m = (1.0f / R_m.norm()) * R_m;
        color diffuse = (L_m & N)  * (k_d & i_md);
        color specular = powf((R_m & V), alpha) * (k_s & i_ms); 
        output = output + diffuse;
        output = output + specular;
        }
    }
    return output;
}
color ray_tracer::tracer(ray ray_in, scene& total_scene,light* lights, int number_of_lights, int recursion_depth){ 
    float temp[3] = {0.0f,0.0f,0.0f};
    color output = color(temp);
    //find first intersecting surface
    surface* surfp;
    v_n point;
    if(!total_scene.intersects_first(ray_in, &point, surfp)){
        return output;
    }
    v_n shadow_ray_intersect;
    surface* shadow_ray_intersect_surf;
    //Texture mapping
    phong coeff = surfp->coefficients;
    coeff.ambient_coeff = coeff.ambient_coeff 
        & surfp->texture_color(vector(point.coord));//surf 
    coeff.diffuse_coeff = coeff.diffuse_coeff 
        & surfp->texture_color(vector(point.coord));
    //phong illumination on point
    for(int i = 0; i< number_of_lights; i++){
        ray shadow_ray = ray(point, lights[i].position - point); //shadow ray test
        if(!total_scene.intersects_first(shadow_ray,
                    &shadow_ray_intersect, shadow_ray_intersect_surf)){
            color tempc = phong_illumination(ray_in, vector(point.normal), 
                    point, coeff,lights[i],true);
            output = output + tempc;
        }
        else{
            color tempc = phong_illumination(ray_in, vector(point.normal), 
                    point, coeff,lights[i],false);
            output = output + tempc;
        }
    }
    if(recursion_depth >= MAX_RAYTRACE_RECURSION) return output;
    
    //create reflecting and refracting rays
    if(coeff.reflection_coefficient != 0.0f){
        vector p_n = vector(point.normal);
        //ray coming from inside
        if((p_n & ray_in.direction) <0){
            p_n = -p_n;
        }
        ray reflected_ray = reflect(ray_in, p_n, point);

        output = output + coeff.reflection_coefficient * tracer(reflected_ray,total_scene,
                lights, number_of_lights, recursion_depth+1);
    }
    if(surfp->coefficients.refraction_coefficient != 0.0f){
        vector p_n = vector(point.normal);
        color tempc;
        if((p_n & (-ray_in.direction))<0){ //ray coming from inside to outside

            ray refracted_ray = refract(ray_in, -p_n, point, coeff.refract_index,1.0f);
            tempc = tracer(refracted_ray,total_scene,lights, number_of_lights, recursion_depth+1);
        }
        else if((p_n & (-ray_in.direction)) >= 0){ //ray coming from outside to inside
            ray refracted_ray = refract(ray_in, vector(point.normal), point, 
            1.0f,
            coeff.refract_index);
            tempc = tracer(refracted_ray,total_scene,lights, number_of_lights, recursion_depth+1);
        }
        else{
            float black[3] = {0.0f,0.0f,0.0f};
            tempc = color(black);
        }
        output = output + coeff.refraction_coefficient * tempc;
    }
    //return color
    return output;
}
