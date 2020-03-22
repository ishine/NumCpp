/// @file
/// @author David Pilger <dpilger26@gmail.com>
/// [GitHub Repository](https://github.com/dpilger26/NumCpp)
/// @version 1.3
///
/// @section License
/// Copyright 2020 David Pilger
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this
/// software and associated documentation files(the "Software"), to deal in the Software
/// without restriction, including without limitation the rights to use, copy, modify,
/// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
/// permit persons to whom the Software is furnished to do so, subject to the following
/// conditions :
///
/// The above copyright notice and this permission notice shall be included in all copies
/// or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
/// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
/// PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
/// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
/// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
/// DEALINGS IN THE SOFTWARE.
///
/// @section Description
/// "gamma" distrubution.
///
#pragma once

#include "NumCpp/Core/Error.hpp"
#include "NumCpp/Core/Shape.hpp"
#include "NumCpp/Core/StlAlgorithms.hpp"
#include "NumCpp/NdArray.hpp"
#include "NumCpp/Random/generator.hpp"

#include "boost/random/gamma_distribution.hpp"

#include <string>

namespace nc
{
    namespace random
    {
        //============================================================================
        // Method Description:
        ///						Single random value sampled from the "gamma" distrubution.
        ///
        ///                     NumPy Reference: https://docs.scipy.org/doc/numpy/reference/generated/numpy.random.gamma.html#numpy.random.gamma
        ///
        /// @param			    inGammaShape
        /// @param				inScaleValue (default 1)
        /// @return
        ///				NdArray
        ///
        template<typename dtype>
        dtype gamma(dtype inGammaShape, dtype inScaleValue = 1)
        {
            if (inGammaShape <= 0)
            {
                THROW_INVALID_ARGUMENT_ERROR("input gamma shape should be greater than zero.");
            }

            if (inScaleValue <= 0)
            {
                THROW_INVALID_ARGUMENT_ERROR("input scale should be greater than zero.");
            }

            boost::random::gamma_distribution<dtype> dist(inGammaShape, inScaleValue);
            return dist(generator_); 

        }
        //============================================================================
        // Method Description:
        ///						Create an array of the given shape and populate it with
        ///						random samples from a "gamma" distrubution.
        ///
        ///                     NumPy Reference: https://docs.scipy.org/doc/numpy/reference/generated/numpy.random.gamma.html#numpy.random.gamma
        ///
        /// @param				inShape
        /// @param			    inGammaShape
        /// @param				inScaleValue (default 1)
        /// @return
        ///				NdArray
        ///
        template<typename dtype>
        NdArray<dtype> gamma(const Shape& inShape, dtype inGammaShape, dtype inScaleValue = 1)
        {
            if (inGammaShape <= 0)
            {
                THROW_INVALID_ARGUMENT_ERROR("input gamma shape should be greater than zero.");
            }

            if (inScaleValue <= 0)
            {
                THROW_INVALID_ARGUMENT_ERROR("input scale should be greater than zero.");
            }

            NdArray<dtype> returnArray(inShape);

            boost::random::gamma_distribution<dtype> dist(inGammaShape, inScaleValue);

            stl_algorithms::for_each(returnArray.begin(), returnArray.end(),
                [&dist](dtype& value) noexcept -> void
                {
                    value = dist(generator_); 
                });

            return returnArray;
        }
    }
}
