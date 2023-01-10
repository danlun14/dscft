#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
void incrementColumn(const std::vector<std::vector<float>> &what, float whatID, std::vector<float> &where, float n)
{
    for (float i = 0; i < n; i++)
    {
        where[i] += what[i][whatID];
    }
}
void incrementRow(const std::vector<std::vector<float>> &what, float whatID, std::vector<float> &where, float n)
{
    for (float i = 0; i < n; i++)
    {
        where[i] += what[whatID][i];
    }
}
float idofmin(const std::vector<float> &v)
{
    float min = 500;
    float id = 0;
    for (float i = 0; i < v.size(); i++)
    {
        if (v[i] < min)
        {
            min = v[i];
            id = i;
        }
    }
    return id;
}
float idofmax(const std::vector<float> &v)
{
    float max = -1;
    float id = 0;
    for (float i = 0; i < v.size(); i++)
    {
        if (v[i] > max)
        {
            max = v[i];
            id = i;
        }
    }
    return id;
}
int main(int argc, char *argv[])
{
    std::ifstream ifile("game.start");
    std::vector<std::vector<float>> C;
    std::vector<float> Asum, Bsum;
    std::vector<int> Ac, Bc;
    float c1, c2, c3, n;
    float e;
    ifile >> n;
    ifile >> c1;
    ifile >> c2;
    ifile >> c3;
    ifile >> e;
    C.reserve(n);
    C.resize(n);
    Asum.reserve(n);
    Asum.resize(n);
    Bsum.reserve(n);
    Bsum.resize(n);
    Ac.reserve(n);
    Ac.resize(n);
    Bc.reserve(n);
    Bc.resize(n);
    float value = 0;
    for (float i = 0; i < n; i++)
    {
        C[i].reserve(n);
        C.resize(n);
    }
    for (float i = 0; i < n; i++, value += c3)
    {
        C[0][i] = value;
    }
    for (float i = 0; i < n; i++)
    {
        value = C[0][i];
        for (float j = 1; j < n; j++)
        {
            if (j < i)
            {
                value -= c1;
            }
            else if (j == i)
            {
                value = i;
            }
            else
            {
                value += c2;
            }
            C[j][i] = value;
        }
    }
    for (float i = 0; i < n; i++)
    {
        for (float j = 0; j < n; j++)
        {
            std::cout << std::setw(3) << C[i][j] << ' ';
        }
        std::cout << '\n';
    }
    float k = 1;

    float i_ = 0;
    float j_ = 0;
    float Vmin = 0;
    float Vmax = 0;
    float Vavg = 0;
    //
    float Min = -1;
    float checkflag = 0;
    float it = 0;
    float jt = 0;
    float tmpMin = 0;
    i_ = 0;
    j_ = 0;
    incrementRow(C, i_, Asum, n);
    incrementColumn(C, j_, Bsum, n);
    Ac[i_]++;
    Bc[j_]++;
    float Vavglast = 0;
    while (true)
    {
        std::cout << "[" << i_ << "] ";

        for (float i = 0; i < n; i++)
        {

            std::cout << std::setw(3) << Asum[i] << ' ';
        }
        std::cout << '\n';
        std::cout << "[" << j_ << "] ";
        for (float i = 0; i < n; i++)
        {

            std::cout << std::setw(3) << Bsum[i] << ' ';
        }
        std::cout << '\n';
        k++;
        i_ = idofmax(Bsum);
        incrementRow(C, i_, Asum, n);

        j_ = idofmin(Asum);
        incrementColumn(C, j_, Bsum, n);

        Ac[i_]++;
        Bc[j_]++;

        Vmin = (*std::min_element(Asum.begin(), Asum.end())) / k;
        Vmax = (*std::max_element(Bsum.begin(), Bsum.end())) / k;
        Vavglast = Vavg;
        Vavg = (Vmin + Vmax) / 2;
        if (std::abs(Vavg - Vavglast) < e)
        {
            break;
        }
        std::cout << k << ' ' << Vavg << '\n';
    }
    std::cout << Vavg << ' ' << k << '\n';
    std::cout << "[ ";
    for (auto &it : Ac)
    {
        std::cout << it / k << ' ';
    }
    std::cout << "]\n";
    std::cout << "[ ";
    for (auto &it : Bc)
    {
        std::cout << it / k << ' ';
    }
    std::cout << "]\n";
    return 0;
}