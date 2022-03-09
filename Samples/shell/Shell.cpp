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

#include "Shell.h"
#include "PlatformExtensions.h"
#include "ShellFileInterface.h"
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/Profiling.h>
#include <RmlUi_Backend.h>

static Rml::UniquePtr<ShellFileInterface> file_interface;

bool Shell::Initialize()
{
	Rml::String root = PlatformExtensions::FindSamplesRoot();
	if (root.empty())
		return false;

	file_interface = Rml::MakeUnique<ShellFileInterface>(root);
	Rml::SetFileInterface(file_interface.get());

	if (!Backend::InitializeInterfaces())
		return false;

	return true;
}

void Shell::Shutdown()
{
	Backend::ShutdownInterfaces();
	file_interface.reset();
}

bool Shell::OpenWindow(const char* in_name, unsigned int width, unsigned int height, bool allow_resize)
{
	return Backend::OpenWindow(in_name, width, height, allow_resize);
}

void Shell::CloseWindow()
{
	return Backend::CloseWindow();
}

void Shell::LoadFonts()
{
	Rml::String directory = "assets/";

	struct FontFace {
		const char* filename;
		bool fallback_face;
	};
	FontFace font_faces[] = {
		{"LatoLatin-Regular.ttf", false},
		{"LatoLatin-Italic.ttf", false},
		{"LatoLatin-Bold.ttf", false},
		{"LatoLatin-BoldItalic.ttf", false},
		{"NotoEmoji-Regular.ttf", true},
	};

	for (const FontFace& face : font_faces)
	{
		Rml::LoadFontFace(directory + face.filename, face.fallback_face);
	}
}

void Shell::SetContext(Rml::Context* context)
{
	Backend::SetContext(context);
}

void Shell::EventLoop(ShellIdleFunction idle_function)
{
	Backend::EventLoop(idle_function);
}

void Shell::RequestExit()
{
	Backend::RequestExit();
}

void Shell::FrameBegin()
{
	Backend::FrameBegin();
}

void Shell::FramePresent()
{
	Backend::FramePresent();
	RMLUI_FrameMark;
}
