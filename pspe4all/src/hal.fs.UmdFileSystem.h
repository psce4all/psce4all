#ifndef hal_fs_UmdFileSystem_h__
#define hal_fs_UmdFileSystem_h__

//#include "kernel_Types.h"

#include "hal.fs.VirtualFileSystem.h"
#include "hal.fs.SliceFileHandle.h"

#include "hal.fs.iso.h"
#include "hal.fs.cso.h"
#include "hal.fs.7so.h"
#include "hal.fs.dax.h"

namespace hal
{
    namespace fs
    {
        enum UmdType
        {
            UmdTypeNone,
            UmdTypeISO,
            UmdTypeCSO,
            UmdType7SO,
            UmdTypeDAX,
        };

        typedef SliceFileHandle< FileHandle, iso::File > UmdSliceFileHandle;

        class UmdFileHandle : public UmdSliceFileHandle, public hal::heap::Allocator< UmdFileHandle >
        {
        public:
            UmdFileHandle(VirtualFileSystem * vfs, fs::iso::BlockMapping * block_mapping, String const & filename, u64 offset, u64 length, u64 block_unit)
            {
                new(((VirtualFileSystemSlot *)this) - 1) VirtualFileSystemSlot(vfs);
                device()->SetFilename(filename);
                device()->SetBlockMapping(block_mapping);
                device()->SetBlockUnit(qint64(block_unit));
                SetRange(qint64(offset), qint64(length));
            }

            static QIODevice::OpenMode ConvertFileOpenMode(FileOpenMode flags)
            {
                QIODevice::OpenMode result(QIODevice::NotOpen);

                if (flags & In)
                {
                    result |= QIODevice::ReadOnly;
                }

                return result;
            }

            __forceinline void * operator new (size_t, void * p) { return p; }
        };

        class UmdDirHandle : public DirHandle, public hal::heap::Allocator< UmdDirHandle >
        {
        public:
            QList< DirEntry > entries;
            int               index;

            UmdDirHandle(VirtualFileSystem * vfs, QList< DirEntry > const & entries) : DirHandle(vfs), entries(entries), index(0)
            {
            }

            int ReadEntry(DirEntry & entry)
            {
                if (index < entries.length())
                {
                    entry = entries[index++];

                    return index;
                }

                return 0;
            }
        };

        class UmdFileSystem : public VirtualFileSystem, public hal::heap::Allocator< UmdFileSystem >
        {
            friend class IsoFileHandle;
            friend class UmdDirHandle;

        private:
            struct Entry
            {
                FileStat                stat;
                String                 name;
                String                 fullname;
                QHash< String, Entry > entries;

                Entry()
                {
                    stat.permissions = AllAccess & ~(OtherWrite | GroupWrite | UserWrite);
                    stat.is_dir = true;
                    stat.is_root = false;
                    stat.is_link = false;
                    stat.size = 0;
                    stat.sector_offset = 0;
                    stat.sector_size = 0;
                }

                void Clear()
                {
                    stat.permissions = AllAccess & ~(OtherWrite | GroupWrite | UserWrite);
                    stat.is_dir = true;
                    stat.is_root = false;
                    stat.is_link = false;
                    stat.size = 0;
                    stat.sector_offset = 0;
                    stat.sector_size = 0;

                    entries.clear();
                }

                void Mount(StringList & keys, iso_Node const & node, u32 sector_size)
                {
                    Entry   * entry = this;
                    String   fullname = keys.join(L'/');
                    String   key;

                    while (!keys.empty())
                    {
                        key = keys.front();
                        keys.pop_front();
                        entry = &(entry->entries[key]);
                    }

                    entry->name = key;
                    entry->fullname = fullname;
                    entry->stat.is_dir = node.directory_record.isDirectory();
                    entry->stat.sector_offset = node.directory_record.extent;
                    entry->stat.sector_size = sector_size;
                    entry->stat.size = node.directory_record.size;
                    entry->stat.ctime = node.directory_record.date_time;
                    entry->stat.mtime = entry->stat.ctime;
                    entry->stat.atime = entry->stat.ctime;
                    entry->stat.opaque[0] = node.directory_record.extent;
                }

