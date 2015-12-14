// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_BROWSER_AURA_VIEWS_DELEGATE_H_
#define SPROCKET_BROWSER_AURA_VIEWS_DELEGATE_H_

#include "ui/views/views_delegate.h"

class SprocketViewsDelegate : public views::ViewsDelegate {

 public:
  SprocketViewsDelegate();
  ~SprocketViewsDelegate() override;

  void OnBeforeWidgetInit(
      views::Widget::InitParams* params,
      views::internal::NativeWidgetDelegate* delegate) override;

  DISALLOW_COPY_AND_ASSIGN(SprocketViewsDelegate);
};

#endif // SPROCKET_BROWSER_AURA_VIEWS_DELEGATE_H_
