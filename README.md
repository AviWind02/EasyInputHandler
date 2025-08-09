# EasyTrainer Input Handler

A small RED4ext plugin that allows **keyboard and gamepad input checks** from REDscript or CET Lua.  
Created for *EasyTrainer* because CET input didn’t support controllers and native input wasn’t reliable.

## Included Files
- `bin/x64/plugins/EasyTrainerInputHandler.dll` – compiled plugin  
- `r6/scripts/EasyTrainerInputHandler.reds` – native class wrapper for REDscript
- 
[Uploading EasyTrainerInputHandler.reds…]()

If you don’t want to build it yourself, just drop both files in the correct folders.

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
