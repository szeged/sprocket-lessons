// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_BROWSER_CONTENT_BROWSER_CLIENT_H_
#define SPROCKET_BROWSER_CONTENT_BROWSER_CLIENT_H_

#include "content/public/browser/content_browser_client.h"

class SprocketBrowserMainParts;

class SprocketContentBrowserClient : public content::ContentBrowserClient {

 public:
  content::BrowserMainParts* CreateBrowserMainParts(
      const content::MainFunctionParams& parameters) override;

 private:
  SprocketBrowserMainParts* browser_main_parts_;
};

#endif  // SPROCKET_BROWSER_CONTENT_BROWSER_CLIENT_H_
