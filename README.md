# EasyTrainer Input Handler

A small RED4ext plugin that checks keyboard and gamepad input directly through the Windows API.  
It’s used in my CET trainer and accessed through REDScript, allowing the trainer to detect which keys or buttons are pressed, including controllers.

All Windows Virtual-Key codes and XInput button flags are supported. Use their integer values when calling them from Lua - hexadecimal values should work as well.
Links to official lists:  
[Windows Virtual-Key Codes](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)  
[XInput Gamepad Button Flags](https://learn.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad)

## [REDscript Class](EasyTrainerKey/RedScript/EasyTrainerInputHandler.reds)
```reds
public native class EasyTrainerInputHandler extends IScriptable {  
    public native func IsKeyPressed(vkCode: Int32) -> Bool  
    public native func IsGamepadButtonPressed(buttonCode: Int32) -> Bool  
    public native func IsKeyboardActive() -> Bool  
    public native func IsGamepadActive() -> Bool  
    public native func GetPressedKey(index: Int32) -> Int32  
    public native func GetPressedGamepadButton(index: Int32) -> Bool  
}
```

## [Example of how to use it in Lua within CET](https://github.com/AviWind02/EasyTrainers/blob/main/UI/Gamepad/InputHandler.lua)
```lua 
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
```
