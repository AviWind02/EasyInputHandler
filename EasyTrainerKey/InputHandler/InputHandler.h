#pragma once
#include "Common.h"

#include "Gamepad/Gamepad.h"
#include "Keyboard/Keyboard.h"

namespace EasyTrainer::Input
{
    struct InputHandler : RED4ext::IScriptable
    {
        RED4ext::CClass* GetNativeType() override;
    };

    // RTTI type
    extern RED4ext::TTypedClass<InputHandler> g_InputHandlerType;

    // Registration
    void RegisterTypes();
    void PostRegisterTypes();
}
