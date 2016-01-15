// Copyright (c) 2015 University of Szeged.
// Copyright (c) 2015 The Chromium Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sprocket/browser/net/network_delegate.h"

SprocketNetworkDelegate::SprocketNetworkDelegate() {
}

SprocketNetworkDelegate::~SprocketNetworkDelegate() {
}

bool SprocketNetworkDelegate::OnCanAccessFile(
    const net::URLRequest& request,
    const base::FilePath& path) const {
  return true;
}
