// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/resource_context.h"

#include "net/url_request/url_request_context.h"
#include "sprocket/browser/net/url_request_context_getter.h"

SprocketResourceContext::SprocketResourceContext()
    : getter_(NULL) {
}

SprocketResourceContext::~SprocketResourceContext() {
}

net::HostResolver*
SprocketResourceContext::GetHostResolver() {
  return getter_->GetURLRequestContext()->host_resolver();
}

net::URLRequestContext*
SprocketResourceContext::GetRequestContext() {
  return getter_->GetURLRequestContext();
}
