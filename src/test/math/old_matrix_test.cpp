#include <cmath>
#include <limits>
#include <stdexcept>
#include <gtest/gtest.h>
#include <stan/math/matrix.hpp>

using Eigen::Matrix;
using Eigen::Dynamic;

using stan::math::matrix_d;
using stan::math::vector_d;
using stan::math::row_vector_d;

// typedef Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> matrix_d;
// typedef Eigen::Matrix<double,Eigen::Dynamic,1> vector_d;
// typedef Eigen::Matrix<double,1,Eigen::Dynamic> row_vector_d;

TEST(matrixTest,arrayBuilder) {
  using std::vector;
  using stan::math::array_builder;

  EXPECT_EQ(0U, array_builder<double>().array().size());

  vector<double> x
    = array_builder<double>()
    .add(1)
    .add(3)
    .add(2)
    .array();
  EXPECT_EQ(3U,x.size());
  EXPECT_FLOAT_EQ(1.0, x[0]);
  EXPECT_FLOAT_EQ(3.0, x[1]);
  EXPECT_FLOAT_EQ(2.0, x[2]);

  vector<vector<int> > xx
    = array_builder<vector<int> >()
    .add(array_builder<int>().add(1).add(2).array())
    .add(array_builder<int>().add(3).add(4).array())
    .add(array_builder<int>().add(5).add(6).array())
    .array();

  EXPECT_EQ(3U,xx.size());
  for (size_t i = 0; i < 3; ++i)
    EXPECT_EQ(2U,xx[i].size());
  EXPECT_EQ(1,xx[0][0]);
  EXPECT_EQ(2,xx[0][1]);
  EXPECT_EQ(3,xx[1][0]);
  EXPECT_EQ(4,xx[1][1]);
  EXPECT_EQ(5,xx[2][0]);
  EXPECT_EQ(6,xx[2][1]);
}

TEST(matrix_test, resize_double) {
  double x = 5;
  std::vector<size_t> dims;
  stan::math::resize(x,dims);
}
TEST(matrix_test, resize_svec_double) {
  std::vector<double> y;
  std::vector<size_t> dims;
  EXPECT_EQ(0U, y.size());

  dims.push_back(4U);
  stan::math::resize(y,dims);
  EXPECT_EQ(4U, y.size());

  dims[0] = 2U;
  stan::math::resize(y,dims);
  EXPECT_EQ(2U, y.size());
}
TEST(matrix_test, resize_vec_double) {
  Matrix<double,Dynamic,1> v(2);
  std::vector<size_t> dims;
  EXPECT_EQ(2, v.size());

  dims.push_back(17U);
  stan::math::resize(v,dims);
  EXPECT_EQ(17, v.size());

  dims[0] = 3U;
  stan::math::resize(v,dims);
  EXPECT_EQ(3, v.size());
}
TEST(matrix_test, resize_rvec_double) {
  Matrix<double,1,Dynamic> rv(2);
  std::vector<size_t> dims;
  EXPECT_EQ(2, rv.size());

  dims.push_back(17U);
  stan::math::resize(rv,dims);
  EXPECT_EQ(17, rv.size());

  dims[0] = 3U;
  stan::math::resize(rv,dims);
  EXPECT_EQ(3, rv.size());
}
TEST(matrix_test, resize_mat_double) {
  Matrix<double,Dynamic,Dynamic> m(2,3);
  std::vector<size_t> dims;
  EXPECT_EQ(2, m.rows());
  EXPECT_EQ(3, m.cols());

  dims.push_back(7U);
  dims.push_back(17U);
  stan::math::resize(m,dims);
  EXPECT_EQ(7, m.rows());
  EXPECT_EQ(17, m.cols());
}
TEST(matrix_test, resize_svec_svec_double) {
  std::vector<std::vector<double> > xx;
  EXPECT_EQ(0U,xx.size());
  std::vector<size_t> dims;
  dims.push_back(4U);
  dims.push_back(5U);
  stan::math::resize(xx,dims);
  EXPECT_EQ(4U,xx.size());
  EXPECT_EQ(5U,xx[0].size());

  dims[0] = 3U;
  dims[1] = 7U;
  stan::math::resize(xx,dims);
  EXPECT_EQ(3U,xx.size());
  EXPECT_EQ(7U,xx[1].size());  
}
TEST(matrix_test, resize_svec_v_double) {
  std::vector<Matrix<double,Dynamic,1> > xx;
  EXPECT_EQ(0U,xx.size());
  std::vector<size_t> dims;
  dims.push_back(4U);
  dims.push_back(5U);
  stan::math::resize(xx,dims);
  EXPECT_EQ(4U,xx.size());
  EXPECT_EQ(5,xx[0].size());

  dims[0] = 3U;
  dims[1] = 7U;
  stan::math::resize(xx,dims);
  EXPECT_EQ(3U,xx.size());
  EXPECT_EQ(7,xx[1].size());  
}
TEST(matrix_test, resize_svec_rv_double) {
  std::vector<Matrix<double,1,Dynamic> > xx;
  EXPECT_EQ(0U,xx.size());
  std::vector<size_t> dims;
  dims.push_back(4U);
  dims.push_back(5U);
  stan::math::resize(xx,dims);
  EXPECT_EQ(4U,xx.size());
  EXPECT_EQ(5,xx[0].size());

  dims[0] = 3U;
  dims[1] = 7U;
  stan::math::resize(xx,dims);
  EXPECT_EQ(3U,xx.size());
  EXPECT_EQ(7,xx[1].size());  
}
TEST(matrix_test, resize_svec_svec_matrix_double) {
  std::vector<std::vector<Matrix<double,Dynamic,Dynamic> > > mm;
  std::vector<size_t> dims;
  dims.push_back(4U);
  dims.push_back(5U);
  dims.push_back(6U);
  dims.push_back(3U);
  stan::math::resize(mm,dims);
  EXPECT_EQ(4U,mm.size());
  EXPECT_EQ(5U,mm[0].size());
  EXPECT_EQ(6,mm[1][2].rows());
  EXPECT_EQ(3,mm[3][4].cols());
}

