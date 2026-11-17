#pragma once

#include <cstdint>

namespace bms {

enum class FaultCode : uint8_t {
    None = 0,
    OverVoltage = 1,
    UnderVoltage = 2,
    OverTemperature = 3
};

class ICommBus {
public:
    virtual ~ICommBus() = default;
    virtual bool sendFaultAlert(uint8_t cellId, FaultCode fault) = 0;
};

} // namespace bms
