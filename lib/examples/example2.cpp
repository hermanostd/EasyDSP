#include "EasyDSP.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <expected>

int main() {
    ///< example: 

    std::cout << "this example shows: " << std::endl;
    std::cout << "-how to create a basic window" << std::endl;
    std::cout << "-how to create a basic window and set it to non rectangular on creation" << std::endl;
    std::cout << "-how to change a window type" << std::endl;
    std::cout << "-how to use getters in oh::wnd" << std::endl;
    std::cout << "-apply a window to your desired signal" << std::endl;
    std::cout << std::endl;

    std::vector <oh::wnd::WindowType> w_types = {oh::wnd::WindowType::Rectangular, oh::wnd::WindowType::Hanning, oh::wnd::WindowType::Hamming, oh::wnd::WindowType::Blackman};

    size_t first_size = 87;       ///< random size
    size_t second_size = 9;     ///< easy to print

    std::vector <double> first_test_signal(second_size, 1.0);

    std::cout << "This is the default way of creating windows: " << std::endl;
    {
        auto ham = oh::wnd::Window::create(oh::wnd::WindowType::Hamming, first_size);
        if(!ham) {
            std::cout << toString(ham.error());
        } else {
            std::cout << "succesfully created window: " << toString(ham -> getType()) << std::endl;
        }

        auto black = oh::wnd::Window::create(oh::wnd::WindowType::Rectangular, first_size);
        if(!black) {
            std::cout << toString(black.error());
        } else {
            std::cout << "succesfully created window: " << toString(black -> getType()) << std::endl;
        }


    }

    std::cout << std::endl;

    std::cout << "but you can also create them without specyfing the WindowType: " << std::endl;

    std::cout << std::endl;

    auto win = oh::wnd::Window::create(second_size);
    if(!win) {
        std::cout << toString(win.error());
    } else {
        std::cout << "succesfully created window: " << toString(win -> getType()) << std::endl;
    }


    for (auto window : w_types) {
        std::cout << std::endl;
        std::cout << "window type tested: " << toString(window);

        std::vector <double> second_test_signal(second_size, 1.0);

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "---checking setWindowType---" << std::endl;

        if(auto w = win -> setWindowType(window); !w) {
            std::cout << toString(w.error());
        } else {
            std::cout << "succesfully set window: " << toString(window) << std::endl;
        }

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "---checking apply---" << std::endl;

        std::cout << std::endl;
        std::cout << "Test signal: ";
        for (auto v : first_test_signal) {
            std::cout << v << " ";
        }
        std::cout << std::endl;

        auto w = win -> apply(first_test_signal);
            
        if (!w) {
            std::cout << toString(w.error());
        } else {  
            std::cout << "After window: ";
            for (auto v : *w) {
                std::cout << v << " ";
            }
        }

        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "Test signal: ";
        for (auto v : second_test_signal) {
            std::cout << v << " ";
        }
        std::cout << std::endl;

        auto q = win -> applyInPlace(second_test_signal);
            
        if (!q) {
            std::cout << toString(q.error());
        } else {  
            std::cout << "Test signal after window: ";
            for (auto v : second_test_signal) {
                std::cout << v << " ";
            }
        }

        std::cout << std::endl;
 

        
    }
}