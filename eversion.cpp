/*
t g++ eversion.cpp -o evert && ./evert -time 0.90
*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
typedef   int32_t  i32;
typedef   int64_t  i64;
typedef  uint32_t  u32;
typedef  uint64_t  u64;
typedef  double    f64;
typedef  float     f32;

#define SEP "\n-------------------------------------------------------------------------------------------------------------------------------\x1b[31m#\x1b[0m"


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
struct TwoJet{
  f64 f;
  f64 fu, fv;
  f64 fuv;

  TwoJet(){}
  TwoJet(f64 d, f64 du, f64 dv){             f = d; fu = du; fv = dv; fuv = 0; }
  TwoJet(f64 d, f64 du, f64 dv, f64 duv){ f = d; fu = du; fv = dv; fuv = duv; }
  operator f64(){  return f; }
  int  operator<( f64 d){  return f < d; }
  int  operator>( f64 d){  return f > d; }
  int  operator<=(f64 d){  return f <= d; }
  int  operator>=(f64 d){  return f >= d; }
  f64  df_du(){     return fu; }
  f64  df_dv(){     return fv; }
  f64  d2f_dudv(){  return fuv; }
  void operator+=(TwoJet x){  f += x.f; fu += x.fu; fv += x.fv; fuv += x.fuv;  }
  void operator+=(f64 d){  f += d;  }
  void operator*=(TwoJet x){
    fuv = f*x.fuv + fu*x.fv + fv*x.fu + fuv*x.f;
    fu  = f*x.fu + fu*x.f;
    fv  = f*x.fv + fv*x.f;
    f  *= x.f;
  }
  void operator*=(f64 d){  f *= d; fu *= d; fv *= d; fuv *= d;  }
  void operator%=(f64 d){  f = fmod(f, d); if(f < 0) f += d;  }
  void operator^=(f64 n){  printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJet");
    if(f>0){
      f64 x0 = pow(f, n);
      f64 x1 = n * x0/f;
      f64 x2 = (n-1)*x1/f;
      fuv    = x1*fuv + x2*fu*fv;
      fu     = x1*fu;
      fv     = x1*fv;
      f      = x0;
    }
  }
  void Annihilate(int index){
    if(     index == 0)  fu = 0;
    else if(index == 1)  fv = 0;
    fuv = 0;
  }
  void TakeSin(){  printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJet");
    *this *= 2*M_PI;
    f64 s  = sin(f);
    f64 c  = cos(f);
    f      = s; fu = fu*c; fv = fv*c; fuv = c*fuv - s*fu*fv;
  }
  void TakeCos(){  printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJet");
    *this *= 2*M_PI;
    f64 s  = cos(f);
    f64 c  = -sin(f);
    f      = s; fu = fu*c; fv = fv*c; fuv = c*fuv - s*fu*fv;
  }
  // friend TwoJet operator+(  const TwoJet x, const TwoJet y);
  // friend TwoJet operator*(  const TwoJet x, const TwoJet y);
  // friend TwoJet operator+(  const TwoJet x, f64 d);
  // friend TwoJet operator*(  const TwoJet x, f64 d);
  // friend TwoJet Sin(        const TwoJet x);
  // friend TwoJet Cos(        const TwoJet x);
  // friend TwoJet operator^(  const TwoJet x, f64 n);
  // friend TwoJet Annihilate( const TwoJet x, int index);
  // friend TwoJet Interpolate(const TwoJet v1, const TwoJet v2, const TwoJet weight);
  // friend void   printJet(   const TwoJet);
  // friend class  TwoJet D(   const class ThreeJet x, int index);
  // friend class  ThreeJet;
};

// ----------------------------------------------------------------------------------------------------------------------------#
TwoJet operator+(const TwoJet x, const TwoJet y){  return TwoJet(x.f+y.f, x.fu+y.fu, x.fv+y.fv, x.fuv + y.fuv);  }
TwoJet operator*(const TwoJet x, const TwoJet y){
  return TwoJet(
    x.f*y.f,
    x.f*y.fu  + x.fu*y.f,
    x.f*y.fv  + x.fv*y.f,
    x.f*y.fuv + x.fu*y.fv + x.fv*y.fu + x.fuv*y.f
  );
}
TwoJet operator+(const TwoJet x, f64 d){  return TwoJet(x.f + d, x.fu, x.fv, x.fuv);  }
TwoJet operator*(const TwoJet x, f64 d){  return TwoJet(d*x.f, d*x.fu, d*x.fv, d*x.fuv);  }
TwoJet Sin(const TwoJet x){
  TwoJet t = x*(2*M_PI);
  f64 s    = sin(t.f);
  f64 c    = cos(t.f);
  return TwoJet(s, c*t.fu, c*t.fv, c*t.fuv - s*t.fu*t.fv);
}
TwoJet Cos(const TwoJet x){
  TwoJet t = x*(2*M_PI);
  f64 s    =  cos(t.f);
  f64 c    = -sin(t.f);
  return TwoJet(s, c*t.fu, c*t.fv, c*t.fuv - s*t.fu*t.fv);
}
TwoJet operator^(const TwoJet x, f64 n){
  f64 x0 = pow(x.f, n);
  f64 x1 = (x.f == 0) ? 0 : n * x0/x.f;
  f64 x2 = (x.f == 0) ? 0 : (n-1)*x1/x.f;
  return TwoJet(x0, x1*x.fu, x1*x.fv, x1*x.fuv + x2*x.fu*x.fv);
}
TwoJet Annihilate(const TwoJet x, int index){  return TwoJet(x.f, index == 1 ? x.fu : 0, index == 0 ? x.fv : 0, 0);  }
TwoJet Interpolate(const TwoJet v1, const TwoJet v2, const TwoJet weight){  return (v1) * ((weight) * (-1) + 1) + v2*weight;  }

void printJet(const TwoJet v){  printf("%f (%f %f)\n", v.f, v.fu, v.fv);  }


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
class ThreeJet{
  f64 f;
  f64 fu, fv;
  f64 fuu, fuv, fvv;
  f64 fuuv, fuvv;

  ThreeJet(f64 d, f64 du, f64 dv, f64 duu, f64 duv, f64 dvv, f64 duuv, f64 duvv){
    f = d; fu = du; fv = dv; fuu = duu; fuv = duv; fvv = dvv; fuuv = duuv; fuvv = duvv;
  }

  public:
  ThreeJet(){}
  ThreeJet(f64 d, f64 du, f64 dv){
    f = d; fu = du; fv = dv; fuu = fuv = fvv = fuuv = fuvv = 0;
  }

  operator TwoJet(){  return TwoJet(f, fu, fv, fuv);  }
  operator f64(){     return f;  }
  int operator<( f64 d){  return f < d;   }
  int operator>( f64 d){  return f > d;   }
  int operator<=(f64 d){  return f <= d;  }
  int operator>=(f64 d){  return f >= d;  }
  void operator %=(f64 d){
    f = fmod(f, d); if (f < 0) f += d;
  }

  friend ThreeJet operator+(  const ThreeJet x, const ThreeJet y);
  friend ThreeJet operator*(  const ThreeJet x, const ThreeJet y);
  friend ThreeJet operator+(  const ThreeJet x, f64 d);
  friend ThreeJet operator*(  const ThreeJet x, f64 d);
  friend ThreeJet Sin(        const ThreeJet x);
  friend ThreeJet Cos(        const ThreeJet x);
  friend ThreeJet operator^(  const ThreeJet x, f64 n);
  friend ThreeJet Annihilate( const ThreeJet x, int index);
  friend ThreeJet Interpolate(const ThreeJet v1, const ThreeJet v2, const ThreeJet weight);
  friend void     printJet(   const ThreeJet);
  friend class    TwoJet D(   const class ThreeJet x, int index);
};

// ----------------------------------------------------------------------------------------------------------------------------#
ThreeJet operator+(const ThreeJet x, const ThreeJet y){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJet");
  ThreeJet result;
  result.f    = x.f + y.f;
  result.fu   = x.fu + y.fu;
  result.fv   = x.fv + y.fv;
  result.fuu  = x.fuu + y.fuu;
  result.fuv  = x.fuv + y.fuv;
  result.fvv  = x.fvv + y.fvv;
  result.fuuv = x.fuuv + y.fuuv;
  result.fuvv = x.fuvv + y.fuvv;
  return result;
}

ThreeJet operator*(const ThreeJet x, const ThreeJet y){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJet");
  ThreeJet result;
  result.f    = x.f*y.f;
  result.fu   = x.f*y.fu + x.fu*y.f;
  result.fv   = x.f*y.fv + x.fv*y.f;
  result.fuu  = x.f*y.fuu + 2*x.fu*y.fu + x.fuu*y.f;
  result.fuv  = x.f*y.fuv + x.fu*y.fv + x.fv*y.fu + x.fuv*y.f;
  result.fvv  = x.f*y.fvv + 2*x.fv*y.fv + x.fvv*y.f;
  result.fuuv = x.f*y.fuuv + 2*x.fu*y.fuv + x.fv*y.fuu + 2*x.fuv*y.fu + x.fuu*y.fv + x.fuuv*y.f;
  result.fuvv = x.f*y.fuvv + 2*x.fv*y.fuv + x.fu*y.fvv + 2*x.fuv*y.fv + x.fvv*y.fu + x.fuvv*y.f;
  return result;
}

ThreeJet operator+(const ThreeJet x, f64 d){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJet");
  ThreeJet result;
  result   = x;
  result.f+= d;
  return result;
}

ThreeJet operator*(const ThreeJet x, f64 d){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJet");
  ThreeJet result;
  result.f    = d*x.f;
  result.fu   = d*x.fu;
  result.fv   = d*x.fv;
  result.fuu  = d*x.fuu;
  result.fuv  = d*x.fuv;
  result.fvv  = d*x.fvv;
  result.fuuv = d*x.fuuv;
  result.fuvv = d*x.fuvv;
  return result;
}

ThreeJet Sin(const ThreeJet x){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJet result;
  ThreeJet t  = x*(2*M_PI);
  f64 s       = sin(t.f);
  f64 c       = cos(t.f);
  result.f    = s;
  result.fu   = c*t.fu;
  result.fv   = c*t.fv;
  result.fuu  = c*t.fuu  - s*t.fu*t.fu;
  result.fuv  = c*t.fuv  - s*t.fu*t.fv;
  result.fvv  = c*t.fvv  - s*t.fv*t.fv;
  result.fuuv = c*t.fuuv - s*(2*t.fu*t.fuv + t.fv*t.fuu) - c*t.fu*t.fu*t.fv;
  result.fuvv = c*t.fuvv - s*(2*t.fv*t.fuv + t.fu*t.fvv) - c*t.fu*t.fv*t.fv;
  return result;
}

ThreeJet Cos(const ThreeJet x){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJet result;
  ThreeJet t  = x*(2*M_PI);
  f64 s       = cos(t.f);
  f64 c       = -sin(t.f);
  result.f    = s;
  result.fu   = c*t.fu;
  result.fv   = c*t.fv;
  result.fuu  = c*t.fuu  - s*t.fu*t.fu;
  result.fuv  = c*t.fuv  - s*t.fu*t.fv;
  result.fvv  = c*t.fvv  - s*t.fv*t.fv;
  result.fuuv = c*t.fuuv - s*(2*t.fu*t.fuv + t.fv*t.fuu) - c*t.fu*t.fu*t.fv;
  result.fuvv = c*t.fuvv - s*(2*t.fv*t.fuv + t.fu*t.fvv) - c*t.fu*t.fv*t.fv;
  return result;
}

ThreeJet operator^(const ThreeJet x, f64 n){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJet");
  f64 x0      = pow(x.f, n);
  f64 x1      = (x.f == 0) ? 0 : n * x0/x.f;
  f64 x2      = (x.f == 0) ? 0 : (n-1) * x1/x.f;
  f64 x3      = (x.f == 0) ? 0 : (n-2) * x2/x.f;
  ThreeJet result;
  result.f    = x0;
  result.fu   = x1*x.fu;
  result.fv   = x1*x.fv;
  result.fuu  = x1*x.fuu  + x2*x.fu*x.fu;
  result.fuv  = x1*x.fuv  + x2*x.fu*x.fv;
  result.fvv  = x1*x.fvv  + x2*x.fv*x.fv;
  result.fuuv = x1*x.fuuv + x2*(2*x.fu*x.fuv + x.fv*x.fuu) + x3*x.fu*x.fu*x.fv;
  result.fuvv = x1*x.fuvv + x2*(2*x.fv*x.fuv + x.fu*x.fvv) + x3*x.fu*x.fv*x.fv;
  return result;
}

TwoJet D(const ThreeJet x, int index){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJet");
  TwoJet result;
  if(index == 0){
    result.f   = x.fu;
    result.fu  = x.fuu;
    result.fv  = x.fuv;
    result.fuv = x.fuuv;
  }else if(index == 1){
    result.f   = x.fv;
    result.fu  = x.fuv;
    result.fv  = x.fvv;
    result.fuv = x.fuvv;
  }else{
    result.f   = result.fu = result.fv =
    result.fuv = 0;
  }
  return result;
}

ThreeJet Annihilate(const ThreeJet x, int index){
  ThreeJet result = ThreeJet(x.f,0,0);
  if(index == 0){
    result.fv  = x.fv;
    result.fvv = x.fvv;
  }else if(index == 1){
    result.fu  = x.fu;
    result.fuu = x.fuu;
  }
  return result;
}

ThreeJet Interpolate(const ThreeJet v1, const ThreeJet v2, const ThreeJet weight){
  return (v1) * ((weight) * (-1) + 1) + v2*weight;
}

void printJet(const ThreeJet v){  printf("%f (%f %f)\n", v.f, v.fu, v.fv);  }


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
struct TwoJetVec{
  TwoJet x, y, z;
  TwoJetVec(){}
  TwoJetVec(TwoJet a, TwoJet b, TwoJet c){  x = a; y = b; z = c;  }
};

// ----------------------------------------------------------------------------------------------------------------------------#
TwoJetVec operator+(TwoJetVec v, TwoJetVec w){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  TwoJetVec result;
  result.x = v.x + w.x;
  result.y = v.y + w.y;
  result.z = v.z + w.z;
  return result;
}

TwoJetVec operator*(TwoJetVec v, TwoJet  a){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  TwoJetVec result;
  result.x = v.x*a;
  result.y = v.y*a;
  result.z = v.z*a;
  return result;
}

TwoJetVec operator*(TwoJetVec v, f64 a){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  TwoJetVec result;
  result.x = v.x*a;
  result.y = v.y*a;
  result.z = v.z*a;
  return result;
}

TwoJetVec AnnihilateVec(TwoJetVec v, int index){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  TwoJetVec result;
  result.x = Annihilate(v.x, index);
  result.y = Annihilate(v.y, index);
  result.z = Annihilate(v.z, index);
  return result;
}

TwoJetVec Cross(TwoJetVec v, TwoJetVec w){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  TwoJetVec result;
  result.x = v.y*w.z + v.z*w.y*-1;
  result.y = v.z*w.x + v.x*w.z*-1;
  result.z = v.x*w.y + v.y*w.x*-1;
  return result;
}

TwoJet Dot(TwoJetVec v, TwoJetVec w){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  return v.x*w.x + v.y*w.y + v.z*w.z;
}

TwoJetVec Normalize(TwoJetVec v){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  TwoJet a = Dot(v,v);
  if(a > 0)  a = a^-0.5;
  else       a = TwoJet(0, 0, 0);
  return v*a;
}

TwoJetVec RotateZ(TwoJetVec v, TwoJet angle){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  TwoJet s = Sin(angle);
  TwoJet c = Cos(angle);
  TwoJetVec result;
  result.x =          v.x*c + v.y*s;
  result.y = v.x*s*-1 + v.y*c;
  result.z = v.z;
  return result;
}

TwoJetVec RotateY(TwoJetVec v, TwoJet angle){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  TwoJetVec result;
  TwoJet s = Sin(angle);
  TwoJet c = Cos(angle);
  result.x = v.x*c + v.z*s*-1;
  result.y = v.y;
  result.z = v.x*s + v.z*c    ;
  return result;
}

TwoJetVec RotateX(TwoJetVec v, TwoJet angle){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  TwoJetVec result;
  TwoJet s = Sin(angle);
  TwoJet c = Cos(angle);
  result.x = v.x;
  result.y = v.y*c + v.z*s;
  result.z = v.y*s*-1 + v.z*c;
  return result;
}

TwoJetVec InterpolateVec(TwoJetVec v1, TwoJetVec v2, TwoJet weight){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  return (v1) * (weight*-1 + 1) + v2*weight;
}

TwoJet Length(TwoJetVec v){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "TwoJetVec");
  return (v.x^2 + v.y^2) ^ (.5);
}


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
struct ThreeJetVec{
  ThreeJet x, y, z;
  operator TwoJetVec(){  return TwoJetVec(x,y,z);  }
};

// ----------------------------------------------------------------------------------------------------------------------------#
ThreeJetVec operator+(ThreeJetVec v, ThreeJetVec w){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJetVec result;
  result.x = v.x + w.x;
  result.y = v.y + w.y;
  result.z = v.z + w.z;
  return result;
}

ThreeJetVec operator*(ThreeJetVec v, ThreeJet  a){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJetVec result;
  result.x = v.x*a;
  result.y = v.y*a;
  result.z = v.z*a;
  return result;
}

ThreeJetVec operator*(ThreeJetVec v, f64 a){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJetVec result;
  result.x = v.x*a;
  result.y = v.y*a;
  result.z = v.z*a;
  return result;
}

ThreeJetVec AnnihilateVec(ThreeJetVec v, int index){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJetVec result;
  result.x = Annihilate(v.x, index);
  result.y = Annihilate(v.y, index);
  result.z = Annihilate(v.z, index);
  return result;
}

TwoJetVec D(ThreeJetVec x, int index){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  TwoJetVec result;
  result.x = D(x.x, index);
  result.y = D(x.y, index);
  result.z = D(x.z, index);
  return result;
}

ThreeJetVec Cross(ThreeJetVec v, ThreeJetVec w){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJetVec result;
  result.x = v.y*w.z + v.z*w.y*-1;
  result.y = v.z*w.x + v.x*w.z*-1;
  result.z = v.x*w.y + v.y*w.x*-1;
  return result;
}

ThreeJet Dot(ThreeJetVec v, ThreeJetVec w){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  return v.x*w.x + v.y*w.y + v.z*w.z;
}

ThreeJetVec Normalize(ThreeJetVec v){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJet a = Dot(v,v);
  if(a > 0)  a = a^-0.5;
  else       a = ThreeJet(0, 0, 0);
  return v*a;
}

ThreeJetVec RotateZ(ThreeJetVec v, ThreeJet angle){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJetVec result;
  ThreeJet s = Sin(angle);
  ThreeJet c = Cos(angle);
  result.x =          v.x*c + v.y*s;
  result.y = v.x*s*-1 + v.y*c;
  result.z = v.z;
  return result;
}

ThreeJetVec RotateY(ThreeJetVec v, ThreeJet angle){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJetVec result;
  ThreeJet s = Sin(angle);
  ThreeJet c = Cos(angle);
  result.x   = v.x*c + v.z*s*-1;
  result.y   = v.y;
  result.z   = v.x*s + v.z*c    ;
  return result;
}

ThreeJetVec RotateX(ThreeJetVec v, ThreeJet angle){  // printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  %s\n", __FILE__, __LINE__, __func__, "ThreeJetVec");
  ThreeJetVec result;
  ThreeJet s = Sin(angle);
  ThreeJet c = Cos(angle);
  result.x   = v.x;
  result.y   = v.y*c + v.z*s;
  result.z   = v.y*s*-1 + v.z*c;
  return result;
}

ThreeJetVec InterpolateVec(ThreeJetVec v1, ThreeJetVec v2, ThreeJet weight){  return (v1) * (weight*-1 + 1) + v2*weight;  }
ThreeJet Length(ThreeJetVec v){  return (v.x^2 + v.y^2) ^ (.5);  }


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
#define NSTRIPS 8

// ----------------------------------------------------------------------------------------------------------------------------#
extern int nstrips;

TwoJetVec FigureEight(TwoJetVec w, TwoJetVec h, TwoJetVec bend, TwoJet form, TwoJet v){
  TwoJet height;
  v %= 1;
  height = (Cos(v*2) + -1) * (-1);
  if(v > 0.25 && v < 0.75)  height = height*-1 + 4;
  height = height*0.6;
  h = h + bend*(height*height*(1/64.));
  return w*Sin(v*2) + (h) * (Interpolate((Cos(v) + -1) * (-2), height, form));
}
  
TwoJetVec AddFigureEight(ThreeJetVec p, ThreeJet u, TwoJet v, ThreeJet form, ThreeJet scale){
  ThreeJet size = form*scale;
  form          = form*2 + form*form*-1;
  TwoJetVec dv  = AnnihilateVec(D(p, 1), 1);
  p             = AnnihilateVec(p, 1);
  TwoJetVec du  = Normalize(D(p, 0));
  TwoJetVec h   = Normalize(Cross(du, dv))*TwoJet(size);
  TwoJetVec w   = Normalize(Cross(h, du))*(TwoJet(size)*1.1);
  return RotateZ(TwoJetVec(p) + FigureEight(w, h, du*D(size, 0)*(D(u, 0)^(-1)), form, v), v*(1./nstrips));
}


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
ThreeJetVec Arc(ThreeJet u, ThreeJet v, f64 xsize, f64 ysize, f64 zsize){
  ThreeJetVec result;
  u = u*0.25;
  result.x = Sin(u) * Sin(v) * xsize;
  result.y = Sin(u) * Cos(v) * ysize;
  result.z = Cos(u) * zsize;
  return result;
}

ThreeJetVec Straight(ThreeJet u, ThreeJet v, f64 xsize, f64 ysize, f64 zsize){
  ThreeJetVec result;
  u        = u * 0.25;
  result.x = Sin(v) * xsize;
  result.y = Cos(v) * ysize;
  result.z = Cos(u) * zsize;
  return result;
}

ThreeJet Param1(ThreeJet x){
  f64 offset = 0;
  x %= 4;
  if(x > 2){  x = x+(-2); offset = 2;  }
  if(x <= 1)  return x*2 + (x^2)*(-1) + offset;
  else        return (x^2) + x*(-2) + (2 + offset);
}

ThreeJet Param2(ThreeJet x){
  f64 offset = 0;
  x %= 4;
  if(x > 2){ x = x+(-2); offset = 2; }
  if(x <= 1) return (x^2) + offset;
  else return (x^2)*(-1) + x*4 + (-2 + offset);
}

// ----------------------------------------------------------------------------------------------------------------------------#
ThreeJet TInterp(f64 x){  return ThreeJet(x,0,0);  }

ThreeJet UInterp(ThreeJet x){
  x %= 2;
  if(x > 1)  x = x*(-1) + 2;
  return (x^2)*3 + (x^3) * (-2);
}

#define FFPOW 3
ThreeJet FFInterp(ThreeJet x){
  x %= 2;
  if(x > 1)  x = x*(-1) + 2;
  x = x*1.06 + -0.05;
  if(     x < 0)  return ThreeJet(0, 0, 0);
  else if(x > 1)  return ThreeJet(0, 0, 0) + 1;
  else            return (x ^ (FFPOW-1)) * (FFPOW) + (x^FFPOW) * (-FFPOW+1);
}

#define FSPOW 3
ThreeJet FSInterp(ThreeJet x){
  x %= 2;
  if(x > 1)  x = x*(-1) + 2;
  return ((x ^ (FSPOW-1)) * (FSPOW) + (x^FSPOW) * (-FSPOW+1)) * (-0.2);
}

// ----------------------------------------------------------------------------------------------------------------------------#
ThreeJetVec Stage0(ThreeJet u, ThreeJet v){  return Straight(u, v, 1, 1, 1);  }
ThreeJetVec Stage1(ThreeJet u, ThreeJet v){  return Arc(u, v, 1, 1, 1);  }
ThreeJetVec Stage2(ThreeJet u, ThreeJet v){  return InterpolateVec(Arc(Param1(u), v, 0.9, 0.9,-1), Arc(Param2(u), v, 1, 1, 0.5),  UInterp(u));  }
ThreeJetVec Stage3(ThreeJet u, ThreeJet v){  return InterpolateVec(Arc(Param1(u), v,-0.9,-0.9,-1), Arc(Param2(u), v,-1, 1,-0.5), UInterp(u));  }
ThreeJetVec Stage4(ThreeJet u, ThreeJet v){  return Arc(u, v, -1,-1, -1);  }

ThreeJetVec Scene01(ThreeJet u, ThreeJet v, f64 t){  return InterpolateVec(Stage0(u,v), Stage1(u,v), TInterp(t));  }
ThreeJetVec Scene12(ThreeJet u, ThreeJet v, f64 t){  return InterpolateVec(Stage1(u,v), Stage2(u,v), TInterp(t));  }
ThreeJetVec Scene23(ThreeJet u, ThreeJet v, f64 t){
  t = TInterp(t) * 0.5;
  f64 tt = (u <= 1) ? t : -t;
  return InterpolateVec(RotateZ(Arc(Param1(u), v, 0.9, 0.9,-1), ThreeJet(tt,0,0)), RotateY(Arc(Param2(u), v, 1, 1, 0.5), ThreeJet(t,0,0)), UInterp(u)
  );
}
ThreeJetVec Scene34(ThreeJet u, ThreeJet v, f64 t){  return InterpolateVec(Stage3(u,v), Stage4(u,v), TInterp(t));  }

// ----------------------------------------------------------------------------------------------------------------------------#
TwoJetVec BendIn(     ThreeJet u, ThreeJet v, f64 t){  t = TInterp(t);          return AddFigureEight(Scene01(u,ThreeJet(0,0,1),t), u,v, ThreeJet(0,0,0),             FSInterp(u));  }
TwoJetVec Corrugate(  ThreeJet u, ThreeJet v, f64 t){  t = TInterp(t);          return AddFigureEight(Stage1( u,ThreeJet(0,0,1)),   u,v, FFInterp(u)*ThreeJet(t,0,0), FSInterp(u));  }
TwoJetVec PushThrough(ThreeJet u, ThreeJet v, f64 t){                           return AddFigureEight(Scene12(u,ThreeJet(0,0,1),t), u,v, FFInterp(u),                 FSInterp(u));  }
TwoJetVec Twist(      ThreeJet u, ThreeJet v, f64 t){                           return AddFigureEight(Scene23(u,ThreeJet(0,0,1),t), u,v, FFInterp(u),                 FSInterp(u));  }
TwoJetVec UnPush(     ThreeJet u, ThreeJet v, f64 t){                           return AddFigureEight(Scene34(u,ThreeJet(0,0,1),t), u,v, FFInterp(u),                 FSInterp(u));  }
TwoJetVec UnCorrugate(ThreeJet u, ThreeJet v, f64 t){  t = TInterp((t)*(-1)+1); return AddFigureEight(Stage4( u,ThreeJet(0,0,1)),   u,v, FFInterp(u)*ThreeJet(t,0,0), FSInterp(u));  }


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
typedef TwoJetVec surface_time_fn(ThreeJet u, ThreeJet v, f64 t);

extern int bezier;
extern int nstrips;

// ----------------------------------------------------------------------------------------------------------------------------#
void print_point(TwoJetVec p, f64 ps, f64 pus, f64 pvs, f64 puvs){
  printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  ", __FILE__, __LINE__, __func__);
  if(bezier){
    f64 xyz[3];
    xyz[0] = f64(p.x)*ps + p.x.df_du()*pus/3. + p.x.df_dv()*pvs/3. + p.x.d2f_dudv()*puvs/9.;
    xyz[1] = f64(p.y)*ps + p.y.df_du()*pus/3. + p.y.df_dv()*pvs/3. + p.y.d2f_dudv()*puvs/9.;
    xyz[2] = f64(p.z)*ps + p.z.df_du()*pus/3. + p.z.df_dv()*pvs/3. + p.z.d2f_dudv()*puvs/9.;
    printf("%g %g %g\n", xyz[0], xyz[1], xyz[2]);
  }else{
    f64 x  = f64(p.x)*ps ;
    f64 y  = f64(p.y)*ps ;
    f64 z  = f64(p.z)*ps ;
    f64 nx = p.y.df_du()*p.z.df_dv()-p.z.df_du()*p.y.df_dv();
    f64 ny = p.z.df_du()*p.x.df_dv()-p.x.df_du()*p.z.df_dv();
    f64 nz = p.x.df_du()*p.y.df_dv()-p.y.df_du()*p.x.df_dv();
    f64 s  = nx*nx + ny*ny + nz*nz;
    if(s > 0)  s = sqrt(1/s);
    printf("%f %f %f    %f %f %f\n", x, y, z, nx*s, ny*s, nz*s);
  }
}

// ----------------------------------------------------------------------------------------------------------------------------#
void print_mesh(TwoJetVec p){  // Main mesh-printing function?
  printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m  ", __FILE__, __LINE__, __func__);
  f64 x  = f64(p.x);
  f64 y  = f64(p.y);
  f64 z  = f64(p.z);
  f64 nx = p.y.df_du()*p.z.df_dv()-p.z.df_du()*p.y.df_dv();
  f64 ny = p.z.df_du()*p.x.df_dv()-p.x.df_du()*p.z.df_dv();
  f64 nz = p.x.df_du()*p.y.df_dv()-p.y.df_du()*p.x.df_dv();
  f64 s  = nx*nx + ny*ny + nz*nz;
  if(s > 0)  s = sqrt(1/s);
  printf("%9.6f %9.6f %9.6f    %9.6f %9.6f %9.6f\n", x, y, z, nx*s, ny*s, nz*s);
}

// ----------------------------------------------------------------------------------------------------------------------------#
void print_spline(TwoJetVec v00, TwoJetVec v01, TwoJetVec v10, TwoJetVec v11, f64 us, f64 vs, f64 s0, f64 s1, f64 t0, f64 t1){ 
  printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m\n", __FILE__, __LINE__, __func__);
  if(bezier){
    print_point(v00, 1,  0, 0, 0);
    print_point(v00, 1, us, 0, 0);
    print_point(v10, 1,-us, 0, 0);
    print_point(v10, 1,  0, 0, 0);
  
    print_point(v00, 1,  0, vs,     0);
    print_point(v00, 1, us, vs, us*vs);
    print_point(v10, 1,-us, vs,-us*vs);
    print_point(v10, 1,  0, vs,     0);
  
    print_point(v01, 1, 0,-vs, 0);
    print_point(v01, 1, us,-vs,-us*vs);
    print_point(v11, 1,-us,-vs, us*vs);
    print_point(v11, 1, 0,-vs, 0);
  
    print_point(v01, 1, 0, 0, 0);
    print_point(v01, 1, us, 0, 0);
    print_point(v11, 1,-us, 0, 0);
    print_point(v11, 1, 0, 0, 0);
    printf("%g %g  %g %g  %g %g  %g %g\n\n", s0,t0,  s1,t0,  s0,t1, s1,t1);
  }else{
    print_point(v00, 1, us, vs, us*vs);
    print_point(v10, 1, us, vs, us*vs);
    print_point(v11, 1, us, vs, us*vs);
    print_point(v01, 1, us, vs, us*vs);
    putchar('\n');
  }
}

f64 sqr(f64 x){  return x*x;  }
f64 calc_speed_v(TwoJetVec v){  return sqrt(sqr(v.x.df_dv()) + sqr(v.y.df_dv()) + sqr(v.z.df_dv()));  }
f64 calc_speed_u(TwoJetVec v){  return sqrt(sqr(v.x.df_du()) + sqr(v.y.df_du()) + sqr(v.z.df_du()));  }

// ----------------------------------------------------------------------------------------------------------------------------#
void print_scene(surface_time_fn* func, f64 umin, f64 umax, f64 adu, f64 vmin, f64 vmax, f64 adv, f64 t){
  puts(SEP); printf("\x1b[32m%s\x1b[0m:L\x1b[94m%d\x1b[0m  \x1b[31m%-16s\x1b[0m\n", __FILE__, __LINE__, __func__);
  int jmax = (fabs(umax-umin)/adu + .5);  if(jmax == 0)  jmax = 1;
  int kmax = (fabs(vmax-vmin)/adv + .5);  if(kmax == 0)  kmax = 1;
  f64 du   = (umax-umin) / jmax;
  f64 dv   = (vmax-vmin) / kmax;

  // ----------------------------------------------------------------------------------------------------------------------------#
  f64 u, v;
  static TwoJetVec** values = (TwoJetVec**)calloc(jmax+1, sizeof(TwoJetVec *));
  f64*  speedv = (f64*)calloc(jmax+1, sizeof(f64));
  f64** speedu = (f64**)calloc(jmax+1, sizeof(f64 *));

  for(int j=0; j <= jmax; ++j){
    u = umin + j*du;
    values[j] = (TwoJetVec*)calloc(kmax+1, sizeof(TwoJetVec));
    speedu[j] = (f64*)calloc(kmax+1, sizeof(f64));
    speedv[j] = calc_speed_v((*func)(ThreeJet(u, 1, 0), ThreeJet(0, 0, 1), t));
    if(speedv[j] == 0){  // Perturb a bit, hoping to avoid degeneracy!
      u += (u<1) ? 1e-9 : -1e-9;
      speedv[j] = calc_speed_v((*func)(ThreeJet(u, 1, 0), ThreeJet(0, 0, 1), t));
    }
    for(int k=0; k <= kmax; ++k){
      v = vmin + k*dv;
      values[j][k] = (*func)(ThreeJet(u, 1, 0), ThreeJet(v, 0, 1), t);
      speedu[j][k] = calc_speed_u(values[j][k]);
    }
  }

  // ----------------------------------------------------------------------------------------------------------------------------#
  if(bezier){
    printf("{ STBBP\n");
    for(int j=0; j < jmax; ++j){
      u = umin + j*du;
      for(int k=0; k < kmax; ++k){
        v = vmin + k*dv;
        print_spline(values[j][k], values[j][k+1], values[j+1][k], values[j+1][k+1], du, dv, umin+j*du, umin+(j+1)*du,  vmin+k*dv, vmin+(k+1)*dv);
      }
    }
  // ----------------------------------------------------------------------------------------------------------------------------#
  }else{
    int nu = kmax+1, nv = jmax+1;
    printf("{ NMESH\n");
    printf("%d %d\n", nu, nv);
    for(int j=0; j <= jmax; ++j){
      for(int k=0; k <= kmax; ++k)
        print_mesh(values[j][k]);
      putchar('\n');
    }
  }

  printf("}\n");
}


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
f64 scale    = M_PI;
int bezier   = 0;
int nstrips = NSTRIPS;

char USAGE[] = 
"Usage.  evert [-time T] [-nstrips N] [-scale S] [-bezier]\n\
  [-umin Umin] [-umax Umax]  [-du Ustep]\n[-vmin Vmin] [-vmax Vmax]  [-dv Vstep]\n\
  [-corr Tc] [-push Tp] [-twist Tt] [-unpush Tu] [-uncorr Tf]\n\n\
Generate an everting sphere in Geomview/OOGL MESH or (if -bezier) Bezier form, at eversion time T, for T at least 0 and at most 1.\n\n\
Surface (of T := 0 sphere) parametrized by\n\
  \"u\": u=0 at +Z pole, u=1 at equator, u=2 at -Z pole,\n\
  \"v\": v=0 at +Y, increasing toward +X, v=1 at longitude 2pi/(number of strips)\n\n\
Emits slice ranging in u from Umin..Umax, v from Vmin..Vmax, with each OOGL MESH (or Bezier) element spanning range Ustep x Vstep.\n\n\
With -whole, include transformations to replicate [0..1,0..1] to whole sphere.\n\
strip, plus every other strip in +Z hemisphere; numbers range 0 .. nstrips-1.\n\n\
Eversion stages corrugate-push-twist-unpush begin at times given by -corr -push -twist -unpush respectively.  Produces radius-S sphere.\n\n\
  Defaults:\n-time 0 -nstrips 8 -scale 1 -umin 0 -umax 1  -du .08333  -vmin 0  -vmax 1  -dv .08333 -corr 0 -push .1 -twist .23 -unpush .6 -uncorr .93";

// ----------------------------------------------------------------------------------------------------------------------------#
int main(int argc, char** argv){
  puts(SEP); puts(USAGE);
  f64 corrstart   = .00;  //   These are the milestones where the animations "change phase"! =D
  f64 pushstart   = .10;
  f64 twiststart  = .23;
  f64 unpushstart = .60;
  f64 uncorrstart = .93;

  f64 vmin = 0, umin = 0;
  f64 vmax = 1, umax = 1;
  f64 du   = 1./12;
  f64 dv   = 1./12;

  f64 time     = 0;
  f64 bendtime = -1;   // -1 means don't do bendtime at all

  // ----------------------------------------------------------------------------------------------------------------------------#
  argv++;
  while(--argc){
    if(     !strcmp("-time",   argv[0])){  time    = atof(argv[1]);  argv++; argc--;  }
    else if(!strcmp("-umin",   argv[0])){  umin    = atof(argv[1]);  argv++; argc--;  }
    else if(!strcmp("-umax",   argv[0])){  umax    = atof(argv[1]);  argv++; argc--;  }
    else if(!strcmp("-vmin",   argv[0])){  vmin    = atof(argv[1]);  argv++; argc--;  }
    else if(!strcmp("-vmax",   argv[0])){  vmax    = atof(argv[1]);  argv++; argc--;  }
    else if(!strcmp("-du",     argv[0])){  du      = atof(argv[1]);  argv++; argc--;  }
    else if(!strcmp("-dv",     argv[0])){  dv      = atof(argv[1]);  argv++; argc--;  }
    else if(!strcmp("-nstrips",argv[0])){  nstrips = atoi(argv[1]);  argv++; argc--;  }
    else if(!strcmp("-scale",  argv[0])){  scale   = atof(argv[1]);  argv++; argc--;  }
    else if(!strcmp("-bezier", argv[0])){  bezier  = 1;  }
    else{  printf("evert: Unrecognized argument \"%s\"\n", argv[0]);  return 1;  }
    argv++;
  }

  if(bendtime >= 0.0)
    print_scene(BendIn, umin, umax, du, vmin, vmax, dv, bendtime);
  else{
    // time = (time - howfar) / chunk
    if(     time>=uncorrstart && uncorrstart>=0)  print_scene(UnCorrugate,umin,umax,du,vmin,vmax,dv, (time - uncorrstart) /  (1-uncorrstart));
    else if(time>=unpushstart && unpushstart>=0)  print_scene(UnPush,     umin,umax,du,vmin,vmax,dv, (time - unpushstart) /  (((uncorrstart<0) ? 1. : uncorrstart) - unpushstart));
    else if(time>=twiststart  && twiststart >=0)  print_scene(Twist,      umin,umax,du,vmin,vmax,dv, (time - twiststart)  /  (((unpushstart<0) ? 1. : unpushstart) - twiststart));
    else if(time>=pushstart   && pushstart  >=0)  print_scene(PushThrough,umin,umax,du,vmin,vmax,dv, (time - pushstart)   /  (((twiststart <0) ? 1. : twiststart)  - pushstart));
    else if(time>=corrstart   && corrstart  >=0)  print_scene(Corrugate,  umin,umax,du,vmin,vmax,dv, (time - corrstart)   /  (((pushstart  <0) ? 1. : pushstart)   - corrstart));
  }

}
