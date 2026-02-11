#ifndef STORMER
#define STORMER
#include "PhysDescription.h"
#include "../Types.h"
#include "../world/WorldDescription.h"

namespace Stormer {
    static float3 one(float xc, float yc, float zc, float xp, float yp, float zp, float ax, float ay, float az) { //xc: x-current, xp: x-previous, ax, acceleration-x

        float3 currentPos = {xc, yc, zc};
        float3 previousPos = {xp, yp, zp};

        float3 accel = {ax, ay, az};

        return currentPos + Setup::PhysDescription::DAMPING * (currentPos - previousPos) + accel * (Setup::WorldDescription::DT * Setup::WorldDescription::DT);
    }

    static void two(float& xCurrent, float& yCurrent, float& zCurrent, float& xPrevious, float& yPrevious, float& zPrevious, float& xFuture, float& yFuture, float& zFuture) {

        xPrevious = xCurrent;
        yPrevious = yCurrent;
        zPrevious = zCurrent;

        xCurrent = xFuture;
        yCurrent = yFuture;
        zCurrent = zFuture;
    }
}

#endif //STORMER