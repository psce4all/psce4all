#ifndef hal_fs_iso_h__
#define hal_fs_iso_h__

//#include "common/common_Thread.h"

#include "hal.String.h"

namespace hal
{
    namespace fs
    {
        namespace iso
        {
            struct BlockMapping
            {
                qint64                      m_file_offset;
                qint64                      m_file_size;
                void                      * m_block_array;
                u32                         m_block_size;
                u32                         m_sector_offset;
                u32                         m_sector_size;
                QCache< u32, QByteArray >   m_cache;
                CriticalSection mutable     m_critical_section;

                BlockMapping() : m_file_offset(0), m_file_size(0), m_block_array(0), m_block_size(0), m_sector_offset(0), m_sector_size(2048), m_cache(64)
                {
                }

                virtual ~BlockMapping()
                {
                }

                void SetFileOffset(qint64 offset)
                {
                    m_file_offset = offset;
                }

                quint64 GetFileOffset() const
                {
                    return m_file_offset;
                }

                void SetFileSize(qint64 length)
                {
                    m_file_size = length;
                }

                qint64 GetFileSize() const
                {
                    return m_file_size;
                }

                void SetBlockSize(u32 size, QByteArray * buffer = 0)
                {
                    m_block_size = size;
                    if (buffer) buffer[0].reserve(size);
                }

                qint64 GetBlockSize() const
                {
                    return m_block_size;
                }

                void SetBlockArray(void * block_array)
                {
                    m_block_array = block_array;
                }

                void * GetBlockArray() const
                {
                    return m_block_array;
                }

                void SetSectorOffset(qint64 offset)
                {
                    m_sector_offset = offset;
                }

                quint64 GetSectorOffset() const
                {
                    return m_sector_offset;
                }

                void SetSectorSize(u32 size)
                {
                    m_sector_size = size;
                }

                qint64 GetSectorSize() const
                {
                    return m_sector_size;
                }

                void ClearCache()
                {
                    CriticalSectionScope scope(m_critical_section);

                    m_cache.clear();
                }

                QByteArray * GetCachedSector(u32 index) const
                {
                    CriticalSectionScope scope(m_critical_section);

                    return m_cache[index];
                }

                QByteArray * NewCachedSector(u32 index, QByteArray const & buffer)
                {
                    QByteArray * result = __new QByteArray(buffer);

                    CriticalSectionScope scope(m_critical_section);

                    m_cache.insert(index, result);

                    return result;
                }

                virtual bool CompressedBlock(u32 index, qint64 & position, qint64 & length)
                {
                    position = qint64(m_block_size) * index;
                    length = qint64(m_block_size);

                    return false;
                }

                virtual qint64 DecompressBlock(QByteArray * /*buffer*/)
                {
                    // MUST BE REIMPLEMENTED in the derived class !
                    return -1LL;
                }
            };

            class File : public QIODevice
            {
                using QIODevice::peek; // no internal buffer please ! that bastard kinda enforces buffer operation even with Unbuffered mode so don't use
                using QIODevice::ungetChar;

            public:
                File() : m_block_mapping(0), m_block_unit(1ULL)
                {
                }

                File(const String & filename) : m_block_mapping(0), m_block_unit(1ULL)
                {
                    m_file.setFileName(filename);
                }

                File(QObject * parent) : QIODevice(parent), m_block_mapping(0), m_block_unit(1ULL)
                {
                }

                File(const String & filename, QObject * parent) : QIODevice(parent), m_block_mapping(0), m_block_unit(1ULL)
                {
                    m_file.setFileName(filename);
                }

                void SetFilename(const String & filename)
                {
                    m_file.setFileName(filename);
                }

                String GetFilename()
                {
                    return m_file.fileName();
                }

                void SetBlockMapping(BlockMapping * block_mapping)
                {
                    m_block_mapping = block_mapping;
                    if (block_mapping)
                    {
                        m_buffer[0].reserve(block_mapping->GetBlockSize() + block_mapping->GetSectorOffset());
                        m_buffer[1].reserve(block_mapping->GetBlockSize() * 2);
                    }
                }

