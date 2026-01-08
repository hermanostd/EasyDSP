#include "EasyDSP.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <expected>

int main() {
    std::cout << "this is a simple program to showcase the features of easydsp" << std::endl;
    std::cout << std::endl;

    /// creating a lowpass
    auto lp = oh::fir::Lowpass::create(0.25, 9);
    if(!lp) {
        std::cout << lp->FIRErrorToString(lp.error());
    } else {
        std::cout << "succesfully created Lowpass" << std::endl;
    }
    /// creating a bandpass
    auto bp = oh::fir::Bandpass::create(0.1, 0.4, 9);
    if(!bp) {
        std::cout << lp->FIRErrorToString(lp.error());
    } else {
        std::cout << "succesfully created Bandpass" << std::endl;
    }
    /// creating a highpass
    auto hp = oh::fir::Highpass::create(0.25, 9);
    if(!hp) {
        std::cout << lp->FIRErrorToString(lp.error());
    } else {
        std::cout << "succesfully created Highpass" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "---checking getters---" << std::endl;

    std::cout << std::endl;
    std::cout << "-------getType--------" << std::endl;
    std::cout << std::endl;

    std::cout << "Lowpass: " << lp->FIRTypeToString(lp -> getType()) << std::endl;
    std::cout << "Bandpass: " << lp->FIRTypeToString(bp -> getType()) << std::endl;
    std::cout << "Highpass: " << lp->FIRTypeToString(hp -> getType()) << std::endl;

    std::cout << std::endl;
    std::cout << "-------getSize--------" << std::endl;
    std::cout << std::endl;

    std::cout << "Lowpass: " << lp -> getSize() << std::endl;;
    std::cout << "Bandpass: " << bp -> getSize() << std::endl;
    std::cout << "Highpass: " << hp -> getSize() << std::endl;

    std::cout << std::endl;
    std::cout << "----getCoefficients----" << std::endl;
    std::cout << std::endl;

    std::cout << "Lowpass: " << std::endl;
    for(auto w : lp -> getCoefficients()) {
        std::cout << w << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Bandpass: " << std::endl;
    for(auto w : bp -> getCoefficients()) {
        std::cout << w << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Highpass: " << std::endl;
    for(auto w : hp -> getCoefficients()) {
        std::cout << w << std::endl;
    }
    
}