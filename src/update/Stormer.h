#ifndef STORMER
#define STORMER
#include "../types.h"
#include "../world/WorldDescription.h"

namespace Stormer {
    static float3 one(float xc, float yc, float zc, float xp, float yp, float zp, float ax, float ay, float az) {

        float3 currentPos = {xc, yc, zc};
        float3 previousPos = {xp, yp, zp};

        float3 accel = {ax, ay, az};

        return (currentPos * 2.0) - previousPos + (accel * (World::DT * World::DT));
    }

    static void two(float& xc, float& yc, float& zc, float& xp, float& yp, float& zp, float& xf, float& yf, float& zf) {

        xp = xc;
        yp = yc;
        zp = zc;

        xc = xf;
        yc = yf;
        zc = zf;
    }
}

#endif //STORMER