TEST(matrix,get_base1_vec1) {
  using stan::math::get_base1;
  std::vector<double> x(2);
  x[0] = 10.0;
  x[1] = 20.0;
  EXPECT_FLOAT_EQ(10.0,get_base1(x,1,"x[1]",0));
  EXPECT_FLOAT_EQ(20.0,get_base1(x,2,"x[1]",0));
  
  get_base1(x,2,"x[2]",0) = 5.0;
  EXPECT_FLOAT_EQ(5.0,get_base1(x,2,"x[1]",0));

  EXPECT_THROW(get_base1(x,0,"x[0]",0),
               std::out_of_range);
  EXPECT_THROW(get_base1(x,3,"x[3]",0),
               std::out_of_range);
}
TEST(matrix,get_base1_vec2) {
  using stan::math::get_base1;
  using std::vector;
  size_t M = 3;
  size_t N = 4;

  vector<vector<double> > x(M,vector<double>(N,0.0));
  

  for (size_t m = 1; m <= M; ++m)
    for (size_t n = 1; n <= N; ++n)
      x[m - 1][n - 1] = (m * 10) + n;

  for (size_t m = 1; m <= M; ++m) {
    for (size_t n = 1; n <= N; ++n) {
      double expected = x[m - 1][n - 1];
      double found = get_base1(get_base1(x, m, "x[m]",1),
                               n, "x[m][n]",2);
      EXPECT_FLOAT_EQ(expected,found);
    }
  }

  get_base1(get_base1(x,1,"",-1),2,"",-1) = 112.5;
  EXPECT_FLOAT_EQ(112.5, x[0][1]);

  EXPECT_THROW(get_base1(x,0,"",-1),std::out_of_range);
  EXPECT_THROW(get_base1(x,M+1,"",-1),std::out_of_range);
  
  EXPECT_THROW(get_base1(get_base1(x,1,"",-1), 
                         12,"",-1),
               std::out_of_range);
}
TEST(matrix,get_base1_matrix) {
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::get_base1;
  Matrix<double,Dynamic,Dynamic> x(4,3);
  for (size_t i = 0; i < 4; ++i)
    for (size_t j = 0; j < 3; ++j)
      x(i,j) = i * j;
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      EXPECT_FLOAT_EQ(x(i,j),
                      get_base1(x,i+1,j+1,"x",1));
      EXPECT_FLOAT_EQ(x(i,j),
          get_base1(x,i+1,"x",1)(0,j));
      Matrix<double,1,Dynamic> xi
        = get_base1<double>(x,i+1,"x",1);
      EXPECT_FLOAT_EQ(x(i,j),xi[j]);
      EXPECT_FLOAT_EQ(x(i,j),get_base1(xi,j+1,"xi",2));
      // this is no good because can't get ref to inside val
      // could remedy by adding const versions, but don't need for Stan GM
      // double xij = get_base1<double>(get_base1<double>(x,i+1,"x",1),
      //                                j+1,"xi",2);
    }
  }
  EXPECT_THROW(get_base1(x,10,"x",1), std::out_of_range);
  EXPECT_THROW(get_base1(x,0,"x",1), std::out_of_range);
  EXPECT_THROW(get_base1(x,100,1,"x",1), std::out_of_range);
  EXPECT_THROW(get_base1(x,1,100,"x",1), std::out_of_range);
  EXPECT_THROW(get_base1(x,0,1,"x",1), std::out_of_range);
  EXPECT_THROW(get_base1(x,1,0,"x",1), std::out_of_range);
}
TEST(matrix,get_base1_vector) {
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::get_base1;
  Matrix<double,1,Dynamic> x(3);
  x << 1, 2, 3;
  
  for (size_t i = 0; i < 3; ++i)
    EXPECT_FLOAT_EQ(x(i), get_base1(x,i+1,"x",1));
  EXPECT_THROW(get_base1(x,0,"x",1), std::out_of_range);
  EXPECT_THROW(get_base1(x,100,"x",1), std::out_of_range);
}
TEST(matrix,get_base1_row_vector) {
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::get_base1;
  Matrix<double,Dynamic,1> x(3);
  x << 1, 2, 3;
  
  for (size_t i = 0; i < 3; ++i)
    EXPECT_FLOAT_EQ(x(i), get_base1(x,i+1,"x",1));
  EXPECT_THROW(get_base1(x,0,"x",1), std::out_of_range);
  EXPECT_THROW(get_base1(x,100,"x",1), std::out_of_range);
}
TEST(matrix,get_base1_8) {
  using stan::math::get_base1;
  using std::vector;
  double x0(42.0);
  // ~ 4m entries ~ 32MB memory + sizes
  vector<double> x1(9,x0);
  vector<vector<double> > x2(8,x1);
  vector<vector<vector<double> > > x3(7,x2);
  vector<vector<vector<vector<double> > > > x4(6,x3);
  vector<vector<vector<vector<vector<double> > > > > x5(5,x4);
  vector<vector<vector<vector<vector<vector<double> > > > > > x6(4,x5);
  vector<vector<vector<vector<vector<vector<vector<double> > > > > > > x7(3,x6);
  vector<vector<vector<vector<vector<vector<vector<vector<double> > > > > > > > x8(2,x7);

  EXPECT_EQ(x0, x8[0][0][0][0][0][0][0][0]);
  
  for (size_t i1 = 0; i1 < x8.size(); ++i1)
    for (size_t i2 = 0; i2 < x8[0].size(); ++i2)
      for (size_t i3 = 0; i3 < x8[0][0].size(); ++i3)
        for (size_t i4 = 0; i4 < x8[0][0][0].size(); ++i4)
          for (size_t i5 = 0; i5 < x8[0][0][0][0].size(); ++i5)
            for (size_t i6 = 0; i6 < x8[0][0][0][0][0].size(); ++i6)
              for (size_t i7 = 0; i7 < x8[0][0][0][0][0][0].size(); ++i7)
                for (size_t i8 = 0; i8 < x8[0][0][0][0][0][0][0].size(); ++i8)
                  x8[i1][i2][i3][i4][i5][i6][i7][i8]
                    = i1 * i2 * i3 * i4 * i5 * i6 * i7 * i8;

  for (size_t i1 = 0; i1 < x8.size(); ++i1)
    for (size_t i2 = 0; i2 < x8[0].size(); ++i2)
      for (size_t i3 = 0; i3 < x8[0][0].size(); ++i3)
        for (size_t i4 = 0; i4 < x8[0][0][0].size(); ++i4)
          for (size_t i5 = 0; i5 < x8[0][0][0][0].size(); ++i5)
            for (size_t i6 = 0; i6 < x8[0][0][0][0][0].size(); ++i6)
              for (size_t i7 = 0; i7 < x8[0][0][0][0][0][0].size(); ++i7)
                for (size_t i8 = 0; i8 < x8[0][0][0][0][0][0][0].size(); ++i8)
                  EXPECT_FLOAT_EQ(x8[i1][i2][i3][i4][i5][i6][i7][i8],
                                  get_base1(x8,i1+1,i2+1,i3+1,i4+1,i5+1,i6+1,i7+1,i8+1,
                                            "x8",1));
}





