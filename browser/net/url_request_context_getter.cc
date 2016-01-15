// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/net/url_request_context_getter.h"

#include "base/threading/worker_pool.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/cookie_store_factory.h"
#include "net/base/network_delegate_impl.h"
#include "net/cert/cert_verifier.h"
#include "net/http/http_auth_handler_factory.h"
#include "net/http/http_cache.h"
#include "net/http/http_server_properties_impl.h"
#include "net/proxy/proxy_service.h"
#include "net/ssl/channel_id_service.h"
#include "net/ssl/default_channel_id_store.h"
#include "net/ssl/ssl_config_service_defaults.h"
#include "net/url_request/data_protocol_handler.h"
#include "net/url_request/file_protocol_handler.h"
#include "net/url_request/static_http_user_agent_settings.h"
#include "net/url_request/url_request_context.h"
#include "net/url_request/url_request_context_storage.h"
#include "net/url_request/url_request_job_factory_impl.h"
#include "sprocket/common/content_client.h"

SprocketURLRequestContextGetter::SprocketURLRequestContextGetter(
    const base::FilePath& base_path,
    content::ProtocolHandlerMap* protocol_handlers)
    : base_path_(base_path) {
  std::swap(protocol_handlers_, *protocol_handlers);

  proxy_config_service_ =
      net::ProxyService::CreateSystemProxyConfigService(
          content::BrowserThread::UnsafeGetMessageLoopForThread(content::BrowserThread::IO)->task_runner(),
          content::BrowserThread::UnsafeGetMessageLoopForThread(content::BrowserThread::FILE)->task_runner());
}

SprocketURLRequestContextGetter::~SprocketURLRequestContextGetter() {
}

net::URLRequestContext* SprocketURLRequestContextGetter::GetURLRequestContext() {
  if (!url_request_context_) {
    url_request_context_.reset(new net::URLRequestContext());
    network_delegate_.reset(new net::NetworkDelegateImpl);
    url_request_context_->set_network_delegate(network_delegate_.get());

    // Generate Storage
    storage_.reset(new net::URLRequestContextStorage(url_request_context_.get()));

    storage_->set_channel_id_service(make_scoped_ptr(new net::ChannelIDService(
        new net::DefaultChannelIDStore(NULL),
        base::WorkerPool::GetTaskRunner(true))));

    storage_->set_cert_verifier(net::CertVerifier::CreateDefault());
    storage_->set_proxy_service(net::ProxyService::CreateUsingSystemProxyResolver(proxy_config_service_.Pass(), 0, NULL));
    storage_->set_ssl_config_service(new net::SSLConfigServiceDefaults);
    storage_->set_transport_security_state(make_scoped_ptr(new net::TransportSecurityState));

    scoped_ptr<net::HostResolver> host_resolver(net::HostResolver::CreateDefaultResolver(NULL));

    storage_->set_http_auth_handler_factory( net::HttpAuthHandlerFactory::CreateDefault(host_resolver.get()));
    storage_->set_http_server_properties(scoped_ptr<net::HttpServerProperties>(new net::HttpServerPropertiesImpl()));

    storage_->set_host_resolver(host_resolver.Pass());

    // Generate Cookie Store
    storage_->set_cookie_store(content::CreateCookieStore(content::CookieStoreConfig()));

    // Setting HTTP user agent
    storage_->set_http_user_agent_settings(make_scoped_ptr(
        new net::StaticHttpUserAgentSettings(
        "en-us,en", GetSprocketUserAgent())));

    // Cache settings
    base::FilePath cache_path = base_path_.Append(FILE_PATH_LITERAL("Cache"));
    net::HttpCache::DefaultBackend* main_backend =
        new net::HttpCache::DefaultBackend(
            net::DISK_CACHE,
            net::CACHE_BACKEND_DEFAULT,
            cache_path,
            0,    // If |max_bytes| is  zero, a default value will be calculated automatically.
            content::BrowserThread::GetMessageLoopProxyForThread(content::BrowserThread::CACHE));

    net::HttpNetworkSession::Params network_session_params;
    network_session_params.cert_verifier             = url_request_context_->cert_verifier();
    network_session_params.transport_security_state  = url_request_context_->transport_security_state();
    network_session_params.channel_id_service        = url_request_context_->channel_id_service();
    network_session_params.proxy_service             = url_request_context_->proxy_service();
    network_session_params.ssl_config_service        = url_request_context_->ssl_config_service();
    network_session_params.http_auth_handler_factory = url_request_context_->http_auth_handler_factory();
    network_session_params.network_delegate          = network_delegate_.get();
    network_session_params.http_server_properties    = url_request_context_->http_server_properties();
    network_session_params.ignore_certificate_errors = true;
    network_session_params.host_resolver             = url_request_context_->host_resolver();

    storage_->set_http_transaction_factory(make_scoped_ptr(new net::HttpCache(network_session_params, main_backend)));

    job_factory_.reset(new net::URLRequestJobFactoryImpl());

    for (auto it = protocol_handlers_.begin(); it != protocol_handlers_.end(); ++it) {
      job_factory_->SetProtocolHandler(it->first, make_scoped_ptr(it->second.release()));
    }
    protocol_handlers_.clear();

    job_factory_->SetProtocolHandler(url::kDataScheme, make_scoped_ptr(new net::DataProtocolHandler));
    job_factory_->SetProtocolHandler(url::kFileScheme, make_scoped_ptr(new net::FileProtocolHandler(
        content::BrowserThread::GetBlockingPool()->GetTaskRunnerWithShutdownBehavior(
            base::SequencedWorkerPool::SKIP_ON_SHUTDOWN))));

    storage_->set_job_factory(job_factory_.Pass());
  }

  return url_request_context_.get();
}

scoped_refptr<base::SingleThreadTaskRunner> SprocketURLRequestContextGetter::GetNetworkTaskRunner() const {
  return content::BrowserThread::GetMessageLoopProxyForThread(content::BrowserThread::IO);
}
