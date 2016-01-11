// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/browser_main_parts.h"

#include "sprocket/browser/window.h"
#include "ui/base/ime/input_method_initializer.h"

SprocketBrowserMainParts::SprocketBrowserMainParts(
    const content::MainFunctionParams& parameters) {
}

SprocketBrowserMainParts::~SprocketBrowserMainParts() {
}

void SprocketBrowserMainParts::PreEarlyInitialization() {
  ui::InitializeInputMethodForTesting();
}

void SprocketBrowserMainParts::PreMainMessageLoopRun() {
  SprocketWindow::Initialize();

  SprocketWindow::CreateNewWindow(gfx::Size());
}

void SprocketBrowserMainParts::PostMainMessageLoopRun() {
  SprocketWindow::Deinitialize();
}