TEST(MathMatrix,dot_self) {
  using stan::math::dot_self;

  Eigen::Matrix<double,Eigen::Dynamic,1> v1(1);
  v1 << 2.0;
  EXPECT_NEAR(4.0,dot_self(v1),1E-12);
  Eigen::Matrix<double,Eigen::Dynamic,1> v2(2);
  v2 << 2.0, 3.0;
  EXPECT_NEAR(13.0,dot_self(v2),1E-12);
  Eigen::Matrix<double,Eigen::Dynamic,1> v3(3);
  v3 << 2.0, 3.0, 4.0;
  EXPECT_NEAR(29.0,dot_self(v3),1E-12);

  Eigen::Matrix<double,1,Eigen::Dynamic> rv1(1);
  rv1 << 2.0;
  EXPECT_NEAR(4.0,dot_self(rv1),1E-12);
  Eigen::Matrix<double,1,Eigen::Dynamic> rv2(2);
  rv2 << 2.0, 3.0;
  EXPECT_NEAR(13.0,dot_self(rv2),1E-12);
  Eigen::Matrix<double,1,Eigen::Dynamic> rv3(3);
  rv3 << 2.0, 3.0, 4.0;
  EXPECT_NEAR(29.0,dot_self(rv3),1E-12);

  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> m1(1,1);
  m1 << 2.0;
  EXPECT_NEAR(4.0,dot_self(m1),1E-12);
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> m2(2,1);
  m2 << 2.0, 3.0;
  EXPECT_NEAR(13.0,dot_self(m2),1E-12);
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> m3(3,1);
  m3 << 2.0, 3.0, 4.0;
  EXPECT_NEAR(29.0,dot_self(m3),1E-12);

  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> mm2(1,2);
  mm2 << 2.0, 3.0;
  EXPECT_NEAR(13.0,dot_self(mm2),1E-12);
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> mm3(1,3);
  mm3 << 2.0, 3.0, 4.0;
  EXPECT_NEAR(29.0,dot_self(mm3),1E-12);

}
TEST(MathMatrix,columns_dot_self) {
  using stan::math::columns_dot_self;

  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> m1(1,1);
  m1 << 2.0;
  EXPECT_NEAR(4.0,columns_dot_self(m1)(0,0),1E-12);
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> m2(1,2);
  m2 << 2.0, 3.0;
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> x;
  x = columns_dot_self(m2);
  EXPECT_NEAR(4.0,x(0,0),1E-12);
  EXPECT_NEAR(9.0,x(0,1),1E-12);
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> m3(2,2);
  m3 << 2.0, 3.0, 4.0, 5.0;
  x = columns_dot_self(m3);
  EXPECT_NEAR(20.0,x(0,0),1E-12);
  EXPECT_NEAR(34.0,x(0,1),1E-12);
}
TEST(MathMatrix,dimensionValidation) {
  using stan::math::determinant;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  Matrix<double,Dynamic,Dynamic> x(3,3);
  x << 1, 2, 3, 1, 4, 9, 1, 8, 27;

  ASSERT_FALSE(boost::math::isnan(determinant(x)));

  Matrix<double,Dynamic,Dynamic> xx(3,2);
  xx << 1, 2, 3, 1, 4, 9;
  EXPECT_THROW(stan::math::determinant(xx),std::domain_error);
  
}
TEST(MathMatrix,nonzeroMinMax) {
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using std::numeric_limits;
  Matrix<double,Dynamic,Dynamic> m;
  Matrix<double,Dynamic,1> v;
  Matrix<double,1,Dynamic> rv;
  EXPECT_EQ(numeric_limits<double>::infinity(),
            stan::math::min(m));
  EXPECT_EQ(numeric_limits<double>::infinity(),
            stan::math::min(v));
  EXPECT_EQ(numeric_limits<double>::infinity(),
            stan::math::min(rv));

  EXPECT_EQ(-numeric_limits<double>::infinity(),
            stan::math::max(m));
  EXPECT_EQ(-numeric_limits<double>::infinity(),
            stan::math::max(v));
  EXPECT_EQ(-numeric_limits<double>::infinity(),
            stan::math::max(rv));

  EXPECT_THROW(stan::math::mean(m), std::domain_error);
  EXPECT_THROW(stan::math::mean(v), std::domain_error);
  EXPECT_THROW(stan::math::mean(rv), std::domain_error);

  Matrix<double,Dynamic,Dynamic> m_nz(2,3);
  Matrix<double,Dynamic,1> v_nz(2);
  Matrix<double,1,Dynamic> rv_nz(3);
  EXPECT_NO_THROW(stan::math::min(m_nz));
  EXPECT_NO_THROW(stan::math::min(v_nz));
  EXPECT_NO_THROW(stan::math::min(rv_nz));

  EXPECT_NO_THROW(stan::math::max(m_nz));
  EXPECT_NO_THROW(stan::math::max(v_nz));
  EXPECT_NO_THROW(stan::math::max(rv_nz));

  EXPECT_NO_THROW(stan::math::mean(m_nz));
  EXPECT_NO_THROW(stan::math::mean(v_nz));
  EXPECT_NO_THROW(stan::math::mean(rv_nz));
}
TEST(MathMatrix,minVectorValues) {
  using stan::math::min;
  std::vector<int> n;
  EXPECT_THROW(min(n),std::domain_error);
  n.push_back(1);
  EXPECT_EQ(1,min(n));
  n.push_back(2);
  EXPECT_EQ(1,min(n));
  n.push_back(0);
  EXPECT_EQ(0,min(n));
  
  std::vector<double> x;
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),min(x));
  x.push_back(1.0);
  EXPECT_FLOAT_EQ(1.0,min(x));
  x.push_back(0.0);
  EXPECT_FLOAT_EQ(0.0,min(x));
  x.push_back(2.0);
  EXPECT_FLOAT_EQ(0.0,min(x));
  x.push_back(-10.0);
  EXPECT_FLOAT_EQ(-10.0,min(x));

  vector_d v;
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),min(v));
  v = vector_d(1);
  v << 1.0;
  EXPECT_FLOAT_EQ(1.0,min(v));
  v = vector_d(2);
  v << 1.0, 0.0;
  EXPECT_FLOAT_EQ(0.0,min(v));
  v = vector_d(3);
  v << 1.0, 0.0, 2.0;
  EXPECT_FLOAT_EQ(0.0,min(v));
  v = vector_d(4);
  v << 1.0, 0.0, 2.0, -10.0;
  EXPECT_FLOAT_EQ(-10.0,min(v));

  row_vector_d rv;
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),min(rv));
  rv = row_vector_d(1);
  rv << 1.0;
  EXPECT_FLOAT_EQ(1.0,min(rv));
  rv = row_vector_d(2);
  rv << 1.0, 0.0;
  EXPECT_FLOAT_EQ(0.0,min(rv));
  rv = row_vector_d(3);
  rv << 1.0, 0.0, 2.0;
  EXPECT_FLOAT_EQ(0.0,min(rv));
  rv = row_vector_d(4);
  rv << 1.0, 0.0, 2.0, -10.0;
  EXPECT_FLOAT_EQ(-10.0,min(rv));

  matrix_d m;
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),min(m));
  m = matrix_d(1,1);
  m << 1.0;
  EXPECT_FLOAT_EQ(1.0,min(m));
  m = matrix_d(2,2);
  m << 1.0, 0.0, 2.0, -10.0;
  EXPECT_FLOAT_EQ(-10.0,min(m));
}

