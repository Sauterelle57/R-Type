// AsioWrapperInterface.hpp
#ifndef IWRAPPER_HPP_
#define IWRAPPER_HPP_

#include <string>
#include <vector>
#include "Protocol.hpp"

namespace rt {

    class IWrapper {
    public:

        virtual ~IWrapper() = default;

        virtual void run() = 0;
        virtual void startReceive() = 0;
        virtual void sendToByStruct(const Protocol& message, const std::string& ipAddress, unsigned short port) = 0;
        virtual std::vector<char> getReceivedData() const = 0;
        virtual Protocol getReceivedDataByStruct() const = 0;
        virtual std::pair<std::string, int> getRemoteEndpoint() const = 0;
    };

} // namespace rt

#endif /* IWRAPPER_HPP_ */
