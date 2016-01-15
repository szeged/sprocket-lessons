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
  if (!url.is_empty())
    sprocket_web_contents_delegate->LoadURL(url);

  return sprocket_web_contents_delegate;
}

// static
SprocketWebContentsDelegate* SprocketWebContentsDelegate::AdoptWebContents(
    SprocketWindow* window,
    content::WebContents* web_contents) {
  return new SprocketWebContentsDelegate(window, web_contents);
}

SprocketWebContentsDelegate::SprocketWebContentsDelegate(SprocketWindow* window,
                                         content::WebContents* web_contents)
    : window_(window) {
  web_contents_.reset(web_contents);
  window->PlatformSetContents(this);
  web_contents->SetDelegate(this);
}

SprocketWebContentsDelegate::~SprocketWebContentsDelegate() {
}

void SprocketWebContentsDelegate::AddNewContents(content::WebContents* source,
                                         content::WebContents* new_contents,
                                         WindowOpenDisposition disposition,
                                         const gfx::Rect& initial_rect,
                                         bool user_gesture,
                                         bool* was_blocked) {
  SprocketWindow* window = SprocketWindow::CreateNewWindow(gfx::Size(initial_rect.size()));
  AdoptWebContents(window, new_contents);
}

void SprocketWebContentsDelegate::LoadURL(const GURL& url) {
  content::NavigationController::LoadURLParams params(url);
  params.transition_type = ui::PageTransitionFromInt(
      ui::PAGE_TRANSITION_TYPED | ui::PAGE_TRANSITION_FROM_ADDRESS_BAR);
  web_contents_->GetController().LoadURLWithParams(params);
  web_contents_->Focus();
}
