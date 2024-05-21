//
// Created by Alan 15/05/2024
//

#pragma once

#include <memory>

/// @author Alan
/// @brief singleton pattern provider
/// @tparam T any object type
template <typename T>
class Singleton
{
public:
    /// @author Alan
    /// @brief returns an static instance of the object, checks if it exists first
    /// @return a static object
    template <typename... Args>
    static T& Instance(Args... args)
    {
        // check if instance exists first
        if (!_instance)
        {
                _instance = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }
        return *_instance;
    }

    // delete copy ctor
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;

protected:
    // hide ctor, dtor
    Singleton(){};
    ~Singleton(){};

private:
    static std::unique_ptr<T> _instance;

};

template <typename T>
std::unique_ptr<T> Singleton<T>::_instance = nullptr;
