#include <iostream>
#include <fstream>
#include <chrono>

#include "world/MeshData.h"
#include "world/WorldDescription.h"
#include "update/GaussSeidel.h"
#include "update/Stormer.h"

#include "constraints/ConstraintEditor.h"

int main() {

    int gridWidth = 10;
    int gridHeight = 10;
    int spacing = 5;

    int tVertices = gridWidth * gridHeight;

    Data::VertexData vertices = Data::VertexData();
    vertices.accelX.resize(tVertices);
    vertices.accelY.resize(tVertices);
    vertices.accelZ.resize(tVertices);

    vertices.mass.resize(tVertices);

    vertices.posX.resize(tVertices);
    vertices.posY.resize(tVertices);
    vertices.posZ.resize(tVertices);

    vertices.prevPosX.resize(tVertices);
    vertices.prevPosY.resize(tVertices);
    vertices.prevPosZ.resize(tVertices);

    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            int idx = y * gridWidth + x;

            vertices.posX[idx] = x * spacing;
            vertices.posY[idx] = 0.0f;
            vertices.posZ[idx] = y * spacing;

            if (y == 0 && (x == 0)) {
                vertices.mass[idx] = 0.0f;
            } else {
                vertices.mass[idx] = 1.0f / 20.0f;
            }

        }
    }

    vertices.prevPosX = vertices.posX;
    vertices.prevPosY = vertices.posY;
    vertices.prevPosZ = vertices.posZ;

    for (int i = 0; i < vertices.accelX.size(); i++) {

        if (vertices.mass[i] == 0) { continue; }

        vertices.accelX[i] = World::GRAVITY.x;
        vertices.accelY[i] = World::GRAVITY.y;
        vertices.accelZ[i] = World::GRAVITY.z;
    }

    Data::ConstraintData constraints = Data::ConstraintData();

    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            int idx = y * gridWidth + x;

            if (x < gridWidth - 1) {
                int rightIdx = y * gridWidth + (x + 1);

                if (y == 0) {
                    addConstraint(idx, rightIdx, 0.3f, vertices, constraints);
                } else {
                    addConstraint(idx, rightIdx, 0.3f, vertices, constraints);
                }
            }

            if (y < gridHeight - 1) {
                int bottomIdx = (y + 1) * gridWidth + x;
                addConstraint(idx, bottomIdx, 0.3f, vertices, constraints);
            }

            if (x < gridWidth - 1 && y < gridHeight - 1) {
                int diagDownIdx = (y + 1) * gridWidth + (x + 1);
                addConstraint(idx, diagDownIdx, 0.3f, vertices, constraints);

                if (x > 0) {
                    int diagDownLeftIdx = (y + 1) * gridWidth + (x - 1);
                    addConstraint(idx, diagDownLeftIdx, 0.3f, vertices, constraints);
                }
            }
        }
    }

    Data::IntermediatePos gSeidelTemps = Data::IntermediatePos();
    gSeidelTemps.predictedPosX = vertices.posX;
    gSeidelTemps.predictedPosY = vertices.posY;
    gSeidelTemps.predictedPosZ = vertices.posZ;

    std::ofstream csvFile("positions.csv");
    csvFile << "Frame,Vertex,PosX,PosY,PosZ" << std::endl;

    std::chrono::time_point pre = std::chrono::system_clock::now();

    for (int i = 0; i < 2048; i++) {
        for (int j = 0; j < vertices.accelX.size(); j++) {
            float3 res = Stormer::one(vertices.posX[j], vertices.posY[j], vertices.posZ[j], vertices.prevPosX[j], vertices.prevPosY[j], vertices.prevPosZ[j], vertices.accelX[j], vertices.accelY[j], vertices.accelZ[j]);

            gSeidelTemps.predictedPosX[j] = res.x;
            gSeidelTemps.predictedPosY[j] = res.y;
            gSeidelTemps.predictedPosZ[j] = res.z;
        }

        for (int j = 0; j < World::GS_ITER; j++) {
            gaussSeidel(constraints, gSeidelTemps, vertices);
        }

        for (int j = 0; j < vertices.accelX.size(); j++) {
            Stormer::two(vertices.posX[j], vertices.posY[j], vertices.posZ[j], vertices.prevPosX[j], vertices.prevPosY[j], vertices.prevPosZ[j], gSeidelTemps.predictedPosX[j], gSeidelTemps.predictedPosY[j], gSeidelTemps.predictedPosZ[j]);
        }

        /*for (int j = 0; j < vertices.accelX.size(); j++) {
            csvFile << i << "," << j << "," << vertices.posX[j] << "," << vertices.posY[j] << "," << vertices.posZ[j] << std::endl;
        }*/
    }

    std::chrono::time_point post = std::chrono::system_clock::now();

    std::chrono::duration tTime = post - pre;

    std::cout << tTime << std::endl;

    csvFile.close();
    //std::cout << "Position data written to positions.csv" << std::endl;

    return 0;
}