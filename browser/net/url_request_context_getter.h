// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_BROWSER_NET_URL_REQUEST_CONTEXT_GETTER_H_
#define SPROCKET_BROWSER_NET_URL_REQUEST_CONTEXT_GETTER_H_

#include "net/url_request/url_request_context_getter.h"

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/content_browser_client.h"

namespace net {
class NetworkDelegate;
class ProxyConfigService;
class URLRequestContext;
class URLRequestContextStorage;
class URLRequestJobFactoryImpl;
}

class SprocketURLRequestContextGetter : public net::URLRequestContextGetter {

 public:
  SprocketURLRequestContextGetter(
      const base::FilePath& base_path,
      content::ProtocolHandlerMap* protocol_handlers);
  net::URLRequestContext* GetURLRequestContext() override;
  scoped_refptr<base::SingleThreadTaskRunner> GetNetworkTaskRunner()
      const override;

 protected:
  ~SprocketURLRequestContextGetter() override;

 private:
  base::FilePath base_path_;
  content::ProtocolHandlerMap protocol_handlers_;

  scoped_ptr<net::ProxyConfigService> proxy_config_service_;
  scoped_ptr<net::NetworkDelegate> network_delegate_;
  scoped_ptr<net::URLRequestContext> url_request_context_;
  scoped_ptr<net::URLRequestContextStorage> storage_;
  scoped_ptr<net::URLRequestJobFactoryImpl> job_factory_;

  DISALLOW_COPY_AND_ASSIGN(SprocketURLRequestContextGetter);
};

#endif // SPROCKET_BROWSER_NET_URL_REQUEST_CONTEXT_GETTER_H_
