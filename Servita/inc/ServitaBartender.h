#pragma once

#include <SinricProDevice.h>
#include <Capabilities/ModeController.h>

#include <SinricProNamespace.h>
namespace SINRICPRO_NAMESPACE {

/**
 * @brief ServitaBartender class that inherits from SinricProDevice and ModeController
 * 
 * This class is used to define the ServitaBartender device for SinricPro
 * 
 * @param deviceId The device ID for the ServitaBartender
 */
class ServitaBartender: public SinricProDevice, public ModeController<ServitaBartender> {
  friend class ModeController<ServitaBartender>;
public:
  ServitaBartender(const String &deviceId) : SinricProDevice(deviceId, "ServitaBartender") {};
};

extern ServitaBartender *servitaBartender;

} // SINRICPRO_NAMESPACE

using ServitaBartender = SINRICPRO_NAMESPACE::ServitaBartender;