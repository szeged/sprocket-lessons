// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_BROWSER_WEB_CONTENTS_H_
#define SPROCKET_BROWSER_WEB_CONTENTS_H_

#include "content/public/browser/web_contents_delegate.h"

#include "content/public/browser/web_contents.h"

class SprocketWindow;

class SprocketWebContentsDelegate : public content::WebContentsDelegate {

 public:
  ~SprocketWebContentsDelegate() override;

  static SprocketWebContentsDelegate* CreateSprocketWebContentsDelegate(
      SprocketWindow* window,
      content::BrowserContext* browser_context,
      const GURL& url,
      const gfx::Size& initial_size);
  static SprocketWebContentsDelegate* AdoptWebContents(
      SprocketWindow* window,
      content::WebContents* web_contents);
  void AddNewContents(content::WebContents* source,
                      content::WebContents* new_contents,
                      WindowOpenDisposition disposition,
                      const gfx::Rect& initial_rect,
                      bool user_gesture,
                      bool* was_blocked) override;
  void LoadURL(const GURL& url);

  content::WebContents* web_contents() const { return web_contents_.get(); }
  SprocketWindow* window() { return window_; }

 private:
  explicit SprocketWebContentsDelegate(SprocketWindow* window,
                               content::WebContents* web_contents);

  scoped_ptr<content::WebContents> web_contents_;
  SprocketWindow* window_;

  DISALLOW_COPY_AND_ASSIGN(SprocketWebContentsDelegate);
};

#endif // SPROCKET_BROWSER_UI_WEB_CONTENTS_H_