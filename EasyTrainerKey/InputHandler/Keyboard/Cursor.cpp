#include "InputHandler/Keyboard/Keyboard.h"

namespace EasyTrainer::Input {
    namespace Keyboard {

        static bool s_cursorEnabled = false;

        // CET ForceCursor reloc
        static RED4ext::UniversalRelocFunc<void (*)(RED4ext::CBaseEngine::UnkD0*, RED4ext::CName, bool)>
            ForceCursor(2130646213UL);

        void SetCursorVisible(bool enable)
        {
            if (s_cursorEnabled == enable)
                return; 

            auto* engine = RED4ext::CGameEngine::Get();
            if (!engine || !engine->unkD0)
                return;

            RED4ext::CName reason("EasyTrainer");
            ForceCursor(engine->unkD0, reason, enable);

            if (enable) {
                ShowCursor(TRUE); 
            }
            else {
                ShowCursor(FALSE);  // hide once - we don't want to force hide it so others can use it 
            }

            s_cursorEnabled = enable;
        }

        void ShowCursorFn(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
        {
            bool enable = false;
            RED4ext::GetParameter(aFrame, &enable);
            aFrame->code++;

            SetCursorVisible(enable);
            if (aOut) *aOut = s_cursorEnabled;
        }

        void IsCursorVisibleFn(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
        {
            aFrame->code++;
            if (aOut) *aOut = s_cursorEnabled;
        }

    } 
} 
