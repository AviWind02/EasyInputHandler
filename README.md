# EasyTrainer Input Handler

A small RED4ext plugin that allows **keyboard and gamepad input checks** from REDscript or CET Lua.  
Created for *EasyTrainer* because CET input didn’t support controllers and native input wasn’t reliable.

## REDscript Class
```reds
public native class EasyTrainerInputHandler extends IScriptable {
    public native func IsKeyPressed(vkCode: Int32) -> Bool
    public native func IsGamepadButtonPressed(buttonCode: Int32) -> Bool
    public native func IsKeyboardActive() -> Bool
    public native func IsGamepadActive() -> Bool
    public native func GetPressedKey(index: Int32) -> Int32
    public native func GetPressedGamepadButton(index: Int32) -> Bool
}

[Windows Virtual-Key Codes](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)
[XInput Gamepad Button Flags](https://learn.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad)

-- Initialize handler
local ETInput = nil
local function GetETInput()
    if not ETInput then
        ETInput = EasyTrainerInputHandler.new()
    end
    return ETInput
end

-- Example virtual-key and gamepad codes
local VK_ENTER = 13
local GP_A = 4096

-- Example: "Select" button (Enter or Gamepad A)
local function Select()
    return GetETInput():IsKeyPressed(VK_ENTER) or GetETInput():IsGamepadButtonPressed(GP_A)
end
