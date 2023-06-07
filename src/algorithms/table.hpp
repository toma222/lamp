
#pragma once

#include <utility>
#include <vector>
#include <assert.h>
#include "../core/logging.hpp"

namespace lamp
{
    template <typename KeyT, typename EntryT>
    class Table
    {
    private:
        std::vector<std::pair<KeyT, EntryT>> m_table;

    public:
        Table() = default;
        ~Table() = default;

        EntryT Get(KeyT key)
        {
            for (auto &&item : m_table)
            {
                if (key == item.first)
                    return item.second;
            }

            LOG(lamp::ERROR, "Item that matches that key does not exist (exiting)");
            assert(false);
        }

        // This loops over all the elements so be careful
        bool Exists(KeyT key)
        {
            for (auto &&item : m_table)
            {
                if (key == item.first)
                    return true;
            }

            return false;
        }

        // Assumes that you are using a good hash algorithm and aren't an idiot
        void Add(KeyT key, EntryT entry)
        {
            std::pair<KeyT, EntryT> e = std::make_pair(key, entry);
            m_table.push_back(e);
        }
    };
} // namespace lamp
