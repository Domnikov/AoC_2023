#pragma once

#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <variant>

#define P_RR(...) fprintf(stderr, __VA_ARGS__);


#define COLOR_LINE "\033[1;33m"
#define COLOR_VAR "\033[1;36m"
#define COLOR_EQ "\033[1;37m"
#define COLOR_VAL "\033[1;36m"
#define COLOR_SEP "\033[1;35m"
#define COLOR_RESET "\033[0m"

inline std::ostream& operator<<( std::ostream& dest, __int128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}

// template<typename T> void dout(std::string name, T arg){
//     std::cerr << COLOR_VAR << name << COLOR_EQ << " = " << COLOR_VAL << arg << COLOR_RESET << std::endl;
// }
//
// template<typename T1, typename... T2> void dout(std::string names, T1 arg, T2... args){
//     std::cerr << COLOR_VAR << names.substr(0, names.find(',')) << COLOR_EQ << " = " << COLOR_VAL << arg << COLOR_SEP << " ; ";
//     dout(names.substr(names.find(',') + 1), args...);
// }
//
// #define P(...) std::cerr << COLOR_LINE << "[Line " << __LINE__ << "] ", dout(#__VA_ARGS__, __VA_ARGS__)

#define P1(a)       std::cerr << #a << " = " << a << std::endl;

#define P2(a,b)     std::cerr << #a << " = " << a << ";\t" \
    << #b << " = " << b << std::endl;

#define P3(a,b,c)           std::cerr << #a << " = " << a << ";\t" \
    << #b << " = " << b << ";\t" \
    << #c << " = " << c << std::endl;

#define P4(a,b,c,d)         std::cerr << #a << " = " << a << ";\t" \
    << #b << " = " << b << ";\t" \
    << #c << " = " << c << ";\t" \
    << #d << " = " << d << std::endl;

#define P5(a,b,c,d,e)       std::cerr << #a << " = " << a << ";\t" \
    << #b << " = " << b << ";\t" \
    << #c << " = " << c << ";\t" \
    << #d << " = " << d << ";\t" \
    << #e << " = " << e << std::endl;

#define P6(a,b,c,d,e,f)     std::cerr << #a << " = " << a << ";\t" \
    << #b << " = " << b << ";\t" \
    << #c << " = " << c << ";\t" \
    << #d << " = " << d << ";\t" \
    << #e << " = " << e << ";\t" \
    << #f << " = " << f << std::endl;

#define P7(a,b,c,d,e,f,g)   std::cerr << #a << " = " << a << ";\t" \
    << #b << " = " << b << ";\t" \
    << #c << " = " << c << ";\t" \
    << #d << " = " << d << ";\t" \
    << #e << " = " << e << ";\t" \
    << #f << " = " << f << ";\t" \
    << #g << " = " << g << std::endl;

#define P8(a,b,c,d,e,f,g,h) std::cerr << #a << " = " << a << ";\t" \
    << #b << " = " << b << ";\t" \
    << #c << " = " << c << ";\t" \
    << #d << " = " << d << ";\t" \
    << #e << " = " << e << ";\t" \
    << #f << " = " << f << ";\t" \
    << #g << " = " << g << ";\t" \
    << #h << " = " << h << std::endl;


#define P9(a,b,c,d,e,f,g,h,i) std::cerr << #a << " = " << a << ";\t" \
    << #b << " = " << b << ";\t" \
    << #c << " = " << c << ";\t" \
    << #d << " = " << d << ";\t" \
    << #e << " = " << e << ";\t" \
    << #f << " = " << f << ";\t" \
    << #g << " = " << g << ";\t" \
    << #h << " = " << h << ";\t" \
    << #i << " = " << i << std::endl;

#define P10(a,b,c,d,e,f,g,h,i,j) std::cerr << #a << " = " << a << ";\t" \
    << #b << " = " << b << ";\t" \
    << #c << " = " << c << ";\t" \
    << #d << " = " << d << ";\t" \
    << #e << " = " << e << ";\t" \
    << #f << " = " << f << ";\t" \
    << #g << " = " << g << ";\t" \
    << #h << " = " << h << ";\t" \
    << #i << " = " << i << ";\t" \
    << #j << " = " << j << std::endl;

#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME
#define P(...) GET_MACRO(__VA_ARGS__, P10, P9, P8, P7, P6, P5, P4, P3, P2, P1)(__VA_ARGS__)

#define LL    long long
#define ULL   unsigned long long
#define S     std::string
#define VECI  std::vector<LL>
using VECII=std::vector<std::vector<LL>>;
#define VECF  std::vector<double>
#define VECS  std::vector<S>
#define VECSS std::vector<std::vector<S>>

