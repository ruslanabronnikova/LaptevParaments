#include <iostream>
#include <cmath>
#include <iomanip>

class Array
{
public:

    typedef double
        value_type;
    typedef double*
        iterator;
    typedef const double*
        const_iterator;
    typedef double&
        reference;
    typedef const double&
        const_reference;
    typedef std::size_t
        size_type;

    Array(const size_type n);
    Array(iterator first, iterator last);

    ~Array()
    {
        delete[]pt;
    }

    iterator begin() { return pt; }
    const_iterator begin() const { return pt; }
    iterator end() { return pt + cc; }
    const_iterator end() const { return pt + cc; }

    size_type size() const
    {
        return cc;
    }

    void resize(size_type newsize);

    size_type capacity() const
    {
        return sizedef;
    }

    bool empty() const
    {
        if (cc == 0)
            return true;
        else
            return false;
    }

    reference operator[](size_type index);
    const_reference operator[](size_type index) const;
    reference front() { return pt[0]; }
    const_reference front() const { return pt[0]; }

    reference back()
    {
        return pt[size() - 1];
    }

    const_reference back() const { return pt[size() - 1]; }


    void push_back(const value_type& v);

    void pop_back()
    {
        pt[cc - 1] = 0;
        cc--;
    }

    void clear()
    {
        cc = 0;
    }

    void show()
    {
        for (int i = 0; i < cc; i++)
        {
            std::cout.precision(3);
            std::cout << std::fixed << pt[i] << " ";
        }
        std::cout << '\n';
    }

private:

    size_type cc;

    value_type* pt;

    static const size_type min = 10;

    size_type sizedef;

};

double summary(const Array& arr)
{
    double sum = 0;

    for (int i = 0; i < arr.size(); i++)
        sum += arr[i];

    return sum;
}

double average(const Array& arr)
{
    double aver = summary(arr) / arr.size();

    return aver;
}

void task(Array& arr)
{
    double min = arr[0];

    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] < min)
            min = arr[i];
    }

    for (int i = 0; i < arr.size(); i++)
        (arr.begin())[i] = (arr.begin())[i] * min;
}

void Array::push_back(const value_type& v)
{
    if (cc == sizedef)
        resize(sizedef * 2);

    pt[cc++] = v;
}

void Array::resize(size_type newsize)
{
    value_type* s = new value_type[newsize];

    for (size_type i = 0; i < cc; ++i)
        s[i] = pt[i];

    delete[] pt;

    pt = s;
    sizedef = newsize;
}

Array::Array(iterator first, iterator last)
{
    if (first < last)
    {
        sizedef = (first - last);
        pt = new value_type[sizedef];

        for (int i = 0; i < sizedef; ++i)
            pt[i] = *(first + i);

        cc = sizedef;
    }
}

Array::Array(const size_type n)
{
    sizedef = n;
    pt = new value_type[n];
    cc = 0;
}

double& Array::operator[](size_type index)
{
    if (index < cc)
        return pt[index];
}

const double& Array::operator[](size_type index) const
{
    if (index < cc)
        return pt[index];
}

int main()
{
    int size, c = 1;
    double elem, sum = 0, aver = 0;

    std::cin >> size;

    Array arr(size);

    for (int i = 0; i < size; i++)
    {
        std::cin >> elem;

        arr.push_back(elem);
    }

    std::cout << arr.size() << '\n';

    arr.show();

    sum = summary(arr);
    aver = average(arr);

    arr.push_back(sum);
    arr.push_back(aver);

    arr.show();

    task(arr);

    arr.show();

    while (true)
    {
        std::cin >> c;

        if (c == 0)
        {
            break;
        }

        else
        {
            switch (c)
            {
            case 1:
                std::cin >> elem;

                arr.push_back(elem);

                std::cout << "+:" << arr.size() << '\n';

                arr.show();

                sum = summary(arr);
                aver = average(arr);

                arr.push_back(sum);
                arr.push_back(aver);

                arr.show();

                task(arr);

                arr.show();

                break;
            case 2:
                arr.pop_back();

                std::cout << "-:" << arr.size() << '\n';

                arr.show();

                sum = summary(arr);
                aver = average(arr);

                arr.push_back(sum);
                arr.push_back(aver);

                arr.show();

                task(arr);

                arr.show();
                break;
            }
        }
    }
    return 0;
}