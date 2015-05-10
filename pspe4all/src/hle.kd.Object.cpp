/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

namespace hle
{
    namespace kd
    {
        ObjectPool Objects;

        /// KernelObject ////////////////////////////////////////////////////////////

        char const * Object::m_object_type = "KernelObject";

        Object::Object(char const * name)
        {
            ::memset(m_name, 0, 32);
            if (name) ::strncpy(m_name, name, 31);
            Objects.Attach(this);
        }

        Object::~Object()
        {
            Objects.Detach(this);
        }

        void Object::GetQuickInfos(char * data, size_t size)
        {
            ::strncpy(data, "-", size-1);
        }

        void ObjectPool::Dump()
        {
            unsigned * occupied_entry = occupied;

            for (int i = 0, j = 0; i < max_count/32; ++i, ++occupied_entry)
            {
                unsigned mask = *occupied_entry;
                for (unsigned k = 1; k; ++j, k <<= 1)
                {
                    if (mask & k)
                    {
                        char buffer[1024];

                        if (pool[j])
                        {
                            pool[j]->GetQuickInfos(buffer, 1024);

                            forcef(kd, "KernelObject %i: %s \"%s\": %s", j + handle_offset, pool[j]->GetType(), pool[j]->GetName(), buffer);
                        }
                    }
                }
            }
        }
    }
}