                BlockMapping * GetBlockMapping() const
                {
                    return m_block_mapping;
                }

                void SetBlockUnit(qint64 block_unit)
                {
                    m_block_unit = block_unit;
                }

                qint64 GetBlockUnit() const
                {
                    return m_block_unit;
                }

                virtual bool open(QIODevice::OpenMode /*mode*/)
                {
                    bool result = isOpen();
                    if (!result)
                    {
                        result = m_file.open(ReadOnly | Unbuffered); // no internal buffer please !
                        if (result)
                        {
                            result = QIODevice::open(ReadOnly | Unbuffered); // no internal buffer please !
                            if (result)
                            {
                                if (m_block_mapping)
                                {
                                    m_block_mapping->ClearCache();
                                }
                                result = QIODevice::seek(0LL);
                            }
                        }
                    }
                    return result;
                }

                virtual void close()
                {
                    if (isOpen())
                    {
                        m_file.close();
                    }

                    QIODevice::close();
                }

                virtual bool atEnd() const
                {
                    if (!m_block_mapping)
                    {
                        return m_file.atEnd();
                    }

                    return QIODevice::atEnd();
                }

                virtual qint64 bytesAvailable() const
                {
                    if (!m_block_mapping)
                    {
                        return (m_file.bytesAvailable() + m_block_unit - 1) / m_block_unit;
                    }

                    return qMax(size() - pos(), qint64(0));
                }

                virtual bool reset()
                {
                    if (!m_block_mapping)
                    {
                        return m_file.reset();
                    }

                    m_block_mapping->ClearCache();

                    return m_file.reset() && QIODevice::seek(0);
                }

                virtual qint64 size() const
                {
                    if (!m_block_mapping)
                    {
                        return (m_file.size() + m_block_unit - 1) / m_block_unit;
                    }

                    return (m_block_mapping->GetFileSize() + m_block_unit - 1) / m_block_unit;
                }

                virtual qint64 pos() const
                {
                    if (!m_block_mapping)
                    {
                        return m_file.pos() / m_block_unit;
                    }

                    return QIODevice::pos();
                }

                virtual bool seek(qint64 pos)
                {
                    if (!m_block_mapping)
                    {
                        return m_file.seek(pos * m_block_unit);
                    }

                    return QIODevice::seek(pos);
                }

            protected:
                virtual qint64 readData(char *data, qint64 maxSize)
                {
                    qint64 n = 0LL;

                    if (maxSize < 0LL)
                    {
                        return -1LL;
                    }

                    if (!m_block_mapping)
                    {
                        n = m_file.read(data, maxSize * m_block_unit);

                        return qMax((n + m_block_unit - 1) / m_block_unit, -1LL);
                    }

                    qint64 x = QIODevice::pos() * m_block_unit;

                    maxSize = qMax(qMin(maxSize, size() - x), 0LL);

                    while (maxSize)
                    {
                        u32 i = u32(x / m_block_mapping->GetSectorSize());
                        u32 d = u32(x % m_block_mapping->GetSectorSize());

                        qint64 m = maxSize;

                        QByteArray * buffer = m_block_mapping->GetCachedSector(i);
                        if (!buffer)
                        {
                            qint64 p;
                            qint64 l;
                            bool   c = m_block_mapping->CompressedBlock((i * m_block_mapping->GetSectorSize()) / m_block_mapping->GetBlockSize(), p, l);

                            m = -1LL;

                            if (m_file.seek(m_block_mapping->GetFileOffset() + p))
                            {
                                if (c) // compressed block (supposedly we have l < m_block_size)
                                {
                                    m_buffer[1].resize(l);

                                    if (m_file.read(m_buffer[1].data() + m_block_mapping->GetSectorOffset(), l) < 0)
                                    {
                                        return -1;
                                    }

                                    m = m_block_mapping->DecompressBlock(m_buffer);
                                }
                                else // uncompressed block
                                {
                                    m = m_file.read(m_buffer[0].data() + m_block_mapping->GetSectorOffset(), l);
                                }

                                if (m > 0LL)
                                {
                                    u32 sector_size = m_block_mapping->GetSectorSize();
                                    u32 sectors_per_block = m_block_mapping->GetBlockSize() / sector_size;
                                    u32 sector_index = i - (i % sectors_per_block);

                                    for (u32 j = 0, k; j < sectors_per_block; ++j, ++sector_index)
                                    {
                                        k = j * sector_size;
                                        if (k < u32(m))
                                        {
                                            QByteArray * cached = m_block_mapping->NewCachedSector(sector_index, m_buffer[0].mid(k, sector_size));
                                            if (i == sector_index)
                                            {
                                                buffer = cached;
                                            }
                                        }
                                    }
                                }
                            }

                            if (m < 0LL)
                            {
                                return -1LL;
                            }
                        }

                        if (m == 0LL)
                        {
                            break;
                        }

                        m = qMin(qMin(maxSize, m), m_block_mapping->GetSectorSize() - qint64(d));
                        ::memcpy(data, buffer->data() + m_block_mapping->GetSectorOffset() + d, m);

                        n += m;
                        maxSize -= m;
                        x += m;
                        data += u32(m);
                    }

                    return (n + m_block_unit - 1) / m_block_unit;
                }

