// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/aura/widget_delegate_view.h"

#include "ui/views/controls/webview/webview.h"
#include "ui/views/background.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/views/widget/widget.h"
#include "sprocket/browser/web_contents_delegate.h"
#include "sprocket/browser/window.h"

SprocketWidgetDelegateView::SprocketWidgetDelegateView()
    : sprocket_web_contents_(NULL),
      contents_view_(new views::View) {
}

SprocketWidgetDelegateView::~SprocketWidgetDelegateView() {
}

void SprocketWidgetDelegateView::SetWebContents(SprocketWebContentsDelegate* sprocket_web_contents_delegate,
    const gfx::Size& size) {
  sprocket_web_contents_ = sprocket_web_contents_delegate;

  contents_view_->SetLayoutManager(new views::FillLayout());

  content::WebContents* web_contents = sprocket_web_contents_delegate->web_contents();
  web_view_ = new views::WebView(web_contents->GetBrowserContext());
  web_view_->SetWebContents(web_contents);
  web_view_->SetPreferredSize(size);
  web_contents->Focus();

  contents_view_->AddChildView(web_view_);
  Layout();

  // Resize the widget, keeping the same origin.
  gfx::Rect bounds = GetWidget()->GetWindowBoundsInScreen();
  bounds.set_size(GetWidget()->GetRootView()->GetPreferredSize());
  GetWidget()->SetBounds(bounds);
}

void SprocketWidgetDelegateView::InitSprocketWindow() {
  set_background(views::Background::CreateStandardPanelBackground());

  views::FillLayout* layout = new views::FillLayout();
  SetLayoutManager(layout);

  AddChildView(contents_view_);
}

void SprocketWidgetDelegateView::WindowClosing() {
  delete sprocket_web_contents_->window();
}

views::View* SprocketWidgetDelegateView::GetContentsView() {
  return this;
}

void SprocketWidgetDelegateView::ViewHierarchyChanged(
    const ViewHierarchyChangedDetails& details) {
  if (details.is_add && details.child == this) {
    InitSprocketWindow();
  }
}
