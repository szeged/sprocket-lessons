// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/aura/views_delegate.h"

#include "ui/views/widget/desktop_aura/desktop_native_widget_aura.h"

SprocketViewsDelegate::SprocketViewsDelegate() {
}

SprocketViewsDelegate::~SprocketViewsDelegate() {
}

void SprocketViewsDelegate::OnBeforeWidgetInit(
    views::Widget::InitParams* params,
    views::internal::NativeWidgetDelegate* delegate) {
  if (!params->native_widget)
    params->native_widget = new views::DesktopNativeWidgetAura(delegate);
}
