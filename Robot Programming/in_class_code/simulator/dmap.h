#pragma once
#include "grid.h"

struct DMapGridCell
{
    DMapGridCell *parent = 0;
}

struct Dmap : public Grid_<DMapGridCell>
{
    Dmap(int r, int c) : Grid_<DMapGridCell>(r, c) {}

    void clear()
    {
        for (auto &v : _values)
        {
            v.parent = 0;
        }
    }
};
