#include <cmath>
#include <stdexcept>
#include <gtest/gtest.h>
#include "stan/math/special_functions.hpp"

TEST(MathSpecialFunctions,logicalGt) {
  using stan::math::logical_gt;
  EXPECT_TRUE(logical_gt(1,0));
  EXPECT_TRUE(logical_gt(2,1.00));
  EXPECT_TRUE(logical_gt(2.0,1));
  EXPECT_TRUE(logical_gt(0,-1));

  EXPECT_FALSE(logical_gt(1,1));
  EXPECT_FALSE(logical_gt(5.7,5.7));
  EXPECT_FALSE(logical_gt(-5.7,9.0));
  EXPECT_FALSE(logical_gt(0,0.0));
}
TEST(MathSpecialFunctions,logicalGte) {
  using stan::math::logical_gte;
  EXPECT_TRUE(logical_gte(1,0));
  EXPECT_TRUE(logical_gte(2.0,1.0));
  EXPECT_TRUE(logical_gte(2.0, 1));
  EXPECT_TRUE(logical_gte(0, -1));
  EXPECT_TRUE(logical_gte(1,1));
  EXPECT_TRUE(logical_gte(5.7,5.7));

  EXPECT_FALSE(logical_gte(-9.0, 5.7));
  EXPECT_FALSE(logical_gte(-2,-1));
}
TEST(MathSpecialFunctions,asBool) {
  using stan::math::as_bool;
  EXPECT_TRUE(as_bool(1));
  EXPECT_TRUE(as_bool(1.7));
  EXPECT_TRUE(as_bool(-1.7));
  EXPECT_TRUE(as_bool(std::numeric_limits<double>::infinity()));
  EXPECT_TRUE(as_bool(-std::numeric_limits<double>::infinity()));
  // don't like this behavior, but it's what C++ does
  EXPECT_TRUE(as_bool(std::numeric_limits<double>::quiet_NaN()));

  EXPECT_FALSE(as_bool(0));
  EXPECT_FALSE(as_bool(0.0));
  EXPECT_FALSE(as_bool(0.0f));
}
TEST(MathSpecialFunctions,BoostUseTr1Def) {
 bool BOOST_RESULT_OF_USE_TR1_is_defined = false;

#ifdef BOOST_RESULT_OF_USE_TR1
 BOOST_RESULT_OF_USE_TR1_is_defined = true;
#endif

 EXPECT_TRUE(BOOST_RESULT_OF_USE_TR1_is_defined);
}
TEST(MathSpecialFunctions,BoostNoDeclTypeDef) {
 bool BOOST_NO_DECLTYPE_is_defined = false;
#ifdef BOOST_NO_DECLTYPE
 BOOST_NO_DECLTYPE_is_defined = true;
#endif
 EXPECT_TRUE(BOOST_NO_DECLTYPE_is_defined);
}


TEST(MathsSpecialFunctions, pi_fun) {
  EXPECT_FLOAT_EQ(4.0 * std::atan(1.0), stan::math::pi());
}
TEST(MathsSpecialFunctions, e_fun) {
  EXPECT_FLOAT_EQ(std::exp(1.0), stan::math::e());
}
TEST(MathsSpecialFunctions, sqrt2_fun) {
  EXPECT_FLOAT_EQ(std::sqrt(2.0), stan::math::sqrt2());
}
TEST(MathsSpecialFunctions, log10_fun) {
  EXPECT_FLOAT_EQ(std::log(10.0), stan::math::log10());
}

TEST(MathsSpecialFunctions, infty) {
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), stan::math::positive_infinity());
}
TEST(MathsSpecialFunctions, neg_infty) {
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  stan::math::negative_infinity());
}
TEST(MathsSpecialFunctions, nan) {
  EXPECT_TRUE(std::isnan(stan::math::not_a_number()));
}
TEST(MathsSpecialFunctions, epsilon) {
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::epsilon(),
                  stan::math::epsilon());
}
TEST(MathsSpecialFunctions, negative_epsilon) {
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::epsilon(),
                  stan::math::negative_epsilon());
}
