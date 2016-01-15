// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/web_contents_delegate.h"

#include "sprocket/browser/window.h"

// static
SprocketWebContentsDelegate* SprocketWebContentsDelegate::CreateSprocketWebContentsDelegate(
    SprocketWindow* window,
    content::BrowserContext* browser_context,
    const GURL& url,
    const gfx::Size& initial_size) {
  content::WebContents::CreateParams create_params(browser_context);
  const gfx::Size& size = SprocketWindow::AdjustWindowSize(initial_size);
  create_params.initial_size = size;
  content::WebContents* web_contents = content::WebContents::Create(create_params);

  SprocketWebContentsDelegate* sprocket_web_contents_delegate = new SprocketWebContentsDelegate(window, web_contents);

  return sprocket_web_contents_delegate;
}

SprocketWebContentsDelegate::SprocketWebContentsDelegate(SprocketWindow* window,
                                         content::WebContents* web_contents)
    : window_(window) {
  web_contents_.reset(web_contents);
  web_contents->SetDelegate(this);
}

SprocketWebContentsDelegate::~SprocketWebContentsDelegate() {
}
