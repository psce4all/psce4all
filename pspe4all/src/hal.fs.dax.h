#ifndef hal_fs_dax_h__
#define hal_fs_dax_h__

#include "hal.fs.iso.h"

namespace hal
{
    namespace fs
    {
        namespace dax
        {
#pragma pack(push, 1)

            struct Header
            {
                u32 magic;
                u32 iso_size;
                u32 version;
                u32 ncareas;
                u32 reserved[4];
            };

            struct NCArea
            {
                u32 frame;
                u32 size;
            };

            struct Entry
            {
                u32 position;
                u16 length;
                u16 uncompressed;
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
                    if (!((Entry *)m_block_array)[index].uncompressed)
                    {
                        position = qint64(((Entry *)m_block_array)[index].position);
                        length = qint64(((Entry *)m_block_array)[index].length);

                        return true;
                    }

                    position = qint64(((Entry *)m_block_array)[index].position);
                    length = qint64(8192);

                    return false;
                }

                virtual qint64 DecompressBlock(QByteArray * buffer)
                {
                    qint64 result = -1LL;

                    z_stream stream;
                    stream.next_in = (Bytef    *)(buffer[1].data());
                    stream.avail_in = (uInt)(buffer[1].size());
                    stream.next_out = (Bytef    *)(buffer[0].data() + m_sector_offset);
                    stream.avail_out = (uInt)(buffer[0].capacity() - m_sector_offset);
                    stream.zalloc = (alloc_func)0;
                    stream.zfree = (free_func)0;

                    if (::inflateInit(&stream) == Z_OK)
                    {
                        if (::inflate(&stream, Z_FULL_FLUSH) == Z_STREAM_END)
                        {
                            buffer[0].resize(stream.total_out);
                            result = qint64(stream.total_out);
                        }

                        if (::inflateEnd(&stream) != Z_OK)
                        {
                            result = -1LL;
                        }
                    }

                    return result;
                }
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
                            result = header.magic == 0x00584144/*DAX\0*/ && header.version < 2;
                            if (result)
                            {
                                u32      block_count = (header.iso_size + 8191) / 8192;
                                Entry  * entries = __new Entry[block_count];
                                u32    * positions = __new u32[block_count];
                                u16    * lengths = __new u16[block_count];
                                NCArea * ncareas = 0;

                                result = read((char *)positions, block_count*sizeof(u32)) == block_count*sizeof(u32);

                                if (result)
                                {
                                    result = read((char *)lengths, block_count*sizeof(u16)) == block_count*sizeof(u16);

                                    if (result)
                                    {
                                        if (header.ncareas > 0)
                                        {
                                            ncareas = __new NCArea[header.ncareas];

                                            result = read((char *)ncareas, header.ncareas*sizeof(NCArea)) == header.ncareas*sizeof(NCArea);
                                        }

                                        if (result)
                                        {
                                            for (u32 i = 0; i < block_count; ++i)
                                            {
                                                entries[i].position = positions[i];
                                                entries[i].length = lengths[i];
                                                entries[i].uncompressed = false;

                                                for (u32 j = 0; j < header.ncareas; ++j)
                                                {
                                                    if (u32(i - ncareas[j].frame) < ncareas[j].size)
                                                    {
                                                        entries[i].uncompressed = true;
                                                        ncareas[j] = ncareas[--header.ncareas];
                                                        break;
                                                    }
                                                }
                                            }

                                            close();

                                            fs::dax::BlockMapping * mapping = __new fs::dax::BlockMapping;
                                            mapping->SetFileOffset(0);
                                            mapping->SetFileSize(header.iso_size);
                                            mapping->SetBlockArray(entries);
                                            mapping->SetBlockSize(8192);

                                            SetBlockMapping(mapping);

                                            block_mapping = mapping;

                                            if (fs::iso::Image::Load(block_mapping))
                                            {
                                                __delete[] ncareas;
                                                __delete[] lengths;
                                                __delete[] positions;

                                                return true;
                                            }

                                            block_mapping = 0;

                                            __delete mapping;
                                        }

                                        __delete[] ncareas;
                                        __delete[] lengths;
                                        __delete[] positions;

                                        return false;
                                    }
                                }

                                __delete[] ncareas;
                                __delete[] lengths;
                                __delete[] positions;
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

typedef hal::fs::dax::Image dax_Image;

#endif // hal_fs_dax_h__
