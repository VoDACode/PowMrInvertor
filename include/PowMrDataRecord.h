#pragma once
#include <Arduino.h>
#include "PowMrEnums.h"
#include "lwip/def.h"

#define POWMR_DATA_JSON_SIZE 1024 * 3

#define DEVELOPMENT_MODE 1
#define TEST_FEATURES 1

struct PowMrDataAC
{
    float voltage = 0;
    float frequency = 0;
    PowMrEnums::ACInputVoltage input_voltage_range = PowMrEnums::Appliances;
    PowMrEnums::OutputVoltage output_voltage = PowMrEnums::v230;
};

struct PowMrDataPV
{
    float voltage = 0;
    float current = 0;
    float power = 0;
};

struct PowMrDataBattery
{
    float voltage = 0;
    float soc = 0;
    float charge_current = 0;
    float discharge_current = 0;
    float charge_power = 0;
    PowMrEnums::MaxChargeCurrent max_total_charge_current = PowMrEnums::MaxChargeCurrent::MaxChargeCurrent_A30;
    PowMrEnums::MaxUtilityChargeCurrent max_utility_charge_current = PowMrEnums::MaxUtilityChargeCurrent::MaxUtilityChargeCurrent_A2;
    PowMrEnums::ChargeSourcePriority charge_source_priority = PowMrEnums::ChargeSourcePriority::SolarAndUtilityCharger;
    PowMrEnums::BackToBatteryVoltage back_to_battery_voltage = PowMrEnums::BackToBatteryVoltage::BackToBatteryV29_0;
    PowMrEnums::BackToUtilityVoltage back_to_utility_voltage = PowMrEnums::BackToUtilityVoltage::BackToUtilityV22_0;
    float back_to_utility_voltage_unit = 0;
    float back_to_battery_voltage_unit = 0;
    float bulk_charge_voltage = 0;
    float float_charge_voltage = 0;
    float low_cut_off_voltage = 0;
};
struct PowMrDataBatteryEqualize
{
    float voltage = 0;
    float time = 0;
    float timeout = 0;
    float interval = 0;
    bool runImmediately = false;
    bool enabled = false;
};

struct PowMrDataLoad
{
    float voltage = 0;
    float frequency = 0;
    float power = 0;
    float va = 0;
    float percent = 0;
    float percent_ = 0;
    PowMrEnums::OutputSourcePriority output_source_priority = PowMrEnums::OutputSourcePriority::SolarFirst;
};

struct PowMrDataRecord
{
    uint16_t* rawRegisterData = nullptr;
    bool available = false;

    PowMrDataAC ac;
    PowMrDataPV pv;
    PowMrDataBattery battery;
    PowMrDataBatteryEqualize equalize;
    PowMrDataLoad load;

    uint16_t error_code = 0;
    uint16_t output_source_priority = 0;
    float target_output_frequency = 0;

#ifdef TEST_FEATURES
    bool record_fault_code = false;
    bool is_overload = false;
    bool charging = false;
    bool alarm = false;
    bool backlight = false;
    bool restartOverload = false;
    bool restartOverheat = false;
    bool beepOnPrimarySourceFail = false;
    bool returnToPrimarySource = false;
    bool overloadBypass = false;
    bool onBattery = false;
    bool acActive = false;
    bool loadOff = false;
    bool loadEnabled = false;
#endif

#ifdef DEVELOPMENT_MODE
    uint16_t registersFrom4515to4534[19];
    uint16_t register4539;
    uint16_t register4554;
#endif

    PowMrEnums::ChargerStatus charger_status = PowMrEnums::ChargerStatus::Off;