TEST(MathMatrix,maxVectorValues) {
  using stan::math::max;
  std::vector<int> n;
  EXPECT_THROW(max(n),std::domain_error);
  n.push_back(1);
  EXPECT_EQ(1,max(n));
  n.push_back(2);
  EXPECT_EQ(2,max(n));
  n.push_back(0);
  EXPECT_EQ(2,max(n));
  
  std::vector<double> x;
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(),max(x));
  x.push_back(1.0);
  EXPECT_FLOAT_EQ(1.0,max(x));
  x.push_back(0.0);
  EXPECT_FLOAT_EQ(1.0,max(x));
  x.push_back(2.0);
  EXPECT_FLOAT_EQ(2.0,max(x));
  x.push_back(-10.0);
  EXPECT_FLOAT_EQ(2.0,max(x));

  vector_d v;
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(),max(v));
  v = vector_d(1);
  v << 1.0;
  EXPECT_FLOAT_EQ(1.0,max(v));
  v = vector_d(2);
  v << 1.0, 0.0;
  EXPECT_FLOAT_EQ(1.0,max(v));
  v = vector_d(3);
  v << 1.0, 0.0, 2.0;
  EXPECT_FLOAT_EQ(2.0,max(v));
  v = vector_d(4);
  v << 1.0, 0.0, 2.0, -10.0;
  EXPECT_FLOAT_EQ(2.0,max(v));

  row_vector_d rv;
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(),max(rv));
  rv = row_vector_d(1);
  rv << 1.0;
  EXPECT_FLOAT_EQ(1.0,max(rv));
  rv = row_vector_d(2);
  rv << 1.0, 0.0;
  EXPECT_FLOAT_EQ(1.0,max(rv));
  rv = row_vector_d(3);
  rv << 1.0, 0.0, 2.0;
  EXPECT_FLOAT_EQ(2.0,max(rv));
  rv = row_vector_d(4);
  rv << 1.0, 0.0, 2.0, -10.0;
  EXPECT_FLOAT_EQ(2.0,max(rv));

  matrix_d m;
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(),max(m));
  m = matrix_d(1,1);
  m << 1.0;
  EXPECT_FLOAT_EQ(1.0,max(m));
  m = matrix_d(2,2);
  m << 1.0, 0.0, 2.0, -10.0;
  EXPECT_FLOAT_EQ(2.0,max(m));
}


