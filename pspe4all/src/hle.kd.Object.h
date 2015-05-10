/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#define declare_kernel_type(DerivedClass, BaseClass) \
    typedef BaseClass Super; \
    static char const * m_object_type; \
    virtual bool CheckExactType(char const * type) { return type == DerivedClass::m_object_type; } \
    virtual bool CheckType(char const * type, bool exact = true) { return DerivedClass::CheckExactType(type) || (!exact && BaseClass::CheckType(type)); } \
    virtual char const * GetType() const { return DerivedClass::m_object_type; } \
    virtual void GetQuickInfos(char * data, size_t Size);

namespace hle
{
    namespace kd
    {
        struct Object
        {
            char                 m_name[32];
            SceUID               m_uid;

            static char const  * m_object_type;

            virtual bool         CheckExactType(char const * type)
            {
                return type == Object::m_object_type;
            }
            virtual bool         CheckType(char const * type, bool /*exact*/ = true)
            {
                return CheckExactType(type);
            }
            virtual char const * GetType() const
            {
                return m_object_type;
            }
            virtual void         GetQuickInfos(char * data, size_t size);
            virtual int          Delete(int intr) = 0;

            SceUID               GetUid() const
            {
                return m_uid;
            }
            char const         * GetName()
            {
                return m_name;
            }

            /**/                 Object(char const * name = 0);
            virtual             ~Object();
        };

        class ObjectPool
        {
            enum
            {
                max_count = 4096, handle_offset = 0x100
            };

            Object * pool[max_count];

            unsigned occupied[max_count/32];

        public:
            ObjectPool()
            {
                memset(occupied, 0, sizeof(occupied));
            }

            SceUID Attach(Object * object)
            {
                unsigned * occupied_entry = occupied;

                for (int i = 0, j = 0; i < max_count/32; ++i, ++occupied_entry)
                {
                    unsigned mask = *occupied_entry;
                    for (unsigned k = 1; k; ++j, k <<= 1)
                    {
                        if ((mask & k) == 0)
                        {
                            *occupied_entry |= k;
                            pool[j] = object;
                            object->m_uid = j + handle_offset;
                            return j + handle_offset;
                        }
                    }
                }
                return 0;
            }

            void Detach(Object * object)
            {
                SceUID handle = object->m_uid;
                if (IsValid(handle))
                {
                    int i = handle - handle_offset;
                    occupied[i/32] &= ~(1<<(i&31));
                    object->m_uid = SCE_KERNEL_ERROR_UNKNOWN_UID;
                    pool[i] = 0;
                }
            }

            template< class T >
            void Detach(SceUID handle, bool exact = true)
            {
                T * object;
                if (!Get(handle, object, exact))
                {
                    int i = handle - handle_offset;
                    occupied[i/32] &= ~(1<<(i&31));
                    object->m_uid = SCE_KERNEL_ERROR_UNKNOWN_UID;
                    pool[i] = 0;
                }
            }

            template< class T >
            u32 Release(SceUID handle)
            {
                T * object;

                u32 error = Get(handle, object, true);

                if (!error)
                {
                    object->Delete(0);
                }

                return error;
            }

            bool IsValid(SceUID handle)
            {
                int index = handle - handle_offset;

                return (0 <= index) && (index < max_count) && (occupied[index/32] & (1<<(index&31)));
            }

            template< class T >
            u32 Get(SceUID handle, T *& t, bool exact = true)
            {
                u32 result = IsValid(handle) ? SCE_KERNEL_ERROR_OK : SCE_KERNEL_ERROR_UNKNOWN_UID;

                if (!result)
                {
                    t = static_cast<T *>(pool[handle - handle_offset]);
                    if (!t || !t->CheckType(T::m_object_type, exact))
                    {
                        result = u32(SCE_KERNEL_ERROR_UNMATCH_UID_TYPE);
                    }
                }

                return result;
            }

