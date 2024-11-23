#ifndef WINDOWBLUR_H
#define WINDOWBLUR_H

#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <dwmapi.h>

// namespace godot {
using namespace godot;

class WindowBlur : public Object {
	GDCLASS(WindowBlur, Object);

private:
    enum AccentState
    {
        ACCENT_DISABLED = 0,
        ACCENT_ENABLE_GRADIENT = 1,
        ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
        ACCENT_ENABLE_BLURBEHIND = 3,
        ACCENT_INVALID_STATE = 4
    };

    typedef struct AccentPolicy
    {
        AccentState AccentState;
        int AccentFlags;
        int GradientColor;
        int AnimationId;
    };

    typedef enum {
        WCA_ACCENT_POLICY = 19,
        WCA_EXCLUDED_FROM_DDA = 24
    } WINDOWCOMPOSITIONATTRIB;

    typedef struct tagWINDOWCOMPOSITIONATTRIBDATA {
        WINDOWCOMPOSITIONATTRIB Attrib;
        void* pvData;
        UINT cbData;
    } WINDOWCOMPOSITIONATTRIBDATA;

    typedef BOOL (WINAPI *SWCA)(HWND hwnd, const WINDOWCOMPOSITIONATTRIBDATA* pwcad);

protected:
	static void _bind_methods();

public:
    enum BLUR_TYPE {
        AUTO = DWMSBT_AUTO,
        NONE = DWMSBT_NONE,
        MICA = DWMSBT_MAINWINDOW,
        ACRYLIC = DWMSBT_TRANSIENTWINDOW,
        MICA_ALT = DWMSBT_TABBEDWINDOW
    };

	WindowBlur();
	~WindowBlur();

    void set_window_blur(int window_handle, WindowBlur::BLUR_TYPE blur);
};

// }

VARIANT_ENUM_CAST(WindowBlur::BLUR_TYPE);

#endif