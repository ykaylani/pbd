#ifndef MESHDATA
#define MESHDATA
#include <vector>

namespace Data {
    struct VertexData {
        std::vector<float> posX;
        std::vector<float> posY;
        std::vector<float> posZ;

        std::vector<float> prevPosX;
        std::vector<float> prevPosY;
        std::vector<float> prevPosZ;

        std::vector<float> accelX;
        std::vector<float> accelY;
        std::vector<float> accelZ;

        std::vector<float> mass;
    };

    struct ConstraintData {
        std::vector<int> idxA;
        std::vector<int> idxB;

        std::vector<float> length;
        std::vector<float> stiffness;

        std::vector<float> lambda;
    };

    struct IntermediatePos {
        std::vector<float> predictedPosX;
        std::vector<float> predictedPosY;
        std::vector<float> predictedPosZ;
    };
}

#endif //MESHDATA