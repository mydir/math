#ifndef STAN_MATH_PRIM_SCAL_PROB_DOUBLE_EXPONENTIAL_LCCDF_HPP
#define STAN_MATH_PRIM_SCAL_PROB_DOUBLE_EXPONENTIAL_LCCDF_HPP

#include <stan/math/prim/scal/meta/is_constant_struct.hpp>
#include <stan/math/prim/scal/meta/partials_return_type.hpp>
#include <stan/math/prim/scal/meta/OperandsAndPartials.hpp>
#include <stan/math/prim/scal/err/check_consistent_sizes.hpp>
#include <stan/math/prim/scal/err/check_finite.hpp>
#include <stan/math/prim/scal/err/check_not_nan.hpp>
#include <stan/math/prim/scal/err/check_positive_finite.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <stan/math/prim/scal/fun/log1m.hpp>
#include <stan/math/prim/scal/fun/constants.hpp>
#include <stan/math/prim/scal/meta/include_summand.hpp>
#include <stan/math/prim/scal/fun/sign.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/variate_generator.hpp>
#include <cmath>

namespace stan {
  namespace math {

    template <typename T_y, typename T_loc, typename T_scale>
    typename return_type<T_y, T_loc, T_scale>::type
    double_exponential_lccdf(const T_y& y, const T_loc& mu,
                                const T_scale& sigma) {
      static const char* function("double_exponential_lccdf");
      typedef typename stan::partials_return_type<T_y, T_loc, T_scale>::type
        T_partials_return;

      T_partials_return ccdf_log(0.0);

      if (!(stan::length(y)
            && stan::length(mu)
            && stan::length(sigma)))
        return ccdf_log;

      check_not_nan(function, "Random variable", y);
      check_finite(function, "Location parameter", mu);
      check_positive_finite(function, "Scale parameter", sigma);
      check_consistent_sizes(function,
                             "Random variable", y,
                             "Location parameter", mu,
                             "Scale Parameter", sigma);

      using std::log;
      using std::exp;
      using std::exp;

      OperandsAndPartials<T_y, T_loc, T_scale>
        operands_and_partials(y, mu, sigma);

      VectorView<const T_y> y_vec(y);
      VectorView<const T_loc> mu_vec(mu);
      VectorView<const T_scale> sigma_vec(sigma);
      const double log_half = std::log(0.5);
      size_t N = max_size(y, mu, sigma);

      for (size_t n = 0; n < N; n++) {
        const T_partials_return y_dbl = value_of(y_vec[n]);
        const T_partials_return mu_dbl = value_of(mu_vec[n]);
        const T_partials_return sigma_dbl = value_of(sigma_vec[n]);
        const T_partials_return scaled_diff = (y_dbl - mu_dbl) / sigma_dbl;
        const T_partials_return inv_sigma = 1.0 / sigma_dbl;
        if (y_dbl < mu_dbl) {
          ccdf_log += log1m(0.5 * exp(scaled_diff));

          const T_partials_return rep_deriv = 1.0
            / (2.0 * exp(-scaled_diff) - 1.0);
          if (!is_constant_struct<T_y>::value)
            operands_and_partials.d_x1[n] -= rep_deriv * inv_sigma;
          if (!is_constant_struct<T_loc>::value)
            operands_and_partials.d_x2[n] += rep_deriv * inv_sigma;
          if (!is_constant_struct<T_scale>::value)
            operands_and_partials.d_x3[n] += rep_deriv * scaled_diff
              * inv_sigma;
        } else {
          ccdf_log += log_half - scaled_diff;

          if (!is_constant_struct<T_y>::value)
            operands_and_partials.d_x1[n] -= inv_sigma;
          if (!is_constant_struct<T_loc>::value)
            operands_and_partials.d_x2[n] += inv_sigma;
          if (!is_constant_struct<T_scale>::value)
            operands_and_partials.d_x3[n] += scaled_diff * inv_sigma;
        }
      }
      return operands_and_partials.value(ccdf_log);
    }

  }
}
#endif
