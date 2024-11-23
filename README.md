# Window Background Blur

This GDExtension lets you enable background blur on your window on Windows 10 and 11.

![Background blur example](media/background_blur.jpg)

If you wish to see it work on Mac and Linux, see [How to contribute](#how-to-contribute).

## How to use

### Check the demo

The simplest way to test this extension is to open the [demo](demo) folder with Godot. Just launch the game and hit the `blur` button and voilà!

### Use in your project

**Step 1**

Copy the `demo/bin` folder in your project wherever you want, Godot will detect the `.gdextension`. I provide Windows 64 bits debug and release builds. If you need 32 bits, see [How to compile](#how-to-compile).

**Step 2**

In you script, create a `WindowBlur` object and call `set_window_blur`.

```GDScript
# Create a WindowBlur object
var window_blur: WindowBlur = WindowBlur.new()

# Get the window handle as an int, used to identify a window
var hwnd: int = DisplayServer.window_get_native_handle(DisplayServer.WINDOW_HANDLE)

# Set the blur to WindowBlur.ACRYLIC (the best looking one!)
window_blur.set_window_blur(hwnd, WindowBlur.ACRYLIC)

# Reset the blur to AUTO, letting the compositor decide what it should look like.
window_blur.set_window_blur(hwnd, WindowBlur.AUTO)
```

### Windows 11

- **WindowBlur.AUTO**: The default. Let the Desktop Window Manager (DWM) automatically decide the system-drawn backdrop material for this window. This applies the backdrop material just behind the default Win32 title bar. This behavior attempts to preserve maximum backwards compatibility. For this reason, the DWM might also decide to draw no backdrop material at all based on internal heuristics.
- **WindowBlur.NONE**: Don't draw any system backdrop.
- **WindowBlur.MICA**: Draw the backdrop material effect corresponding to a long-lived window behind the entire window bounds.
- **WindowBlur.ACRYLIC**: Draw the backdrop material effect corresponding to a transient window behind the entire window bounds.
- **WindowBlur.MICA_ALT**: Draw the backdrop material effect corresponding to a window with a tabbed title bar behind the entire window bounds.

See the [Windows docs](https://learn.microsoft.com/en-us/windows/win32/api/dwmapi/ne-dwmapi-dwm_systembackdrop_type) for more info.

### Windows 10

Windows 10 doesn't support all these types (to me knowledge), so setting **MICA**, **ACRYLIC** or **MICA_ALT** will enable blur and **AUTO** or **NONE** will remove it.

## How to compile

TODO

## How to contribute

If you want to help implement support for MacOS or Linux please open an issue before starting working on it so we can discuss it!

Comment on issues to let others know you want to work on it. This avoids losing time working on something that's already being worked on. 

Don't hesitate to open issues if you want to report bugs or suggest improvements.

## License

The code is distributed under the MIT license. See [LICENSE](LICENSE).