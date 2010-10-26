/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_UI_CACHES_H
#define ANDROID_UI_CACHES_H

#ifndef LOG_TAG
    #define LOG_TAG "OpenGLRenderer"
#endif

#include <utils/Singleton.h>

#include "Extensions.h"
#include "FontRenderer.h"
#include "GammaFontRenderer.h"
#include "TextureCache.h"
#include "LayerCache.h"
#include "GradientCache.h"
#include "PatchCache.h"
#include "ProgramCache.h"
#include "PathCache.h"
#include "TextDropShadowCache.h"
#include "FboCache.h"
#include "Line.h"
#include "ResourceCache.h"

namespace android {
namespace uirenderer {

///////////////////////////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////////////////////////

#define REQUIRED_TEXTURE_UNITS_COUNT 3

// Generates simple and textured vertices
#define FV(x, y, u, v) { { x, y }, { u, v } }

// This array is never used directly but used as a memcpy source in the
// OpenGLRenderer constructor
static const TextureVertex gMeshVertices[] = {
        FV(0.0f, 0.0f, 0.0f, 0.0f),
        FV(1.0f, 0.0f, 1.0f, 0.0f),
        FV(0.0f, 1.0f, 0.0f, 1.0f),
        FV(1.0f, 1.0f, 1.0f, 1.0f)
};
static const GLsizei gMeshStride = sizeof(TextureVertex);
static const GLsizei gMeshTextureOffset = 2 * sizeof(float);
static const GLsizei gMeshCount = 4;

///////////////////////////////////////////////////////////////////////////////
// Debug
///////////////////////////////////////////////////////////////////////////////

struct CacheLogger {
    CacheLogger() {
        LOGD("Creating caches");
    }
}; // struct CacheLogger

///////////////////////////////////////////////////////////////////////////////
// Caches
///////////////////////////////////////////////////////////////////////////////

class Caches: public Singleton<Caches> {
    Caches();

    friend class Singleton<Caches>;

    CacheLogger mlogger;

    GLuint mCurrentBuffer;

public:
    void bindMeshBuffer();
    void bindMeshBuffer(const GLuint buffer);
    void unbindMeshBuffer();

    bool blend;
    GLenum lastSrcMode;
    GLenum lastDstMode;
    Program* currentProgram;

    // VBO to draw with
    GLuint meshBuffer;

    // GL extensions
    Extensions extensions;

    // Misc
    GLint maxTextureSize;

    TextureCache textureCache;
    LayerCache layerCache;
    GradientCache gradientCache;
    ProgramCache programCache;
    PathCache pathCache;
    PatchCache patchCache;
    TextDropShadowCache dropShadowCache;
    FboCache fboCache;
    GammaFontRenderer fontRenderer;
    ResourceCache resourceCache;

    Line line;
}; // class Caches

}; // namespace uirenderer

}; // namespace android

#endif // ANDROID_UI_CACHES_H
