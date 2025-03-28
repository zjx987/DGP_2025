/***************************************************************************
 # Copyright (c) 2015-23, NVIDIA CORPORATION. All rights reserved.
 #
 # Redistribution and use in source and binary forms, with or without
 # modification, are permitted provided that the following conditions
 # are met:
 #  * Redistributions of source code must retain the above copyright
 #    notice, this list of conditions and the following disclaimer.
 #  * Redistributions in binary form must reproduce the above copyright
 #    notice, this list of conditions and the following disclaimer in the
 #    documentation and/or other materials provided with the distribution.
 #  * Neither the name of NVIDIA CORPORATION nor the names of its
 #    contributors may be used to endorse or promote products derived
 #    from this software without specific prior written permission.
 #
 # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND ANY
 # EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 # IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 # PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 # CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 # EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 # PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 # PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 # OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 # (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 # OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **************************************************************************/
#pragma once
#include "utils/HostDeviceShared.slangh"

#ifdef HOST_CODE
#include "Scene/Material/TextureHandle.slang"
#include "Scene/Material/DiffuseSpecularData.slang"
#else
__exported import Scene.Material.TextureHandle;
__exported import Scene.Material.DiffuseSpecularData;
#endif

USTC_CG_NAMESPACE_OPEN_SCOPE

/** This is a host/device structure that describes a measured MERL material.
*/
struct MERLMaterialData
{
    // MaterialHeader (16B) is stored just before this struct in memory.
    uint bufferID = 0;                  ///< Buffer ID in material system where BRDF data is stored.
    uint samplerID = 0;                 ///< Texture sampler ID for LUT sampler.
    DiffuseSpecularData extraData = {}; ///< Parameters for a best fit BRDF approximation.
    TextureHandle texAlbedoLUT;         ///< Texture handle for albedo LUT.

    static constexpr uint kAlbedoLUTSize = 256;
};

USTC_CG_NAMESPACE_CLOSE_SCOPE
