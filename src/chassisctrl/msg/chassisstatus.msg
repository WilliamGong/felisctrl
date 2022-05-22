# enum Gear
uint8 GEAR_NEUTRAL = 0
uint8 GEAR_FORWARD = 1
uint8 GEAR_BACK = 2

# enum Mode
uint8 MODE_POWEROFF = 0
uint8 MODE_STANDBY = 16     # 0x10
uint8 MODE_REMOTECTRL = 48  # 0x30
uint8 MODE_WIRECTRL = 64    # 0x40
uint8 MODE_EMERGENCY = 80   # 0x50

# enum GearSwitch
uint8 GEARSWITCH_REMOTE = 0
uint8 GEARSWITCH_WIRE = 1
uint8 GEARSWITCH_OFFLINE = 2

uint8 currentMode
uint16 fault
uint8 counterStatus1

uint8 remote
uint8 realtime
uint8 remoteAccelerator
uint8 realtimeAccelerator
uint16 angle
uint8 countStatus2

uint8 pressure
uint8 brake
uint8 remoteMode
uint8 emergencyStatus
bool remoteStatus
uint8 countStatus3