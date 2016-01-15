// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/app/main_delegate.h"

#include "base/path_service.h"
#include "sprocket/browser/content_browser_client.h"
#include "ui/base/resource/resource_bundle.h"

SprocketMainDelegate::SprocketMainDelegate() {
}

SprocketMainDelegate::~SprocketMainDelegate() {
}

bool SprocketMainDelegate::BasicStartupComplete(int* exit_code) {
  base::FilePath pak_file;
  PathService::Get(base::DIR_MODULE, &pak_file);
  pak_file = pak_file.Append(FILE_PATH_LITERAL("sprocket.pak"));
  ui::ResourceBundle::InitSharedInstanceWithPakPath(pak_file);

  return false;
}

content::ContentBrowserClient* SprocketMainDelegate::CreateContentBrowserClient() {
  browser_client_.reset(new SprocketContentBrowserClient);
  return browser_client_.get();
}
