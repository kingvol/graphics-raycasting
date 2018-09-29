#include "shape.h"

#include "debugging.h"

#include <vector>
#include <cmath> // std::sqrt()

namespace graphics101 {

bool Sphere::rayIntersect( const ray3& ray, Intersection& hit_out ) const {
    // Your code goes here.
    ray3 newRay = ray;
    mat4 inverseTransform =  transformInverse();
    mat3 m = mat3(inverseTransform);
    newRay.p = m*ray.p;
    newRay.d = m*ray.d;
//    double a = dot(newRay.d, newRay.d);
//    double b = 2*dot(newRay.p,  newRay.d);
//    double c = dot(newRay.p, newRay.p) - 1;
    double a = newRay.d.x*newRay.d.x + newRay.d.y*newRay.d.y+newRay.d.z*newRay.d.z;
    double b = 2*(newRay.p.x*newRay.d.x + newRay.p .y*newRay.d.y+ newRay.p .z*newRay.d.z);
    double c = newRay.p.x*newRay.p.x + newRay.p.y*newRay.p.y+ newRay.p .z*newRay.d.z - 1.0;
    double d = b*b - 4*a*c;
    if(d<0) return false;
    if (d == 0){
        double t = -b/(2*a);
        hit_out.t = t;
    }
    if (d > 0){
        double t_zero = (-b - sqrt(d))/(2*a);
        double t_one =  (-b + sqrt(d))/(2*a);
        hit_out.t = t_zero;
           //   std::cout << "Saved2: r" << d<< std::endl;

    }
    hit_out.position  =ray.p+hit_out.t*ray.d;
    //hit_out.normal = newRay.
    //std::cout << "Saved: r" <<a<<","<<b<<","<<c<<","<<hit_out.t<< std::endl;
    //std::cout << "Saved: r" <<ray.d.x<<","<<newRay.d.x<<","<<c<<","<<hit_out.t<< std::endl;
   // vec3 aa{ 100, 100, 100 };
   // hit_out.position=aa;
    hit_out.material = material();
    //hit_out.material.color_diffuse=vec3(0,255,0);
    //hit_out.material.color_diffuse=vec3(0,255,0);
    //rayColor= hit_out.material.color_diffuse;
  //      std::cout << "Saved2: r" << rayColor.r <<"b:" << rayColor.b<< std::endl;
    // Remember that this intersection occurs in object-space.
    // You convert the world-space ray to object-space by multipling transformInverse() * ray.p and ray.d.
    // When filling out `hit_out`, don't forget to return the resulting position and normal in world-space.
    // For the normal, that means left-multiplying the object-space normal by transpose( transformInverse() ).
    
    return (d >= 0);
}

bool Plane::rayIntersect( const ray3& ray, Intersection& hit_out ) const {
    // Your code goes here.



    ray3 newRay = ray;
    mat4 inverseTransform =  transformInverse();
    mat3 m = mat3(inverseTransform);
    newRay.p = m*ray.p;
    newRay.d = m*ray.d;
    double b = newRay.d.z;
    double c = newRay.p.z;
    double t = -c/b;
    double q = 0;
    if (t >= 0){
        hit_out.t = t;
        hit_out.material = material();
    }
    return (t >= 0);
    // Remember that this intersection occurs in object-space.
    // You convert the world-space ray to object-space by multipling transformInverse() * ray.p and ray.d.
    // When filling out `hit_out`, don't forget to return the resulting position and normal in world-space.
    // For the normal, that means left-multiplying the object-space normal by transpose( transformInverse() ).
    //hit_out.material.color_diffuse=vec3(0,0,255);
    ////vec3 rayColor= hit_out.material.color_diffuse;
    //std::cout << "Saved33333: r" << rayColor.r <<"b:" << rayColor.b<< std::endl;
    return false;
}

bool Cylinder::rayIntersect( const ray3& ray, Intersection& hit_out ) const {
    // Your code goes here.
    ray3 newRay = ray;
    mat4 inverseTransform =  transformInverse();
    mat3 m = mat3(inverseTransform);
    newRay.p = m*ray.p;
    newRay.d = m*ray.d;
    double a = newRay.d.x*newRay.d.x + newRay.d.y*newRay.d.y;
    double b = 2*(newRay.p.x*newRay.d.x + newRay.p .y*newRay.d.y);
    double c = newRay.p.x*newRay.p.x + newRay.p.y*newRay.p.y - 1.0;
    double d = b*b - 4*a*c;
    if (d == 0.0){
        double t = -b/(2*a);
        if (t < 0){
            return false;
        }
        hit_out.t = t;
        vec3 q = newRay.p + t*newRay.d;
        if (q.z > 1 || q.z < - 1){
            //t is invalid
             return false;
        }

    }
    if (d > 0){
        double t_zero = (-b - sqrt(d))/(2*a);
        double t_one =  (-b + sqrt(d))/(2*a);
        if (t_zero < 0 || t_one < 0)
            return false;
        vec3 q_zero =newRay.p + t_zero*newRay.d;
        vec3 q_one =newRay.p + t_one*newRay.d;
        bool t_one_invalid = false;
        bool t_zero_invalid = false;
        if (q_zero.z > 1 || q_zero.z < -1){
            t_one_invalid = true;
        }
        if (q_one.z > 1 || q_zero.z < - 1){
            t_one_invalid = false;
        }
        hit_out.t = t_zero;

    }
    hit_out.material = material();

   // hit_out.material.color_diffuse=vec3(0,0,255);
     //vec3 rayColor= hit_out.material.color_diffuse;
    //std::cout << "Saved4444: r" << rayColor.r <<"b:" << rayColor.b<< std::endl;

    // Remember that this intersection occurs in object-space.
    // You convert the world-space ray to object-space by multipling transformInverse() * ray.p and ray.d.
    // When filling out `hit_out`, don't forget to return the resulting position and normal in world-space.
    // For the normal, that means left-multiplying the object-space normal by transpose( transformInverse() ).
}

bool Cone::rayIntersect( const ray3& ray, Intersection& hit_out ) const {
    // Your code goes here.
    ray3 newRay = ray;
    mat4 inverseTransform =  transformInverse();
    mat3 m = mat3(inverseTransform);
    newRay.p = m*ray.p;
    newRay.d = m*ray.d;
    double a = newRay.d.x*newRay.d.x + newRay.d.y*newRay.d.y - newRay.d.z*newRay.d.z;
    double b = 2*(newRay.p.x*newRay.d.x + newRay.p.y*newRay.d.y + (1-newRay.p.z)*newRay.d.z);
    double c = newRay.p.x*newRay.p.x + newRay.p.y*newRay.p.y -(1-newRay.p.z)*(1-newRay.p.z);
    double d = b*b - 4*a*c;
    if (d == 0){
        double t = -b/(2*a);
        hit_out.t = t;
    }
    if (d > 0){
        double t_zero = (-b - sqrt(d))/(2*a);
        double t_one =  (-b + sqrt(d))/(2*a);
        //if ()
        hit_out.t = t_zero;

    }
   // hit_out.material = material();
    // Remember that this intersection occurs in object-space.
    // You convert the world-space ray to object-space by multipling transformInverse() * ray.p and ray.d.
    // When filling out `hit_out`, don't forget to return the resulting position and normal in world-space.
    // For the normal, that means left-multiplying the object-space normal by transpose( transformInverse() ).

    return false;
}

bool Cube::rayIntersect( const ray3& ray, Intersection& hit_out ) const {
    // Your code goes here.

    // Remember that this intersection occurs in object-space.
    // You convert the world-space ray to object-space by multipling transformInverse() * ray.p and ray.d.
    // When filling out `hit_out`, don't forget to return the resulting position and normal in world-space.
    // For the normal, that means left-multiplying the object-space normal by transpose( transformInverse() ).
    ray3 newRay = ray;
    mat4 inverseTransform =  transformInverse();
    mat3 m = mat3(inverseTransform);
    newRay.p = m*ray.p;
    newRay.d = m*ray.d;
    double a = newRay.d.x*newRay.d.x + newRay.d.y*newRay.d.y - newRay.d.z*newRay.d.z;
    double b = 2*(newRay.p.x*newRay.d.x + newRay.p.y*newRay.d.y + (1-newRay.p.z)*newRay.d.z);
    double c = newRay.p.x*newRay.p.x + newRay.p.y*newRay.p.y -(1-newRay.p.z)*(1-newRay.p.z);
    double d = b*b - 4*a*c;
    if (d == 0){
        double t = -b/(2*a);
        hit_out.t = t;
    }
    if (d > 0){
        double t_zero = (-b - sqrt(d))/(2*a);
        double t_one =  (-b + sqrt(d))/(2*a);
        //if ()
        hit_out.t = t_zero;

    }
   // hit_out.material = material();
    return false;
}

bool Mesh::rayIntersect( const ray3& ray, Intersection& hit_out ) const {
    // Your code goes here.

    // Remember that this intersection occurs in object-space.
    // You convert the world-space ray to object-space by multipling transformInverse() * ray.p and ray.d.
    // When filling out `hit_out`, don't forget to return the resulting position and normal in world-space.
    // For the normal, that means left-multiplying the object-space normal by transpose( transformInverse() ).
    ray3 newRay = ray;
    mat4 inverseTransform =  transformInverse();
    mat3 m = mat3(inverseTransform);
    newRay.p = m*ray.p;
    newRay.d = m*ray.d;
    double a = newRay.d.x*newRay.d.x + newRay.d.y*newRay.d.y - newRay.d.z*newRay.d.z;
    double b = 2*(newRay.p.x*newRay.d.x + newRay.p.y*newRay.d.y + (1-newRay.p.z)*newRay.d.z);
    double c = newRay.p.x*newRay.p.x + newRay.p.y*newRay.p.y -(1-newRay.p.z)*(1-newRay.p.z);
    double d = b*b - 4*a*c;
    if (d == 0){
        double t = -b/(2*a);
        hit_out.t = t;
    }
    if (d > 0){
        double t_zero = (-b - sqrt(d))/(2*a);
        double t_one =  (-b + sqrt(d))/(2*a);
        //if ()
        hit_out.t = t_zero;

    }
   // hit_out.material = material();
    return false;
}

}
