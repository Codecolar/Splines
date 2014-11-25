/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 1998-2014                                                 |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                | 
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

#include "Splines.hh"

#include <iomanip>

/**
 * 
 */

namespace Splines {

  using namespace std ; // load standard namspace

  valueType
  CubicSplineBase::operator () ( valueType x ) const { 
    sizeType i = Spline::search( x ) ;
    Hermite3( x-X[i], X[i+1]-X[i], base ) ;
    return base[0] * Y[i]   +
           base[1] * Y[i+1] +
           base[2] * Yp[i]  +
           base[3] * Yp[i+1] ;
  }

  valueType
  CubicSplineBase::D( valueType x ) const {
    sizeType i = Spline::search( x ) ;
    Hermite3_D( x-X[i], X[i+1]-X[i], base_D ) ;
    return base_D[0] * Y[i]   +
           base_D[1] * Y[i+1] +
           base_D[2] * Yp[i]  +
           base_D[3] * Yp[i+1] ;
  }

  valueType
  CubicSplineBase::DD( valueType x ) const { 
    sizeType i = Spline::search( x ) ;
    Hermite3_DD( x-X[i], X[i+1]-X[i], base_DD ) ;
    return base_DD[0] * Y[i]   +
           base_DD[1] * Y[i+1] +
           base_DD[2] * Yp[i]  +
           base_DD[3] * Yp[i+1] ;
  }

  valueType
  CubicSplineBase::DDD( valueType x ) const { 
    sizeType i = Spline::search( x ) ;
    Hermite3_DDD( x-X[i], X[i+1]-X[i], base_DDD ) ;
    return base_DDD[0] * Y[i]   +
           base_DDD[1] * Y[i+1] +
           base_DDD[2] * Yp[i]  +
           base_DDD[3] * Yp[i+1] ;
  }

  // Implementation
  void
  CubicSplineBase::copySpline( CubicSplineBase const & S ) {
    npts = S.npts ;
    X.resize( S.X.size() ) ;
    Y.resize( S.Y.size() ) ;
    Yp.resize( S.Yp.size() ) ;
    std::copy( S.X.begin(), S.X.end(), X.begin() ) ;
    std::copy( S.Y.begin(), S.Y.end(), Y.begin() ) ;
    std::copy( S.Yp.begin(), S.Yp.end(), Yp.begin() ) ;
  }
     
  void
  CubicSplineBase::writeToStream( std::basic_ostream<char> & s ) const {
    sizeType nseg = sizeType(Y.size()-1) ;
    for ( sizeType i = 0 ; i < nseg ; ++i )
      s << "segment N." << setw(4) << i
        << " X:[" << X[i] << ", " << X[i+1]
        << "] Y:[" << Y[i] << ", " << Y[i+1] 
        << "] Yp:[" << Yp[i] << ", " << Yp[i+1] 
        << "] slope: " << (Y[i+1]-Y[i])/(X[i+1]-X[i])
        << '\n' ; 
  }

}
