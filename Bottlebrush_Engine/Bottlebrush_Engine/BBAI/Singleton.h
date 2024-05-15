//
// Created by Alan 15/05/2024
//

#pragma once

#include <memory>

/// @brief singleton pattern provider
/// @tparam T any object type
template <class T>
class Singleton
{
	public:
		/// @brief returns an static instance of the object, checks if it exists first
		/// @return a static object
		static T& Instance() 
		{
			// check if instance exists first
			if (_instance == nullptr) 
			{
				_instance = new T();
            } 
			else return *_instance;
		}

		// delete copy ctor
        Singleton(Singleton const&) = delete;
        Singleton& operator=(Singleton const&) = delete;

	private:
		static std::unique_ptr<T> _instance;

		// hide ctor, dtor
		Singleton() {};
        ~Singleton() {};
};
