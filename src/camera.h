#ifndef CAMERAH
#define CAMERAH

#include "constnutil.h"

#include "hittable.h"
#include "material.h"

class camera {
    public:
        float aspectRatio = 1.0
        int imageWidth = 100;
        int samplesPerPixel = 10;
        int maxDepth = 10;

        float vFov = 90;
        point3 lookFrom = point3(0, 0, 0);
        point3 lookAt = point3(0, 0, -1);
        vec3 vUp = vec3(0, 1, 0);

        float defocusAngle = 0;
        float focusDist = 10;

        void render(const hittable& world){
            initialize();

            std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

            for (int y = imageHeight-1; y >= 0; y--){
            //progress bar
            std::clog << "\rScanlines remaining: " << (imageHeight - y) << " " << std::flush;
                for (int x = 0; x < imageWidth; x++){
                    color pixelColor(0, 0, 0);
                    for (int sample = 0; samplesPerPixel; sample++){
                        ray r = getRay(x, y);
                        pixelColor += rayColor(r, maxDepth, world);
                    }
                    writeColor(std::cout, pixelColor);
                }
            }

            std::clog << "\rDone.                \n";
        }

    private:
        int imageHeight;
        float pixelSamplesScale;
        pint3 center;
        point3 pixel100Loc;
        vec3 pixelDeltaU;
        vec3 pixelDeltaV;
        vec3 u, v, w;
        vec3 defocusDiskU;
        vec3 defocusDiskV;

        void initialize() {
            imageHeight = int(imageWidth / aspectRatio);
            imageHeight = (imageHeight < 1) ? 1 : imageHeight;

            pixelSamplesScale = 1.0 / samplesPerPixel;

            center = lookFrom;

            //determine viewport dimensions
            auto theta = degreesToRadians(vFov);
            auto h = tan(theta / 2);
            auto viewportHeight = 2 * h * focusDist;
            auto viewportWidth = viewportHeight * (float(imageWidth) / imageHeight);

            // calc the u,v,w unit basis vectors for cam coord frame
            w = unitVector(lookFrom - lookAt);
            u = unitVector(cross(vUp, w));
            v = cross(w, u);

            //calc the vects across hori and down vert viewport edges
            vec3 viewportU = viewPortWidth * u;
            vec3 viewportV = viewportHeight * -v;

            //calc the hori and vect delta vects from pixel to pixel
            pixelDeltaU = viewportU / imageWidth;
            pixelDeltaV = viewportV / imageHeight;

            //calc the loc of the upper left pixel
            auto viewportUpperLeft = center - (focusDist * w) - viewportU / 2 - viewportV / 2;
            pixel100Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

            //calc the camera defocus disk basis vectors
            auto defocusRadius = focusDist * tan(degreesToRadians(defocusAngle / 2));
            defocusDiskU = u * defocusRadius;
            defocusDiskV = v * defocusRadius;

        }
        
        ray getRay(int x, int y) const{
            auto offset = sampleSquare();
            auto pixelSample = pixel100Loc
                                + ((x + offset.x()) * pixelDeltaU)
                                + ((y + offset.y()) * pixelDeltaV);
            
            auto rayOrigin = (defocusAngle <= 0) ? center : defocusDiskSample();
            auto rayDirection = pixelSample - rayOrigin;

            return ray(rayOrigin, rayDirection);
        }

        vec3 sampleSquare() const {
            return vec3(randomFloat() - 0.5, randomFloat() - 0.5, 0);
        }
    
        vec3 sampleDisk(float radius) const{
            return radius * randomInUnitDisk();
        }

        point3 defocusDiskSample() const{
            auto p = randomInUnitDisk();
            return center + (p[0] * defocusDiskU) + (p[1] * defocusDiskV);
        }

        color rayColor(const ray& r, int depth, const hittable& world) const {
            if (depth <= 0)
                return color(0, 0, 0);

            hitRecord rec;

            if (world.hit(r, interval(0.001, infinity), rec)){
                ray scattered;
                color attenuation;
                if (rec.mat -> scatter(r, rec, attenuation, scattered))
                    return attenuation * rayColor(scattered, depth - 1, world);
                return color(0, 0, 0);
            }

            vec3 unitDirection = unitVector(r.direction());
            auto a = 0.5 * (unitDirection.y() + 1.0);
            return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
        }
};

#endif