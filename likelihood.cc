#include <iostream>
#include <fstream>
#include <array>
#include <cmath>

constexpr std::size_t file_length {234};
constexpr std::size_t bin_amount {11};
constexpr double mean {3.11538};

double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k+1);
}

double prob(std::array<int, bin_amount> daten, double mu) {
    double likelihood = 1.;
    for(int k : daten) {
        likelihood *= poisson(mu, k);
    }
    return likelihood;
}

int main() {
    std::array<int, bin_amount> daten {};

    std::ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < file_length ; ++i) {
        fin >> n_i;
        daten[n_i]++;
    }
    fin.close();

    std::cout << prob(daten, mean) << std::endl;

    std::ofstream fout("likelihood.txt");
    for(double mu = 0.; mu <= 6.; mu+=0.1) {
        fout << mu << " " << prob(daten, mu) << std::endl;
    }
    fout.close();

}
