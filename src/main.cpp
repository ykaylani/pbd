#include <iostream>
#include "world/MeshData.h"
#include "world/WorldDescription.h"

#include "update/GaussSeidel.h"
#include "update/Stormer.h"

int main() {

    Data::MeshDataVertices vertices = Data::MeshDataVertices();
    vertices.accelX.resize(2);
    vertices.accelY.resize(2);
    vertices.accelZ.resize(2);

    vertices.mass.resize(2);

    vertices.posX.resize(2);
    vertices.posY.resize(2);
    vertices.posZ.resize(2);

    vertices.prevPosX.resize(2);
    vertices.prevPosY.resize(2);
    vertices.prevPosZ.resize(2);

    vertices.posX[0] = 20;

    vertices.prevPosX = vertices.posX;
    vertices.prevPosY = vertices.posY;
    vertices.prevPosZ = vertices.posZ;

    vertices.mass[0] = 1.0 / 20.0;
    vertices.mass[1] = 0;

    for (int i = 0; i < vertices.accelX.size(); i++) {
        vertices.accelX[i] = World::gravity.x * vertices.mass[i];
        vertices.accelY[i] = World::gravity.y * vertices.mass[i];
        vertices.accelZ[i] = World::gravity.z * vertices.mass[i];
    }

    Data::MeshDataConstraints constraints = Data::MeshDataConstraints();
    constraints.idxA.resize(1);
    constraints.idxB.resize(1);
    constraints.length.resize(1);

    constraints.length[0] = 20;
    constraints.idxA[0] = 0;
    constraints.idxB[0] = 1;

    Data::MeshDataGSeidel gSeidelTemps = Data::MeshDataGSeidel();
    gSeidelTemps.predictedPosX = vertices.posX;
    gSeidelTemps.predictedPosY = vertices.posY;
    gSeidelTemps.predictedPosZ = vertices.posZ;


    for (int i = 0; i < 2048; i++) {
        for (int j = 0; j < vertices.accelX.size(); j++) {
            float3 res = Stormer::one(vertices.posX[j], vertices.posY[j], vertices.posZ[j], vertices.prevPosX[j], vertices.prevPosY[j], vertices.prevPosZ[j], vertices.accelX[j], vertices.accelY[j], vertices.accelZ[j]);

            gSeidelTemps.predictedPosX[j] = res.x;
            gSeidelTemps.predictedPosY[j] = res.y;
            gSeidelTemps.predictedPosZ[j] = res.z;
        }

        for (int j = 0; j < World::GS_ITER; j++) {
            gaussSeidelIT1(constraints, gSeidelTemps, vertices);
        }

        for (int j = 0; j < vertices.accelX.size(); j++) {
            Stormer::two(vertices.posX[j], vertices.posY[j], vertices.posZ[j], vertices.prevPosX[j], vertices.prevPosY[j], vertices.prevPosZ[j], gSeidelTemps.predictedPosX[j], gSeidelTemps.predictedPosY[j], gSeidelTemps.predictedPosZ[j]);
        }

        std::cout << vertices.posZ[0] << std::endl;
    }

    return 0;
}