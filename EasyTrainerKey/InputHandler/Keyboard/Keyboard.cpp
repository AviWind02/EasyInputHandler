#include "InputHandler/Keyboard/Keyboard.h"

namespace EasyTrainer::Input {
    namespace Keyboard {

		// checking if window is foreground - if not, ignore key presses(to be used in lua)
        static bool IsGameWindowFocused()
        {
            HWND hwnd = GetForegroundWindow();
            if (!hwnd)
                return false;

            DWORD pid = 0;
            GetWindowThreadProcessId(hwnd, &pid);
            return pid == GetCurrentProcessId();
        }

        bool IsKeyDown(int vKey)
        {
            if (!IsGameWindowFocused())
                return false;
            return (GetAsyncKeyState(vKey) & 0x8000) != 0;
        }

        void IsKeyPressed(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
        {
            int32_t keyCode;
            RED4ext::GetParameter(aFrame, &keyCode);
            aFrame->code++;

            if (aOut) *aOut = IsKeyDown(keyCode);
        }

        void IsKeyboardActive(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
        {
            aFrame->code++;
            if (aOut) {
                for (int key = 0x01; key <= 0xFE; key++) {
                    if (IsKeyDown(key)) {
                        *aOut = true;
                        return;
                    }
                }
                *aOut = false;
            }
        }

        void GetPressedKey(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, int32_t* aOut, int64_t)
        {
            aFrame->code++;
            if (aOut) {
                *aOut = 0;
                for (int key = 0x01; key <= 0xFE; key++) {
                    if (IsKeyDown(key)) {
                        *aOut = key;
                        return;
                    }
                }
            }
        }

    }
}
