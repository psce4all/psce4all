#ifndef hal_fs_c7so_h__
#define hal_fs_c7so_h__

//#include "lzma.h"

#include "hal.fs.iso.h"

namespace hal
{
    namespace fs
    {
        namespace c7so
        {
#pragma pack(push, 1)

            struct Header
            {
                u32 magic;
                u32 header_size;
                u64 iso_size;
                u32 block_size;
                u8  version;
                u8  align;
                u16 pad;
            };

            struct Entry
            {
                u32 position : 31;
                u32 uncompressed : 1;
            };

#pragma pack(pop)

            struct BlockMapping : fs::iso::BlockMapping
            {
                BlockMapping() : fs::iso::BlockMapping()
                {
                }

                virtual ~BlockMapping()
                {
                    __delete[]((Entry *)m_block_array);
                }

                virtual bool CompressedBlock(u32 index, qint64 & position, qint64 & length)
                {
                    position = (qint64(((Entry *)m_block_array)[index + 0].position) << m_block_shift);
                    length = (qint64(((Entry *)m_block_array)[index + 1].position) << m_block_shift) - position;
                    return                !((Entry *)m_block_array)[index + 0].uncompressed;
                }

                virtual qint64 DecompressBlock(QByteArray * buffer)
                {
                    qint64 result = -1LL;

                    lzma_stream stream = LZMA_STREAM_INIT;

                    if (::lzma_auto_decoder(&stream, UINT64_MAX, 0) == LZMA_OK)
                    {
                        stream.next_in = (uint8_t *)(buffer[1].data());
                        stream.avail_in = (size_t)(buffer[1].size());
                        stream.next_out = (uint8_t *)(buffer[0].data() + m_sector_offset);
                        stream.avail_out = (size_t)(buffer[0].capacity() - m_sector_offset);

                        if (::lzma_code(&stream, LZMA_FINISH) == LZMA_STREAM_END)
                        {
                            buffer[0].resize(stream.total_out);
                            result = qint64(stream.total_out);
                        }

                        ::lzma_end(&stream);
                    }

                    return result;
                }

                void SetBlockShift(u32 block_shift)
                {
                    m_block_shift = block_shift;
                }

                u32 m_block_shift;
            };

            class Image : public fs::iso::Image
            {
            public:
                Image(String const & filename) : fs::iso::Image(filename)
                {
                }

                bool Load(fs::iso::BlockMapping * & block_mapping)
                {
                    Header header;

                    bool result = open(QIODevice::ReadOnly);
                    if (result)
                    {
                        result = read((char *)&header, sizeof(header)) == sizeof(header);
                        if (result)
                        {
                            result = header.magic == 0x4F533743/*C7SO*/ && header.version == 1;
                            if (result)
                            {
                                u32     block_shift = header.align;
                                u32     block_count = (header.iso_size + header.block_size - 1) / header.block_size;
                                Entry * entries = __new Entry[block_count + 1];

                                if (read((char *)entries, (block_count + 1)*sizeof(Entry)))
                                {
                                    close();

                                    fs::c7so::BlockMapping * mapping = __new fs::c7so::BlockMapping;
                                    mapping->SetFileOffset(0);
                                    mapping->SetFileSize(header.iso_size);
                                    mapping->SetBlockArray(entries);
                                    mapping->SetBlockSize(header.block_size);
                                    mapping->SetBlockShift(block_shift);

                                    SetBlockMapping(mapping);

                                    block_mapping = mapping;

                                    if (fs::iso::Image::Load(block_mapping))
                                    {
                                        return true;
                                    }

                                    block_mapping = 0;

                                    __delete mapping;

                                    return false;
                                }

                                __delete[] entries;
                            }

                            close();
                        }
                    }
                    return result;
                }
            };
        }
    }
}

typedef hal::fs::c7so::Image c7so_Image;

#endif // hal_fs_c7so_h__
