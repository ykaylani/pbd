#ifndef GAUSSSEIDEL
#define GAUSSSEIDEL
#include "../world/MeshData.h"
#include "../types.h"

inline void GaussSeidelIT1(Data::MeshDataC& constraints, Data::MeshDataGS& positions, Data::MeshDataVt& particles) {

    for (int i = 0; i < constraints.length.size(); i++) {

        int idxParticle1 = constraints.idxA[i];
        int idxParticle2 = constraints.idxB[i];

        float particle1x = positions.predictedPosX[idxParticle1];
        float particle1y = positions.predictedPosY[idxParticle1];
        float particle1z = positions.predictedPosZ[idxParticle1];

        float particle2x = positions.predictedPosX[idxParticle2];
        float particle2y = positions.predictedPosY[idxParticle2];
        float particle2z = positions.predictedPosZ[idxParticle2];

        float3 particle1pos = {particle1x, particle1y, particle1z};
        float3 particle2pos = {particle2x, particle2y, particle2z};

        float w1 = 1 / particles.mass[idxParticle1];
        float w2 = 1 / particles.mass[idxParticle2];

        float Cx = float3::magnitude(particle1pos - particle2pos) - constraints.length[i];
        float lambda = Cx / (w1 + w2);

        float3 x1C = float3::unit(particle1pos - particle2pos);
        float3 x2C = float3::unit(particle2pos - particle1pos);

        float3 dx1 = -lambda * w1 * x1C;
        float3 dx2 = -lambda * w2 * x2C;

        positions.predictedPosX[idxParticle1] += dx1.x;
        positions.predictedPosY[idxParticle1] += dx1.y;
        positions.predictedPosZ[idxParticle1] += dx1.z;

        positions.predictedPosX[idxParticle2] += dx2.x;
        positions.predictedPosY[idxParticle2] += dx2.y;
        positions.predictedPosZ[idxParticle2] += dx2.z;
    }
}

#endif //GAUSSSEIDEL