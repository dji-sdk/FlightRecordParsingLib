//
//  fr_standardization_battery_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_battery_interface_h
#define fr_standardization_battery_interface_h

#include <stdio.h>
#include <vector>
#include <memory>

namespace DJIFR {
    namespace standardization {
        class BatteryState {
        public:
            
            //MARK: - Property Set & Get
            
            /// Returns the component index. Index is zero based.
            virtual int index() const = 0;
            
            /// Returns the current battery voltage [mV].
            virtual int32_t voltage() const = 0;
            
            /// Returns the real time current draw of the battery (mA). A negative value means\n   the battery is being discharged, and a positive value means it is being charged.
            virtual int32_t current() const = 0;
            
            /// Returns the battery's temperature, in Celsius, with range [-128, 127] degrees.
            virtual double temperature() const = 0;
            
            /// Gets the battery's cell voltages. There will be a voltage for each cell in the battery.
            virtual std::vector<int32_t> cellVoltages() const = 0;
            
            /// Returns the percentage of battery energy left with range [0, 100].
            virtual int32_t chargeRemainingInPercent() const = 0;
            
            /// The low battery warning threshold as a percentage. \n   The percentage is in the range of [15, 50].
            virtual int32_t lowBatteryWarningThreshold() const = 0;
            
            /// The serious low battery warning threshold in percentage. \n   The minimum value is 10. \n   The maximum value is value from `lowBatteryWarningThreshold` minus 5.
            virtual int32_t seriousLowBatteryWarningThreshold() const = 0;
            
            /// Returns the battery's remaining lifetime as a percentage, with range [0, 100]. A
            /// new battery will be close to 100%. As a battery experiences charge/discharge
            /// cycles, the value will go down. In unsupported products, this value will always be 0.
            virtual int32_t lifetimeRemaining() const = 0;
            
            /// Returns the design capacity of the battery in mAh (milliamp hours). It is the ideal capacity when the battery is new.
            /// This value will not change over time. It is only supported by smart battery.
            virtual int32_t designCapacity() const = 0;
            
            /// Returns the total number of discharges the battery has gone through over its lifetime.
            /// The total number of discharges includes discharges that happen through normal use and discharges that are manually set.
            virtual int32_t numberOfDischarges() const = 0;
            
            /// `YES` if only one battery is inserted on the the right or starboard side of the aircraft.
            /// The aircraft can still take off but the flight time will be shorter.
            virtual bool isInSingleBatteryMode() const = 0;
            
            /// Returns the total amount of energy, in mAh (milliamp hours), stored in the
            /// battery when the battery is fully charged. The energy of the battery at full
            /// charge changes over time as the battery continues to get used. Over time, as the
            /// battery continues to be recharged, the value of `fullChargeCapacity` will
            /// decrease.
            virtual uint32_t fullChargeCapacity() const = 0;
            
            /// Returns the remaining energy stored in the battery in mAh (milliamp hours).
            virtual uint32_t chargeRemaining() const = 0;
        };
    
        using BatteryStateSharedPtr = std::shared_ptr<BatteryState>;
    }
}

#endif /* fr_standardization_battery_interface_h */
