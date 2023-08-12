#include <cstddef>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <string>
#include <fcntl.h>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <unordered_set>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>    
#include <sys/stat.h>    
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
namespace yesdb {
    class Entry {
    public:
        Entry()=default;
        Entry(int fd, int offset, int size_);
        int fd_;
        int offset_;
        int size_;
    };

    class Yesdb{
    public:
        Yesdb(std::string filename);
        ~Yesdb();
        bool Open();
        bool Close();
        bool Put(const std::string key, const std::string value);
        bool Get(const std::string key, std::string &value);
        bool Flush();
        bool Sync();

    private:
        std::string filename_;
        int fd_;
        int offset_;
        std::string data_;
        std::unordered_map<std::string, Entry> key_dir;
        std::shared_mutex mutex;
        inline static const char *TOMBSTONE = "YESDB_TOMBSTONE_VALUE";

        bool ReadData(Entry entry, std::string &value);
        bool Serialize();
        bool Deserialize();
    };
} // namespace yesdb