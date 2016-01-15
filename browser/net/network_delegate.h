// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SPROCKET_BROWSER_NET_NETWORK_DELEGATE_H_
#define SPROCKET_BROWSER_NET_NETWORK_DELEGATE_H_

#include "net/base/network_delegate_impl.h"

class SprocketNetworkDelegate : public net::NetworkDelegateImpl {

 public:
  SprocketNetworkDelegate();
  ~SprocketNetworkDelegate() override;

 private:
  bool OnCanAccessFile(const net::URLRequest& request,
                       const base::FilePath& path) const override;

  DISALLOW_COPY_AND_ASSIGN(SprocketNetworkDelegate);
};

#endif // SPROCKET_BROWSER_NET_NETWORK_DELEGATE_H_
