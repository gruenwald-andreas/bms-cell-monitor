#include "bms/CellMonitor.hpp"
#include <iostream>

class ConsoleCommBus : public bms::ICommBus {
public:
    bool sendFaultAlert(uint8_t cellId, bms::FaultCode fault) override {
        std::cout << "[CAN-ALERT] Zelle " << static_cast<int>(cellId)
                  << " meldet Fehlercode: " << static_cast<int>(fault) << "\n";
        return true;
    }
};

int main() {
    ConsoleCommBus bus;
    bms::CellMonitor monitor(bus);

    // Normale Zellwerte setzen
    for (std::size_t i = 0; i < bms::CellMonitor::kNumCells; ++i) {
        monitor.updateCell(i, {3700, 250});
    }

    std::cout << "Status 1: " << static_cast<int>(monitor.evaluateSystemHealth()) << "\n";

    // Überspannung an Zelle 2 simulieren
    monitor.updateCell(2, {4350, 280});
    std::cout << "Status 2: " << static_cast<int>(monitor.evaluateSystemHealth()) << "\n";

    return 0;
}
