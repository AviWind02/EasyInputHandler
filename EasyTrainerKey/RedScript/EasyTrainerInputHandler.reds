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
