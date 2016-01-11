// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_BROWSER_BROWSER_MAIN_PARTS_H_
#define SPROCKET_BROWSER_BROWSER_MAIN_PARTS_H_

#include "content/public/browser/browser_main_parts.h"

#include "content/public/common/main_function_params.h"

class SprocketBrowserMainParts : public content::BrowserMainParts {

 public:
  explicit SprocketBrowserMainParts(
      const content::MainFunctionParams& parameters);
  ~SprocketBrowserMainParts() override;

  void PreEarlyInitialization() override;
  void PreMainMessageLoopRun() override;
  void PostMainMessageLoopRun() override;

  DISALLOW_COPY_AND_ASSIGN(SprocketBrowserMainParts);
};

#endif // SPROCKET_BROWSER_BROWSER_MAIN_PARTS_H_
