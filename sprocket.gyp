# Copyright (c) 2015 University of Szeged.
# Copyright (c) 2015 The Chromium Authors.
# All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
{
  'variables': {
    'pkg-config': 'pkg-config',
    'chromium_code': 1,
    'sprocket_version': '0.1.0.0',
  },
  'targets': [
    {
      'target_name': 'sprocket_lib',
      'type': 'static_library',
      'dependencies': [
        # Content dependencies
        '<(DEPTH)/content/content.gyp:content_app_both',
        '<(DEPTH)/content/content.gyp:content_common',
        '<(DEPTH)/content/content.gyp:content_gpu',
        '<(DEPTH)/content/content.gyp:content_plugin',
        '<(DEPTH)/content/content.gyp:content_ppapi_plugin',
        '<(DEPTH)/content/content.gyp:content_renderer',
        '<(DEPTH)/content/content.gyp:content_resources',
        '<(DEPTH)/content/content.gyp:content_utility',
        '<(DEPTH)/content/content.gyp:content_browser',
        '<(DEPTH)/ui/views/views.gyp:views',
      ],
      'sources': [
        'browser/aura/views_delegate.cc',
        'browser/aura/views_delegate.h',
        'browser/aura/window_aura.cc',
        'browser/window.cc',
        'browser/window.h',
      ],
    },
    {
      'target_name': 'sprocket',
      'type': 'executable',
      'dependencies': [
        'sprocket_lib',
      ],
      'sources': [
        'app/main.cc',
      ],
    }]
}
