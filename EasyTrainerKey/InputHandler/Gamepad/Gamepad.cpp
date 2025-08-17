#include "InputHandler/Gamepad/Gamepad.h"

namespace EasyTrainer::Input {
    namespace Gamepad {

        static bool IsGameWindowFocused()
        {
            HWND hwnd = GetForegroundWindow();
            if (!hwnd)
                return false;

            DWORD pid = 0;
            GetWindowThreadProcessId(hwnd, &pid);
            return pid == GetCurrentProcessId();
        }

        static bool GetState(XINPUT_STATE& state)
        {
            if (!IsGameWindowFocused())
                return false;
            return (XInputGetState(0, &state) == ERROR_SUCCESS);
        }

        void IsGamepadButtonPressed(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
        {
            int32_t buttonCode;
            RED4ext::GetParameter(aFrame, &buttonCode);
            aFrame->code++;

            if (aOut) {
                XINPUT_STATE state{};
                *aOut = GetState(state) && (state.Gamepad.wButtons & buttonCode) != 0;
            }
        }

        void IsGamepadActive(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
        {
            aFrame->code++;
            if (aOut) {
                XINPUT_STATE state{};
                *aOut = GetState(state) && (state.Gamepad.wButtons != 0);
            }
        }

        void GetPressedGamepadButton(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, int32_t* aOut, int64_t)
        {
            aFrame->code++;
            if (aOut) {
                *aOut = 0;
                XINPUT_STATE state{};
                if (GetState(state)) {
                    if (state.Gamepad.wButtons != 0)
                        *aOut = static_cast<int32_t>(state.Gamepad.wButtons);
                }
            }
        }

        void GetGamepadAxis(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, int32_t* aOut, int64_t)
        {
            int32_t axisCode;
            RED4ext::GetParameter(aFrame, &axisCode);
            aFrame->code++;

            if (aOut) {
                *aOut = 0;
                XINPUT_STATE state{};
                if (GetState(state)) {
                    switch (axisCode) {
                    case 0: *aOut = state.Gamepad.sThumbLX; break;
                    case 1: *aOut = state.Gamepad.sThumbLY; break;
                    case 2: *aOut = state.Gamepad.sThumbRX; break;
                    case 3: *aOut = state.Gamepad.sThumbRY; break;
                    case 4: *aOut = state.Gamepad.bLeftTrigger; break;
                    case 5: *aOut = state.Gamepad.bRightTrigger; break;
                    }
                }
            }
        }

        static bool StickDir(short x, short y, const char* dir)
        {
            const SHORT DZ = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
            if (abs(x) < DZ) x = 0;
            if (abs(y) < DZ) y = 0;

            if (strcmp(dir, "up") == 0) return y > 0 && x == 0;
            if (strcmp(dir, "down") == 0) return y < 0 && x == 0;
            if (strcmp(dir, "left") == 0) return x < 0 && y == 0;
            if (strcmp(dir, "right") == 0) return x > 0 && y == 0;
            if (strcmp(dir, "upleft") == 0) return x < 0 && y > 0;
            if (strcmp(dir, "upright") == 0) return x > 0 && y > 0;
            if (strcmp(dir, "downleft") == 0) return x < 0 && y < 0;
            if (strcmp(dir, "downright") == 0) return x > 0 && y < 0;

            return false;
        }

        void IsLeftStickDirection(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
        {
            RED4ext::CString dir;
            RED4ext::GetParameter(aFrame, &dir);
            aFrame->code++;

            if (aOut) {
                XINPUT_STATE state{};
                *aOut = false;
                if (GetState(state)) {
                    *aOut = StickDir(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, dir.c_str());
                }
            }
        }

        void IsRightStickDirection(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
        {
            RED4ext::CString dir;
            RED4ext::GetParameter(aFrame, &dir);
            aFrame->code++;

            if (aOut) {
                XINPUT_STATE state{};
                *aOut = false;
                if (GetState(state)) {
                    *aOut = StickDir(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, dir.c_str());
                }
            }
        }

        void GetLeftTrigger(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, int32_t* aOut, int64_t)
        {
            aFrame->code++;
            if (aOut) {
                XINPUT_STATE state{};
                *aOut = GetState(state) ? state.Gamepad.bLeftTrigger : 0;
            }
        }

        void GetRightTrigger(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, int32_t* aOut, int64_t)
        {
            aFrame->code++;
            if (aOut) {
                XINPUT_STATE state{};
                *aOut = GetState(state) ? state.Gamepad.bRightTrigger : 0;
            }
        }

        void GetLeftTriggerNormalized(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, float* aOut, int64_t)
        {
            aFrame->code++;
            if (aOut) {
                XINPUT_STATE state{};
                *aOut = GetState(state) ? state.Gamepad.bLeftTrigger / 255.0f : 0.0f;
            }
        }

        void GetRightTriggerNormalized(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, float* aOut, int64_t)
        {
            aFrame->code++;
            if (aOut) {
                XINPUT_STATE state{};
                *aOut = GetState(state) ? state.Gamepad.bRightTrigger / 255.0f : 0.0f;
            }
        }

        void SetGamepadVibration(RED4ext::IScriptable*, RED4ext::CStackFrame* aFrame, bool* aOut, int64_t)
        {
            int32_t left, right;
            RED4ext::GetParameter(aFrame, &right);
            RED4ext::GetParameter(aFrame, &left);
            aFrame->code++;

            XINPUT_VIBRATION vib{};
            vib.wLeftMotorSpeed = static_cast<WORD>(left);
            vib.wRightMotorSpeed = static_cast<WORD>(right);

            if (aOut) *aOut = (XInputSetState(0, &vib) == ERROR_SUCCESS);
        }

    } 
} 
