#ifndef GAUSSSEIDEL
#define GAUSSSEIDEL
#include "../Types.h"

inline void gaussSeidel(float3& particle1pos, float3& particle2pos, float weight1, float weight2, float distanceConstraint, float cStiffness) {

    if (weight1 + weight2 == 0.0f) { return; }

    float Cx = float3::magnitude(particle1pos - particle2pos) - distanceConstraint;
    float lambda = Cx / (weight1 + weight2);

    float3 direction1 = float3::unit(particle1pos - particle2pos);
    float3 direction2 = float3::unit(particle2pos - particle1pos);

    float3 dx1 = -lambda * weight1 * direction1;
    float3 dx2 = -lambda * weight2 * direction2;

    particle1pos = particle1pos + dx1 * cStiffness;
    particle2pos = particle2pos + dx2 * cStiffness;
}

#endif //GAUSSSEIDEL