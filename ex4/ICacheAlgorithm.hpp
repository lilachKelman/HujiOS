#ifndef PROJECT_ICACHEALGORITHM_H
#define PROJECT_ICACHEALGORITHM_H

#include <stdlib.h>
#include <unordered_map>
#include <list>
#include <iostream>
#include <unistd.h>

typedef std::pair<int, int> KeyType;
typedef std::pair<void *, std::list<KeyType>::iterator> ValueType;
typedef void* DataType;

template<class T, typename U>
struct PairHash
{
    const size_t operator()(const std::pair<T, U> &key) const
    {
        return std::hash<T>()(key.first) ^ std::hash<U>()(key.second);
    }
};

template<class T, typename U>
struct PairEqual
{
    bool operator()(const std::pair<T, U> &lhs, const std::pair<T, U> &rhs) const
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

//template<typename Key, typename Data>
using CacheMap = std::unordered_map<KeyType, std::pair<DataType, typename std::list<KeyType>::iterator>,
        PairHash<int, int>, PairEqual<int, int>>;
//using CacheMap = std::unordered_map<KeyType, std::pair<DataType , std::list<std::pair<int, int>>::iterator>>;
//        PairHash<int, int>, PairEqual<int, int>>;


class ICacheAlgorithm
{
protected:
    size_t _capacity;
    CacheMap _cache;

    /**
     * Updates the cache buffer.
     * @param cm position iterator for the cache queue
     */
    virtual void Update(CacheMap::iterator &cm) = 0;

public:
    ICacheAlgorithm(size_t size) : _capacity(size)
    {}

    ICacheAlgorithm(ICacheAlgorithm &&other) : _capacity(std::move(other._capacity)),
                                               _cache(std::move(other._cache))
    {}

    virtual ~ICacheAlgorithm()
    {
        CleanCache();
    }

    /**
     * Assignment move operator
     * @param other the object to move from
     * @return updated object reference
     */
    ICacheAlgorithm &operator=(ICacheAlgorithm &&other)
    {
        if (this != &other)
        {
            _capacity = other._capacity;
            _cache = std::move(other._cache);
        }

        return *this;
    }

    void CleanCache()
    {
        for (auto &item : _cache)
        {
            free(item.second.first);
        }

        _cache.clear();
    }

    /**
     * Gets an item from the cache by a given key
     * @param key item key
     * @return Data item
     */
    virtual void *Get(KeyType key) = 0;

    /**
     * Adds an item to the cache (buffer)
     * @param key item key to be added to the cache
     * @param page item data to be added
     * @return 0 if all goes well; -1 if error.
     */
    virtual int Set(KeyType key, DataType page) = 0;

    virtual void PrintCache(FILE *f) = 0;

};


#endif //PROJECT_ICACHEALGORITHM_H
