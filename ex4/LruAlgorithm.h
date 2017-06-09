//
// Created by jenia90 on 6/4/17.
//

#ifndef PROJECT_LRUALGORITHM_H
#define PROJECT_LRUALGORITHM_H

#include "ICacheAlgorithm.hpp"

template<typename Key = int, typename Data=char *>
class LruAlgorithm : public ICacheAlgorithm<Key, Data>
{
    using Base = ICacheAlgorithm<Key, Data>;

    virtual void Update(typename CacheMap<Key, Data>::iterator &cm);

    void CleanCache(CacheMap<Key, Data> &cm);
public:
    LruAlgorithm(size_t size) : ICacheAlgorithm<Key, Data>(size)
    {}

    virtual ~LruAlgorithm();

    virtual Data Get(Key key);

    virtual int Set(Key key, Data page);
};


#endif //PROJECT_LRUALGORITHM_H