            template< class T >
            T * Get(SceUID handle, u32 & error)
            {
                T * t = 0;

                error = Get(handle, t);

                return t;
            }

            Object *& operator [](SceUID handle)
            {
                return pool[handle - handle_offset];
            }

            template< class T >
            void Clear(bool exact = true)
            {
                unsigned * occupied_entry = occupied;

                for (int i = 0, j = 0; i < max_count/32; ++i, ++occupied_entry)
                {
                    unsigned mask = *occupied_entry;
                    for (unsigned k = 1; k; ++j, k <<= 1)
                    {
                        if (mask & k)
                        {
                            T * object = static_cast<T *>(pool[j]);
                            if (object->CheckType(T::type, exact))
                            {
                                object->Delete(0);
                            }
                        }
                    }
                }
            }

            void ClearAll()
            {
                unsigned * occupied_entry = occupied;

                for (int i = 0, j = 0; i < max_count/32; ++i, ++occupied_entry)
                {
                    unsigned mask = *occupied_entry;
                    for (unsigned k = 1; k; ++j, k <<= 1)
                    {
                        if (mask & k)
                        {
                            pool[j]->Delete(0);
                        }
                    }
                }
            }

            template< class T >
            int Count(bool exact = true)
            {
                int        count          = 0;
                unsigned * occupied_entry = occupied;

                for (int i = 0, j = 0; i < max_count/32; ++i, ++occupied_entry)
                {
                    unsigned mask = *occupied_entry;
                    for (unsigned k = 1; k; ++j, k <<= 1)
                    {
                        if (mask & k)
                        {
                            T * object = static_cast<T *>(pool[j]);
                            if (object->CheckType(T::type, exact))
                            {
                                count++;
                            }
                        }
                    }
                }
                return count;
            }

            int CountAll()
            {
                int        count = 0;
                unsigned * occupied_entry = occupied;

                for (int i = 0; i < max_count/32; ++i, ++occupied_entry)
                {
                    unsigned mask = *occupied_entry;
                    for (unsigned k = 1; k; k <<= 1)
                    {
                        if (mask & k)
                        {
                            count++;
                        }
                    }
                }
                return count;
            }

            template< class T >
            T * Next(T * object = 0)
            {
                int index = object ? ((int)object->GetUid() - handle_offset + 1) : 0;

                object = 0;

                int      i = index/32;
                unsigned k = 1<<(index&31);
                unsigned * occupied_entry = occupied + i;

                for (int j = index; i < max_count/32; ++i, ++occupied_entry)
                {
                    unsigned mask = *occupied_entry;
                    while (k)
                    {
                        if (mask & k)
                        {
                            Object * pool_entry = pool[j];
                            if (pool_entry && pool_entry->CheckType(T::m_object_type, true))
                            {
                                object = static_cast<T *>(pool_entry);
                                break;
                            }
                        }
                        ++j;
                        k <<= 1;
                    }
                    k = 1;
                }

                return object;
            }

            template< class T, typename... A >
            void Iterate(bool f(T *, A...), A... arguments)
            {
                int index = 0;

                Object * object = 0;

                int      i = index/32;
                unsigned k = 1<<(index&31);
                unsigned * occupied_entry = occupied + i;

                for (int j = index; i < max_count/32; ++i, ++occupied_entry)
                {
                    unsigned mask = *occupied_entry;
                    while (k)
                    {
                        if (mask & k)
                        {
                            Object * pool_entry = pool[j];
                            if (pool_entry && pool_entry->CheckType(T::m_object_type, true))
                            {
                                object = static_cast<T *>(pool_entry);
                                if (!f(object, arguments))
                                {
                                    break;
                                }
                            }
                        }
                        ++j;
                        k <<= 1;
                    }
                    k = 1;
                }
            }

            void Dump();
        };

        extern ObjectPool Objects;
    }

    typedef kd::Object     KernelObject;
    typedef kd::ObjectPool KernelObjectPool;
}
