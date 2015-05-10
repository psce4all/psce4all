#ifndef hal_fs_ProxyFileSystem_h__
#define hal_fs_ProxyFileSystem_h__

#include "hal.fs.VirtualFileSystem.h"

namespace hal
{
    namespace fs
    {
        class ProxyFileSystem : public VirtualFileSystem
        {
        public:
            VirtualFileSystem * real_vfs;

            ProxyFileSystem(VirtualFileSystem * parent, VirtualFileSystem * vfs) : VirtualFileSystem(parent), real_vfs(vfs) {}
            ~ProxyFileSystem() {}

            using VirtualFileSystem::RealFileSystem;

            virtual VirtualFileSystem * RealFileSystem(String & /*name*/) { return real_vfs; }
            virtual VirtualFileSystem * RealFileSystem(String & /*oldname*/, String & /*newname*/) { return real_vfs; }

            FileHandle * Open(String const & name, FileOpenMode flags, FileAccessMode mode) { String path(name); return RealFileSystem(path)->Open(path, flags, mode); }
            void         Close(FileHandle *handle) { RealFileSystem(handle)->Close(handle); }
            int          Read(FileHandle * handle, char * data, u32 length) { return RealFileSystem(handle)->Read(handle, data, length); }
            int          Write(FileHandle * handle, char const * data, u32 length) { return RealFileSystem(handle)->Write(handle, data, length); }
            s64          Lseek(FileHandle * handle, s64 offset, Whence whence) { return RealFileSystem(handle)->Lseek(handle, offset, whence); }
            int          Ioctl(FileHandle * handle, u32 cmd, u32 argp, u32 argl, u32 outp, u32 outl) { return RealFileSystem(handle)->Ioctl(handle, cmd, argp, argl, outp, outl); }
            bool         Remove(String const & name) { String path(name); return RealFileSystem(path)->Remove(path); }
            bool         Rename(String const & oldname, String const & newname) { String oldpath(oldname); String newpath(newname); return RealFileSystem(oldpath, newpath)->Rename(oldpath, newpath); }
            DirHandle  * Dopen(String const & name) { String path(name); return RealFileSystem(path)->Dopen(path); }
            void         Dclose(DirHandle * handle) { return RealFileSystem(handle)->Dclose(handle); }
            int          Dread(DirHandle * handle, DirEntry & entry) { return RealFileSystem(handle)->Dread(handle, entry); }
            bool         Mkdir(String const & name, FileAccessMode mode) { String path(name); return RealFileSystem(path)->Mkdir(path, mode); }
            bool         Rmdir(String const & name) { String path(name); return RealFileSystem(path)->Rmdir(path); }
            bool         Chdir(String const & name) { String path(name); return RealFileSystem(path)->Chdir(path); }
            bool         Getstat(String const & name, FileStat & stat) { String path(name); return RealFileSystem(path)->Getstat(path, stat); }
            int          Devctl(String const & name, u32 cmd, u32 argp, u32 argl, u32 outp, u32 outl) { String path(name); return RealFileSystem(path)->Devctl(path, cmd, argp, argl, outp, outl); }

            virtual String toString() const { return Stringf(L"ProxyFileSystem(%ws)", real_vfs->toString().data()); }
        };
    }
}

typedef hal::fs::ProxyFileSystem fs_ProxyFileSystem;

#endif // hal_fs_ProxyFileSystem_h__