TEST(MathMatrix,variance) {
  using stan::math::variance;
  std::vector<double> x;
  EXPECT_THROW(variance(x),std::domain_error);
  x.push_back(1.0);
  EXPECT_FLOAT_EQ(0.0,variance(x));
  x.push_back(2.0);
  EXPECT_NEAR(0.5,variance(x),0.000001);
  x.push_back(3.0);
  EXPECT_FLOAT_EQ(1.0,variance(x));

  vector_d v;
  EXPECT_THROW(variance(v),std::domain_error);
  v = vector_d(1);
  v << 1.0;
  EXPECT_FLOAT_EQ(0.0,variance(v));
  v = vector_d(2);
  v << 1.0, 2.0;
  EXPECT_NEAR(0.5,variance(v),0.000001);
  v = vector_d(3);
  v << 1.0, 2.0, 3.0;
  EXPECT_FLOAT_EQ(1.0,variance(v));

  row_vector_d rv;
  EXPECT_THROW(variance(rv),std::domain_error);
  rv = row_vector_d(1);
  rv << 1.0;
  EXPECT_FLOAT_EQ(0.0,variance(rv));
  rv = row_vector_d(2);
  rv << 1.0, 2.0;
  EXPECT_NEAR(0.5,variance(rv),0.000001);
  rv = row_vector_d(3);
  rv << 1.0, 2.0, 3.0;
  EXPECT_FLOAT_EQ(1.0,variance(rv));


  matrix_d m;
  EXPECT_THROW(variance(m),std::domain_error);
  m = matrix_d(1,1);
  m << 1.0;
  EXPECT_FLOAT_EQ(0.0,variance(m));
  m = matrix_d(2,3);
  m << 1.0, 2.0, 4.0, 9.0, 16.0, 25.0;
  EXPECT_NEAR(88.3,variance(m),0.000001);
}

