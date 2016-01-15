// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_BROWSER_AURA_WIDGET_DELEGATE_VIEW_H_
#define SPROCKET_BROWSER_AURA_WIDGET_DELEGATE_VIEW_H_

#include "ui/views/widget/widget_delegate.h"

namespace views {
class View;
class WebView;
}

class SprocketWebContentsDelegate;

class SprocketWidgetDelegateView : public views::WidgetDelegateView {

 public:
  SprocketWidgetDelegateView();
  ~SprocketWidgetDelegateView() override;

  void SetWebContents(SprocketWebContentsDelegate* sprocket_web_contents_delegate,
                      const gfx::Size& size);

 private:
  void WindowClosing() override;
  View* GetContentsView() override;
  void ViewHierarchyChanged( const ViewHierarchyChangedDetails& details) override;

  void InitSprocketWindow();

  SprocketWebContentsDelegate* sprocket_web_contents_;
  views::View* contents_view_;
  views::WebView* web_view_;

  DISALLOW_COPY_AND_ASSIGN(SprocketWidgetDelegateView);
};

#endif // SPROCKET_BROWSER_AURA_WIDGET_DELEGATE_VIEW_H_
