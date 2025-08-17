#include "InputHandler/InputHandler.h"
#include "InputHandler/Keyboard/Keyboard.h"
#include "InputHandler/Gamepad/Gamepad.h"

namespace EasyTrainer::Input {

    RED4ext::TTypedClass<InputHandler> g_InputHandlerType("EasyInputHandler");

    RED4ext::CClass* InputHandler::GetNativeType()
    {
        return &g_InputHandlerType;
    }

    void RegisterTypes()
    {
        g_InputHandlerType.flags.isNative = true;
        RED4ext::CRTTISystem::Get()->RegisterType(&g_InputHandlerType);
    }

    void PostRegisterTypes()
    {
        auto regFunc = [&](const char* name, auto fn)
            {
                auto f = RED4ext::CClassFunction::Create(&g_InputHandlerType, name, name, fn, { .isNative = true });
                f->SetReturnType("Bool");
                g_InputHandlerType.RegisterFunction(f);
            };

        auto regFuncInt = [&](const char* name, auto fn)
            {
                auto f = RED4ext::CClassFunction::Create(&g_InputHandlerType, name, name, fn, { .isNative = true });
                f->SetReturnType("Int32");
                g_InputHandlerType.RegisterFunction(f);
            };

        auto regFuncFloat = [&](const char* name, auto fn)
            {
                auto f = RED4ext::CClassFunction::Create(&g_InputHandlerType, name, name, fn, { .isNative = true });
                f->SetReturnType("Float");
                g_InputHandlerType.RegisterFunction(f);
            };

        auto rtti = RED4ext::CRTTISystem::Get();
        g_InputHandlerType.parent = rtti->GetClass("IScriptable");

        regFunc("IsKeyPressed", &Keyboard::IsKeyPressed);
        regFunc("IsKeyboardActive", &Keyboard::IsKeyboardActive);
        regFuncInt("GetPressedKey", &Keyboard::GetPressedKey);

        regFunc("ShowCursor", &Keyboard::ShowCursorFn);
        regFunc("IsCursorVisible", &Keyboard::IsCursorVisibleFn);

        regFunc("IsGamepadButtonPressed", &Gamepad::IsGamepadButtonPressed);
        regFunc("IsGamepadActive", &Gamepad::IsGamepadActive);
        regFuncInt("GetPressedGamepadButton", &Gamepad::GetPressedGamepadButton);
        regFuncInt("GetGamepadAxis", &Gamepad::GetGamepadAxis);

        regFunc("IsLeftStickDirection", &Gamepad::IsLeftStickDirection);
        regFunc("IsRightStickDirection", &Gamepad::IsRightStickDirection);
        regFuncInt("GetLeftTrigger", &Gamepad::GetLeftTrigger);
        regFuncInt("GetRightTrigger", &Gamepad::GetRightTrigger);
        regFuncFloat("GetLeftTriggerNormalized", &Gamepad::GetLeftTriggerNormalized);
        regFuncFloat("GetRightTriggerNormalized", &Gamepad::GetRightTriggerNormalized);
        regFunc("SetGamepadVibration", &Gamepad::SetGamepadVibration);
    }

}
