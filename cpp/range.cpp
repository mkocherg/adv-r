#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector range2(NumericVector x, const bool na_rm) {
  NumericVector out(2);
  out[0] = R_PosInf;
  out[1] = R_NegInf;

  int n = x.length();
  for(int i = 0; i < n; ++i) {
    if (!na_rm && R_IsNA(x[i])) {
      out[0] = NA_REAL;
      out[1] = NA_REAL;
      return(out);
    }

    if (x[i] < out[0]) out[0] = x[i];
    if (x[i] > out[1]) out[1] = x[i];
  }

  return(out);

}

// Iterators - the right way (but no faster than raw access)
// [[Rcpp::export]]
NumericVector range3(NumericVector x, const bool na_rm) {
  NumericVector out(2);
  out[0] = R_PosInf;
  out[1] = R_NegInf;

  NumericVector::iterator it;
  NumericVector::iterator end = x.end();
  for(it = x.begin(); it != end; ++it) {
    double val = *it;
    if (!na_rm && R_IsNA(val)) {
      out[0] = NA_REAL;
      out[1] = NA_REAL;
      return(out);
    }

    if (val < out[0]) out[0] = val;
    if (val > out[1]) out[1] = val;
  }

  return(out);

}

// Iterators - the _really_ right way but much slower
// [[Rcpp::export]]
NumericVector range3a(const NumericVector& x, const bool na_rm) {
  NumericVector out(2);
  out[0] = R_PosInf;
  out[1] = R_NegInf;

  NumericVector::iterator it;
  for(it = x.begin(); it != x.end(); ++it) {
    double val = *it;
    if (!na_rm && R_IsNA(val)) {
      out[0] = NA_REAL;
      out[1] = NA_REAL;
      return(out);
    }

    if (val < out[0]) out[0] = val;
    if (val > out[1]) out[1] = val;
  }

  return(out);
}
