#pragma once
#include "Common.h"

namespace EasyTrainer::Input {
    namespace Gamepad {

        // Buttons
        void IsGamepadButtonPressed(RED4ext::IScriptable*, RED4ext::CStackFrame*, bool* aOut, int64_t);
        void IsGamepadActive(RED4ext::IScriptable*, RED4ext::CStackFrame*, bool* aOut, int64_t);
        void GetPressedGamepadButton(RED4ext::IScriptable*, RED4ext::CStackFrame*, int32_t* aOut, int64_t);

        // Axis
        void GetGamepadAxis(RED4ext::IScriptable*, RED4ext::CStackFrame*, int32_t* aOut, int64_t);

        // Stick directions
        void IsLeftStickDirection(RED4ext::IScriptable*, RED4ext::CStackFrame*, bool* aOut, int64_t);
        void IsRightStickDirection(RED4ext::IScriptable*, RED4ext::CStackFrame*, bool* aOut, int64_t);

        // Triggers
        void GetLeftTrigger(RED4ext::IScriptable*, RED4ext::CStackFrame*, int32_t* aOut, int64_t);
        void GetRightTrigger(RED4ext::IScriptable*, RED4ext::CStackFrame*, int32_t* aOut, int64_t);
        void GetLeftTriggerNormalized(RED4ext::IScriptable*, RED4ext::CStackFrame*, float* aOut, int64_t);
        void GetRightTriggerNormalized(RED4ext::IScriptable*, RED4ext::CStackFrame*, float* aOut, int64_t);

        // Vibration
        void SetGamepadVibration(RED4ext::IScriptable*, RED4ext::CStackFrame*, bool* aOut, int64_t);

    }
} 
