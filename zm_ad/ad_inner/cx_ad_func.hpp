#pragma once
#include "ad_func.hpp"

#include "cp_ad_func.hpp"
#include "_cu_ad_inner.h"





template<int _Id, int _GDim_>
inline void _cx_AdF1(bool is_gp, int s0, int gDm
	, void* pIn0, int in0_s1
	, void* pInG0, int inG0_s1
	, void* pOut, int out_s1
	, void* pOutG, int outG_s1)
{
	if (is_gp)
	{
		_cu_AdF1<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
	else
	{
		_cp_AdF1<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
}

template<int _Id, int _GDim_>
inline void _cx_AdF2(bool is_gp, int s0, int gDm
	, void* pIn0, int in0_s1
	, void* pInG0, int inG0_s1
	, void* pIn1, int in1_s1
	, void* pInG1, int inG1_s1
	, void* pOut, int out_s1
	, void* pOutG, int outG_s1)
{
	if (is_gp)
	{
		_cu_AdF2<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pIn1, in1_s1, pInG1, inG1_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
	else
	{
		_cp_AdF2<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pIn1, in1_s1, pInG1, inG1_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
}

template<int _Id, int _GDim_>
inline void _cx_AdF3(bool is_gp, int s0, int gDm
	, void* pIn0, int in0_s1
	, void* pInG0, int inG0_s1
	, void* pIn1, int in1_s1
	, void* pInG1, int inG1_s1
	, void* pIn2, int in2_s1
	, void* pInG2, int inG2_s1
	, void* pOut, int out_s1
	, void* pOutG, int outG_s1)
{
	if (is_gp)
	{
		_cu_AdF3<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pIn1, in1_s1, pInG1, inG1_s1
			, pIn2, in2_s1, pInG2, inG2_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
	else
	{
		_cp_AdF3<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pIn1, in1_s1, pInG1, inG1_s1
			, pIn2, in2_s1, pInG2, inG2_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
}


template<int _Id, int _GDim_>
inline void _cx_AdF4(bool is_gp, int s0, int gDm
	, void* pIn0, int in0_s1
	, void* pInG0, int inG0_s1
	, void* pIn1, int in1_s1
	, void* pInG1, int inG1_s1
	, void* pIn2, int in2_s1
	, void* pInG2, int inG2_s1
	, void* pIn3, int in3_s1
	, void* pInG3, int inG3_s1
	, void* pOut, int out_s1
	, void* pOutG, int outG_s1)
{
	if (is_gp)
	{
		_cu_AdF4<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pIn1, in1_s1, pInG1, inG1_s1
			, pIn2, in2_s1, pInG2, inG2_s1
			, pIn3, in3_s1, pInG3, inG3_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
	else
	{
		_cp_AdF4<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pIn1, in1_s1, pInG1, inG1_s1
			, pIn2, in2_s1, pInG2, inG2_s1
			, pIn3, in3_s1, pInG3, inG3_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
}

template<int _Id, int _GDim_>
inline void _cx_AdF5(bool is_gp, int s0, int gDm
	, void* pIn0, int in0_s1
	, void* pInG0, int inG0_s1
	, void* pIn1, int in1_s1
	, void* pInG1, int inG1_s1
	, void* pIn2, int in2_s1
	, void* pInG2, int inG2_s1
	, void* pIn3, int in3_s1
	, void* pInG3, int inG3_s1
	, void* pIn4, int in4_s1
	, void* pInG4, int inG4_s1
	, void* pOut, int out_s1
	, void* pOutG, int outG_s1)
{
	if (is_gp)
	{
		_cu_AdF5<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pIn1, in1_s1, pInG1, inG1_s1
			, pIn2, in2_s1, pInG2, inG2_s1
			, pIn3, in3_s1, pInG3, inG3_s1
			, pIn4, in4_s1, pInG4, inG4_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
	else
	{
		_cp_AdF5<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pIn1, in1_s1, pInG1, inG1_s1
			, pIn2, in2_s1, pInG2, inG2_s1
			, pIn3, in3_s1, pInG3, inG3_s1
			, pIn4, in4_s1, pInG4, inG4_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
}



template<int _Id, int _GDim_>
inline void _cx_AdF6(bool is_gp, int s0, int gDm
	, void* pIn0, int in0_s1
	, void* pInG0, int inG0_s1
	, void* pIn1, int in1_s1
	, void* pInG1, int inG1_s1
	, void* pIn2, int in2_s1
	, void* pInG2, int inG2_s1
	, void* pIn3, int in3_s1
	, void* pInG3, int inG3_s1
	, void* pIn4, int in4_s1
	, void* pInG4, int inG4_s1
	, void* pIn5, int in5_s1
	, void* pInG5, int inG5_s1
	, void* pOut, int out_s1
	, void* pOutG, int outG_s1)
{
	if (is_gp)
	{
		_cu_AdF6<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pIn1, in1_s1, pInG1, inG1_s1
			, pIn2, in2_s1, pInG2, inG2_s1
			, pIn3, in3_s1, pInG3, inG3_s1
			, pIn4, in4_s1, pInG4, inG4_s1
			, pIn5, in5_s1, pInG5, inG5_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
	else
	{
		_cp_AdF6<_Id, _GDim_>(s0, gDm
			, pIn0, in0_s1, pInG0, inG0_s1
			, pIn1, in1_s1, pInG1, inG1_s1
			, pIn2, in2_s1, pInG2, inG2_s1
			, pIn3, in3_s1, pInG3, inG3_s1
			, pIn4, in4_s1, pInG4, inG4_s1
			, pIn5, in5_s1, pInG5, inG5_s1
			, pOut, out_s1, pOutG, outG_s1);
	}
}

inline void _cx_materialBack(bool is_gp, int s0
	, Ad_Ftype* pBkGd, int bkGd_s1
	, Ad_Ftype* pOutGd, int outGd_s1
	, Ad_Ftype* pInGd, int inGd_s1)
{
	if (is_gp)
	{
		_cu_materialBack(s0
			, pBkGd, bkGd_s1
			, pOutGd, outGd_s1
			, pInGd, inGd_s1);
	}
	else
	{
		_cp_materialBack(s0
			, pBkGd, bkGd_s1
			, pOutGd, outGd_s1
			, pInGd, inGd_s1);
	}
}

/*

template<int _Id, int _GDim_>
inline void _cp_AdF1(int s0, int gDm
	, void* pIn0, int in0_s1
	, void* pInG0, int inG0_s1
	, void* pOut, int out_s1
	, void* pOutG, int outG_s1)
{
	for (int i = 0; i < s0; i++)
	{
		ABf bf_in0(i, in0_s1, pIn0, pInG0, gDm);
		ABf bf_out(i, out_s1, pOut, pOutG, gDm);

		AdF<_Id>::In1<_GDim_>::op(bf_in0, bf_out);
	}
}

template<int _Id, int _GDim_>
inline void _cp_AdF2(int s0, int gDm
	, void* pIn0, int in0_s1
	, void* pInG0, int inG0_s1
	, void* pIn1, int in1_s1
	, void* pInG1, int inG1_s1
	, void* pOut, int out_s1
	, void* pOutG, int outG_s1)
{
	for (int i = 0; i < s0; i++)
	{
		ABf bf_in0(i, in0_s1, pIn0, pInG0, gDm);
		ABf bf_in1(i, in1_s1, pIn1, pInG1, gDm);
		ABf bf_out(i, out_s1, pOut, pOutG, gDm);

		AdF<_Id>::In2<_GDim_>::op(bf_in0, bf_in1, bf_out);
	}
}



inline void _cp_materialBack(int s0
	, Ad_Ftype* pBkGd, int bkGd_s1
	, Ad_Ftype* pOutGd, int outGd_s1
	, Ad_Ftype* pInGd, int inGd_s1)
{
	assert(inGd_s1 * bkGd_s1 == outGd_s1);

	for (int i = 0; i < s0; i++)
	{
		_RawBf bkGd(i, pBkGd, bkGd_s1);
		_RawBf outGd(i, pOutGd, outGd_s1);
		_RawBf inGd(i, pInGd, inGd_s1);

		//LG<<"bkGD: "<<bkGd[0];



		_materialBack(bkGd, bkGd_s1, outGd, inGd, inGd_s1);
	}
}



*/