#ifndef PHYSDESCRIPTION
#define PHYSDESCRIPTION
#include <cstdint>
#include "../Types.h"

namespace Setup {
    namespace PhysDescription {
        constexpr int32_t CSOLVER_ITERATIONS = 4;
        constexpr float3 GRAVITY = float3(0.0f, -9.8f, 0.0f);
        constexpr float DAMPING = 0.995f;
    }
}

#endif //PHYSDESCRIPTION