// Avi
// EasyTrainer Input Plugin
// Bridges keyboard, mouse/cursor, and gamepad input via RED4ext

#include "Common.h"
#include "InputHandler/InputHandler.h"

RED4EXT_C_EXPORT bool RED4EXT_CALL Main(
    RED4ext::PluginHandle,
    RED4ext::EMainReason reason,
    const RED4ext::Sdk*)
{
    if (reason == RED4ext::EMainReason::Load) {
        auto* rtti = RED4ext::CRTTISystem::Get();
        rtti->AddRegisterCallback(EasyTrainer::Input::RegisterTypes);
        rtti->AddPostRegisterCallback(EasyTrainer::Input::PostRegisterTypes);
    }
    return true;
}

RED4EXT_C_EXPORT void RED4EXT_CALL Query(RED4ext::PluginInfo* i)
{
    i->name = L"EasyInputHandler";
    i->author = L"Avi";
    i->version = RED4EXT_SEMVER(1, 0, 0);
    i->runtime = RED4EXT_RUNTIME_LATEST;
    i->sdk = RED4EXT_SDK_LATEST;
}

RED4EXT_C_EXPORT uint32_t RED4EXT_CALL Supports()
{
    return RED4EXT_API_VERSION_LATEST;
}
