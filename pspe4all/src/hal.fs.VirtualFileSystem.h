#ifndef fs_VirtualFileSystem_h__
#define fs_VirtualFileSystem_h__

#include "hal.hmm.h"
#include "hal.String.h"
#include "hal.LinkedList.h"

namespace hal
{
    namespace fs
    {
        void InitializeOnce();

        enum FileAccessMode
        {
            AllAccess = 0777,

            OtherExecute = 0001,
            OtherWrite = 0002,
            OtherRead = 0004,

            GroupExecute = 0010,
            GroupWrite = 0020,
            GroupRead = 0040,

            UserExecute = 0100,
            UserWrite = 0200,
            UserRead = 0400,

            //Directory    = 0x1000,
            //RegularFile  = 0x2000,
            //SymbolicLink = 0x4000
        };

        enum FileOpenMode
        {
            In = 1,
            Out = 2,
            Append = 4,
            Truncate = 8
        };

        enum Whence
        {
            Set = 0,
            Current = 1,
            End = 2,
        };

        class VirtualFileSystem;

        class FileHandle;
        class DirHandle;
        class FileStat;
        class DirEntry;

        class VirtualFileSystemSlot
        {
        public:
            VirtualFileSystem * vfs;

            VirtualFileSystemSlot(VirtualFileSystem * vfs) : vfs(vfs) {}

            static VirtualFileSystem * RealFileSystem(FileHandle * handle);
            static VirtualFileSystem * RealFileSystem(DirHandle * handle);
        };

        class VirtualFileSystem : public LinkedList< VirtualFileSystem >::Node, public hal::hmm::Allocator< VirtualFileSystem >
        {
        public:
            VirtualFileSystem              * parent;
            LinkedList< VirtualFileSystem >  children;

            VirtualFileSystem(VirtualFileSystem * parent);
            virtual ~VirtualFileSystem();

            virtual VirtualFileSystem * RealFileSystem(FileHandle * handle);
            virtual VirtualFileSystem * RealFileSystem(DirHandle * handle);
            virtual VirtualFileSystem * RealFileSystem(String & /*name*/);
            virtual VirtualFileSystem * RealFileSystem(String & /*oldname*/, String & /*newname*/);

            virtual FileHandle        * Open(String const & name, FileOpenMode flags, FileAccessMode mode) = 0;
            virtual void                Close(FileHandle * handle) = 0;

            virtual int                 Read(FileHandle * handle, char * data, u32 length);
            int                         Read(FileHandle * handle, QByteArray & bytes);
            virtual int                 Write(FileHandle * handle, char const * data, u32 length);
            int                         Write(FileHandle * handle, QByteArray const & bytes);
            virtual s64                 Lseek(FileHandle * handle, s64 offset, Whence whence);
            virtual int                 Ioctl(FileHandle * handle, u32 cmd, u32 argp, u32 argl, u32 outp, u32 outl) = 0;

            virtual DirHandle         * Dopen(String const & name) = 0;
            virtual void                Dclose(DirHandle * handle) = 0;
            virtual int                 Dread(DirHandle * handle, DirEntry & entry) = 0;

            virtual bool                Mkdir(String const & name, FileAccessMode mode) = 0;
            virtual bool                Rmdir(String const & name) = 0;
            virtual bool                Chdir(String const & name) = 0;

            virtual bool                Remove(String const & name) = 0;
            virtual bool                Rename(String const & oldname, String const & newname) = 0;
            virtual bool                Getstat(String const & name, FileStat & stat) = 0;

            virtual int                 Devctl(String const & name, u32 cmd, u32 argp, u32 argl, u32 outp, u32 outl) = 0;

            QByteArray                  ReadAll(String const & file);

            void                        SetParent(VirtualFileSystem * parent);

            virtual String              toString() const;

            void                        Startup();
        };

        class NullFileSystem : public VirtualFileSystem
        {
        public:
            NullFileSystem(VirtualFileSystem * vfs = 0) : VirtualFileSystem(vfs) {}
            virtual ~NullFileSystem() {}

            virtual VirtualFileSystem * RealFileSystem(FileHandle *) { return this; }
            virtual VirtualFileSystem * RealFileSystem(DirHandle *) { return this; }

            virtual FileHandle        * Open(String const &, FileOpenMode, FileAccessMode) { return 0; }
            virtual void                Close(FileHandle *) {}
            virtual int                 Read(FileHandle *, char *, u32) { return 0; }
            virtual int                 Write(FileHandle *, char const *, u32) { return 0; }
            virtual s64                 Lseek(FileHandle *, s64, Whence) { return 0; }
            virtual int                 Ioctl(FileHandle *, u32, u32, u32, u32, u32) { return -1; }
            virtual bool                Remove(String const &) { return false; }
            virtual bool                Rename(String const &, String const &) { return false; }
            virtual DirHandle         * Dopen(String const &) { return 0; }
            virtual void                Dclose(DirHandle *) {}
            virtual int                 Dread(DirHandle *, DirEntry &) { return 0; }
            virtual bool                Mkdir(String const &, FileAccessMode) { return false; }
            virtual bool                Rmdir(String const &) { return false; }
            virtual bool                Chdir(String const &) { return false; }
            virtual bool                Getstat(String const &, FileStat &) { return false; }
            virtual int                 Devctl(String const &, u32, u32, u32, u32, u32) { return -1; }

            virtual String              toString() const;
        };

        class FileStat
        {
        public:
            u32                permissions;
            u32                size;
            u32                sector_offset;
            u32                sector_size;
            void *             sector_mapping;
            u32                is_dir : 1;
            u32                is_root : 1;
            u32                is_link : 1;
            u32                opaque[6];
            QDateTime          ctime;
            QDateTime          atime;
            QDateTime          mtime;

            String toString() const
            {
                return Stringf(L"FileStat(size:%u, is_dir:%s, ctime:%ws)", size, is_dir ? "yes" : "no", ctime.toString(Qt::ISODate));
            }
        };

        class FileHandle : public VirtualFileSystemSlot
        {
        public:
            FileHandle(VirtualFileSystem * vfs) : FileHandle(vfs)
            {
            }

            // TODO
        };

        class DirHandle : public VirtualFileSystemSlot
        {
        public:
            DirHandle(VirtualFileSystem * vfs) : VirtualFileSystemSlot(vfs)
            {
            }

            virtual int ReadEntry(DirEntry &entry) = 0;
        };

        class DirEntry
        {
        public:
            FileStat           stat;
            String             name;

            String toString() const
            {
                return Stringf(L"DirEntry(\"%ws\", %ws)", name.data(), stat.toString());
            }
        };

        __forceinline VirtualFileSystem *VirtualFileSystemSlot::RealFileSystem(FileHandle *handle)
        {
            return handle->vfs;
        }

        __forceinline VirtualFileSystem *VirtualFileSystemSlot::RealFileSystem(DirHandle *handle)
        {
            return handle->vfs;
        }
    }
}

typedef hal::fs::FileAccessMode    fs_FileAccessMode;
typedef hal::fs::FileOpenMode      fs_FileOpenMode;
typedef hal::fs::Whence            fs_Whence;
typedef hal::fs::FileStat          fs_FileStat;
typedef hal::fs::FileHandle        fs_FileHandle;
typedef hal::fs::DirHandle         fs_DirHandle;
typedef hal::fs::VirtualFileSystem fs_VirtualFileSystem;
typedef hal::fs::NullFileSystem    fs_NullFileSystem;

#endif // fs_VirtualFileSystem_h__
