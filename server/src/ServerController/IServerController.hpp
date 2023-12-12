// IServerController.hpp
#ifndef RTYPE_ISERVERCONTROLLER_HPP
#define RTYPE_ISERVERCONTROLLER_HPP

namespace rt {

    class IServerController {
    public:
        virtual ~IServerController() = default;
        virtual void run() = 0;
    };

} // rt

#endif //RTYPE_ISERVERCONTROLLER_HPP