    void init(uint16_t *data)
    {
        rawRegisterData = new uint16_t[45];
        memcpy(rawRegisterData, data, 45 * sizeof(uint16_t));
        // start from 4501 register
        output_source_priority = htons(data[0]);     // register 4501
        ac.voltage = div(htons(data[1]), 10.0);      // register 4502
        ac.frequency = div(htons(data[2]), 10.0);    // register 4503
        pv.voltage = div(htons(data[3]), 10.0);      // register 4504
        pv.power = htons(data[4]);                   // register 4505
        battery.voltage = div(htons(data[5]), 10.0); // register 4506
        battery.soc = htons(data[6]);                // register 4507
        battery.charge_current = htons(data[7]);     // register 4508
        battery.discharge_current = htons(data[8]);  // register 4509
        load.voltage = div(htons(data[9]), 10.0);    // register 4510
        load.frequency = div(htons(data[10]), 10.0); // register 4511
        load.power = htons(data[11]);                // register 4512
        load.va = htons(data[12]);                   // register 4513
        load.percent = htons(data[13]);              // register 4514
        load.percent_ = htons(data[14]);             // register 4515

        error_code = htons(data[29]); // register 4530

#ifdef TEST_FEATURES
        uint16_t binary_flags = htons(data[34]); // register 4535   // incorrect. need to check
        record_fault_code = (binary_flags & 0x1) != 0;
        equalize.enabled = (binary_flags & 0x2) != 0;
        equalize.runImmediately = (binary_flags & 0x4) != 0;
        alarm = (binary_flags & 0x100) != 0; // incorrect. need to check
        backlight = (binary_flags & 0x400) != 0;
        restartOverload = (binary_flags & 0x800) != 0;
        restartOverheat = (binary_flags & 0x1000) != 0;
        beepOnPrimarySourceFail = (binary_flags & 0x2000) != 0;
        returnToPrimarySource = (binary_flags & 0x4000) != 0;
        overloadBypass = (binary_flags & 0x8000) != 0;
#endif

        battery.charge_source_priority = (PowMrEnums::ChargeSourcePriority)htons(data[35]);        // register 4536
        load.output_source_priority = (PowMrEnums::OutputSourcePriority)htons(data[36]);           // register 4537
        ac.input_voltage_range = (PowMrEnums::ACInputVoltage)htons(data[37]);                      // register 4538
        target_output_frequency = div(htons(data[39]), 10.0);                                      // register 4540
        battery.max_total_charge_current = (PowMrEnums::MaxChargeCurrent)htons(data[40]);          // register 4541
        ac.output_voltage = (PowMrEnums::OutputVoltage)htons(data[41]);                            // register 4542    // Menu 10
        battery.max_utility_charge_current = (PowMrEnums::MaxUtilityChargeCurrent)htons(data[42]); // register 4543

        battery.back_to_utility_voltage = (PowMrEnums::BackToUtilityVoltage)htons(data[43]); // register 4544
        battery.back_to_utility_voltage_unit = div(htons(data[43]), 10.0);                   // register 4544
        battery.back_to_battery_voltage = (PowMrEnums::BackToBatteryVoltage)htons(data[43]); // register 4545
        battery.back_to_battery_voltage_unit = div(htons(data[44]), 10.0);                   // register 4545

        battery.bulk_charge_voltage = div(htons(data[45]), 10.0);  // register 4546
        battery.float_charge_voltage = div(htons(data[46]), 10.0); // register 4547
        battery.low_cut_off_voltage = div(htons(data[47]), 10.0);  // register 4548
        equalize.voltage = div(htons(data[48]), 10.0);             // register 4549
        equalize.time = htons(data[49]);                           // register 4550
        equalize.timeout = htons(data[50]);                        // register 4551
        equalize.interval = htons(data[51]);                       // register 4552
#ifdef TEST_FEATURES
        uint16_t binary_flags_2 = htons(data[52]); // register 4553    // i think this is incorrect register
        onBattery = (binary_flags_2 & 0x100) != 0;
        acActive = (binary_flags_2 & 0x200) != 0;
        loadOff = (binary_flags_2 & 0x1000) != 0;
        acActive = (binary_flags_2 & 0x2000) != 0;
        loadEnabled = (binary_flags_2 & 0x4000) != 0;

        binary_flags_2 = htons(data[53]); // register 4554
        onBattery = (binary_flags_2 & 0x1) != 0;
#endif

        charger_status = (PowMrEnums::ChargerStatus)htons(data[54]); // register 4555
#ifdef DEVELOPMENT_MODE
        // skipped registers from list:
        // 4516 - 4531 (15 registers)
        // 4517
        // 4518
        // 4519
        // 4520
        // 4521
        // 4522
        // 4523
        // 4524
        // 4525
        // 4526
        // 4527 - maybe, this is selected frequency * 10
        // 4528
        // 4529
        // 4530 - error code
        // 4531
        // 4532
        // 4533
        // 4534

        // 4539 (1 register)
        // 4554 (1 register)

        // register 4515 - 4534
        for (int i = 0; i < 19; i++)
        {
            registersFrom4515to4534[i] = htons(data[15 + i]);
        }

        // register 4539
        register4539 = htons(data[38]);

        // register 4554
        register4554 = htons(data[53]);
#endif
    }

    float div(float a, float b)
    {
        if (b == 0)
            return 0;
        return a / b;
    }
};
