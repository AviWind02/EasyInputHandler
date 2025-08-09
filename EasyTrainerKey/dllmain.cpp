#include "pch.h"
#include <RED4ext/RED4ext.hpp>
#include <RED4ext/CNamePool.hpp>
#include <RED4ext/Api/PluginHandle.hpp>
#include <RED4ext/Api/Sdk.hpp>
#include <RED4ext/Api/Version.hpp>
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "Xinput9_1_0.lib")

struct EasyTrainerInputHandler : RED4ext::IScriptable
{
    RED4ext::CClass* GetNativeType() override;
};

RED4ext::TTypedClass<EasyTrainerInputHandler> etNativeClass("EasyTrainerInputHandler");

RED4ext::CClass* EasyTrainerInputHandler::GetNativeType()
{
    return &etNativeClass;
}

inline bool IsKeyDown(int vKey)
{
    return (GetAsyncKeyState(vKey) & 0x8000) != 0;
}

inline bool IsPadButtonDown(WORD button)
{
    XINPUT_STATE state{};
    if (XInputGetState(0, &state) == ERROR_SUCCESS)
        return (state.Gamepad.wButtons & button) != 0;
    return false;
}


void IsKeyPressed(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
{
    int32_t keyCode;
    RED4ext::GetParameter(aFrame, &keyCode);
    aFrame->code++;

    if (aOut) *aOut = IsKeyDown(keyCode);
}

void IsGamepadButtonPressed(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
{
    int32_t buttonCode;
    RED4ext::GetParameter(aFrame, &buttonCode);
    aFrame->code++;

    if (aOut) *aOut = IsPadButtonDown(static_cast<WORD>(buttonCode));
}

void IsKeyboardActive(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
{
    aFrame->code++;
    if (aOut)
    {
        for (int key = 0x01; key <= 0xFE; key++)
        {
            if (IsKeyDown(key))
            {
                *aOut = true;
                return;
            }
        }
        *aOut = false;
    }
}

void IsGamepadActive(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
{
    aFrame->code++;
    if (aOut)
    {
        XINPUT_STATE state{};
        if (XInputGetState(0, &state) == ERROR_SUCCESS)
        {
            *aOut = (state.Gamepad.wButtons != 0);
            return;
        }
        *aOut = false;
    }
}

void GetPressedKey(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, int32_t* aOut, int64_t)
{
    aFrame->code++;
    if (aOut)
    {
        *aOut = 0;
        for (int key = 0x01; key <= 0xFE; key++)
        {
            if (IsKeyDown(key))
            {
                *aOut = key;
                return;
            }
        }
    }
}

void GetPressedGamepadButton(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, int32_t* aOut, int64_t)
{
    aFrame->code++;
    if (aOut)
    {
        *aOut = 0;
        XINPUT_STATE state{};
        if (XInputGetState(0, &state) == ERROR_SUCCESS)
        {
            WORD buttons = state.Gamepad.wButtons;
            if (buttons != 0)
                *aOut = static_cast<int32_t>(buttons);
        }
    }
}


RED4EXT_C_EXPORT void RED4EXT_CALL RegisterTypes()
{
    etNativeClass.flags.isNative = true;
    RED4ext::CRTTISystem::Get()->RegisterType(&etNativeClass);
}

RED4EXT_C_EXPORT void RED4EXT_CALL PostRegisterTypes()
{
    auto regFunc = [&](const char* name, auto fn)
        {
            auto f = RED4ext::CClassFunction::Create(&etNativeClass, name, name, fn, { .isNative = true });
            f->SetReturnType("Bool");
            etNativeClass.RegisterFunction(f);
        };

    auto rtti = RED4ext::CRTTISystem::Get();
    etNativeClass.parent = rtti->GetClass("IScriptable");

    regFunc("IsKeyPressed", &IsKeyPressed);
    regFunc("IsGamepadButtonPressed", &IsGamepadButtonPressed);
    regFunc("IsKeyboardActive", &IsKeyboardActive);
    regFunc("IsGamepadActive", &IsGamepadActive);

    auto regFuncInt = [&](const char* name, auto fn)
    {
        auto f = RED4ext::CClassFunction::Create(&etNativeClass, name, name, fn, { .isNative = true });
        f->SetReturnType("Int32");
        etNativeClass.RegisterFunction(f);
    };

    regFuncInt("GetPressedKey", &GetPressedKey);
    regFuncInt("GetPressedGamepadButton", &GetPressedGamepadButton);


}

RED4EXT_C_EXPORT bool RED4EXT_CALL Main(RED4ext::PluginHandle, RED4ext::EMainReason reason, const RED4ext::Sdk*)
{
    if (reason == RED4ext::EMainReason::Load)
    {
        auto* rtti = RED4ext::CRTTISystem::Get();
        rtti->AddRegisterCallback(RegisterTypes);
        rtti->AddPostRegisterCallback(PostRegisterTypes);
    }
    return true;
}

RED4EXT_C_EXPORT void RED4EXT_CALL Query(RED4ext::PluginInfo* i)
{
    i->name = L"EasyTrainerInputHandler";
    i->author = L"Avi";
    i->version = RED4EXT_SEMVER(1, 0, 0);
    i->runtime = RED4EXT_RUNTIME_LATEST;
    i->sdk = RED4EXT_SDK_LATEST;
}

RED4EXT_C_EXPORT uint32_t RED4EXT_CALL Supports()
{
    return RED4EXT_API_VERSION_LATEST;
}
