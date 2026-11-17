#include "bms/CellMonitor.hpp"
#include <iostream>

class ConsoleCommBus : public bms::ICommBus {
public:
    bool sendFaultAlert(uint8_t cellId, bms::FaultCode fault) override {
        std::cout << "[CAN-ALERT] Cell " << static_cast<int>(cellId)
                  << " reported fault code: " << static_cast<int>(fault) << "\n";
        return true;
    }
};

int main() {
    ConsoleCommBus bus;
    bms::CellMonitor monitor(bus);

    // Populate all cells with nominal operating values
    for (std::size_t i = 0; i < bms::CellMonitor::kNumCells; ++i) {
        monitor.updateCell(i, {3700, 250});
    }

    std::cout << "Status 1: " << static_cast<int>(monitor.evaluateSystemHealth()) << "\n";

    // Simulate an over-voltage condition on cell 2
    monitor.updateCell(2, {4350, 280});
    std::cout << "Status 2: " << static_cast<int>(monitor.evaluateSystemHealth()) << "\n";

    return 0;
}
