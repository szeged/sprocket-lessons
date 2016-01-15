// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/browser_main_parts.h"

#include "sprocket/browser/window.h"
#include "sprocket/browser/web_contents_delegate.h"
#include "net/base/filename_util.h"
#include "ui/base/ime/input_method_initializer.h"

namespace {

GURL GetStartupURL() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  const base::CommandLine::StringVector& args = command_line->GetArgs();

  if (args.empty())
    return GURL("https://www.google.com/");

  GURL url(args[0]);
  if (url.is_valid() && url.has_scheme())
    return url;

  return net::FilePathToFileURL(base::FilePath(args[0]));
}

}

SprocketBrowserMainParts::SprocketBrowserMainParts(
    const content::MainFunctionParams& parameters) {
}

SprocketBrowserMainParts::~SprocketBrowserMainParts() {
}

void SprocketBrowserMainParts::PreEarlyInitialization() {
  ui::InitializeInputMethodForTesting();
}

void SprocketBrowserMainParts::PreMainMessageLoopRun() {
  set_browser_context(new SprocketBrowserContext());

  SprocketWindow::Initialize();

  SprocketWindow* window = SprocketWindow::CreateNewWindow(gfx::Size());
  SprocketWebContentsDelegate::CreateSprocketWebContentsDelegate(window,
                                                 browser_context(),
                                                 GetStartupURL(),
                                                 gfx::Size());
}

void SprocketBrowserMainParts::PostMainMessageLoopRun() {
  SprocketWindow::Deinitialize();
  browser_context_.reset();
}