                bool Lookup(StringList & keys, Entry *& result)
                {
                    Entry * entry = this;

                    while (!keys.empty())
                    {
                        String key(keys.front());
                        keys.pop_front();

                        if (entry->entries.contains(key))
                        {
                            entry = &(entry->entries[key]);
                        }
                        else
                        {
                            return false;
                        }
                    }

                    result = entry;

                    return true;
                }

                bool Lookup(StringList & keys, QList< DirEntry > & result)
                {
                    Entry * entry = this;

                    while (!keys.empty())
                    {
                        String key(keys.front());
                        keys.pop_front();

                        auto i = entry->entries.find(key);
                        if (i != entry->entries.end())
                        {
                            entry = &(*i);
                        }
                        else
                        {
                            return false;
                        }
                    }

                    if (entry->stat.is_dir && !entry->entries.isEmpty())
                    {
                        for (auto i = entry->entries.begin(); i != entry->entries.end(); ++i)
                        {
                            Entry const & value = i->second;

                            DirEntry info;
                            info.name = value.name;
                            info.stat = value.stat;
                            result.append(info);
                        }

                        return true;
                    }

                    return false;
                }
            };

        protected:
            Entry               m_root;
            String              m_umdname;
            UmdType             m_umdtype;
            u32                 m_sector_size;
            iso::BlockMapping * m_block_mapping;

            void Reload()
            {
                m_root.Clear();

                delete m_block_mapping;

                m_block_mapping = 0;

                ciso_Image ciso_image(m_umdname);
                c7so_Image c7so_image(m_umdname);
                dax_Image  dax_image(m_umdname);
                iso_Image  iso_image(m_umdname);

                iso_Image * image;

                if (ciso_image.Load(m_block_mapping) && m_block_mapping)
                {
                    image = &ciso_image;
                    m_umdtype = UmdTypeCSO;
                }
                else if (c7so_image.Load(m_block_mapping) && m_block_mapping)
                {
                    image = &c7so_image;
                    m_umdtype = UmdType7SO;
                }
                else if (dax_image.Load(m_block_mapping) && m_block_mapping)
                {
                    image = &dax_image;
                    m_umdtype = UmdTypeDAX;
                }
                else if (iso_image.Load(m_block_mapping))
                {
                    image = &iso_image;
                    m_umdtype = UmdTypeISO;
                }
                else
                {
                    m_umdtype = UmdTypeNone;
                    return;
                }

                m_sector_size = image->GetSectorSize();

                m_root.stat.sector_size = m_sector_size;
                m_root.stat.size = m_block_mapping ? m_block_mapping->GetFileSize() : image->size();
                m_root.stat.ctime = image->GetCreationDateTime();
                m_root.stat.mtime = image->GetCreationDateTime();
                m_root.stat.atime = image->GetCreationDateTime();
                m_root.stat.opaque[0] = 0;

                foreach(iso_Node const & entry, image->GetNodeList())
                {
                    QStringList keys(entry.fullname.split(QChar('/'), String::SkipEmptyParts));
                    m_root.Mount(keys, entry, image->GetSectorSize());
                }
            }

        public:
            UmdFileSystem(VirtualFileSystem * parent, String const & isopath) : VirtualFileSystem(parent), m_umdname(QDir::cleanPath(isopath)), m_block_mapping(0)
            {
                Reload();
            }

            ~UmdFileSystem()
            {
                __delete m_block_mapping;
            }

            String GetDiscId()
            {
                QByteArray data(ReadAll("UMD_DATA.BIN").split('|').first());

                return String::fromUtf8(data.constData()).trimmed().remove(QChar('-'));
            }

            UmdType GetType() const
            {
                return m_umdtype;
            }

