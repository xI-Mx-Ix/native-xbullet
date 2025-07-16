#include <iostream>
#include <jni.h>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>

#include "net_xmx_nativexbullet_Gravity.h"

JNIEXPORT void JNICALL Java_net_xmx_nativexbullet_Gravity_setGravityInternal
  (JNIEnv* env, jclass clazz, jlong physicsSystemPtr, jfloat gx, jfloat gy, jfloat gz) {

    if (physicsSystemPtr == 0) {
        std::cerr << "[xbullet library] Error: Received a NULL pointer for PhysicsSystem from Java." << std::endl;
        return;
    }

    JPH::PhysicsSystem* physSystem = reinterpret_cast<JPH::PhysicsSystem*>(physicsSystemPtr);

    physSystem->SetGravity(JPH::Vec3(gx, gy, gz));
}

JNIEXPORT jstring JNICALL Java_net_xmx_nativexbullet_Gravity_getXBulletVersion
  (JNIEnv *env, jclass clazz) {

    return env->NewStringUTF("xbullet-1.0-test");
}