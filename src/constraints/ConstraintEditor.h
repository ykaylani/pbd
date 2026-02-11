#ifndef CONSTRAINTEDITOR
#define CONSTRAINTEDITOR
#include "../mesh/MeshData.h"
#include <cmath>

void addConstraint(int idxA, int idxB, float stiffness, Data::VertexData& vertices, Data::ConstraintData& constraints) {
    float dx = vertices.posX[idxA] - vertices.posX[idxB];
    float dy = vertices.posY[idxA] - vertices.posY[idxB];
    float dz = vertices.posZ[idxA] - vertices.posZ[idxB];
    float length = sqrt(dx*dx + dy*dy + dz*dz);

    constraints.idxA.push_back(idxA);
    constraints.idxB.push_back(idxB);
    constraints.length.push_back(length);
    constraints.stiffness.push_back(stiffness);
}

#endif //CONSTRAINTEDITOR