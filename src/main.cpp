#include <iostream>

#include "joltjni_bridge.h"

#include "net_xmx_nativexbullet_Gravity.h"

JNIEXPORT void JNICALL Java_net_xmx_nativexbullet_Gravity_setNative
(JNIEnv* env, jclass clazz, jlong physicsSystemPtr, jfloat gx, jfloat gy, float gz) {

    std::cout << "C++ (xbullet.dll): Native function 'setNative' was called." << std::endl;

    if (physicsSystemPtr == 0) {
        std::cerr << "C++ (xbullet.dll): Error, received a null pointer from Java!" << std::endl;
        return;
    }

    Java_com_github_stephengold_joltjni_PhysicsSystem_setGravity(
        nullptr, nullptr, physicsSystemPtr, gx, gy, gz);

    std::cout << "C++ (xbullet.dll): Call to joltjni.dll to set gravity finished." << std::endl;
}