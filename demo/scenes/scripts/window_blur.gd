extends Control

@onready var window_blur: WindowBlur = WindowBlur.new()
@onready var blur_toggle: Button = $BlurToggle

# TODO
# -[X] Ability to unblur
# -[] Blur on windaube 10?

func _ready() -> void:
	print("Is transparency avail: ", DisplayServer.is_window_transparency_available())
	get_viewport().transparent_bg = true

func _on_blur_toggle_toggled(toggled_on: bool) -> void:
	toggle_blur(toggled_on)

func toggle_blur(state: bool) -> void:
	var hwnd: int = DisplayServer.window_get_native_handle(DisplayServer.WINDOW_HANDLE)
	print("Window handle: ", hwnd)
	if state:
		blur_toggle.text = "UNBLUR"
		window_blur.set_window_blur(hwnd, WindowBlur.ACRYLIC)
	else:
		blur_toggle.text = "BLUR"
		window_blur.set_window_blur(hwnd, WindowBlur.AUTO)
		pass
	