                virtual qint64 writeData(const char * /*data*/, qint64 /*maxSize*/)
                {
                    return 0;
                }

            private:
                BlockMapping              * m_block_mapping;
                qint64                      m_block_unit;
                QFile                       m_file;
                QByteArray                  m_buffer[2];
            };


#pragma pack(push, 1)

            struct u16b
            {
                u16 l;
                u16 b;

                operator u16() const
                {
                    return l;
                }
            };

            struct u32b
            {
                u32 l;
                u32 b;

                operator u32() const
                {
                    return l;
                }
            };

            // 8.4.26 Volume Creation Date and Time (BP 814 to 830)
            struct DateTime
            {
                union
                {
                    struct
                    {
                        s8 year[4];
                        s8 month[2];
                        s8 day[2];
                        s8 hour[2];
                        s8 minute[2];
                        s8 second[2];
                        s8 hsecond[2];
                        s8 offset;
                    };

                    u8     pad[17];
                };

                operator QDateTime() const
                {
                    return QDateTime(QDate(int(year[0] - '0') * 1000 + int(year  [1] - '0') * 100 + int(year  [2] - '0') * 10 + int(year  [3] - '0'),
                        /**/                                                                        int(month [0] - '0') * 10 + int(month [1] - '0'),
                        /**/                                                                        int(day   [0] - '0') * 10 + int(day   [1] - '0')),
                        /**/         QTime(int(hour[0] - '0') * 10   + int(hour  [1] - '0'),
                        /**/                                                                        int(minute[0] - '0') * 10 + int(minute[1] - '0'),
                        /**/                                                                        int(second[0] - '0') * 10 + int(second[1] - '0'),
                        /**/                                           int(second[0] - '0') * 100 + int(second[1] - '0') * 10));
                }
            };

            struct DirectoryRecord
            {
                /// 9.1.5 Recording Date and Time (BP 19 to 25)
                struct DateTime
                {
                    u8 year;
                    u8 month;
                    u8 day;
                    u8 hour;
                    u8 minute;
                    u8 second;
                    s8 offset;

                    operator QDateTime() const
                    {
                        return QDateTime(QDate(int(year) + 1900,
                            /**/               int(month),
                            /**/               int(day)),
                            /**/         QTime(int(hour),
                            /**/               int(minute),
                            /**/               int(second)));
                    }
                };

