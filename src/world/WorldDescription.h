#ifndef WORLDDESCRIPTION
#define WORLDDESCRIPTION
#include <cstdint>
#include "../Types.h"

namespace World {

    constexpr int32_t HZ = 50;
    constexpr float DT = 1.0f / HZ;

    constexpr int32_t GS_ITER = 1;

    constexpr float CONSTRAINT_DAMPING = 0.99f;

    constexpr float3 gravity = float3(0.0f, -9.8f, 0.0f);
}

#endif //WORLDDESCRIPTION