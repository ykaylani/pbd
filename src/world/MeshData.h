#ifndef MESHDATA
#define MESHDATA
#include <vector>

namespace Data {
    struct MeshDataVertices {
        std::vector<float> posX;
        std::vector<float> posY;
        std::vector<float> posZ;

        std::vector<float> prevPosX;
        std::vector<float> prevPosY;
        std::vector<float> prevPosZ;

        std::vector<float> accelX;
        std::vector<float> accelY;
        std::vector<float> accelZ;

        std::vector<float> mass; //mass is ALWAYS inverse
    };

    struct MeshDataConstraints {
        std::vector<int> idxA;
        std::vector<int> idxB;

        std::vector<float> length;
    };

    struct MeshDataGSeidel {
        std::vector<float> predictedPosX;
        std::vector<float> predictedPosY;
        std::vector<float> predictedPosZ;
    };
}

#endif //MESHDATA