                enum FlagsEnum
                {
                    Existence = 1 << 0,
                    Directory = 1 << 1,
                    AssociatedFile = 1 << 2,
                    Record = 1 << 3,
                    Protection = 1 << 4,
                    Reserved5 = 1 << 5,
                    Reserved6 = 1 << 6,
                    MultiExtent = 1 << 7,
                };

                u8         length;
                u8         extended_attribute_length;
                u32b       extent;
                u32b       size;
                DateTime   date_time;
                u8         flags;
                u8         file_unit_size;
                u8         interleave;
                u16b       volume_sequence_number;
                u8         name_length;

                bool isDirectory() const { return flags & Directory; }
            };

            // 8 Volume Descriptors
            struct VolumeDescriptorHeader
            {
                enum Type
                {
                    BootRecord = 0x00, // 8.2 Boot Record
                    VolumePartitionSetTerminator = 0xFF, // 8.3 Volume Descriptor Set Terminator
                    PrimaryVolumeDescriptor = 0x01, // 8.4 Primary Volume Descriptor
                    SupplementaryVolumeDescriptor = 0x02, // 8.5 Supplementary Volume Descriptor
                    VolumePartitionDescriptor = 0x03  // 8.6 Volume Partition Descriptor
                };

                u8 type;
                u8 id[5];
                u8 version;
            };

            // 8.4 Primary Volume Descriptor
            struct PrimaryVolumeDescriptor
            {
                VolumeDescriptorHeader  header;
                u8                      pad1[1];
                u8                      system_id[32];
                u8                      volume_id[32];
                u8                      pad2[8];
                u32b                    volume_space_size;
                u8                      pad3[32];
                u32                     volume_set_size;
                u32                     volume_sequence_number;
                u16b                    logical_block_size;
                u32b                    path_table_size;
                u32                     type_L_path_table;
                u32                     type_L_path_table_opt;
                u32                     type_M_path_table;
                u32                     type_M_path_table_opt;
                DirectoryRecord         directory_record;
                u8                      pad4[1];
                u8                      volume_set_identifier[128];
                u8                      publisher_id[128];
                u8                      preparer_id[128];
                u8                      application_id[128];
                u8                      copyright_file_id[37];
                u8                      abstract_file_id[37];
                u8                      bibliographic_file_id[37];
                DateTime                volume_creation_datetime;
                DateTime                volume_modification_datetime;
                DateTime                volume_expiration_datetime;
                DateTime                volume_effective_datetime;
                u8                      file_structure_version;
                u8                      pad5[1];
                u8                      application_use[512];
                u8                      pad6[653];
            };

#pragma pack(pop)

            class Node
            {
            public:
                DirectoryRecord directory_record;
                String          name;
                String          fullname;

                Node(DirectoryRecord const & directory_record, String const & name, Node const * parent) : directory_record(directory_record), name(name)
                {
                    if (parent)
                    {
                        fullname = parent->fullname + "/" + name;
                    }
                    else
                    {
                        fullname = name;
                    }
                }
            };

            typedef QList< Node > NodeList;

            class Image : public File
            {
                u32         m_sector_size;
                NodeList    m_entries;
                QDateTime   m_ctime;

