//
// Copyright 2020 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef Hd_USTC_CG_RENDER_DELEGATE_H
#define Hd_USTC_CG_RENDER_DELEGATE_H

#include "api.h"
#include "nodes/system/node_system.hpp"
#include "nvrhi/nvrhi.h"
#include "pxr/base/tf/staticTokens.h"
#include "pxr/imaging/hd/renderDelegate.h"
#include "pxr/pxr.h"
#include "renderParam.h"
#include "renderer.h"

#include "../nodes/shaders/shaders/Scene/SceneTypes.slang"

namespace USTC_CG {
class LensSystem;
struct RenderGlobalPayload;
}  // namespace USTC_CG

USTC_CG_NAMESPACE_OPEN_SCOPE
class Hd_USTC_CG_Material;
class Hd_USTC_CG_Light;
using namespace pxr;
#define Hd_USTC_CG_RENDER_SETTINGS_TOKENS        \
    (enableAmbientOcclusion)(enableSceneColors)( \
        ambientOcclusionSamples)(renderMode)
// Also: HdRenderSettingsTokens->convergedSamplesPerPixel

TF_DECLARE_PUBLIC_TOKENS(
    Hd_USTC_CG_RenderSettingsTokens,
    Hd_USTC_CG_RENDER_SETTINGS_TOKENS);

class HD_USTC_CG_API Hd_USTC_CG_RenderDelegate final : public HdRenderDelegate {
   public:
    /// Render delegate constructor.
    Hd_USTC_CG_RenderDelegate();
    /// Render delegate constructor.
    Hd_USTC_CG_RenderDelegate(const HdRenderSettingsMap& settingsMap);
    /// Render delegate destructor.
    ~Hd_USTC_CG_RenderDelegate() override;

    /// Supported types
    const TfTokenVector& GetSupportedRprimTypes() const override;
    const TfTokenVector& GetSupportedSprimTypes() const override;
    const TfTokenVector& GetSupportedBprimTypes() const override;

    // Basic value to return from the RD
    HdResourceRegistrySharedPtr GetResourceRegistry() const override;

    // Prims
    HdRenderPassSharedPtr CreateRenderPass(
        HdRenderIndex* index,
        const HdRprimCollection& collection) override;

    HdInstancer* CreateInstancer(HdSceneDelegate* delegate, const SdfPath& id)
        override;
    void DestroyInstancer(HdInstancer* instancer) override;

    HdRprim* CreateRprim(const TfToken& typeId, const SdfPath& rprimId)
        override;
    void DestroyRprim(HdRprim* rPrim) override;

    HdSprim* CreateSprim(const TfToken& typeId, const SdfPath& sprimId)
        override;
    HdSprim* CreateFallbackSprim(const TfToken& typeId) override;
    void DestroySprim(HdSprim* sprim) override;

    HdBprim* CreateBprim(const TfToken& typeId, const SdfPath& bprimId)
        override;
    HdBprim* CreateFallbackBprim(const TfToken& typeId) override;
    void DestroyBprim(HdBprim* bprim) override;

    void CommitResources(HdChangeTracker* tracker) override;

    HdRenderParam* GetRenderParam() const override;

    VtValue GetRenderSetting(TfToken const& key) const override;
    void SetRenderSetting(const TfToken& key, const VtValue& value) override;
    bool Stop(bool blocking) override;

private:
    static const TfTokenVector SUPPORTED_RPRIM_TYPES;
    static const TfTokenVector SUPPORTED_SPRIM_TYPES;
    static const TfTokenVector SUPPORTED_BPRIM_TYPES;

    void _Initialize();

    std::atomic<int> _sceneVersion;
    std::shared_ptr<Hd_USTC_CG_RenderParam> _renderParam;
    HdRenderThread _renderThread;
    std::shared_ptr<Hd_USTC_CG_Renderer> _renderer;
    pxr::VtArray<Hd_USTC_CG_Light*> lights;
    pxr::VtArray<Hd_USTC_CG_Camera*> cameras;
    pxr::TfHashMap<SdfPath, Hd_USTC_CG_Material*, TfHash> materials;
    pxr::VtArray<Hd_USTC_CG_Mesh*> meshes;
    nvrhi::IDevice* nvrhi_device;
    std::unique_ptr<RenderGlobalPayload> _globalPayload;
    std::shared_ptr<NodeSystem> node_system;

    static std::mutex _mutexResourceRegistry;
    static std::atomic_int _counterResourceRegistry;
    static HdResourceRegistrySharedPtr _resourceRegistry;

    Hd_USTC_CG_RenderDelegate(const Hd_USTC_CG_RenderDelegate&) = delete;
    Hd_USTC_CG_RenderDelegate& operator=(const Hd_USTC_CG_RenderDelegate&) =
        delete;

   public:
    HdAovDescriptor GetDefaultAovDescriptor(const TfToken& name) const override;

   private:
    // A list of render setting exports.
    HdRenderSettingDescriptorList _settingDescriptors;

   private:
    bool m_TearingSupported = false;
};

USTC_CG_NAMESPACE_CLOSE_SCOPE

#endif  // Hd_USTC_CG_RENDER_DELEGATE_H
