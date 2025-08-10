// Avi
// Created for EasyTrainer because native input handling in my mod wasn't great.
// CET input worked okay but lacked controller support, so this file bridges both
// keyboard and gamepad input checks via RED4ext.

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

// Checks if the game window is currently focused
bool IsGameWindowFocused()
{
    HWND hwnd = GetForegroundWindow();
    if (!hwnd)
        return false;

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);

    return pid == GetCurrentProcessId();
}

// Checks if a given virtual key is currently down
bool IsKeyDown(int vKey)
{
    if (!IsGameWindowFocused())
        return false;

    return (GetAsyncKeyState(vKey) & 0x8000) != 0;
}

// Checks if a given gamepad button is currently down
bool IsPadButtonDown(WORD button)
{
    if (!IsGameWindowFocused())
        return false;

    XINPUT_STATE state{};
    if (XInputGetState(0, &state) == ERROR_SUCCESS)
        return (state.Gamepad.wButtons & button) != 0;
    return false;
}

// Returns true if the specified keyboard key is pressed
void IsKeyPressed(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
{
    int32_t keyCode;
    RED4ext::GetParameter(aFrame, &keyCode);
    aFrame->code++;

    if (aOut) *aOut = IsKeyDown(keyCode);
}

// Returns true if the specified gamepad button is pressed
void IsGamepadButtonPressed(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
{
    int32_t buttonCode;
    RED4ext::GetParameter(aFrame, &buttonCode);
    aFrame->code++;

    if (aOut) *aOut = IsPadButtonDown(static_cast<WORD>(buttonCode));
}

// Returns true if any keyboard key is currently pressed
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

// Returns true if any gamepad button is currently pressed
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

// Returns the virtual key code of the first pressed keyboard key (0 if none)
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

// Returns the gamepad button for currently pressed buttons (0 if none)
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

    auto regFuncInt = [&](const char* name, auto fn)
    {
        auto f = RED4ext::CClassFunction::Create(&etNativeClass, name, name, fn, { .isNative = true });
        f->SetReturnType("Int32");
        etNativeClass.RegisterFunction(f);
    };


    auto rtti = RED4ext::CRTTISystem::Get();
    etNativeClass.parent = rtti->GetClass("IScriptable");

    regFunc("IsKeyPressed", &IsKeyPressed);
    regFunc("IsGamepadButtonPressed", &IsGamepadButtonPressed);
    regFunc("IsKeyboardActive", &IsKeyboardActive);
    regFunc("IsGamepadActive", &IsGamepadActive);

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
