// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/browser_context.h"

#include "base/nix/xdg_util.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/storage_partition.h"
#include "sprocket/browser/resource_context.h"
#include "sprocket/browser/net/url_request_context_getter.h"

SprocketBrowserContext::SprocketBrowserContext()
    : resource_context_(new SprocketResourceContext) {
  scoped_ptr<base::Environment> env(base::Environment::Create());
  base::FilePath config_dir(
      base::nix::GetXDGDirectory(env.get(),
                                 base::nix::kXdgConfigHomeEnvVar,
                                 base::nix::kDotConfigDir));
  path_ = config_dir.Append("sprocket");

  if (!base::PathExists(path_))
    base::CreateDirectory(path_);
}

SprocketBrowserContext::~SprocketBrowserContext() {
  if (resource_context_) {
    content::BrowserThread::DeleteSoon(
        content::BrowserThread::IO, FROM_HERE, resource_context_.release());
  }
}

scoped_ptr<content::ZoomLevelDelegate> SprocketBrowserContext::CreateZoomLevelDelegate(
    const base::FilePath& partition_path) {
  return NULL;
}

base::FilePath SprocketBrowserContext::GetPath() const {
  return path_;
}

bool SprocketBrowserContext::IsOffTheRecord() const {
  return false;
}

net::URLRequestContextGetter*
SprocketBrowserContext::GetRequestContext() {
  return GetDefaultStoragePartition(this)->GetURLRequestContext();
}

net::URLRequestContextGetter*
SprocketBrowserContext::GetRequestContextForRenderProcess(
    int renderer_child_id) {
  return GetRequestContext();
 }

net::URLRequestContextGetter*
SprocketBrowserContext::GetMediaRequestContext() {
  return GetRequestContext();
}

net::URLRequestContextGetter*
SprocketBrowserContext::GetMediaRequestContextForRenderProcess(
    int renderer_child_id) {
  return GetRequestContext();
}

net::URLRequestContextGetter*
SprocketBrowserContext::GetMediaRequestContextForStoragePartition(
    const base::FilePath& partition_path,
    bool in_memory) {
  return GetRequestContext();
}

content::ResourceContext*
SprocketBrowserContext::GetResourceContext() {
  return resource_context_.get();
}

content::DownloadManagerDelegate*
SprocketBrowserContext::GetDownloadManagerDelegate() {
  return NULL;
}

content::BrowserPluginGuestManager*
SprocketBrowserContext::GetGuestManager() {
  return NULL;
}

storage::SpecialStoragePolicy*
SprocketBrowserContext::GetSpecialStoragePolicy() {
  return NULL;
}

content::PushMessagingService*
SprocketBrowserContext::GetPushMessagingService() {
  return NULL;
}

content::SSLHostStateDelegate*
SprocketBrowserContext::GetSSLHostStateDelegate() {
  return NULL;
}

content::PermissionManager*
SprocketBrowserContext::GetPermissionManager() {
  return NULL;
}

net::URLRequestContextGetter*
SprocketBrowserContext::CreateRequestContext(
    content::ProtocolHandlerMap* protocol_handlers) {
  url_request_getter_ = new SprocketURLRequestContextGetter(
      GetPath(),
      protocol_handlers);
  resource_context_->set_url_request_context_getter(url_request_getter_.get());
  return url_request_getter_.get();
}
