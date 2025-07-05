#pragma once
#include "ad_macro.hpp"
#include "ad_bf.hpp"

// #ifdef ZM_AD_IN_CU
// #include "zm_log.hpp"
// #endif


AD_API void _materialBack(
	_RawBf bkGd, int nbk, _RawBf outGd
	, _RawBf inGd, int nIn)
{
	for (int i = 0; i < nbk; i++)
	{
		for (int j = 0; j < nIn; j++)
		{
			int idx = i * nIn + j;
			
// #ifdef ZM_AD_IN_CU
// 			LG << "idx: " << outGd[idx];
// 			LG << "i: bkGd[i] " << bkGd[i]<<" i"<<i;
// 			LG << "j : " << inGd[j];
// 			LG << "-----------------";
// #endif

			inGd[j] += outGd[idx] * bkGd[i];
		}
	}
}


template<int _Id>
struct AdFReturnEDef {
	static const int out_dim = 1;
};


template<int _Id, int _GdDim_>
struct AdFOpDef_1 {
	AD_API static AdVal getAd(AdBf& bf, int dm) {return bf.getAD<_GdDim_>(dm);}
	AD_API static void op(AdBf in0, AdBf out) {}
	AD_API static void op(AdBf in0, AdBf in1, AdBf out) {}
};

template<int _Id, int _GdDim_>
struct AdFOpDef_2{
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }
	AD_API static void op(AdBf in0, AdBf in1, AdBf out) {}
};

template<int _Id, int _GdDim_>
struct AdFOpDef_3 {
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }
	AD_API static void op(AdBf in0, AdBf in1, AdBf in2, AdBf out) {}
};

template<int _Id, int _GdDim_>
struct AdFOpDef_4 {
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }
	AD_API static void op(AdBf in0, AdBf in1, AdBf in2, AdBf in3, AdBf out) {}
};

template<int _Id, int _GdDim_>
struct AdFOpDef_5 {
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }
	AD_API static void op(AdBf in0, AdBf in1, AdBf in2, AdBf in3, AdBf in4, AdBf out) {}
};

template<int _Id, int _GdDim_>
struct AdFOpDef_6 {
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }
	AD_API static void op(AdBf in0, AdBf in1, AdBf in2, AdBf in3, AdBf in4, AdBf in5, AdBf out) {}
};



//-------------------------------------


// define_ab_func2
// end_define_ab_func2


#define define_ab_func1(__id__, __r_out__) template<>\
struct AdFReturnEDef<__id__> {\
	static const int out_dim = __r_out__;\
};\
template<int _GdDim_>\
struct AdFOpDef_1<__id__, _GdDim_> {\
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }\
	AD_API static void op

#define end_define_ab_func1(__id__) };

///---

#define define_ab_func2(__id__, __r_out__) template<>\
struct AdFReturnEDef<__id__> {\
	static const int out_dim = __r_out__;\
};\
template<int _GdDim_>\
struct AdFOpDef_2<__id__, _GdDim_> {\
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }\
	AD_API static void op

#define end_define_ab_func2(__id__) };


//--

#define define_ab_func3(__id__, __r_out__) template<>\
struct AdFReturnEDef<__id__> {\
	static const int out_dim = __r_out__;\
};\
template<int _GdDim_>\
struct AdFOpDef_3<__id__, _GdDim_> {\
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }\
	AD_API static void op

#define end_define_ab_func3(__id__) };


//----

#define define_ab_func4(__id__, __r_out__) template<>\
struct AdFReturnEDef<__id__> {\
	static const int out_dim = __r_out__;\
};\
template<int _GdDim_>\
struct AdFOpDef_4<__id__, _GdDim_> {\
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }\
	AD_API static void op

#define end_define_ab_func4(__id__) };

//----

#define define_ab_func5(__id__, __r_out__) template<>\
struct AdFReturnEDef<__id__> {\
	static const int out_dim = __r_out__;\
};\
template<int _GdDim_>\
struct AdFOpDef_5<__id__, _GdDim_> {\
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }\
	AD_API static void op

#define end_define_ab_func5(__id__) };

#define define_ab_func6(__id__, __r_out__) template<>\
struct AdFReturnEDef<__id__> {\
	static const int out_dim = __r_out__;\
};\
template<int _GdDim_>\
struct AdFOpDef_6<__id__, _GdDim_> {\
	AD_API static AdVal getAd(AdBf& bf, int dm) { return bf.getAD<_GdDim_>(dm); }\
	AD_API static void op

#define end_define_ab_func6(__id__) };

/*
template<int _Id>
struct AdF
{
	static const int out_dim = 1;

	template<int _GdDim>
	struct In1
	{
		AD_API static void op(ABf in0, ABf out) {}

	};
	template<int _GdDim>
	struct In2
	{
		AD_API static void op(ABf in0, ABf in1, ABf out) {}
	};
	template<int _GdDim>
	struct In3
	{
		AD_API static void op(ABf in0, ABf in1, ABf in2, ABf out) {}
	};
	template<int _GdDim>
	struct In4
	{
		AD_API static void op(ABf in0, ABf in1, ABf in2, ABf in3, ABf out) {}
	};
};
*/

// template<int _Id>
// struct AdF2
// {
// 	template<int _GdDim>
// 	struct Inner1
// 	{
// 		static const int out_dim = 0;
// 		AD_API static void op(ABf in0, ABf in1, ABf out) {
// 
// 		}
// 	};
// };


#include "my_cus_func.hpp"










