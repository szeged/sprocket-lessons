// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/window.h"

#include "sprocket/browser/aura/views_delegate.h"
#include "sprocket/browser/aura/widget_delegate_view.h"
#include "ui/aura/env.h"
#include "ui/aura/window.h"
#include "ui/aura/window_tree_host.h"
#include "ui/gfx/screen.h"
#include "ui/views/widget/desktop_aura/desktop_screen.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_delegate.h"

views::ViewsDelegate* SprocketWindow::views_delegate_ = NULL;

// static
void SprocketWindow::PlatformInitialize() {
  gfx::Screen::SetScreenInstance(gfx::SCREEN_TYPE_NATIVE, views::CreateDesktopScreen());
  views_delegate_ = new SprocketViewsDelegate;
}

// static
void SprocketWindow::PlatformExit() {
  delete views_delegate_;
  views_delegate_ = NULL;
  aura::Env::DeleteInstance();
}

void SprocketWindow::PlatformCreateWindow(int width, int height) {
  window_widget_ = new views::Widget;
  views::Widget::InitParams params;
  params.bounds = gfx::Rect(0, 0, width, height);
  delegate_view_ = new SprocketWidgetDelegateView;
  params.delegate = delegate_view_;
  window_widget_->Init(params);

  content_size_ = gfx::Size(width, height);
  window_ = window_widget_->GetNativeWindow();

  window_->GetHost()->Show();
  window_widget_->Show();
}

void SprocketWindow::PlatformSetContents(SprocketWebContentsDelegate* sprocket_web_contents_delegate) {
  sprocket_web_contents_ = sprocket_web_contents_delegate;
  delegate_view_->SetWebContents(sprocket_web_contents_delegate, content_size_);
}