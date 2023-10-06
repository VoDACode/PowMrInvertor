#pragma once
#include <Arduino.h>
#include <ModbusMaster.h>
#include <SoftwareSerial.h>
#include "TaskTimer.h"
#include "PowMrEnums.h"
#include "PowMrDataRecord.h"

#define MAX_MBUS_WORDS 64

class PowMrInverter
{
private:
    uint8_t _rxPin;
    uint8_t _txPin;
    uint8_t _id;
    void (*_idle)();
    void (*_log)(const char*);

    ModbusMaster node;
    SoftwareSerial* softSerial;

    void log(const char* message);
    bool readData(uint16_t dataAddress, uint16_t dataLength, uint16_t* data, int offset = 0);
public:
    PowMrInverter(uint8_t rxPin, uint8_t txPin, uint8_t id = 1);
    ~PowMrInverter();
    void begin();

    void idle(void (*idle)());
    void setLog(void (*log)(const char*));

    uint16_t readBatteryVoltage();
    uint16_t* scanRegisters(uint16_t startAddress, uint16_t endAddress);

    // 1
    bool setOutputSourcePriority(PowMrEnums::OutputSourcePriority priority);
    // 2
    bool setMaxChargeCurrent(PowMrEnums::MaxChargeCurrent current);
    // 3
    bool setAcInputVoltage(PowMrEnums::ACInputVoltage voltage);
    // 5
    bool setBatteryType(PowMrEnums::BatteryType type);
    // 6
    bool setAutoRestartWhenOverload(bool mode);
    // 7
    bool setAutoRestartWhenOverheat(bool mode);
    // 9
    bool setOutputFrequency(PowMrEnums::OutputFrequency frequency);
    // 10
    bool setOutputVoltage(PowMrEnums::OutputVoltage voltage);
    // 11
    bool setMaxUtilityChargeCurrent(PowMrEnums::MaxUtilityChargeCurrent current);
    // 12
    bool setVoltageBackToUtility(PowMrEnums::BackToUtilityVoltage voltage);
    // 13
    bool setVoltageBackToBattery(PowMrEnums::BackToBatteryVoltage voltage);
    // 16
    bool setChargeSourcePriority(PowMrEnums::ChargeSourcePriority priority);
    // 18
    bool setAlarm(bool enable);
    // 19
    bool setAutoReturnToDefaultScreen(bool enable);
    // 20
    bool setBacklightControl(bool enable);
    // 22
    bool setBeepsWhilePrimarySourceIsInterrupted(bool enable);
    // 23
    bool setEnableBypassWhenOverload(bool enable);
    // 25
    bool setRecordFaultCode(bool enable);
    // 26
    bool setBatteryBulkChargeVoltage(uint16_t voltage);
    // 27
    bool setBatteryFloatChargeVoltage(uint16_t voltage);
    // 29
    bool setBatteryLowCutOffVoltage(uint16_t voltage);
    // 30
    bool setBatteryEqualization(bool enable);
    // 31
    bool setBatteryEqualizationVoltage(uint16_t voltage);
    // 33
    bool setBatteryEqualizationTime(uint16_t time);
    // 34
    bool setBatteryEqualizationTimeout(uint16_t time);
    // 35
    bool setBatteryEqualizationInterval(uint16_t interval);
    // 36
    bool setBatteryEqualizationImmediately(bool enable);

    PowMrDataRecord readData();
};