            FileHandle * Open(String const & name, FileOpenMode flags, FileAccessMode /*mode*/)
            {
                StringList  keys(name.split(L'/', String::SkipEmptyParts));
                Entry     * result;
                u64         offset = 0ULL;
                u64         length = 0ULL;
                u64         block_unit = 1ULL;
                int         wrong_name = 2;

                if (!name.size())
                {
                    offset = u64(0);
                    length = u64(m_root.stat.size);
                    block_unit = u64(m_root.stat.sector_size);
                    wrong_name = 0;
                }

                if (wrong_name && name.startsWith("sce_"))
                {
                    StringList parts(name.mid(4).split(L'_'));

                    for (String const & part : parts)
                    {
                        if (part.startsWith("lbn"))
                        {
                            offset = part.mid(3).toULongLong(0, 16)*m_sector_size;
                            wrong_name--;
                        }
                        else if (part.startsWith("size"))
                        {
                            length = part.mid(4).toULongLong(0, 16);
                            wrong_name--;
                        }
                    }
                }

                if (wrong_name && m_root.Lookup(keys, result) && !result->stat.is_dir)
                {
                    offset = u64(result->stat.sector_offset*result->stat.sector_size);
                    length = u64(result->stat.size);
                    wrong_name = 0;
                }

                if (!wrong_name)
                {
                    switch (m_umdtype)
                    {
                        case UmdTypeISO:
                        case UmdTypeCSO:
                        case UmdType7SO:
                        case UmdTypeDAX:
                        {
                            UmdFileHandle * handle = new UmdFileHandle(this, m_block_mapping, m_umdname, offset, length, block_unit);

                            if (handle->open(UmdFileHandle::ConvertFileOpenMode(flags)))
                            {
                                return handle;
                            }

                            delete handle;

                            break;
                        }
                    }
                }

                return 0;
            }

            void Close(FileHandle * handle)
            {
                delete handle;
            }

            int Ioctl(FileHandle * /*handle*/, u32 /*cmd*/, u32 /*argp*/, u32 /*argl*/, u32 /*outp*/, u32 /*outl*/)
            {
                return -1;
            }

            bool Remove(String const &)
            {
                return false;
            }

            bool Rename(String const &, String const &)
            {
                return false;
            }

            bool Mkdir(String const &, FileAccessMode)
            {
                return false;
            }

            bool Rmdir(String const &)
            {
                return false;
            }

            bool Chdir(String const & name)
            {
                StringList   keys(name.split(L'/', String::SkipEmptyParts));
                Entry      * result;

                return m_root.Lookup(keys, result) && result->stat.is_dir;
            }

            DirHandle * Dopen(String const & name)
            {
                StringList        keys(name.split(L'/', String::SkipEmptyParts));
                QList< DirEntry > result;

                return m_root.Lookup(keys, result) ? __new UmdDirHandle(this, result) : 0;
            }

            void Dclose(DirHandle * handle)
            {
                delete handle;
            }

            int Dread(DirHandle * handle, DirEntry & entry)
            {
                if (handle)
                {
                    return handle->ReadEntry(entry);
                }

                return -1;
            }

            bool Getstat(String const & name, FileStat & stat)
            {
                StringList keys(name.split(L'/', String::SkipEmptyParts));
                Entry     * result;

                if (m_root.Lookup(keys, result))
                {
                    stat = result->stat;

                    return true;
                }

                return false;
            }

            int Devctl(String const & /*name*/, u32 /*cmd*/, u32 /*argp*/, u32 /*argl*/, u32 /*outp*/, u32 /*outl*/)
            {
                return -1;
            }

            String toString() const { return Stringf("IsoFileSystem(\"%ws\")", m_umdname.data()); }
        };
    }
}

typedef hal::fs::UmdFileHandle fs_UmdFileHandle;
typedef hal::fs::UmdDirHandle  fs_UmdDirHandle;
typedef hal::fs::UmdFileSystem fs_UmdFileSystem;

#endif // fs_UmdFileSystem_h__