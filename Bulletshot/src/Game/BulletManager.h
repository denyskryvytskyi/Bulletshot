#pragma once

#include <gdm/gdm.h>
#include "BulletObject.h"

class BulletManager
{
public:
    BulletManager();
    ~BulletManager();

    void Update(float dt);
    void Fire(gdm::vec2 pos, gdm::vec2 dir, float speed, float time, float lifetime);

    const std::vector<BulletObject*>& GetBulletObjects() const;

private:
    std::vector<BulletObject*> m_BulletObjects;
    std::vector<BulletObject*> m_SharedResource;
    std::mutex m_Mutex;
};
//
//template<class DataType>
//class SharedDataWrapper
//{
//private:
//    DataType data;
//    std::mutex mutex;
//
//public:
//    template<typename Func>
//    void processData(const Func& func)
//    {
//        std::lock_guard<std::mutex> lock(mutex);
//        func(data);
//    }
//};
//
//template<class T>
//struct LockObject
//{
//    LockObject(T& obj, std::mutex& mut)
//        : object(obj), locker(mut)
//    {}
//
//    T& object;
//    std::lock_guard<std::mutex> locker;
//};