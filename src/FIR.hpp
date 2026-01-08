#pragma once

#include <cmath>
#include <vector>
#include <numbers>
#include <expected>

namespace oh {

namespace fir {

enum class FIRType {        ///< Enum FIRType
    Lowpass,
    Highpass,
    Bandpass,
    Custom 
};

enum class FIRError {       ///< Enum FIRError
    InvalidSize,
    MismatchedSize,
    InvalidParameterValue,
    InvalidParameterOrder,
    NormalisationFailed
};

/******************************************************************************
 * FIR class, used as a template to create specialised FIR filters.
 * Once created, the filters can not be resized or modified. All setters and
 * non-private helpers must be of type std::expected and must return FIRError
 * on failure. Exceptions are not allowed, every class inheriting from FIR must
 * have a private constuctor, validation must be handled by the create() method.
 ******************************************************************************/

class FIR {         ///< FIR class, used as a template to create specialised FIR filters

    private:

    FIRType m_type;
    std::vector <double> m_coefficients;

    protected:

    static std::expected <void, FIRError> checkFrequencyRange(double fc) {            ///< helper for checking the frequency
        if(fc <= 0 || fc >= 0.5) {
            return std::unexpected(FIRError::InvalidParameterValue);
        } else {
            return {};
        }
    }

    static std::expected <void, FIRError> checkFrequencyOrder(double fc_low, double fc_high) {            ///< helper for checking the frequency
        if(fc_low >= fc_high) {
            return std::unexpected(FIRError::InvalidParameterOrder);
        } else {
            return {};
        }
    }

    static std::expected <void, FIRError> checkSize(size_t size) {          ///< helper for checking the size
        if(size == 0 || size % 2 == 0) {
            return std::unexpected(FIRError::InvalidSize);
        } else {
            return {};
        }
    }

    static double sinc(double x) {          ///< helper for calulating the sinc
        const double eps = 1e-12;
        if (std::abs(x) < eps)
            return 1.0;
        return std::sin(std::numbers::pi * x) / (std::numbers::pi * x);
    }

    FIR(FIRType type, size_t size)  : m_type(type), m_coefficients(size , 0.0) {}           ///< constuctor


    std::expected <void, FIRError> setCoefficients(const std::vector <double>& coefficients) {          ///< setter for coefficients of the filter 
        if (coefficients.size() != m_coefficients.size()) {
            return std::unexpected(FIRError::MismatchedSize);
        } else {
            m_coefficients = coefficients;
        }
        return {};
    }

    std::expected <void, FIRError> normaliseCoefficients() {            ///< normalise coefficients
        const double eps = 1e-12;
        double sum = 0.0f;

        for (auto& v : m_coefficients) {        ///< i love auto :D
            sum += v;
        }

        if (sum < eps) {
            return std::unexpected(FIRError::NormalisationFailed);
        } else {
            for (auto& v : m_coefficients) {
                v /= sum;
            }
        }
        
    }

    virtual std::expected <void, FIRError> calculateCoefficients()  = 0;         ///< pure virtual method, override it in inheriting classes

    public:

    const std::vector <double> & getCoefficients() const {           ///< getter for coefficients of the filter
            return m_coefficients;
    }

    const size_t getSize() const noexcept {            ///< getter for m_coefficients.size()
        return m_coefficients.size();
    }

    const FIRType getType() const noexcept {          ///< getter for m_type
        return m_type;
    }


    std::expected <std::vector<double>, FIRError> convolution(const std::vector<double>& signal) const {        ///< convolution, returns a copy
        const size_t N = signal.size();
        const size_t M = m_coefficients.size();

        if (N == 0 || M == 0) {
            return std::unexpected(FIRError::InvalidSize);
        }

        std::vector<double> w(N + M - 1, 0.0);

        for (size_t n = 0; n < N; ++n) {
            for (size_t m = 0; m < M; ++m) {
            w[n + m] += signal[n] * m_coefficients[m];
            }
        }

        return w;
    }

    std::expected <std::vector<double>, FIRError> convolutionOverride(std::vector<double>& signal) const {        ///< convolution, modifies signal
        if (auto w = convolution(signal); !w) {
            return std::unexpected(w.error());
        } else {
            signal = *w;
            return signal;
        }
    }

    virtual ~FIR() = default;

};

}

}

