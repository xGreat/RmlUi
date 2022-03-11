/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef RMLUI_BACKENDS_PLATFORM_WIN32_H
#define RMLUI_BACKENDS_PLATFORM_WIN32_H

#include "RmlUi_Include_Windows.h"
#include <RmlUi/Core/SystemInterface.h>
#include <RmlUi/Core/Types.h>

namespace Rml {
namespace Input {
	enum KeyIdentifier : unsigned char;
}
} // namespace Rml

class SystemInterface_Win32 : public Rml::SystemInterface {
public:
	/// Get the number of seconds elapsed since the start of the application
	double GetElapsedTime() override;

	/// Set mouse cursor.
	void SetMouseCursor(const Rml::String& cursor_name) override;

	/// Set clipboard text.
	void SetClipboardText(const Rml::String& text) override;

	/// Get clipboard text.
	void GetClipboardText(Rml::String& text) override;
};

namespace RmlWin32 {

bool Initialize();
void Shutdown();

bool InitializeWindow(const char* in_name, unsigned int& inout_width, unsigned int& inout_height, bool allow_resize, HWND& out_window_handle,
	WNDPROC func_window_procedure);
void ShowWindow();
void CloseWindow();

LRESULT WindowProcedure(HWND local_window_handle, UINT message, WPARAM w_param, LPARAM l_param);

float GetDensityIndependentPixelRatio();
void SetContextForInput(Rml::Context* context);

Rml::Input::KeyIdentifier ConvertKey(int win32_key_code);
int GetKeyModifierState();

void DisplayError(const char* fmt, ...);

} // namespace RmlWin32

#endif
