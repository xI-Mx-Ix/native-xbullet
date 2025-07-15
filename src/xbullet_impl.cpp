#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>

#include "net_xmx_nativexbullet_NativeGravityTest.h"

#include <iostream>

JNIEXPORT void JNICALL Java_net_xmx_xbullet_natives_XBulletNatives_setGravityInXBullet
  (JNIEnv *env, jclass clazz, jlong physicsSystemPtr, jfloat gx, jfloat gy, jfloat gz) {

    if (physicsSystemPtr == 0) {
        std::cerr << "[xbullet.dll] Fehler: Ungültiger (NULL) PhysicsSystem Pointer erhalten." << std::endl;
        return;
    }

    JPH::PhysicsSystem* system = reinterpret_cast<JPH::PhysicsSystem*>(physicsSystemPtr);

    JPH::Vec3 new_gravity(gx, gy, gz);

    system->SetGravity(new_gravity);

    std::cout << "[xbullet.dll] Gravitation erfolgreich auf ("
              << gx << ", " << gy << ", " << gz << ") gesetzt." << std::endl;
}