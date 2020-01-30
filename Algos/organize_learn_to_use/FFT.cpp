//------------iterative---------------
const double tau=4.0*acos(0.0);
struct cpx{
    double re, im;
    cpx(double _re, double _im):re(_re), im(_im){re=_re; im=_im;}
    cpx(double _re=0):re(_re){im=0;}
    cpx operator +(cpx z){return cpx(re+z.re, im+z.im);}
    cpx operator -(cpx z){return cpx(re-z.re, im-z.im);}
    cpx operator *(cpx z){return cpx(re*z.re-im*z.im, re*z.im+im*z.re);}
};

void FFT(cpx *y, int n, int rev) {
    for (int i=1, j, k, t; i<n; ++i) {
        for (j=0, k=n>>1, t=i; k; k>>=1, t>>=1) {
            j = j<<1 | t & 1;
        }
        if (i<j) swap(y[i], y[j]);
    }
    for (int s=2, ds=1; s<=n; ds=s, s<<=1) {
        cpx wn(cos(rev*tau/s), sin(rev*tau/s));
        for (int k=0; k<n; k+=s) {
            cpx w(1, 0), t;
            for (int i=k; i<k+ds; ++i, w=w*wn) {
                y[i+ds] = y[i] - (t=w*y[i+ds]);
                y[i] = y[i] + t;
            }
        }
    }   
}

//--------recursive-------
#include <complex>
typedef complex<double> cpx;
const double tau = 4.0*acos(0.0);
void FFT (cpx x[], cpx y[], int dx, int N, int dir) {
    if (N>1) {
        FFT(x, y, 2*dx, N/2, dir);
        FFT(x+dx, y+N/2, 2*dx, N/2, dir);
        FOR(i, 0, N/2) {
            cpx even = y[i], odd=y[i+N/2], twiddle = exp(cpx(0, dir*tau*i/N));
            y[i] = even + twiddle*odd;
            y[i+N/2] = even - twiddle*odd;
        }
    } else y[0]=x[0];
}  















//-------- -XraY- precise -------
typedef long double ld;
 
#define pb push_back
#define mp make_pair
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define sz(x) ((int)(x).size())
#define TASKNAME "text"
 
const ld pi = acos((ld) -1);
 
//BEGIN ALGO
namespace FFT {
  struct com {
    ld x, y;
 
    com(ld _x = 0, ld _y = 0) : x(_x), y(_y) {}
 
    inline com operator + (const com &c) const {
      return com(x + c.x, y + c.y);
    }
    inline com operator - (const com &c) const {
      return com(x - c.x, y - c.y);
    }
    inline com operator * (const com &c) const {
      return com(x * c.x - y * c.y, x * c.y + y * c.x);
    }
    inline com conj() const {
      return com(x, -y);
    }
  };
 
  const static int maxk = 21, maxn = (1 << maxk) + 1;
  com ws[maxn];
  int dp[maxn];
  com rs[maxn];
  int n, k;
  int lastk = -1;
 
  void fft(com *a, bool torev = 0) {
    if (lastk != k) {
      lastk = k;
      dp[0] = 0;
 
      for (int i = 1, g = -1; i < n; ++i) {
        if (!(i & (i - 1))) {
          ++g;
        }
        dp[i] = dp[i ^ (1 << g)] ^ (1 << (k - 1 - g));
      }
 
      ws[1] = com(1, 0);
      for (int two = 0; two < k - 1; ++two) {
        ld alf = pi / n * (1 << (k - 1 - two));
        com cur = com(cos(alf), sin(alf));
 
        int p2 = (1 << two), p3 = p2 * 2;
        for (int j = p2; j < p3; ++j) {
          ws[j * 2 + 1] = (ws[j * 2] = ws[j]) * cur;
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      if (i < dp[i]) {
        swap(a[i], a[dp[i]]);
      }
    }
    if (torev) {
      for (int i = 0; i < n; ++i) {
        a[i].y = -a[i].y;
      }
    }
    for (int len = 1; len < n; len <<= 1) {
      for (int i = 0; i < n; i += len) {
        int wit = len;
        for (int it = 0, j = i + len; it < len; ++it, ++i, ++j) {
          com tmp = a[j] * ws[wit++];
          a[j] = a[i] - tmp;
          a[i] = a[i] + tmp;
        }
      }
    }
  }
 
  com a[maxn];
  int mult(int na, int *_a, int nb, int *_b, long long *ans) {
    if (!na || !nb) {
      return 0;
    }
    for (k = 0, n = 1; n < na + nb - 1; n <<= 1, ++k) ;
    assert(n < maxn);
    for (int i = 0; i < n; ++i) {
      a[i] = com(i < na ? _a[i] : 0, i < nb ? _b[i] : 0);
    }
    fft(a);
    a[n] = a[0];
    for (int i = 0; i <= n - i; ++i) {
      a[i] = (a[i] * a[i] - (a[n - i] * a[n - i]).conj()) * com(0, (ld) -1 / n / 4);
      a[n - i] = a[i].conj();
    }
    fft(a, 1);
    int res = 0;
    for (int i = 0; i < n; ++i) {
      long long val = (long long) round(a[i].x);
      assert(abs(val - a[i].x) < 1e-1);
      if (val) {
        assert(i < na + nb - 1);
        while (res < i) {
          ans[res++] = 0;
        }
        ans[res++] = val;
      }
    }
    return res;
  }
};
//END ALGO