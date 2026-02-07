#ifndef MESHDATA
#define MESHDATA
#include <vector>

namespace Data {
    struct MeshDataVt {
        std::vector<float> vertX;
        std::vector<float> vertY;
        std::vector<float> vertZ;

        std::vector<float> vertXp;
        std::vector<float> vertYp;
        std::vector<float> vertZp;

        std::vector<float> acX;
        std::vector<float> acY;
        std::vector<float> acZ;

        std::vector<float> mass;
    };

    struct MeshDataC {
        std::vector<int> idxA;
        std::vector<int> idxB;

        std::vector<float> length;
    };

    struct MeshDataGS {
        std::vector<float> predictedPosX;
        std::vector<float> predictedPosY;
        std::vector<float> predictedPosZ;
    };
}

#endif //MESHDATA