//
//  fr_standardization_battery_state.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_battery_state_hpp
#define fr_standardization_battery_state_hpp

#include <stdio.h>
#include <vector>
#include <model/protocol/dji_product_type.h>
#include "fr_standardization_battery_interface.h"

namespace DJIFR {
    namespace standardization {
        class BatteryStateImp : public BatteryState {
        public:
            BatteryStateImp();
            virtual ~BatteryStateImp();
            
            std::shared_ptr<BatteryStateImp> clone();
            
            //MARK: - Property Set & Get
            
            /// Returns the component index. Index is zero based.
            int index() const override;
            void set_index(int index);
            
            /// Returns the current battery voltage [mV].
            int32_t voltage() const override;
            /// Sets the current battery voltage [mV].
            void set_voltage(int32_t voltage);
            
            /// Returns the real time current draw of the battery (mA). A negative value means\n   the battery is being discharged, and a positive value means it is being charged.
            int32_t current() const override;
            /// Sets the real time current draw of the battery (mA).
            void set_current(int32_t current);
            
            /// Returns the battery's temperature, in Celsius, with range [-128, 127] degrees.
            double temperature() const override;
            /// Sets the battery's temperature
            void set_temperature(double temperature);
            
            /// Gets the battery's cell voltages. There will be a voltage for each cell in the battery.
            std::vector<int32_t> cellVoltages() const override;
            /// Sets the battery's cell voltages.
            void set_cellVoltages(const std::vector<int32_t>& cellVoltages);
            
            /// Returns the percentage of battery energy left with range [0, 100].
            int32_t chargeRemainingInPercent() const override;
            /// Sets the percentage of battery energy left with range.
            void set_chargeRemainingInPercent(int32_t chargeRemainingInPercent);
            
            /// The low battery warning threshold as a percentage. \n   The percentage is in the range of [15, 50].
            int32_t lowBatteryWarningThreshold() const override;
            /// Sets The low battery warning threshold as a percentage.
            void set_lowBatteryWarningThreshold(int32_t lowBatteryWarningThreshold);
            
            /// The serious low battery warning threshold in percentage. \n   The minimum value is 10. \n   The maximum value is value from `lowBatteryWarningThreshold` minus 5.
            int32_t seriousLowBatteryWarningThreshold() const override;
            /// Sets the serious low battery warning threshold in percentage.
            void set_seriousLowBatteryWarningThreshold(int32_t seriousLowBatteryWarningThreshold);
            
            /// Returns the battery's remaining lifetime as a percentage, with range [0, 100]. A
            /// new battery will be close to 100%. As a battery experiences charge/discharge
            /// cycles, the value will go down. In unsupported products, this value will always be 0.
            int32_t lifetimeRemaining() const override;
            void set_lifetimeRemaining(int32_t lifetimeRemaining);
            
            /// Returns the design capacity of the battery in mAh (milliamp hours). It is the ideal capacity when the battery is new.
            /// This value will not change over time. It is only supported by smart battery.
            int32_t designCapacity() const override;
            void set_designCapacity(int32_t designCapacity);
            
            /// Returns the total number of discharges the battery has gone through over its lifetime.
            /// The total number of discharges includes discharges that happen through normal use and discharges that are manually set.
            int32_t numberOfDischarges() const override;
            void set_numberOfDischarges(int32_t numberOfDischarges);
            
            /// `YES` if only one battery is inserted on the the right or starboard side of the aircraft.
            /// The aircraft can still take off but the flight time will be shorter.
            bool isInSingleBatteryMode() const override;
            void set_isInSingleBatteryMode(bool isInSingleBatteryMode);
            
            /// Returns the total amount of energy, in mAh (milliamp hours), stored in the
            /// battery when the battery is fully charged. The energy of the battery at full
            /// charge changes over time as the battery continues to get used. Over time, as the
            /// battery continues to be recharged, the value of `fullChargeCapacity` will
            /// decrease.
            uint32_t fullChargeCapacity() const override;
            void set_fullChargeCapacity(uint32_t fullChargeCapacity);
            
            /// Returns the remaining energy stored in the battery in mAh (milliamp hours).
            uint32_t chargeRemaining() const override;
            void set_chargeRemaining(uint32_t chargeRemaining);
            
            //MARK: - Private Property
            
            DJI::FlightRecord::DroneType drone_type() const;
            void set_drone_type(DJI::FlightRecord::DroneType drone_type);
            
        private:
            int index_ = 0;
            
            int32_t voltage_;
            
            int32_t current_;
            
            double temperature_;
            
            std::vector<int32_t> cellVoltages_;
            
            int32_t chargeRemainingInPercent_;
            
            int32_t lowBatteryWarningThreshold_;
            
            int32_t seriousLowBatteryWarningThreshold_;
            
            DJI::FlightRecord::DroneType drone_type_;
            
            int32_t lifetimeRemaining_ = 0;
            
            int32_t designCapacity_ = 0;
            
            int32_t numberOfDischarges_ = 0;
            
            bool isInSingleBatteryMode_ = false;
            
            uint32_t fullChargeCapacity_ = 0;
            
            uint32_t chargeRemaining_ = 0;
        };
    }
}

#endif /* fr_standardization_battery_state_hpp */
