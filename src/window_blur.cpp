#include "window_blur.h"
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <Windows.h>

using namespace godot;

void WindowBlur::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_window_blur", "window_handle", "blur"), &WindowBlur::set_window_blur);
    BIND_ENUM_CONSTANT(AUTO);
    BIND_ENUM_CONSTANT(NONE);
    BIND_ENUM_CONSTANT(MICA);
    BIND_ENUM_CONSTANT(ACRYLIC);
    BIND_ENUM_CONSTANT(MICA_ALT);
}

WindowBlur::WindowBlur() {
}

WindowBlur::~WindowBlur() {
	// Add your cleanup here.
}

/// This method calls DwmEnableBlurBehindWindow() to blur the window
///
/// @param window_handle An integer representing the window handle
void WindowBlur::set_window_blur(int window_handle, WindowBlur::BLUR_TYPE blur) {

    godot::UtilityFunctions::print("Querying windows version");
    OSVERSIONINFOEXW osvi = {0};
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);

    // Get the operating system version information
    VerifyVersionInfoW(&osvi, VER_MAJORVERSION, 10);

    // Check if we're running windows 11
    if (osvi.dwMajorVersion >= 11) {
        godot::UtilityFunctions::print("We run W11");
        HRESULT hr = S_OK;

        HWND hwnd = reinterpret_cast<HWND>(window_handle);

        // Try setting the window attributes 
        // https://learn.microsoft.com/en-us/windows/win32/api/dwmapi/nf-dwmapi-dwmsetwindowattribute
        DWM_SYSTEMBACKDROP_TYPE pef = static_cast<DWM_SYSTEMBACKDROP_TYPE>(blur);
        hr = DwmSetWindowAttribute(hwnd, DWMWA_SYSTEMBACKDROP_TYPE, &pef, sizeof(pef));
        if (SUCCEEDED(hr)){
            godot::UtilityFunctions::print("Blur success!");
        }
        else {
            godot::UtilityFunctions::print("Blur FAILED");
            godot::UtilityFunctions::print("hr: ", hr);
        }
    }
    else {
        godot::UtilityFunctions::print("We run W10");
        HWND hwnd = reinterpret_cast<HWND>(window_handle);

        WINDOWCOMPOSITIONATTRIBDATA pwcad = {0};
        AccentPolicy accent = {0};
        accent.AccentFlags = 0x20 | 0x40 | 0x80 | 0x100;
        accent.AccentState = ACCENT_ENABLE_BLURBEHIND;

        pwcad.Attrib = WCA_ACCENT_POLICY;
        pwcad.pvData = &accent;
        pwcad.cbData = sizeof(accent);

        HMODULE handle = LoadLibraryA("user32.dll");
        FARPROC proc = GetProcAddress(handle, "SetWindowCompositionAttribute");
        SWCA pSWCA = (SWCA) proc;
        if(NULL != pSWCA)
        {
            pSWCA(hwnd, &pwcad);
        }
        FreeLibrary(handle);

    }

    // Construct blurbehind struct to blur the entire area
    // DWM_BLURBEHIND bb = {0};
    // bb.dwFlags = DWM_BB_ENABLE;
    // bb.fEnable = true;
    // bb.hRgnBlur = NULL;

    // Apply the blur -> seems to not work -> only for windows < 8
    // https://learn.microsoft.com/en-us/windows/win32/api/dwmapi/nf-dwmapi-dwmenableblurbehindwindow
    // hr = DwmEnableBlurBehindWindow(hwnd, &bb);
    // if (SUCCEEDED(hr)){
    //     godot::UtilityFunctions::print("Blur success!");
    // }
    // else {
    //     godot::UtilityFunctions::print("Blur FAILED");
    // }

}