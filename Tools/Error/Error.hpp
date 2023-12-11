/*
** EPITECH PROJECT, 2023
** bsraytracer
** File description:
** tlsError.hpp
*/

#ifndef RTYPE_ERROR_HPP
#define RTYPE_ERROR_HPP

#include <iostream>
#include <exception>
#include <utility>

namespace tls {
    class Error : public std::exception {
        public:
            explicit Error(std::string err) : _error(std::move(err)) {};
            const char *what() const noexcept override {
                return _error.c_str();
            }
            std::string _error;
    };
}

#endif //RTYPE_ERROR_HPP
