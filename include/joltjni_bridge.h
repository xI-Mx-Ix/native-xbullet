#ifndef JOLTJNI_BRIDGE_H
#define JOLTJNI_BRIDGE_H

#include <jni.h>

extern "C" {

JNIEXPORT void JNICALL
Java_com_github_stephengold_joltjni_PhysicsSystem_setGravity(
    JNIEnv*, jclass, jlong systemVa, jfloat x, jfloat y, jfloat z);

} 

#endif 