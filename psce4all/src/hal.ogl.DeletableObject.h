#ifndef hal_ogl_DeletableObject_h__
#define hal_ogl_DeletableObject_h__

#include "hal.ogl.Core.h"

namespace hal
{
    namespace ogl
    {
        class DeletableObject : protected Core
        {
        public:
            DeletableObject() : m_id(0), m_deletable(false)
            {
            }

            DeletableObject(GLuint id) : m_id(id), m_deletable(false)
            {
            }

            ~DeletableObject()
            {
                assert(("Object is not deleted", (!m_deletable || m_id == 0)));
            }

            template< typename LambdaFunction >
            __forceinline void AssertCreate(LambdaFunction & lambda)
            {
                assert(("Object is already created", (m_id == 0)));

                lambda(this);

                m_deletable = true;
            }

            template< typename LambdaFunction >
            __forceinline void AssertDelete(LambdaFunction & lambda)
            {
                assert(("Object is already deleted or not deletable", (m_deletable && m_id != 0)));

                lambda(this);

                m_id = 0;
                m_deletable = false;
            }

            __forceinline GLuint Id() const { return m_id; }

            __forceinline bool   Deletable() const { return m_deletable; }

            GLuint      m_id;
            bool        m_deletable;
        };
    }
}


#endif // hal_ogl_DeletableObject_h__
