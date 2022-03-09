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

#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <Shell_Common.h>
#include <Shell_Interface.h>

Rml::Context* context = nullptr;

void GameLoop()
{
	context->Update();

	Shell::BeginFrame();
	context->Render();
	Shell::EndFrame();
}

#if defined RMLUI_PLATFORM_WIN32
	#include <windows.h>
int APIENTRY WinMain(HINSTANCE RMLUI_UNUSED_PARAMETER(instance_handle), HINSTANCE RMLUI_UNUSED_PARAMETER(previous_instance_handle),
	char* RMLUI_UNUSED_PARAMETER(command_line), int RMLUI_UNUSED_PARAMETER(command_show))
#else
int main(int RMLUI_UNUSED_PARAMETER(argc), char** RMLUI_UNUSED_PARAMETER(argv))
#endif
{
#ifdef RMLUI_PLATFORM_WIN32
	RMLUI_UNUSED(instance_handle);
	RMLUI_UNUSED(previous_instance_handle);
	RMLUI_UNUSED(command_line);
	RMLUI_UNUSED(command_show);
#else
	RMLUI_UNUSED(argc);
	RMLUI_UNUSED(argv);
#endif

	int window_width = 1024;
	int window_height = 768;

	// Generic OS initialisation, creates a window and attaches OpenGL.
	if (!Shell::InitializeInterfaces() || !Shell::Initialize() || !Shell::OpenWindow("Load Document Sample", window_width, window_height, true))
	{
		Shell::ShutdownInterfaces();
		return -1;
	}

	Rml::Initialise();

	// Create the main RmlUi context and set it on the shell's input layer.
	context = Rml::CreateContext("main", Rml::Vector2i(window_width, window_height));
	if (!context)
	{
		Rml::Shutdown();
		Shell::CloseWindow();
		Shell::ShutdownInterfaces();
		return -1;
	}

	Rml::Debugger::Initialise(context);
	Shell::SetContext(context);
	Shell::LoadFonts();

	// Load and show the demo document.
	if (Rml::ElementDocument* document = context->LoadDocument("assets/demo.rml"))
		document->Show();

	Shell::EventLoop(GameLoop);

	// Shutdown RmlUi.
	Rml::Shutdown();

	Shell::CloseWindow();
	Shell::ShutdownInterfaces();

	return 0;
}
