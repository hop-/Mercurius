#ifndef _BASE_SINGLETON_HPP_
#define _BASE_SINGLETON_HPP_

namespace Base
{

template <typename T>
class Singleton
{
private:
    Singleton& operator=(const Singleton&) = delete;
    Singleton(const Singleton&) = delete;

protected:
    Singleton()
    {}

protected:
    virtual ~Singleton()
    {}

private:
    static T* m_s_instance;

public:
    static T* getInstance()
    {
        if (m_s_instance == 0) {
            m_s_instance = new T();
        }
        return m_s_instance;
    }

    static bool deleteInstance()
    {
        if (m_s_instance == 0) {
            return false;
        }
        delete m_s_instance;
        m_s_instance = 0;
        return true;
    }

};

} // end of namespace Base

#endif // _BASE_SINGLETON_HPP_