                void ProcessDirectoryRecord(Node const & parent)
                {
                    u64 directory_start = u64(parent.directory_record.extent.l * m_sector_size);
                    u64 directory_length = u64(parent.directory_record.size.l);

                    QList< Node > childs;

                    if (directory_length)
                    {
                        File directory_handle(GetFilename());

                        directory_handle.SetBlockMapping(GetBlockMapping());

                        if (directory_handle.open(QIODevice::ReadOnly) && directory_handle.seek(directory_start))
                        {
                            while (directory_handle.pos() - directory_start < directory_length)
                            {
                                QByteArray record = directory_handle.read(1);

                                if (record.size() == 1)
                                {
                                    u8 length = record[0];

                                    if (!length)
                                    {
                                        directory_handle.seek((directory_handle.pos() + m_sector_size) & u32(-s32(m_sector_size)));
                                        continue;
                                    }

                                    record.append(directory_handle.read(length - 1));

                                    if (record.size() == length)
                                    {
                                        String           name;
                                        DirectoryRecord & directory_record = *((DirectoryRecord *)record.data());

                                        if (directory_record.name_length)
                                        {
                                            if (directory_record.name_length == 1 && u32(*(record.data() + 33)) < 2)
                                            {
                                                continue;
                                            }

                                            name = String::fromUtf8(record.data() + 33, directory_record.name_length);

                                            Node info(directory_record, name, &parent);

                                            childs.append(info);
                                            m_entries.append(info);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    foreach(Node const & child, childs)
                    {
                        if (child.directory_record.flags & DirectoryRecord::Directory)
                        {
                            ProcessDirectoryRecord(child);
                        }
                    }
                }

            public:
                Image(String const & filename) : File(filename), m_sector_size(0)
                {
                }

                virtual bool Load(fs::iso::BlockMapping *& block_mapping)
                {
                    struct Format
                    {
                        u32 block_size;
                        u32 block_offset;
                        u32 file_offset;
                    };

                    static Format format[] =
                    {
                        // .iso
                        { 2048, 24, 0 },
                        { 2336, 16, 0 },
                        { 2352, 0, 0 },
                        { 2448, 0, 0 },

                        // ???
                        { 2048, 24, -8 },
                        { 2336, 16, -8 },
                        { 2352, 0, -8 },
                        { 2448, 0, -8 },

                        // .nrg
                        { 2048, 24, 307200 },
                        { 2336, 16, 307200 },
                        { 2352, 0, 307200 },
                        { 2448, 0, 307200 },

                        { 0, 0, 0 }
                    };

                    bool           result = false;
                    BlockMapping * mapping = 0;

                    for (u32 i = 0; format[i].block_size; ++i)
                    {
                        if (i > 0) // real UMD image when i == 0, so no block mapping to get faster access
                        {
                            if (block_mapping) // .CSO/.DAX are always a compressed UMD image (2048,24,0), so no need to proceed further
                            {
                                break;
                            }
                            else if (!mapping)
                            {
                                mapping = __new BlockMapping;
                            }

                            mapping->SetSectorOffset(format[i].block_offset);
                            mapping->SetBlockSize(format[i].block_size);
                            mapping->SetFileOffset(format[i].file_offset);
                            mapping->SetSectorSize(format[i].block_size);
                        }

                        result = open(QIODevice::ReadOnly);

                        if (result)
                        {
                            m_sector_size = format[i].block_size;

                            result = seek(m_sector_size * 16);
                            if (result)
                            {
                                PrimaryVolumeDescriptor primary_volume_descriptor;

                                result = read((char *)&primary_volume_descriptor, sizeof(primary_volume_descriptor)) == sizeof(primary_volume_descriptor);
                                if (result)
                                {
                                    if (primary_volume_descriptor.header.type == 1 && !::memcmp(primary_volume_descriptor.header.id, "CD001", 5))
                                    {
                                        m_ctime = primary_volume_descriptor.volume_creation_datetime;

                                        ProcessDirectoryRecord(Node(primary_volume_descriptor.directory_record, "", 0));

                                        close();

                                        break;
                                    }
                                    else
                                    {
                                        result = false;
                                    }
                                }
                            }
                        }

                        close();
                    }

                    if (result && !block_mapping)
                    {
                        block_mapping = mapping;
                    }
                    else if (!block_mapping)
                    {
                        __delete mapping;
                    }

                    return result;
                }

                NodeList & GetNodeList()
                {
                    return m_entries;
                }

                QDateTime & GetCreationDateTime()
                {
                    return m_ctime;
                }

                u32 GetSectorSize() const
                {
                    return m_sector_size;
                }
            };
        }
    }
}

typedef hal::fs::iso::Image iso_File;
typedef hal::fs::iso::Image iso_Image;
typedef hal::fs::iso::Node  iso_Node;

#endif // hal_fs_iso_h__
