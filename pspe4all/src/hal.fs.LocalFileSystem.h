#ifndef hal_fs_LocalFileSystem_h__
#define hal_fs_LocalFileSystem_h__

#include "hal.fs.VirtualFileSystem.h"

//#include "kernel_Types.h"

namespace hal
{
    namespace fs
    {
        class LocalFileHandle : public FileHandle, hal::heap::Allocator< LocalFileHandle >
        {
        public:
            LocalFileHandle(VirtualFileSystem * vfs, String const & name) : FileHandle(vfs)
            {
            }

            static QIODevice::OpenMode ConvertFileOpenMode(FileOpenMode flags)
            {
                QIODevice::OpenMode result(QIODevice::NotOpen);

                if (flags & In)
                {
                    result |= QIODevice::ReadOnly;
                }

                if (flags & Out)
                {
                    result |= QIODevice::WriteOnly | QIODevice::Unbuffered;
                }

                if (flags & Append)
                {
                    result |= QIODevice::Append;
                }

                if (flags & Truncate)
                {
                    result |= QIODevice::Truncate;
                }

                return result;
            }

            __forceinline void * operator new (size_t, void * p) { return p; }
        };

        class LocalDirHandle : public DirHandle
        {
        public:
            String        path;
            QFileInfoList entries;
            int           index;

            LocalDirHandle(VirtualFileSystem * vfs, String const & path) : DirHandle(vfs), path(path), index(0)
            {
                entries = QDir(path).entryInfoList(QDir::AllEntries, QDir::NoSort);
            }

            int ReadEntry(DirEntry &entry)
            {
                if (index < entries.length())
                {
                    QFileInfo & info = entries[index++];

                    entry.name = info.fileName();
                    entry.stat.permissions = AllAccess;
                    entry.stat.is_dir = info.isDir();
                    entry.stat.is_root = info.isRoot();
                    entry.stat.is_link = info.isSymLink();
                    entry.stat.size = info.size();
                    entry.stat.sector_offset = 0;
                    entry.stat.sector_size = 0;
                    entry.stat.ctime = info.created();
                    entry.stat.atime = info.lastRead();
                    entry.stat.mtime = info.lastModified();

                    return index;
                }

                return -1;
            }
        };

        class LocalFileSystem : public VirtualFileSystem
        {
        private:
            String InternalPath(String const &path)
            {
                return m_rootdir.absoluteFilePath(QDir::cleanPath(path));
            }

        protected:
            QDir m_rootdir;

        public:
            LocalFileSystem(VirtualFileSystem * parent, String const & rootpath) : VirtualFileSystem(parent), m_rootdir(QDir::cleanPath(rootpath))
            {
            }

            FileHandle * Open(String const & name, FileOpenMode flags, FileAccessMode /*mode*/)
            {
                LocalFileHandle * handle = new LocalFileHandle(this, InternalPath(name));

                if (handle->open(LocalFileHandle::ConvertFileOpenMode(flags)))
                {
                    return handle;
                }

                delete handle;

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

            bool Remove(String const & name)
            {
                return LocalFileHandle::remove(InternalPath(name));
            }

            bool Rename(String const & oldname, String const & newname)
            {
                return LocalFileHandle::rename(InternalPath(oldname), InternalPath(newname));
            }

            bool Mkdir(String const & name, FileAccessMode /*mode*/)
            {
                return m_rootdir.mkdir(QDir::cleanPath(name));
            }

            bool Rmdir(String const & name)
            {
                return m_rootdir.rmdir(QDir::cleanPath(name));
            }

            bool Chdir(String const & name)
            {
                // here we just check if the directory exists
                return m_rootdir.exists(InternalPath(name));
            }

            DirHandle * Dopen(String const & name)
            {
                String path = InternalPath(name);

                if (QDir(path).exists())
                {
                    return __new LocalDirHandle(this, path);
                }

                return 0;
            }

            void Dclose(DirHandle * handle)
            {
                __delete handle;
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
                QFileInfo info(InternalPath(name));

                if (info.exists())
                {
                    stat.permissions = AllAccess;
                    stat.is_dir = info.isDir();
                    stat.is_root = info.isRoot();
                    stat.is_link = info.isSymLink();
                    stat.size = info.size();
                    stat.sector_offset = 0;
                    stat.sector_size = 0;
                    stat.ctime = info.created();
                    stat.atime = info.lastRead();
                    stat.mtime = info.lastModified();

                    return true;
                }

                return false;
            }

            int Devctl(String const & /*devname*/, u32 /*cmd*/, u32 /*argp*/, u32 /*argl*/, u32 /*outp*/, u32 /*outl*/)
            {
                return -1;
            }

            String toString() const { return Stringf(L"LocalFileSystem(\"%ws\")", m_rootdir.absolutePath()); }
        };
    }
}

typedef hal::fs::LocalFileHandle fs_LocalFileHandle;
typedef hal::fs::LocalDirHandle  fs_LocalDirHandle;
typedef hal::fs::LocalFileSystem fs_LocalFileSystem;

#endif // fs_LocalFileSystem_h__
