// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/window.h"

#include "base/message_loop/message_loop.h"
#include "sprocket/browser/web_contents_delegate.h"

const int kDefaultWindowWidth = 800;
const int kDefaultWindowHeight = 600;

// static
gfx::Size SprocketWindow::AdjustWindowSize(const gfx::Size& initial_size) {
  if (!initial_size.IsEmpty())
    return initial_size;

  static gfx::Size default_window_size = gfx::Size(
      kDefaultWindowWidth, kDefaultWindowHeight);

  return default_window_size;
}

// static
void SprocketWindow::Initialize() {
  PlatformInitialize();
}

// static
void SprocketWindow::Deinitialize() {
  PlatformExit();
}

// static
SprocketWindow* SprocketWindow::CreateNewWindow(const gfx::Size& initial_size) {
  SprocketWindow* window = new SprocketWindow;

  const gfx::Size& size = SprocketWindow::AdjustWindowSize(initial_size);
  window->PlatformCreateWindow(size.width(), size.height());

  return window;
}

SprocketWindow::~SprocketWindow() {
  delete sprocket_web_contents_;

  base::MessageLoop::current()->PostTask(FROM_HERE, base::MessageLoop::QuitClosure());
}
