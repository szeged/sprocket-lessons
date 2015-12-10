// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/public/app/content_main.h"

int main(int argc, const char** argv) {

  content::ContentMainParams params(NULL);
  params.argc = argc;
  params.argv = argv;

  return content::ContentMain(params);
}
