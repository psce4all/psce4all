/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <list>
#include <unordered_map>

// Class providing fixed-size (by number of records) LRU-replacement cache.
template < typename K, typename V > class LRUCache
{
public:
    typedef K   key_type;
    typedef V * value_type;

    // Key access history, most recent at back
    typedef std::list< key_type > key_tracker_type;

    // Key to value and key history iterator
    typedef std::unordered_map< key_type, std::pair< value_type, typename key_tracker_type::iterator > > key_to_value_type;

    // Constructor specifies the cached function and the maximum number of records to be stored
    LRUCache(size_t c = 32) : m_capacity(c)
    {
    }

    // Obtain value of the cached function for k
    value_type operator()(key_type & k)
    {
        // Attempt to find existing record
        auto const i = m_key_to_value.find(k);

        if (i == m_key_to_value.end())
        {
            // Evaluate function and create new record
            auto const v = __new V(k);
            Insert(k, v);

            // Return the freshly computed value
            return v;
        }
        else
        {
            // Update access record by moving
            // accessed key to back of list
            m_key_tracker.splice(m_key_tracker.end(), m_key_tracker, (*i).second.second);

            // Return the retrieved value
            return (*i).second.first;
        }
    }

    void SetCapacity(size_t c)
    {
        m_capacity = c;
        while (m_key_to_value.size() >= c)
        {
            Evict();
        }
    }

private:

    // Record a fresh key-value pair in the cache
    void Insert(key_type const & k, value_type const & v)
    {
        // Make space if necessary
        if (m_key_to_value.size() >= m_capacity)
        {
            Evict();
        }

        // Record k as most-recently-used key
        auto i = m_key_tracker.insert(m_key_tracker.end(), k);

        // Create the key-value entry, linked to the usage record.
        m_key_to_value.insert(std::make_pair(k, std::make_pair(v, i)));
    }

    // Purge the least-recently-used element in the cache
    void Evict()
    {
        // Identify least recently used key
        auto const i = m_key_to_value.find(m_key_tracker.front());

        __delete (*i).second.first;

        // Erase both elements to completely purge record
        m_key_to_value.erase(i);
        m_key_tracker.pop_front();
    }

    // Maximum number of key-value pairs to be retained
    size_t m_capacity;

    // Key access history
    key_tracker_type m_key_tracker;

    // Key-to-value lookup
    key_to_value_type m_key_to_value;
};
