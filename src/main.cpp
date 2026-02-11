#include <chrono>
#include <iostream>
#include <fstream>

#include "mesh/MeshData.h"
#include "world/WorldDescription.h"
#include "update/GaussSeidel.h"
#include "update/Stormer.h"
#include "constraints/ConstraintEditor.h"
#include "update/PhysDescription.h"

int main() {

    int gridWidth = 10;
    int gridHeight = 10;
    int spacing = 1;

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

            if (y == 0 && (x == 0 || x == gridWidth - 1)) {
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

        if (vertices.mass[i] == 0.0f) { continue; }

        vertices.accelX[i] = Setup::PhysDescription::GRAVITY.x;
        vertices.accelY[i] = Setup::PhysDescription::GRAVITY.y;
        vertices.accelZ[i] = Setup::PhysDescription::GRAVITY.z;
    }

    Data::ConstraintData constraints = Data::ConstraintData();

    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            int idx = y * gridWidth + x;

            if (x < gridWidth - 1) {
                int rightIdx = y * gridWidth + (x + 1);

                if (y == 0) {
                    addConstraint(idx, rightIdx, 0.8f, vertices, constraints);
                } else {
                    addConstraint(idx, rightIdx, 0.8f, vertices, constraints);
                }
            }

            if (y < gridHeight - 1) {
                int bottomIdx = (y + 1) * gridWidth + x;
                addConstraint(idx, bottomIdx, 0.8f, vertices, constraints);
            }

            if (x < gridWidth - 1 && y < gridHeight - 1) {
                int diagDownIdx = (y + 1) * gridWidth + (x + 1);
                addConstraint(idx, diagDownIdx, 0.8f, vertices, constraints);

                if (x > 0) {
                    int diagDownLeftIdx = (y + 1) * gridWidth + (x - 1);
                    addConstraint(idx, diagDownLeftIdx, 0.8f, vertices, constraints);
                }
            }
        }
    }

    Data::IntermediatePos inters = Data::IntermediatePos();
    inters.predictedPosX = vertices.posX;
    inters.predictedPosY = vertices.posY;
    inters.predictedPosZ = vertices.posZ;

    std::ofstream csvFile("positions.csv");
    csvFile << "Frame,Vertex,PosX,PosY,PosZ" << std::endl;

    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

    for (int i = 0; i < 8192; i++) {
        for (int j = 0; j < vertices.accelX.size(); j++) {
            float3 res = Stormer::one(vertices.posX[j], vertices.posY[j], vertices.posZ[j], vertices.prevPosX[j], vertices.prevPosY[j], vertices.prevPosZ[j], vertices.accelX[j], vertices.accelY[j], vertices.accelZ[j]);

            inters.predictedPosX[j] = res.x;
            inters.predictedPosY[j] = res.y;
            inters.predictedPosZ[j] = res.z;
        }

        for (int j = 0; j < Setup::PhysDescription::CSOLVER_ITERATIONS; j++) {
            for (int k = 0; k < constraints.stiffness.size(); k++) {

                int idx1 = constraints.idxA[k];
                int idx2 = constraints.idxB[k];

                float& x1 = inters.predictedPosX[idx1];
                float& y1 = inters.predictedPosY[idx1];
                float& z1 = inters.predictedPosZ[idx1];

                float& x2 = inters.predictedPosX[idx2];
                float& y2 = inters.predictedPosY[idx2];
                float& z2 = inters.predictedPosZ[idx2];

                float3 pos1 = {x1, y1, z1};
                float3 pos2 = {x2, y2, z2};

                gaussSeidel(pos1, pos2, vertices.mass[idx1], vertices.mass[idx2], constraints.length[k], constraints.stiffness[k]);

                x1 = pos1.x;
                y1 = pos1.y;
                z1 = pos1.z;

                x2 = pos2.x;
                y2 = pos2.y;
                z2 = pos2.z;
            }
        }

        for (int j = 0; j < vertices.accelX.size(); j++) {
            Stormer::two(vertices.posX[j], vertices.posY[j], vertices.posZ[j], vertices.prevPosX[j], vertices.prevPosY[j], vertices.prevPosZ[j], inters.predictedPosX[j], inters.predictedPosY[j], inters.predictedPosZ[j]);
        }

        for (int j = 0; j < vertices.accelX.size(); j++) {
            csvFile << i << "," << j << "," << vertices.posX[j] << "," << vertices.posY[j] << "," << vertices.posZ[j] << std::endl;
        }
    }

    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;

    std::cout << time << std::endl;

    csvFile.close();
    std::cout << "Position data written to positions.csv" << std::endl;

    return 0;
}
