#include "bms/CellMonitor.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;

class MockCommBus : public bms::ICommBus {
public:
    MOCK_METHOD(bool, sendFaultAlert, (uint8_t cellId, bms::FaultCode fault), (override));
};

class CellMonitorTest : public ::testing::Test {
protected:
    MockCommBus mockBus;
    bms::CellMonitor monitor{mockBus};

    void SetUp() override {
        for (std::size_t i = 0; i < bms::CellMonitor::kNumCells; ++i) {
            monitor.updateCell(i, {3700, 250});
        }
    }
};

TEST_F(CellMonitorTest, HealthySystemReturnsNoFault) {
    EXPECT_CALL(mockBus, sendFaultAlert(_, _)).Times(0);
    EXPECT_EQ(monitor.evaluateSystemHealth(), bms::FaultCode::None);
}

TEST_F(CellMonitorTest, DetectsOverVoltageAndSendsAlert) {
    monitor.updateCell(1, {4250, 250});

    EXPECT_CALL(mockBus, sendFaultAlert(1, bms::FaultCode::OverVoltage))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_EQ(monitor.evaluateSystemHealth(), bms::FaultCode::OverVoltage);
}

TEST_F(CellMonitorTest, OutOfBoundsIndexReturnsNullopt) {
    EXPECT_FALSE(monitor.getCellData(99).has_value());
}
