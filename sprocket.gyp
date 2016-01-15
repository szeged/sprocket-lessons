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
      'defines': ['SPROCKET_VERSION="<(sprocket_version)"'],
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
        '<(DEPTH)/ui/views/controls/webview/webview.gyp:webview',
        '<(DEPTH)/ui/views/views.gyp:views',
        'sprocket_pak',
      ],
      'sources': [
        'app/main_delegate.cc',
        'app/main_delegate.h',
        'browser/aura/views_delegate.cc',
        'browser/aura/views_delegate.h',
        'browser/aura/widget_delegate_view.cc',
        'browser/aura/widget_delegate_view.h',
        'browser/aura/window_aura.cc',
        'browser/browser_context.cc',
        'browser/browser_context.h',
        'browser/browser_main_parts.cc',
        'browser/browser_main_parts.h',
        'browser/content_browser_client.cc',
        'browser/content_browser_client.h',
        'browser/net/url_request_context_getter.cc',
        'browser/net/url_request_context_getter.h',
        'browser/resource_context.cc',
        'browser/resource_context.h',
        'browser/web_contents_delegate.cc',
        'browser/web_contents_delegate.h',
        'browser/window.cc',
        'browser/window.h',
        'common/content_client.cc',
        'common/content_client.h'
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
    },
    {
      'target_name': 'sprocket_pak',
      'type': 'none',
      'dependencies': [
        '<(DEPTH)/content/app/resources/content_resources.gyp:content_resources',
        '<(DEPTH)/content/app/strings/content_strings.gyp:content_strings',
        '<(DEPTH)/net/net.gyp:net_resources',
      ],
      'actions': [
        {
          'action_name': 'repack_sprocket_pack',
          'variables': {
          'pak_inputs': [
            '<(SHARED_INTERMEDIATE_DIR)/blink/public/resources/blink_resources.pak',
            '<(SHARED_INTERMEDIATE_DIR)/blink/public/resources/blink_image_resources_100_percent.pak',
            '<(SHARED_INTERMEDIATE_DIR)/content/app/resources/content_resources_100_percent.pak',
            '<(SHARED_INTERMEDIATE_DIR)/content/content_resources.pak',
            '<(SHARED_INTERMEDIATE_DIR)/net/net_resources.pak',
            '<(SHARED_INTERMEDIATE_DIR)/ui/resources/ui_resources_100_percent.pak',
            '<(SHARED_INTERMEDIATE_DIR)/ui/resources/webui_resources.pak',
            '<(SHARED_INTERMEDIATE_DIR)/ui/strings/app_locale_settings_en-US.pak',
            '<(SHARED_INTERMEDIATE_DIR)/ui/strings/ui_strings_en-US.pak',
          ],
            'pak_output': '<(PRODUCT_DIR)/sprocket.pak',
          },
          'includes': [ '../build/repack_action.gypi' ],
        },
      ],
    }]
}
