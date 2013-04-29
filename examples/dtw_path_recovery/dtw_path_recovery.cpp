#include "aquila/global.h"
#include "aquila/functions.h"
#include "aquila/ml/Dtw.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <vector>

int main(int argc, char *argv[])
{
    std::srand(std::time(0));

    const std::size_t X_SIZE = 24, Y_SIZE = 24;
    Aquila::DtwDataType from, to;

    std::generate_n(std::back_inserter(from), Y_SIZE, [] () {
        std::vector<double> features;
        features.push_back(Aquila::randomDouble());
        features.push_back(Aquila::randomDouble());
        features.push_back(Aquila::randomDouble());
        return features;
    });

    std::generate_n(std::back_inserter(to), X_SIZE, [] () {
        std::vector<double> features;
        features.push_back(Aquila::randomDouble());
        features.push_back(Aquila::randomDouble());
        features.push_back(Aquila::randomDouble());
        return features;
    });

    Aquila::Dtw dtw;
    double distance = dtw.getDistance(from, to);
    std::cout << "DTW distance: " << distance << "\n";

    std::vector<std::vector<char> > data(from.size());
    for (auto it = data.rbegin(); it != data.rend(); ++it)
    {
        std::fill_n(std::back_inserter(*it), to.size(), '.');
    }

    auto path = dtw.getPath();
    for (auto it = path.begin(); it != path.end(); ++it)
    {
        data[it->first][it->second] = 'o';
    }

    for (auto it = data.rbegin(); it != data.rend(); ++it)
    {
        std::copy(
            std::begin(*it),
            std::end(*it),
            std::ostream_iterator<char>(std::cout, " ")
        );
        std::cout << "\n";
    }

    return 0;
}