template<typename T>
void _P_VEC (const std::vector<T>& vec)
{
    std::cerr << " = [";

    if(!vec.empty())
    {
        std::copy (vec.begin(), vec.end()-1, std::ostream_iterator<T>(std::cerr, ";"));
        std::cerr << vec.back();
    }

    std::cerr << "]\n";
}


template<typename T>
void _P_VEC (const std::vector<std::vector<T>>& vec)
{
    std::cout << ":" << std::endl;
    for(size_t i = 0; i < vec.size(); i++)
    {
        std::cerr << i;
        _P_VEC(vec[i]);
    }
}

#define P_VEC(a) {fprintf(stderr, #a);_P_VEC(a);}

template<typename T>
void _P_VECV (const std::vector<T> vec)
{
    for(size_t i = 0; i < vec.size(); i++)
    {
        std::cerr << "\t" << i << "\t" << vec[i] << std::endl;
    }
}
#define P_VECV(a) {fprintf(stderr, #a ":\n");_P_VECV(a);}

template<typename T>
void _P_VECH (const std::vector<T> vec)
{
    std::cerr << "[";
    for(size_t i = 0; i < vec.size(); i++)
    {
        std::cerr << vec[i] << "[" << i << "]";
        if(i != vec.size()-1)
        {
            std::cerr << ",";
        }
    }
    std::cerr << "]\n";
}
#define P_VECH(a) {fprintf(stderr, #a " = ");_P_VECH(a);}

template<typename T, typename G>
void _P_MAPV (const std::map<T, G>& map)
{
    std::cerr << " = [\n";

    if(!map.empty())
    {
        for(auto& m : map)
        {
            std::cout << "\t" << m.first << ": " << m.second << "\n";
        }
    }

    std::cerr << "]\n";
}

#define P_MAPV(a) fprintf(stderr, #a);_P_MAPV(a)
#define P_MAP  P_MAPV

#define P_LINE std::cout<<__PRETTY_FUNCTION__<<":"<<__LINE__<<std::endl;

#define FOR(i,a) for(decltype(a)  i{};  i != a; ++i)
#define BE(vec) vec.begin(), vec.end()
#define TRANSFORM(src,dst,func) std::transform(src.begin(), src.end(), std::back_inserter(dst), func);
#define VECSTOA(src,dst) TRANSFORM(src,dst,[](auto s){return stoi(s);});

inline VECS splitStr(S str, char delim = ',')
{
    VECS res;
    std::stringstream ss(str);
    while(ss.good())
    {
        std::string sub;
        std::getline(ss, sub, delim);
        if(!sub.empty())res.push_back(sub);
    }
    return res;
}

inline S trunc(S s)
{
    while(s[0] == ' ')
    {
        s.erase(0, 1);
    }
    while(s[s.size()-1] == ' ')
    {
        s.erase(s.size()-1, 1);
    }
    return s;
}

template <int N>
std::string b2s(ULL a)
{
    return std::bitset< N >( a ).to_string();
}

template <int N>
ULL s2b(S s)
{
    std::bitset< N > b(s);
    return b.to_ulong();
}

inline VECS inToVecS(const char* fileName = "input")
{
    std::ifstream file(fileName);
    S str;
    VECS input;
    while (std::getline(file, str))
    {
        input.push_back(str);
    }
    return input;
}

inline VECI inToVecI(const char* fileName = "input")
{
    auto in = inToVecS(fileName);
    VECI input;
    std::transform(in.begin(), in.end(), std::back_inserter(input), [](const auto& s){return stoi(s);});
    return input;
}

inline VECF inToVecF(const char* fileName = "input")
{
    auto in = inToVecS(fileName);
    VECF input;
    std::transform(in.begin(), in.end(), std::back_inserter(input), [](const auto& s){return stof(s);});
    return input;
}

inline VECSS inToVecSS(char delim = ',', const char* fileName = "input")
{
    auto in = inToVecS(fileName);
    VECSS input;
    std::transform(in.begin(), in.end(), std::back_inserter(input), [delim](const auto& s){return splitStr(s, delim);});
    return input;
}


inline S replace(const S& s, const S& from, const S& to = "")
{
    S res = s;
    if(from.empty()) return s;

    size_t startPos = 0;
    while((startPos  = res.find(from, startPos)) != S::npos)
    {
        res = res.replace(startPos, from.size(), to);
        startPos = to.size();
    }
    return trunc(res);
}
