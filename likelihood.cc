#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

constexpr std::size_t file_length {234};
constexpr std::size_t bin_amount {11};
constexpr double mean {3.11538};

double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k+1);
}

double prob(std::vector<int> daten, double mu) {
    double likelihood = 1.;
    for(int k : daten) {
        likelihood *= poisson(mu, k);
    }
    return likelihood;
}

double likelihood_ratio(std::vector<int> daten, double mu) {
    double like_ratio = 1.;
    for (int k: daten) {
        like_ratio *= poisson(mu, k) / poisson(k, k);
    }
    return like_ratio;
}

int main() {
    std::vector<int> daten;

    std::ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < file_length ; ++i) {
        fin >> n_i;
        daten.push_back(n_i);
    }
    fin.close();

    std::cout << prob(daten, mean) << std::endl;

    std::ofstream fout("likelihood.txt");
    std::ofstream fout2("nll.txt");
    std::ofstream fout3("deltanll.txt");
    double log_mean = -2*log(prob(daten, mean));
    double min_log = 1000000;
    double min_mu;
    for(double mu = 0.; mu <= 6.; mu+=0.1) {
	double prob_mu = prob(daten, mu);
	double log_mu = -2*log(prob_mu);
	double del_log = log_mu - log_mean;
        fout << mu << " " << prob_mu << std::endl;
	fout2 << mu << " " << log_mu << std::endl;
	fout3 << mu << " " << del_log << std::endl;
	if (del_log < min_log) {min_log = del_log; min_mu = mu;}
    }
    fout.close();
    fout2.close();
    fout3.close();

    std::cout << "mu= " << min_mu << ", with " << min_log << std::endl;
    
    double mu_low = 0; 
    double mu_high= 0;
    bool mu_low_found = false;
    for(double mu = 0.; mu <= 6.; mu+=0.1){
	double prob_mu = prob(daten, mu);
	double log_mu = -2*log(prob_mu);
	double del_log = log_mu - log_mean;
	if (del_log < min_log + 1) {
	    if (!mu_low_found) {
	        mu_low_found = true;
		mu_low = mu;
	    } else {
	        mu_high = mu;
	    }
	}
    }

    std::cout << "mu intervall: " << mu_low << " - " << mu_high << std::endl;
    std::cout << min_mu << " +"<< mu_high-min_mu << " -" << min_mu-mu_low << std::endl;

    std::cout << "Lambda: " << std::endl << -2*log(likelihood_ratio(daten, min_mu)) << std::endl;
    std::cout << "z: " << std::endl << (-2*log(likelihood_ratio(daten, min_mu)) -233)/sqrt(2*233) << std::endl;
}
