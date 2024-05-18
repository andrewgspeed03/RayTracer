#ifndef MATERIALH
#define MATERIALH

class hitRecord;

class material {
    public:
        virtual bool scatter(const ray& rIn, const hitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
};

#endif