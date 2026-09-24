#include <iostream>
#include "vec3.h"
#include "ray.h"

double hit_sphere(const Point3& center, double radius, const Ray& r) {
    Vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(oc, r.direction());
    double c = dot(oc, oc) - radius*radius;
    
    double discriminant = b*b - 4*a*c;
    
    if (discriminant < 0) {
        return -1.0; 
    } else {
        return (-b - std::sqrt(discriminant)) / (2.0*a);
    }
}

Color ray_color(const Ray& r) {
    Point3 sphere_center(0, 0, -1);
    double t = hit_sphere(sphere_center, 0.5, r);
    
    if (t > 0.0) {
        Point3 hit_point = r.at(t);
        
        Vec3 N = unit_vector(hit_point - sphere_center);
        
        return Color(0.5 * (N.x() + 1.0), 
                     0.5 * (N.y() + 1.0), 
                     0.5 * (N.z() + 1.0));
    }

    Vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    Color white(1.0, 1.0, 1.0);
    Color blue(0.5, 0.7, 1.0);
    return (white * (1.0 - t)) + (blue * t);
}

int main() {

    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0; 

    Point3 origin(0, 0, 0); 
    Vec3 horizontal(viewport_width, 0, 0);
    Vec3 vertical(0, viewport_height, 0);
    
    Point3 lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - Vec3(0, 0, focal_length);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            
            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);
            
            Vec3 direction = lower_left_corner + (horizontal * u) + (vertical * v) - origin;
            Ray r(origin, direction);

            Color pixel_color = ray_color(r);

            int ir = static_cast<int>(255.999 * pixel_color.x());
            int ig = static_cast<int>(255.999 * pixel_color.y());
            int ib = static_cast<int>(255.999 * pixel_color.z());

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    
    std::cerr << "\nDone.\n";
    return 0;
}