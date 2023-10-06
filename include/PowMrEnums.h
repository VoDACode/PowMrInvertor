#pragma once
#include <Arduino.h>
namespace PowMrEnums
{
    enum BackToUtilityVoltage{
        BackToUtilityV21_0 = 210,
        BackToUtilityV21_5 = 215,
        BackToUtilityV22_0 = 220,
        BackToUtilityV22_5 = 225,
        BackToUtilityV23_0 = 230,
        BackToUtilityV23_5 = 235,
        BackToUtilityV24_0 = 240,
        BackToUtilityV24_5 = 245,
        BackToUtilityV25_0 = 250,
        BackToUtilityV25_5 = 255
    };

    enum BackToBatteryVoltage{
        BackToBatteryV24_0 = 240,
        BackToBatteryV24_5 = 245,
        BackToBatteryV25_0 = 250,
        BackToBatteryV25_5 = 255,
        BackToBatteryV26_0 = 260,
        BackToBatteryV26_5 = 265,
        BackToBatteryV27_0 = 270,
        BackToBatteryV27_5 = 275,
        BackToBatteryV28_0 = 280,
        BackToBatteryV28_5 = 285,
        BackToBatteryV29_0 = 290
    };

    enum MaxChargeCurrent{
        MaxChargeCurrent_A10 = 10,
        MaxChargeCurrent_A20 = 20,
        MaxChargeCurrent_A30 = 30,
        MaxChargeCurrent_A40 = 40,
        MaxChargeCurrent_A50 = 50,
        MaxChargeCurrent_A60 = 60,
        MaxChargeCurrent_A70 = 70,
        MaxChargeCurrent_A80 = 80,
        MaxChargeCurrent_A90 = 90,
        MaxChargeCurrent_A100 = 100,
        MaxChargeCurrent_A110 = 110,
        MaxChargeCurrent_A120 = 120,
        MaxChargeCurrent_A130 = 130,
        MaxChargeCurrent_A140 = 140
    };

    enum MaxUtilityChargeCurrent{
        MaxUtilityChargeCurrent_A2 = 2,
        MaxUtilityChargeCurrent_A10 = 10,
        MaxUtilityChargeCurrent_A20 = 20,
        MaxUtilityChargeCurrent_A30 = 30,
        MaxUtilityChargeCurrent_A40 = 40,
        MaxUtilityChargeCurrent_A50 = 50,
        MaxUtilityChargeCurrent_A60 = 60,
        MaxUtilityChargeCurrent_A70 = 70,
        MaxUtilityChargeCurrent_A80 = 80,
        MaxUtilityChargeCurrent_A90 = 90,
        MaxUtilityChargeCurrent_A100 = 100
    };

    enum ACInputVoltage
    {
        Appliances = 0,
        UPS = 1
    };

    enum BatteryType
    {
        AGM = 0,
        Flooded = 1,
        User = 2
    };

    enum OutputSourcePriority
    {
        UtilityFirst = 0,
        SolarFirst = 1,
        SBU = 2
    };

    enum ChargeSourcePriority
    {
        SolarFirstCharger = 0,
        SolarAndUtilityCharger = 1,
        OnlySolarCharger = 2,
    };

    enum ChargerStatus
    {
        Off = 0,
        Idle = 1,
        Active = 2,
    };

    enum OutputFrequency{
        Freq50Hz = 50,
        Freq60Hz = 60
    };
    
    enum OutputVoltage{
        v220 = 220,
        v230 = 230,
        v240 = 240
    };
}