#pragma once


#include <assert.h>

#ifdef AD_IN_CUDA
#define AD_API __device__ inline
typedef long long int int64_t;
typedef int int32_t;


#else
#define AD_API inline
#define ZM_AD_IN_CU
#include "zm_tr.hpp"
#include <cstdint>
#endif


#define Ad_Ftype double
#define Ad_KF tr::kF64