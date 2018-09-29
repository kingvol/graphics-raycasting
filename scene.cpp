#include "scene.h"

// Include all of glm here.
#include "glm/glm.hpp"

#include "debugging.h"

namespace graphics101 {

void Scene::render( QImage& into_image ) {
    // Your code goes here.

    for ( int row = 0; row < into_image.width(); ++row )
        for ( int col = 0; col < into_image.height(); ++col )
        {
            QColor clrCurrent(into_image.pixel( row, col ) );
            vec2 uv =camera->getPixelUV(vec2(row,col),into_image.width(), into_image.height());
            ray3 ray = camera->getRay(uv);           
            vec3 rayColor = this->rayColor(ray);
            QRgb rgb = qRgb(rayColor.r, rayColor.g, rayColor.b);

            //if(row==100 && col==100)
            //if(rayColor.r>0)
                //std::cout << "Saved: r" << rayColor.r <<"b:" << rayColor.b<< std::endl;

            into_image.setPixel(row, col, rgb);

         }
    // Iterate over the pixels of the image. For each pixel:
    // 1. Use camera->getPixelUV() and camera->getRay() to create a ray3.
    // 2. Call rayColor() to get a vec3 color for that ray.
    // 3. Use into_image.setPixel() to set the pixel color.

}

bool Scene::closestIntersection( const ray3& ray, Intersection& hit_out ) const {
    // Your code goes here.
    ShapePtr min_shape;
    real min_t = 31100;
    Intersection hit_o;
    bool res = false;
    int i=0;
    for( const ShapePtr shape: shapes ) {
        if(shape->rayIntersect(ray, hit_out)){
            res = true;
            if(hit_out.t < min_t){

                min_shape = shape;
                hit_o = hit_out;
            }
            else
                std::cout << "Saved: r" << std::endl;
       }
    }
    hit_out = hit_o;
    // Iterate over all the shapes, calling rayIntersect() on each.
    // In C++, a nice iterator for loop can be written as:
    // for( const ShapePtr shape: shapes ) { ... shape->rayIntersect( ... ) ... }

    return res;
}
vec3 Scene::rayColor( const ray3& ray, int max_recursion ) const {
    // Your code goes here.

    // In this ray casting assignment, you will simply call closestIntersection(),
    // and, if there is one, return the .material.color_diffuse;
    // Otherwise, return black (0,0,0).

    assert( max_recursion >= 0 );

    const real eps = 1e-7;

    vec3 c( 0,0,0 );
    Intersection hit_out;

    if(closestIntersection(ray, hit_out))
    {
        return hit_out.material.color_diffuse;
        //return hit_out.material.color_reflect;
    }
    return c;
}

}
