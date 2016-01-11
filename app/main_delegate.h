// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_APP_MAIN_DELEGATE_H_
#define SPROCKET_APP_MAIN_DELEGATE_H_

#include "content/public/app/content_main_delegate.h"

#include "base/memory/scoped_ptr.h"

class SprocketContentBrowserClient;

class SprocketMainDelegate : public content::ContentMainDelegate {

 public:
  SprocketMainDelegate();
  ~SprocketMainDelegate() override;

 protected:
  bool BasicStartupComplete(int* exit_code) override;
  content::ContentBrowserClient* CreateContentBrowserClient() override;

 private:
  scoped_ptr<SprocketContentBrowserClient> browser_client_;

  DISALLOW_COPY_AND_ASSIGN(SprocketMainDelegate);
};

#endif  // SPROCKET_APP_MAIN_DELEGATE_H_
