#ifndef WORLDDESCRIPTION
#define WORLDDESCRIPTION
#include <cstdint>
#include "../Types.h"

namespace Setup {
    namespace WorldDescription {
        constexpr int32_t HZ = 60;
        constexpr float DT = 1.0f / HZ;
    }

}

#endif //WORLDDESCRIPTION