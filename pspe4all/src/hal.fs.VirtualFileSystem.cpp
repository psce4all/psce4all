#include "hal.fs.VirtualFileSystem.h"

//#include "kernel_Types.h"

void hal::fs::InitializeOnce()
{
    QDir::home().mkpath("pspe4all/vfs/ms0/PSP/GAME");
    QDir::home().mkpath("pspe4all/vfs/ms0/PSP/SAVEDATA");
    QDir::home().mkpath("pspe4all/vfs/umd0");
    QDir::home().mkpath("pspe4all/vfs/flash0");
    QDir::home().mkpath("pspe4all/vfs/flash1");
}

hal::fs::VirtualFileSystem::VirtualFileSystem(VirtualFileSystem * parent) : parent(parent)
{
    if (parent)
    {
        parent->children.Append(this);
    }
}

hal::fs::VirtualFileSystem::~VirtualFileSystem()
{
    //VirtualFileSystem * vfs;
    //while (vfs = children.First())
    //{
    //    vfs->RemoveFromList();
    //    __delete vfs;
    //}
}

void hal::fs::VirtualFileSystem::SetParent(VirtualFileSystem * parent)
{
    this->RemoveFromList();
    this->parent = parent;
    if (parent)
    {
        parent->children.Append(this);
    }
}

int hal::fs::VirtualFileSystem::Read(FileHandle * handle, char * data, u32 length)
{
    return handle ? handle->read(data, length) : 0;
}

int hal::fs::VirtualFileSystem::Read(FileHandle * handle, QByteArray & bytes)
{
    return Read(handle, bytes.data(), bytes.length());
}

int hal::fs::VirtualFileSystem::Write(FileHandle * handle, char const * data, u32 length)
{
    return handle ? handle->write(data, length) : 0;
}

int hal::fs::VirtualFileSystem::Write(FileHandle * handle, QByteArray const &bytes)
{
    return Write(handle, bytes.data(), bytes.length());
}

s64 hal::fs::VirtualFileSystem::Lseek(FileHandle * handle, s64 offset, Whence whence)
{
    if (handle)
    {
        int position = offset;

        switch (whence)
        {
        case Set:                                 return (handle->seek(position)) ? position : handle->pos();
        case Current: position += handle->pos();  return (handle->seek(position)) ? position : handle->pos();
        case End:     position += handle->size(); return (handle->seek(position)) ? position : handle->pos();
        }
    }

    return s64(SCE_KERNEL_ERROR_INVAL);
}

QByteArray hal::fs::VirtualFileSystem::ReadAll(String const & file)
{
    QByteArray   data;
    FileHandle * handle = Open(file, In, AllAccess);
    if (handle)
    {
        data = handle->readAll();
        Close(handle);
    }
    return data;
}

hal::String hal::fs::VirtualFileSystem::toString() const
{
    return L"VirtualFileSystem()";
}

hal::fs::VirtualFileSystem * hal::fs::VirtualFileSystem::RealFileSystem(String & /*name*/)
{
    return this;
}

hal::fs::VirtualFileSystem * hal::fs::VirtualFileSystem::RealFileSystem(String & /*oldname*/, String & /*newname*/)
{
    return this;
}

hal::fs::VirtualFileSystem * hal::fs::VirtualFileSystem::RealFileSystem(FileHandle * handle)
{
    return hal::fs::VirtualFileSystemSlot::RealFileSystem(handle);
}

hal::fs::VirtualFileSystem * hal::fs::VirtualFileSystem::RealFileSystem(DirHandle * handle)
{
    return hal::fs::VirtualFileSystemSlot::RealFileSystem(handle);
}

hal::String hal::fs::NullFileSystem::toString() const
{
    return L"NullFileSystem()";
}
