//
// Created by fengxiaotx on 2024/5/21.
//
#include <iostream>
#include <phecda/ProtocolDriver.h>
#include <phecda/DeviceServiceSDK.h>

namespace phecda {
    DeviceServiceSDK::DeviceServiceSDK(const std::string &serviceKey, const std::string &serviceVersion,
                                       ProtocolDriver *protocolDriver) {
        this->serviceKey = serviceKey;
        this->serviceVersion = serviceVersion;
        this->protocolDriver = protocolDriver;
    }

    DeviceServiceSDK
    DeviceServiceSDK::newDeviceService(const std::string &serviceKey, const std::string &serviceVersion,
                                       ProtocolDriver *protocolDriver) {
        return {serviceKey, serviceVersion, protocolDriver};
    }
    void DeviceServiceSDK::addDevice(Device device) {

    }

    std::list<Device> DeviceServiceSDK::getDevices() {
        return {};
    }

    Device DeviceServiceSDK::getDeviceByName(std::string name){
        return {};
    }

    void DeviceServiceSDK::updateDevice(Device device) {

    }

    void DeviceServiceSDK::removeDeviceByName(std::string name) {

    }

    void DeviceServiceSDK::addDeviceProfile(DeviceProfile profile) {

    }

    std::list<DeviceProfile> DeviceServiceSDK::deviceProfiles() {
        return std::list<DeviceProfile>();
    }

    DeviceProfile DeviceServiceSDK::getProfileByName(std::string name) {
        return DeviceProfile();
    }

    void DeviceServiceSDK::updateDeviceProfile(DeviceProfile profile) {

    }

    void DeviceServiceSDK::removeDeviceProfileByName(std::string name) {

    }

    DeviceResource DeviceServiceSDK::deviceResource(std::string deviceName, std::string resourceName) {
        return DeviceResource();
    }

    DeviceCommand DeviceServiceSDK::deviceCommand(std::string deviceName, std::string commandName) {
        return DeviceCommand();
    }

    void DeviceServiceSDK::addDeviceAutoEvent(std::string deviceName, std::string sourceName, AutoEvent autoEvent) {

    }

    void DeviceServiceSDK::removeDeviceAutoEvent(std::string deviceName, std::string autoEventName) {

    }

    void DeviceServiceSDK::run() {
        std::cout << "Hello, World! run" << std::endl;
        protocolDriver->initialize(this);
    }


    std::string DeviceServiceSDK::name() {
        return std::string();
    }

    bool DeviceServiceSDK::asyncReadingsEnabled() {
        return false;
    }


}