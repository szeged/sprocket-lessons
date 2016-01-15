// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_BROWSER_BROWSER_CONTEXT_H_
#define SPROCKET_BROWSER_BROWSER_CONTEXT_H_

#include "content/public/browser/browser_context.h"

#include "base/files/file_util.h"
#include "content/public/browser/content_browser_client.h"

class SprocketResourceContext;
class SprocketURLRequestContextGetter;

class SprocketBrowserContext : public content::BrowserContext {

 public:
  SprocketBrowserContext();
  ~SprocketBrowserContext() override;

  scoped_ptr<content::ZoomLevelDelegate> CreateZoomLevelDelegate(
      const base::FilePath& partition_path) override;
  base::FilePath GetPath() const override;
  bool IsOffTheRecord() const override;
  net::URLRequestContextGetter* GetRequestContext() override;
  net::URLRequestContextGetter* GetRequestContextForRenderProcess(
      int renderer_child_id) override;
  net::URLRequestContextGetter* GetMediaRequestContext() override;
  net::URLRequestContextGetter* GetMediaRequestContextForRenderProcess(
      int renderer_child_id) override;
  net::URLRequestContextGetter*
      GetMediaRequestContextForStoragePartition(
          const base::FilePath& partition_path,
          bool in_memory) override;
  content::ResourceContext* GetResourceContext() override;
  content::DownloadManagerDelegate* GetDownloadManagerDelegate() override;
  content::BrowserPluginGuestManager* GetGuestManager() override;
  storage::SpecialStoragePolicy* GetSpecialStoragePolicy() override;
  content::PushMessagingService* GetPushMessagingService() override;
  content::SSLHostStateDelegate* GetSSLHostStateDelegate() override;
  content::PermissionManager* GetPermissionManager() override;
  net::URLRequestContextGetter* CreateRequestContext(
      content::ProtocolHandlerMap* protocol_handlers);

 private:
  base::FilePath path_;
  scoped_ptr<SprocketResourceContext> resource_context_;
  scoped_refptr<SprocketURLRequestContextGetter> url_request_getter_;

  DISALLOW_COPY_AND_ASSIGN(SprocketBrowserContext);
};

#endif // SPROCKET_BROWSER_BROWSER_CONTEXT_H_
