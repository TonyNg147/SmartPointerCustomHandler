#pragma once
#include <Interface.h>
#include <map>
#include <mutex>
/**
*  @brief This class provides the default cast for all the classes inheritance from InterfaceID
 */
template<typename Impl, typename... I>
class ImplementationSupport: public I...
{
    public:
    static_assert(((std::is_base_of_v<Interface,I>) ||...));
        static_assert((!(std::is_same_v<Impl,I>) || ...));

        void* support_query(const InterfaceID& id)
        {
            std::cout << __LINE__ << " Call herer\n";
            static std::once_flag flag;
            std::call_once(flag, [&]()
            {
                m_castMaps =
                            {{iid<I>, [](Impl* o){return reinterpret_cast<void*>(o);}}...}
                ;
            });
            auto it = m_castMaps.find(id);
            if (it != m_castMaps.end())
            {
                std::cout << __LINE__ << " Call herer\n";
                qWarning() << "Find";
                return it->second(reinterpret_cast<Impl*>(this));
            }
            std::cout << __LINE__ << " Call herer\n";
            return nullptr;
        }

    private:
        std::map<InterfaceID, void*(*)(Impl*)> m_castMaps;
};
