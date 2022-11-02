#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k+1);
}

int main() {
    std::vector<int> zaehler(11);
    constexpr std::size_t lines {234};
    std::ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < lines ; ++i) {
        fin >> n_i;
        if (n_i > zaehler.size()) {std::cout << "Problem, found: " << n_i << std::endl;};
        zaehler[n_i]++;
    }
    fin.close();
    std::ofstream fout("hist.txt");
    for(std::size_t n = 0; n < zaehler.size(); ++n) {
        fout << n << " " << zaehler[n] << std::endl;
    }
    fout.close();


    constexpr double mean = 3.11538;
    std::ofstream fout2("histpoi.txt");
    for(std::size_t k = 0; k < zaehler.size(); ++k) {
        fout2 << k << " " << lines * poisson(mean, k) << std::endl;
    }
    fout2.close();
}
