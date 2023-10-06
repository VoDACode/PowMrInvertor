#include "PowMrInverter.h"

PowMrInverter::PowMrInverter(uint8_t rxPin, uint8_t txPin, uint8_t id)
{
    _rxPin = rxPin;
    _txPin = txPin;
    _id = id;

    softSerial = new SoftwareSerial(_rxPin, _txPin);
}

PowMrInverter::~PowMrInverter()
{
    delete softSerial;
}

void PowMrInverter::begin()
{
    softSerial->begin(2400);
    softSerial->enableIntTx(false);
    node.begin(this->_id, *softSerial);
}

void PowMrInverter::idle(void (*idle)())
{
    _idle = idle;
    node.idle(_idle);
}

void PowMrInverter::setLog(void (*log)(const char *))
{
    _log = log;
}

void PowMrInverter::log(const char *message)
{
    if (_log != NULL)
    {
        _log(message);
    }
}

bool PowMrInverter::readData(uint16_t dataAddress, uint16_t dataLength, uint16_t *data, int offset)
{
    uint8_t result = node.readHoldingRegisters(dataAddress, dataLength);
    if (result == node.ku8MBSuccess)
    {
        for (uint8_t i = 0; i < dataLength; i++)
        {
            data[i + offset] = node.getResponseBuffer(i);
        }
    }
    return result == node.ku8MBSuccess;
}

uint16_t* PowMrInverter::scanRegisters(uint16_t startAddress, uint16_t endAddress)
{
    uint16_t dataLength = endAddress - startAddress + 1;
    uint16_t* data = new uint16_t[dataLength];
    uint16_t dataAddress = startAddress;
    uint16_t dataOffset = 0;
    uint16_t dataChunkLength = 0;

    while (dataLength > 0)
    {
        dataChunkLength = dataLength > MAX_MBUS_WORDS ? MAX_MBUS_WORDS : dataLength;
        readData(dataAddress, dataChunkLength, data);
        dataAddress += dataChunkLength;
        dataOffset += dataChunkLength;
        dataLength -= dataChunkLength;
    }
    return data;
}

PowMrDataRecord PowMrInverter::readData()
{
    PowMrDataRecord resultData;
    uint16_t data[MAX_MBUS_WORDS];
    uint16_t dataAddress = 4501;
    uint16_t dataLength = 45;

    if (!readData(dataAddress, dataLength, data))
    {
        this->log("Error reading data from inverter");
        resultData.available = false;
        return resultData;
    }

    dataAddress = 4546;
    dataLength = 16;

    if (!readData(dataAddress, dataLength, data, 45))
    {
        this->log("Error reading data from inverter");
        resultData.available = false;
        return resultData;
    }

    resultData.available = true;
    resultData.init(data);

    return resultData;
}

// 1
bool PowMrInverter::setOutputSourcePriority(PowMrEnums::OutputSourcePriority priority)
{
    return node.writeSingleRegister(5018, (uint16_t)priority) == node.ku8MBSuccess;
}
// 2
bool PowMrInverter::setMaxChargeCurrent(PowMrEnums::MaxChargeCurrent current)
{
    return node.writeSingleRegister(5022, (uint16_t)current) == node.ku8MBSuccess;
}
// 3
bool PowMrInverter::setAcInputVoltage(PowMrEnums::ACInputVoltage voltage)
{
    return false;
}
// 5
bool PowMrInverter::setBatteryType(PowMrEnums::BatteryType type)
{
    return false;
}
// 6
bool PowMrInverter::setAutoRestartWhenOverload(bool mode)
{
    return false;
}
// 7
bool PowMrInverter::setAutoRestartWhenOverheat(bool mode)
{
    return false;
}
// 9
bool PowMrInverter::setOutputFrequency(PowMrEnums::OutputFrequency frequency)
{
    return false;
}
// 10
bool PowMrInverter::setOutputVoltage(PowMrEnums::OutputVoltage voltage)
{
    return false;
}
// 11
bool PowMrInverter::setMaxUtilityChargeCurrent(PowMrEnums::MaxUtilityChargeCurrent current)
{
    return node.writeSingleRegister(5024, (uint16_t)current) == node.ku8MBSuccess;
}
// 12
bool PowMrInverter::setVoltageBackToUtility(PowMrEnums::BackToUtilityVoltage voltage)
{
    return node.writeSingleRegister(5025, (uint16_t)voltage) == node.ku8MBSuccess;
}
// 13
bool PowMrInverter::setVoltageBackToBattery(PowMrEnums::BackToBatteryVoltage voltage)
{
    return node.writeSingleRegister(5026, (uint16_t)voltage) == node.ku8MBSuccess;
}
// 16
bool PowMrInverter::setChargeSourcePriority(PowMrEnums::ChargeSourcePriority priority)
{
    return node.writeSingleRegister(5017, (uint16_t)priority) == node.ku8MBSuccess;
}
// 18
bool PowMrInverter::setAlarm(bool enable)
{
    return node.writeSingleRegister(5002, enable ? 1 : 0) == node.ku8MBSuccess;
}
// 19
bool PowMrInverter::setAutoReturnToDefaultScreen(bool enable)
{
    return false;
}
// 20
bool PowMrInverter::setBacklightControl(bool enable)
{
    return false;
}
// 22
bool PowMrInverter::setBeepsWhilePrimarySourceIsInterrupted(bool enable)
{
    return node.writeSingleRegister(5007, enable ? 1 : 0) == node.ku8MBSuccess;
}
// 23
bool PowMrInverter::setEnableBypassWhenOverload(bool enable)
{
    return node.writeSingleRegister(5009, enable ? 1 : 0) == node.ku8MBSuccess;
}
// 25
bool PowMrInverter::setRecordFaultCode(bool enable)
{
    return false;
}
// 26
bool PowMrInverter::setBatteryBulkChargeVoltage(uint16_t voltage)
{
    return false;
}
// 27
bool PowMrInverter::setBatteryFloatChargeVoltage(uint16_t voltage)
{
    return false;
}
// 29
bool PowMrInverter::setBatteryLowCutOffVoltage(uint16_t voltage)
{
    return false;
}
// 30
bool PowMrInverter::setBatteryEqualization(bool enable)
{
    return false;
}
// 31
bool PowMrInverter::setBatteryEqualizationVoltage(uint16_t voltage)
{
    return false;
}
// 33
bool PowMrInverter::setBatteryEqualizationTime(uint16_t time)
{
    return false;
}
// 34
bool PowMrInverter::setBatteryEqualizationTimeout(uint16_t time)
{
    return false;
}
// 35
bool PowMrInverter::setBatteryEqualizationInterval(uint16_t interval)
{
    return false;
}
// 36
bool PowMrInverter::setBatteryEqualizationImmediately(bool enable)
{
    return false;
}