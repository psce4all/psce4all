#ifndef hal_fs_MountableFileSystem_h__
#define hal_fs_MountableFileSystem_h__

#include "hal.fs.ProxyFileSystem.h"

namespace hal
{
    namespace fs
    {
        class MountableFileSystem : public ProxyFileSystem
        {
        private:
            struct Entry
            {
                VirtualFileSystem        * vfs;
                std::map< String, Entry >  entries;

                Entry() : vfs(0) {}

                void Mount(StringList & keys, VirtualFileSystem * vfs)
                {
                    Entry * entry = this;

                    while (!keys.empty())
                    {
                        String key(keys.front());

                        keys.pop_front();

                        entry = &(entry->entries[key]);
                    }

                    entry->vfs = vfs;
                }

                void Unmount(StringList & keys)
                {
                    if (!keys.empty())
                    {
                        String key(keys.front());

                        keys.pop_front();

                        if (!keys.empty())
                        {
                            entries[key].Unmount(keys);

                            if (!entries[key].entries.empty() || entries[key].vfs)
                            {
                                return;
                            }
                        }

                        entries.erase(key);
                    }
                }

                void UnmountAll()
                {
                    for (auto i = entries.begin(); i != entries.end();)
                    {
                        Entry & entry = i->second;

                        entry.UnmountAll();

                        i = entries.erase(i);
                    }
                }

                VirtualFileSystem * RealFileSystem(StringList & keys, String & path)
                {
                    VirtualFileSystem * result = vfs;

                    Entry * entry = this;

                    StringList relativepath(keys);

                    while (!keys.empty())
                    {
                        String key(keys.front());

                        keys.pop_front();

                        auto i = entry->entries.find(key);
                        if (i != entry->entries.end())
                        {
                            entry = &(entry->entries[key]);
                            relativepath = keys;

                            if (entry->vfs)
                            {
                                path = relativepath.join(L'/');
                                result = entry->vfs;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }

                    return result;
                }
            };

        protected:
            Entry m_root;

        public:
            MountableFileSystem(VirtualFileSystem * parent, VirtualFileSystem * vfs) : ProxyFileSystem(parent, vfs)
            {
            }

            ~MountableFileSystem()
            {
                UnmountAll();
            }

            void Mount(String const & path, VirtualFileSystem * vfs)
            {
                StringList keys(path.split(L'/', String::SkipEmptyParts));
                m_root.Mount(keys, vfs);
            }

            void Unmount(String const & path)
            {
                StringList keys(path.split(L'/', String::SkipEmptyParts));
                m_root.Unmount(keys);
            }

            void UnmountAll()
            {
                m_root.UnmountAll();
            }

            VirtualFileSystem * RealFileSystem(String & path)
            {
                StringList keys(path.split(L'/', String::SkipEmptyParts));
                return m_root.RealFileSystem(keys, path);
            }

            VirtualFileSystem * RealFileSystem(String & oldpath, String & newpath)
            {
                VirtualFileSystem * new_vfs = RealFileSystem(newpath);
                if (new_vfs && (new_vfs == RealFileSystem(oldpath)))
                {
                    return new_vfs;
                }

                return real_vfs;
            }
        };
    }
}

typedef hal::fs::MountableFileSystem fs_MountableFileSystem;

#endif // hal_fs_MountableFileSystem_h__
