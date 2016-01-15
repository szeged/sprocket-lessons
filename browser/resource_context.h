// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_BROWSER_RESOURCE_CONTEXT_H_
#define SPROCKET_BROWSER_RESOURCE_CONTEXT_H_

#include "content/public/browser/resource_context.h"

namespace net {
class HostResolver;
class URLRequestContext;
}

class SprocketURLRequestContextGetter;

class SprocketResourceContext : public content::ResourceContext {

 public:
  SprocketResourceContext();
  ~SprocketResourceContext() override;

  net::HostResolver* GetHostResolver() override;
  net::URLRequestContext* GetRequestContext() override;

  void set_url_request_context_getter(SprocketURLRequestContextGetter* getter) {
    getter_ = getter;
  }

 private:
  SprocketURLRequestContextGetter* getter_;

  DISALLOW_COPY_AND_ASSIGN(SprocketResourceContext);
};

#endif // SPROCKET_BROWSER_RESOURCE_CONTEXT_H_
