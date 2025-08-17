# EasyTrainer Input Handler

A small RED4ext plugin that checks keyboard and gamepad input directly through the Windows API.
I use it in my CET trainer, and it’s exposed through REDScript so Lua can detect which keys or buttons are pressed (keyboard and controller).

What it does  
Keyboard: Detects if specific keys are pressed (using Windows VK codes). You can also check which device is active or grab the last pressed key.  
Gamepad: Full support for XInput controllers. You can check buttons, sticks, triggers, and even set controller vibration.  
Mouse: Basic cursor handling. You can show/hide it and check if it’s visible(Show when CET is overlay is closed).  

    
Basically, if you need to use controller input or other inputs that CET don’t handle (like controllers), or if you just need mouse control with the overlay turned off, this is a nice little thing to have. I mainly use it for gamepad controllers because the native in-game action system is messy to deal with - actions overlap with keyboard.

All Windows Virtual-Key codes and XInput button flags are supported. Use their integer values when calling them from Lua - hexadecimal values should work as well.
Links to official lists:  
[Windows Virtual-Key Codes](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)  
[XInput Gamepad Button Flags](https://learn.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad)

## [REDscript Class](EasyInputHandler/RedScript/EasyTrainerInputHandler.reds)
```reds
public native class EasyInputHandler extends IScriptable {
    public native func IsKeyPressed(vkCode: Int32) -> Bool
    public native func IsKeyboardActive() -> Bool
    public native func GetPressedKey() -> Int32

    public native func IsGamepadButtonPressed(buttonCode: Int32) -> Bool
    public native func IsGamepadActive() -> Bool
    public native func GetPressedGamepadButton() -> Int32

    public native func GetGamepadAxis(axisCode: Int32) -> Int32

    public native func ShowCursor(enable: Bool) -> Bool
    public native func IsCursorVisible() -> Bool

    public native func IsLeftStickDirection(direction: String) -> Bool
    public native func IsRightStickDirection(direction: String) -> Bool

    public native func GetLeftTrigger() -> Int32
    public native func GetRightTrigger() -> Int32
    public native func GetLeftTriggerNormalized() -> Float
    public native func GetRightTriggerNormalized() -> Float

    public native func SetGamepadVibration(left: Int32, right: Int32) -> Bool
}
```

## Example of how to use it in Lua within CET
[For example, you can look at the CET script to see how it initializes and works, which should give you a clear idea of how to use it yourself.](EasyTrainerKey/CET/init.lua)

```lua 
-- Initialize handler (lazy singleton style)
local EasyInput = nil
local function GetEasyInput()
    if not EasyInput then
        EasyInput = EasyInputHandler.new()
    end
    return EasyInput
end

-- Example key/gamepad codes
local VK_SPACE = 0x20 -- Spacebar
local VK_ENTER = 0x0D -- Enter
local GP_A = 0x1000 -- Gamepad A button (XInput flag)

-- Example: "Select" action (Enter or Gamepad A)
local function IsSelectPressed()
    local input = GetEasyInput()
    return input:IsKeyPressed(VK_ENTER) or input:IsGamepadButtonPressed(GP_A)
end

-- Example: Toggle cursor with Spacebar or Gamepad A
local cursorVisible = true
local function ToggleCursor()
    local input = GetEasyInput()
    if input:IsKeyPressed(VK_SPACE) or input:IsGamepadButtonPressed(GP_A) then
        cursorVisible = not cursorVisible
        input:ShowCursor(cursorVisible)
    end
end

-- Example usage
registerForEvent("onUpdate", function()
    if IsSelectPressed() then
        print("[EasyInput] Select pressed")
    end
    ToggleCursor()
end)
```
