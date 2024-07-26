 #ifndef _SERVITABARTENDER_H_
#define _SERVITABARTENDER_H_

#include <SinricProDevice.h>
#include <Capabilities/ModeController.h>

class ServitaBartender 
: public SinricProDevice
, public ModeController<ServitaBartender> {
  friend class ModeController<ServitaBartender>;
public:
  ServitaBartender(const String &deviceId) : SinricProDevice(deviceId, "ServitaBartender") {};
};

void setupSinricPro();
void loopSinricPro();

#endif