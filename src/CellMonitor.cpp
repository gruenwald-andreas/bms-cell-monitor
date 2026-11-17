#include "bms/CellMonitor.hpp"

namespace bms {

CellMonitor::CellMonitor(ICommBus& commBus) noexcept
    : m_commBus(commBus) {}

void CellMonitor::updateCell(std::size_t index, const CellData& data) {
    if (index < kNumCells) {
        m_cells[index] = data;
    }
}

std::optional<CellData> CellMonitor::getCellData(std::size_t index) const noexcept {
    if (index >= kNumCells) {
        return std::nullopt;
    }
    return m_cells[index];
}

FaultCode CellMonitor::evaluateSystemHealth() {
    for (std::size_t i = 0; i < kNumCells; ++i) {
        const auto& cell = m_cells[i];

        if (cell.voltageMv > kMaxVoltageMv) {
            m_commBus.sendFaultAlert(static_cast<uint8_t>(i), FaultCode::OverVoltage);
            return FaultCode::OverVoltage;
        }
        if (cell.voltageMv < kMinVoltageMv) {
            m_commBus.sendFaultAlert(static_cast<uint8_t>(i), FaultCode::UnderVoltage);
            return FaultCode::UnderVoltage;
        }
        if (cell.temperatureDeciC > kMaxTempDeciC) {
            m_commBus.sendFaultAlert(static_cast<uint8_t>(i), FaultCode::OverTemperature);
            return FaultCode::OverTemperature;
        }
    }
    return FaultCode::None;
}

} // namespace bms
