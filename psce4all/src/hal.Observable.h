/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <functional>
#include <map>
#include <vector>
#include <utility>

namespace hal
{
    template < typename Event, typename Ret, typename... Args >
    class Observable
    {
    public:
        struct Index
        {
            Event m_event;
            unsigned int m_index;
        };

        Observable() = default;
        virtual ~Observable() = default;

        template < typename Observer >
        Index const Register(Event const &event, Observer &&observer)
        {
            auto observers = m_observers[event];
            observers.push_back(std::forward< Observer >(observer));

            return Index(){ event, observers.size() - 1 };
        }

        template < typename Observer >
        Index const Register(Event const &&event, Observer &&observer)
        {
            auto observers = m_observers[std::move(event)];
            observers.push_back(std::forward< Observer >(observer));

            return Index(){ event, observers.size() - 1 };
        }

        template < typename... Parameters >
        void Notify(Event const &event, Parameters... Params) const
        {
            if (m_observers.size() > 0)
            {
                auto iterator = m_observers.find(event);
                if (iterator != m_observers.end())
                {
                    auto &observers = *iterator;
                    for (auto const &observer : observers)
                    {
                        observer(Params...);
                    }
                }
            }
        }

        bool const Remove(Index const &index)
        {
            auto iterator = m_observers.find(index.m_event);
            if (iterator != m_observers.end())
            {
                auto &callbackVectors = *iterator;
                auto callbackRemove = callbackVectors.begin() + index.m_index;
                callbackVectors.erase(callbackRemove);
                return true;
            }
            return false;
        }

        Observable(const Observable &) = delete;
        Observable &operator=(const Observable &) = delete;

    private:
        std::map< Event, std::vector< std::function< Ret(Args...) > > > m_observers;
    };
}
