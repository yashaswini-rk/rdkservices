/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2022 Sky UK
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef CONTROLSETTINGS_H
#define CONTROLSETTINGS_H

#include <string>
#include "libIARM.h"
#include "libIBusDaemon.h"
#include "libIBus.h"
#include "iarmUtil.h"

#include "dsError.h"
#include "dsMgr.h"
#include "hdmiIn.hpp"

#include "bl_table.h"
#include "als_bl_iniparser.h"
#include <iostream>

#include "tvTypes.h"
#include "tvLog.h"
#include "tvSettings.h"
#include <pthread.h>
#include "Module.h"
#include "utils.h"
#include "tvTypes.h"
#include "tvError.h"
#include "Device.h"
#include "TV.h"
#include "STB.h"

#include "tr181api.h"
#include "AbstractPlugin.h"
#include <sys/stat.h>
#include <vector>

#define DECLARE_JSON_RPC_METHOD(method) \
uint32_t method(const JsonObject& parameters, JsonObject& response);

namespace WPEFramework {
namespace Plugin {

    class ControlSettings : public AbstractPlugin {

    private:
        ControlSettings(const ControlSettings&) = delete;
        ControlSettings& operator=(const ControlSettings&) = delete;
	WPEFramework::Plugin::Device *devicePtr;

	DECLARE_JSON_RPC_METHOD(getAspectRatio)
        DECLARE_JSON_RPC_METHOD(setAspectRatio)
        DECLARE_JSON_RPC_METHOD(getVideoFormat)
        DECLARE_JSON_RPC_METHOD(getVolume)
        DECLARE_JSON_RPC_METHOD(setVolume)
	DECLARE_JSON_RPC_METHOD(getBacklight)
        DECLARE_JSON_RPC_METHOD(setBacklight)
        DECLARE_JSON_RPC_METHOD(getVideoFrameRate)
        DECLARE_JSON_RPC_METHOD(getVideoResolution)

   public:
        ControlSettings();
        ~ControlSettings();
        static ControlSettings* _instance;
	void NotifyVideoFormatChange(tvVideoHDRFormat_t format);
        void NotifyVideoResolutionChange(tvResolutionParam_t resolution);
        void NotifyVideoFrameRateChange(tvVideoFrameRate_t frameRate);


        BEGIN_INTERFACE_MAP(ControlSettings)
        INTERFACE_ENTRY(PluginHost::IPlugin)
        INTERFACE_ENTRY(PluginHost::IDispatcher)
        END_INTERFACE_MAP
    
    private:
        uint8_t _skipURL;
        int m_currentHdmiInResoluton;
        int m_videoZoomMode;
        bool m_isDisabledHdmiIn4KZoom;
	void InitializeIARM();
        void DeinitializeIARM();
        bool isIARMConnected();
        bool IARMinit();
        static void dsHdmiVideoModeEventHandler(const char *owner, IARM_EventId_t eventId, void *data, size_t len);
        static void dsHdmiStatusEventHandler(const char *owner, IARM_EventId_t eventId, void *data, size_t len);

        std::string getErrorString (tvError_t eReturn);

    public:
        //   IPlugin methods
        // -------------------------------------------------------------------------------------------------------
        virtual const std::string Initialize(PluginHost::IShell* service);
        virtual void Deinitialize(PluginHost::IShell* service);
        virtual std::string Information() const;
   };
}
}
#endif
