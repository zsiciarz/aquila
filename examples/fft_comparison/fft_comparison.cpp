#include "aquila/global.h"
#include "aquila/transform/AquilaFft.h"
#include "aquila/transform/OouraFft.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <iterator>

using namespace std;

typedef Aquila::ComplexType cplx;

const cplx j(0.0, 1.0);

void dft(double x[], cplx spectrum[], size_t N);
void idft(cplx spectrum[], double x[], size_t N);

template<typename Numeric>
double difference(Numeric correct[], Numeric checked[], size_t N)
{
    Numeric val;
    for (size_t i = 0; i < N; ++i)
        val += abs(correct[i] - checked[i]);

    return abs(val);
}


int main()
{
    const double sampleFreq = 8000.0;
    const double dt = 1.0/sampleFreq;
    const double f1 = 1000.0, f2 = 2000.0;
    bool useRandomSignal = true;

    if (useRandomSignal)
        std::srand(std::time(0));

    cout << "    N    |    Aquila FFT    |     Ooura\n"
            "---------+------------------+----------------\n";
    for (int power = 1; power <= 10; ++power)
    {
        size_t N = 1 << power;

        // generate test signal
        double* x = new double[N];
        for (size_t i = 0; i < N; ++i)
            if (useRandomSignal)
                x[i] = std::rand() / static_cast<double>(RAND_MAX);
            else
                x[i] = sin(2*M_PI*f1*i*dt) + 0.5*sin(2*M_PI*f2*i*dt + 0.75*M_PI);

        // reference spectrum calculated using DFT (hey, that's getting slow!)
        cplx* SPECTRUM_ = new cplx[N];
        fill(SPECTRUM_, SPECTRUM_ + N, 0.0);
        dft(x, SPECTRUM_, N);

        cplx* spectrum = new cplx[N];

        // Aquila custom algorithm
        fill(spectrum, spectrum + N, 0.0);
        Aquila::AquilaFft myFft(N);
        myFft.fft(x, spectrum);
        double aquilaDifference = difference(SPECTRUM_, spectrum, N);

        // Ooura algorithm
        fill(spectrum, spectrum + N, 0.0);
        Aquila::OouraFft oouraFft(N);
        oouraFft.fft(x, spectrum);
        double oouraDifference = difference(SPECTRUM_, spectrum, N);

        cout << "  " << left << setw(7) << N <<
                "|  " << setw(16) << aquilaDifference <<
                "|  " << setw(16) << oouraDifference << "\n";

        delete [] x;
        delete [] spectrum;
        delete [] SPECTRUM_;
    }

    return 0;
}


/**
 * The DFT algorithm.
 */
void dft(double x[], cplx spectrum[], size_t N)
{
    const cplx WN = exp((j) * (2.0 * M_PI / N));
    for (size_t m = 0; m < N; ++m)
    {
        for (size_t n = 0; n < N; ++n)
        {
            spectrum[m] += x[n] * pow(WN, -m*n);
        }
    }
}

/**
 * The inverse DFT algorithm.
 */
void idft(cplx spectrum[], double x[], size_t N)
{
    const cplx WN = exp((j) * (2.0 * M_PI / N));
    for (size_t m = 0; m < N; ++m)
    {
        for (size_t n = 0; n < N; ++n)
        {
            x[m] += real(spectrum[n] * pow(WN, m*n));
        }
        x[m] /= N;
    }
}
