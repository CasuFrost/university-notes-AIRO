using namespace std;
#include "vec_d.h"
#include <assert.h>

VecD::VecD()
{
    size = 0;
    values = 0;
}

VecD::VecD(const VecD &other)
{
    // other is the copy of the object
    size = other.size;
    if (size)
    {
        values = new double[size];
    }
    for (int i = 0; i < size; i++)
    {
        values[i] = other.values[i];
    }
}

VecD::VecD(int size)
{
    this->size = size;
    values = 0;
    if (size)
    {
        values = new double[size];
    }
}

VecD::~VecD()
{
    if (size)
    {
        delete[] values;
    }
}

double &VecD::at(int pos) const
{
    // if assert contains a false expressions, it crash
    assert(pos >= 0 && pos < size && "position not valid");
    return values[pos];
}

void VecD::printMeBadly(ostream &os)
{
    os << "this: " << this << " ";
    os << "size: " << size << " ";
    os << "values: [ ";
    for (int i = 0; i < size; ++i)
    {
        os << values[i] << " ";
    }
    os << "]" << endl;
}

VecD &VecD::operator=(const VecD &other)
{
    if (size && other.size != size)
    {
        delete[] values;
    }
    size = other.size;
    if (size)
    {
        values = new double[size];
    }
    for (int i = 0; i < size; ++i)
    {
        values[i] = other.values[i];
    }
    return *this;
}

VecD VecD::operator+(const VecD &other) const
{
    assert(size == other.size && "size of the vectors should be the same");
    VecD ret(*this);
    for (int i = 0; i < size; ++i)
    {
        ret.at(i) += other.at(i);
    }
    return ret;
}

VecD VecD::operator*(const float s)
{
    VecD ret(*this);
    for (int i = 0; i < size; ++i)
    {
        ret.at(i) *= s;
    }
    return ret;
}

VecD VecD::operator-(const VecD &other) const
{
    assert(size == other.size && "size of the vectors should be the same");
    VecD ret(*this);
    for (int i = 0; i < size; ++i)
    {
        ret.at(i) -= other.at(i);
    }
    return ret;
}

double VecD::operator*(const VecD &other)
{
    assert(size == other.size && "size of the vectors should be the same");
    VecD ret(*this);
    double res = 0;
    for (int i = 0; i < size; ++i)
        res += (ret.at(i) * other.at(i));
    return res;
}
