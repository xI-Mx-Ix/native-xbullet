#include <iostream>

#include <jni.h>

#include <Jolt/Physics/PhysicsSystem.h>
#include "net_xmx_nativexbullet_Gravity.h"

JNIEXPORT void JNICALL Java_net_xmx_nativexbullet_Gravity_setGravity
  (JNIEnv* env, jclass clazz, jlong physicsSystemPtr, jfloat gx, jfloat gy, jfloat gz) {

    if (physicsSystemPtr == 0) {
        std::cerr << "[xbullet library] Error: Received a NULL pointer for PhysicsSystem from Java." << std::endl;
        return;
    }

    JPH::PhysicsSystem* physSystem = reinterpret_cast<JPH::PhysicsSystem*>(physicsSystemPtr);

    physSystem->SetGravity(JPH::Vec3(gx, gy, gz));

    std::cout << "[xbullet library] Successfully called JPH::PhysicsSystem::SetGravity via custom native call." << std::endl;
}
