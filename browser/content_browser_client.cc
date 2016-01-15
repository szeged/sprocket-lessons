// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/content_browser_client.h"

#include "content/public/common/main_function_params.h"
#include "sprocket/browser/browser_main_parts.h"

content::BrowserMainParts* SprocketContentBrowserClient::CreateBrowserMainParts(
    const content::MainFunctionParams& parameters) {
  browser_main_parts_ = new SprocketBrowserMainParts(parameters);
  return browser_main_parts_;
}

net::URLRequestContextGetter* SprocketContentBrowserClient::CreateRequestContext(
    content::BrowserContext* browser_context,
    content::ProtocolHandlerMap* protocol_handlers,
    content::URLRequestInterceptorScopedVector request_interceptors) {
  return browser_main_parts_->browser_context()->CreateRequestContext(protocol_handlers);
}
