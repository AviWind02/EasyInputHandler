#pragma once
#include "Common.h"

namespace EasyTrainer::Input {
    namespace Keyboard {

        // Keyboard
        bool IsKeyDown(int vKey);

        void IsKeyPressed(RED4ext::IScriptable*, RED4ext::CStackFrame*, bool* aOut, int64_t);
        void IsKeyboardActive(RED4ext::IScriptable*, RED4ext::CStackFrame*, bool* aOut, int64_t);
        void GetPressedKey(RED4ext::IScriptable*, RED4ext::CStackFrame*, int32_t* aOut, int64_t);

        // Cursor
        void SetCursorVisible(bool enable);
        void ShowCursorFn(RED4ext::IScriptable*, RED4ext::CStackFrame*, bool* aOut, int64_t);
        void IsCursorVisibleFn(RED4ext::IScriptable*, RED4ext::CStackFrame*, bool* aOut, int64_t);

    } 
} 
