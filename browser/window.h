// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_BROWSER_UI_WINDOW_H_
#define SPROCKET_BROWSER_UI_WINDOW_H_

#include "ui/gfx/geometry/size.h"
#include "ui/gfx/native_widget_types.h"

namespace views {
class Widget;
}

class SprocketWindow {

 public:
  ~SprocketWindow();
  static gfx::Size AdjustWindowSize(const gfx::Size& initial_size);

  static void Initialize();
  static void Deinitialize();
  static SprocketWindow* CreateNewWindow(const gfx::Size& initial_size);

 private:
  static void PlatformInitialize();
  static void PlatformExit();

  void PlatformCreateWindow(int width, int height);

  gfx::NativeWindow window_;
  views::Widget* window_widget_;
};

#endif // SPROCKET_BROWSER_UI_WINDOW_H_
