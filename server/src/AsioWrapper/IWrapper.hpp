/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** IWrapper
*/

// AsioWrapperInterface.hpp
#ifndef IWRAPPER_HPP_
#define IWRAPPER_HPP_

#include <string>
#include <vector>
#include <array>

namespace rt {

class IWrapper {
    public:
        virtual ~IWrapper() = default;

        virtual void run() = 0;
        virtual void startReceive() = 0;
        virtual void sendTo(const std::string& message, const std::string& ipAddress, unsigned short port) = 0;
        virtual std::vector<char> getReceivedData() const = 0;
        virtual const std::array<char, 1024>& getRecvBuffer() const = 0;
        virtual std::pair<std::string, int> getRemoteEndpoint() const = 0;
    };

} // namespace rt

#endif