#ifndef hal_fs_SliceHandle_h__
#define hal_fs_SliceHandle_h__

namespace hal
{
    namespace fs
    {
        template< typename FileHandle, typename RealDevice >
        class SliceFileHandle : public FileHandle
        {
        public:
            SliceFileHandle(qint64 offset = 0, qint64 length = 0)
            {
                m_offset = offset;
                m_length = length;
            }

            SliceFileHandle(QObject * parent, qint64 start = 0, qint64 length = 0) : Device(parent)
            {
                m_offset = offset;
                m_length = length;
            }

            void SetRange(qint64 offset, qint64 length)
            {
                m_offset = offset;
                m_length = length;

                reset();
            }

            virtual ~SliceFileHandle()
            {
                close();
            }

            RealDevice * device()
            {
                return &m_device;
            }

            virtual bool open(QIODevice::OpenMode mode)
            {
                bool result = isOpen();
                if (!result)
                {
                    result = m_device.open(mode);
                    if (result)
                    {
                        result = QIODevice::open(mode);
                        if (result)
                        {
                            result = seek(0);
                        }
                    }
                }
                return result;
            }

            virtual void close()
            {
                if (isOpen())
                {
                    m_device.close();
                }

                QIODevice::close();
            }

            virtual bool atEnd() const
            {
                return !isOpen() || (pos() >= m_length) || !bytesAvailable();
            }

            virtual qint64 bytesAvailable() const
            {
                qint64 result = qMax(m_device.bytesAvailable() - m_offset, qint64(0));
                return (result <= m_length) ? result : m_length;
            }

            virtual qint64 bytesToWrite() const
            {
                qint64 result = m_device.bytesToWrite() - m_offset;
                return ((result <= m_length) ? result : m_length);
            }

            virtual bool reset()
            {
                return m_device.reset() && seek(0);
            }

            virtual bool seek(qint64 pos)
            {
                return m_device.seek(m_offset + pos) && QIODevice::seek(pos);
            }

            virtual qint64 size() const
            {
                return m_length;
            }

        protected:
            virtual qint64 readData(char *data, qint64 maxSize)
            {
                qint64 result = size() - pos();
                return m_device.read(data, (result < maxSize) ? result : maxSize);
            }

            virtual qint64 writeData(const char *data, qint64 maxSize)
            {
                qint64 result = size() - pos();
                return m_device.write(data, (result < maxSize) ? result : maxSize);
            }

        private:
            qint64                              m_offset;
            qint64                              m_length;
            RealDevice                          m_device;
        };
    }
}

#endif // hal_fs_SliceHandle_h__
