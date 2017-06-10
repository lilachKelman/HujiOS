#include <cstddef>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "CacheFS.h"
#include "ICacheAlgorithm.hpp"
#include "LruAlgorithm.h"
#include "LfuAlgorithm.h"
#include <bitset>

#define RET_FAILURE -1
#define RET_SUCCESS 0

template<typename K, typename D>
ICacheAlgorithm<K, D> *_algorithm = nullptr;

/**
 * Gets the current blocks size.
 * @return block size unsigned long
 */
size_t GetBlockSize()
{
    struct stat fi;
    stat("/tmp", &fi);
    return fi.st_blksize;
}

int CacheFS_init(int blocks_num, cache_algo_t cache_algo, double f_old, double f_new)
{
    if (f_new < 0 || f_new > 1 || f_old < 0 || f_old > 1 || (f_new + f_old) > 1 || blocks_num <= 0)
        return RET_FAILURE;

    switch (cache_algo)
    {
        case LRU:
            _algorithm<std::pair<int, int>, char *> =
                    new LruAlgorithm<std::pair<int, int>, char *>(GetBlockSize() * blocks_num);
            break;
        case LFU:
            _algorithm<std::pair<int, int>, char *> =
                    new LfuAlgorithm<std::pair<int, int>, char *>(GetBlockSize() * blocks_num);
            break;
        case FBR:
            break;
        default:
            return RET_FAILURE;
    }
    return RET_SUCCESS;
}

int CacheFS_destroy()
{
    try
    {
        delete _algorithm<std::pair<int, int>, char *>;
    }
    catch (std::exception &e)
    {
        return RET_FAILURE;
    }

    return RET_SUCCESS;
}

int CacheFS_open(const char *pathname)
{
    auto path = realpath(pathname, NULL);
    int pos = std::string(path).find("/tmp");
    if (pos == std::string::npos || pos != 0)
        return RET_FAILURE;

    return open(path, O_RDONLY | O_DIRECT | O_SYNC);
}

int CacheFS_close(int file_id)
{
    _algorithm->RemoveByFileID(file_id);
    close(file_id);
    return RET_SUCCESS;
}

int CacheFS_pread(int file_id, void *buf, size_t count, off_t offset)
{
    return RET_SUCCESS;
}

int CacheFS_print_cache(const char *log_path)
{
    return RET_SUCCESS;
}

int CacheFS_print_stat(const char *log_path)
{
    return RET_SUCCESS;
}
