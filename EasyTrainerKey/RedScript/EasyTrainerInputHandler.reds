public native class EasyTrainerInputHandler extends IScriptable {
    public native func IsKeyPressed(vkCode: Int32) -> Bool
    public native func IsGamepadButtonPressed(buttonCode: Int32) -> Bool
    public native func IsKeyboardActive() -> Bool
    public native func IsGamepadActive() -> Bool
    public native func GetPressedKey(index: Int32) -> Int32
    public native func GetPressedGamepadButton(index: Int32) -> Bool
}
