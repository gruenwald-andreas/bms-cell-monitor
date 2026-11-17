#pragma once

#include "bms/ICommBus.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>

namespace bms {

struct CellData {
    uint16_t voltageMv{0};
    int16_t temperatureDeciC{0}; // e.g., 250 = 25.0 °C
};

class CellMonitor {
public:
    static constexpr std::size_t kNumCells = 4;
    static constexpr uint16_t kMaxVoltageMv = 4200;
    static constexpr uint16_t kMinVoltageMv = 3000;
    static constexpr int16_t kMaxTempDeciC = 600; // 60.0 °C

    explicit CellMonitor(ICommBus& commBus) noexcept;

    void updateCell(std::size_t index, const CellData& data);
    [[nodiscard]] std::optional<CellData> getCellData(std::size_t index) const noexcept;
    [[nodiscard]] FaultCode evaluateSystemHealth();

private:
    ICommBus& m_commBus;
    std::array<CellData, kNumCells> m_cells{};
};

} // namespace bms