TEST(MathMatrix,mean) {
  using stan::math::mean;
  std::vector<double> x;
  EXPECT_THROW(mean(x),std::domain_error);
  x.push_back(1.0);
  EXPECT_FLOAT_EQ(1.0,mean(x));
  x.push_back(2.0);
  EXPECT_NEAR(1.5,mean(x),0.000001);
  x.push_back(3.0);
  EXPECT_FLOAT_EQ(2.0,mean(x));

  vector_d v;
  EXPECT_THROW(mean(v),std::domain_error);
  v = vector_d(1);
  v << 1.0;
  EXPECT_FLOAT_EQ(1.0,mean(v));
  v = vector_d(2);
  v << 1.0, 2.0;
  EXPECT_NEAR(1.5,mean(v),0.000001);
  v = vector_d(3);
  v << 1.0, 2.0, 3.0;
  EXPECT_FLOAT_EQ(2.0,mean(v));

  row_vector_d rv;
  EXPECT_THROW(mean(rv),std::domain_error);
  rv = row_vector_d(1);
  rv << 1.0;
  EXPECT_FLOAT_EQ(1.0,mean(rv));
  rv = row_vector_d(2);
  rv << 1.0, 2.0;
  EXPECT_NEAR(1.5,mean(rv),0.000001);
  rv = row_vector_d(3);
  rv << 1.0, 2.0, 3.0;
  EXPECT_FLOAT_EQ(2.0,mean(rv));

  matrix_d m;
  EXPECT_THROW(mean(m),std::domain_error);
  m = matrix_d(1,1);
  m << 1.0;
  EXPECT_FLOAT_EQ(1.0,mean(m));
  m = matrix_d(2,3);
  m << 1.0, 2.0, 4.0, 9.0, 16.0, 25.0;
  EXPECT_FLOAT_EQ(9.5,mean(m));
}


