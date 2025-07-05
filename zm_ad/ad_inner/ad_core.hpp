#pragma once
#include <vector>



#include "zm_tr.hpp"
#include "zm_array.hpp"
#include "ad_func.hpp"


#include "cx_ad_func.hpp"



template<int _Id, int _GDim_>
void _InnerAdFunc1(int npars, TMat in0, TMat inG0, TMat out0, TMat outG)
{
#ifdef _DEBUG
	EnsureSameDev(in0, inG0, out0, outG);
#endif

	_cx_AdF1<_Id, _GDim_>(checkIsGPU(in0), in0.size(0), npars
		, in0.data_ptr(), in0.size(1)
		, inG0.data_ptr(), inG0.size(1)
		, out0.data_ptr(), out0.size(1)
		, outG.data_ptr(), outG.size(1));
}

template<int _Id, int _GDim_>
void _InnerAdFunc2(int npars
	, TMat in0, TMat inG0
	, TMat in1, TMat inG1
	, TMat out0, TMat outG)
{
	_cx_AdF2<_Id, _GDim_>(checkIsGPU(in0), in0.size(0), npars
		, in0.data_ptr(), in0.size(1)
		, inG0.data_ptr(), inG0.size(1)
		, in1.data_ptr(), in1.size(1)
		, inG1.data_ptr(), inG1.size(1)
		, out0.data_ptr(), out0.size(1)
		, outG.data_ptr(), outG.size(1));
}

template<int _Id, int _GDim_>
void _InnerAdFunc3(int npars
	, TMat in0, TMat inG0
	, TMat in1, TMat inG1
	, TMat in2, TMat inG2
	, TMat out0, TMat outG)
{
	_cx_AdF3<_Id, _GDim_>(checkIsGPU(in0), in0.size(0), npars
		, in0.data_ptr(), in0.size(1)
		, inG0.data_ptr(), inG0.size(1)
		, in1.data_ptr(), in1.size(1)
		, inG1.data_ptr(), inG1.size(1)
		, in2.data_ptr(), in2.size(1)
		, inG2.data_ptr(), inG2.size(1)
		, out0.data_ptr(), out0.size(1)
		, outG.data_ptr(), outG.size(1));
}

template<int _Id, int _GDim_>
void _InnerAdFunc4(int npars
	, TMat in0, TMat inG0
	, TMat in1, TMat inG1
	, TMat in2, TMat inG2
	, TMat in3, TMat inG3
	, TMat out0, TMat outG)
{
	_cx_AdF4<_Id, _GDim_>(checkIsGPU(in0), in0.size(0), npars
		, in0.data_ptr(), in0.size(1)
		, inG0.data_ptr(), inG0.size(1)
		, in1.data_ptr(), in1.size(1)
		, inG1.data_ptr(), inG1.size(1)
		, in2.data_ptr(), in2.size(1)
		, inG2.data_ptr(), inG2.size(1)
		, in3.data_ptr(), in3.size(1)
		, inG3.data_ptr(), inG3.size(1)
		, out0.data_ptr(), out0.size(1)
		, outG.data_ptr(), outG.size(1));
}

template<int _Id, int _GDim_>
void _InnerAdFunc5(int npars
	, TMat in0, TMat inG0
	, TMat in1, TMat inG1
	, TMat in2, TMat inG2
	, TMat in3, TMat inG3
	, TMat in4, TMat inG4
	, TMat out0, TMat outG)
{
	_cx_AdF5<_Id, _GDim_>(checkIsGPU(in0), in0.size(0), npars
		, in0.data_ptr(), in0.size(1)
		, inG0.data_ptr(), inG0.size(1)
		, in1.data_ptr(), in1.size(1)
		, inG1.data_ptr(), inG1.size(1)
		, in2.data_ptr(), in2.size(1)
		, inG2.data_ptr(), inG2.size(1)
		, in3.data_ptr(), in3.size(1)
		, inG3.data_ptr(), inG3.size(1)
		, in4.data_ptr(), in4.size(1)
		, inG4.data_ptr(), inG4.size(1)
		, out0.data_ptr(), out0.size(1)
		, outG.data_ptr(), outG.size(1));
}

template<int _Id, int _GDim_>
void _InnerAdFunc6(int npars
	, TMat in0, TMat inG0
	, TMat in1, TMat inG1
	, TMat in2, TMat inG2
	, TMat in3, TMat inG3
	, TMat in4, TMat inG4
	, TMat in5, TMat inG5
	, TMat out0, TMat outG)
{
	_cx_AdF6<_Id, _GDim_>(checkIsGPU(in0), in0.size(0), npars
		, in0.data_ptr(), in0.size(1)
		, inG0.data_ptr(), inG0.size(1)
		, in1.data_ptr(), in1.size(1)
		, inG1.data_ptr(), inG1.size(1)
		, in2.data_ptr(), in2.size(1)
		, inG2.data_ptr(), inG2.size(1)
		, in3.data_ptr(), in3.size(1)
		, inG3.data_ptr(), inG3.size(1)
		, in4.data_ptr(), in4.size(1)
		, inG4.data_ptr(), inG4.size(1)
		, in5.data_ptr(), in5.size(1)
		, inG5.data_ptr(), inG5.size(1)
		, out0.data_ptr(), out0.size(1)
		, outG.data_ptr(), outG.size(1));
}




template<int _Id, int _GDim_>
void _InnerAdFuncX(int npars
	, const std::vector<TMat>& ins
	, const std::vector<TMat>& inGs
	, TMat out0, TMat outG)
{
#ifdef _DEBUG
	zm::EnsureSameSize(ins, inGs);
#endif

	if (ins.size() == 1) {
		_InnerAdFunc1<_Id, _GDim_>(npars, ins[0], inGs[0], out0, outG);
	}
	else if (ins.size() == 2)
	{
		_InnerAdFunc2<_Id, _GDim_>(npars
			, ins[0], inGs[0]
			, ins[1], inGs[1]
			, out0, outG);
	}
	else if (ins.size() == 3)
	{
		_InnerAdFunc3<_Id, _GDim_>(npars
			, ins[0], inGs[0]
			, ins[1], inGs[1]
			, ins[2], inGs[2]
			, out0, outG);
	}
	else if (ins.size() == 4)
	{
		_InnerAdFunc4<_Id, _GDim_>(npars
			, ins[0], inGs[0]
			, ins[1], inGs[1]
			, ins[2], inGs[2]
			, ins[3], inGs[3]
			, out0, outG);
	}
	else if (ins.size() == 5)
	{
		_InnerAdFunc5<_Id, _GDim_>(npars
			, ins[0], inGs[0]
			, ins[1], inGs[1]
			, ins[2], inGs[2]
			, ins[3], inGs[3]
			, ins[4], inGs[4]
			, out0, outG);
	}
	else if (ins.size() == 6)
	{
		_InnerAdFunc6<_Id, _GDim_>(npars
			, ins[0], inGs[0]
			, ins[1], inGs[1]
			, ins[2], inGs[2]
			, ins[3], inGs[3]
			, ins[4], inGs[4]
			, ins[5], inGs[5]
			, out0, outG);
	}
	else
	{
		std::cout << "undefine"<<std::endl;
	}
}

// 
// template<int _Id>
// void rendF1(int npars, TMat in0, TMat inG0, TMat out0, TMat outG)
// {
// 	if (npars < 100) {
// 		_rendF1<_Id, 100>(npars, in0, inG0, out0, outG);
// 	}
// 	else {
// 		_rendF1<_Id, 1000>(npars, in0, inG0, out0, outG);
// 	}
// }
// 
// template<int _Id>
// void rendF2(int npars
// 	, TMat in0, TMat inG0
// 	, TMat in1, TMat inG1
// 	, TMat out0, TMat outG)
// {
// 	if (npars < 100) {
// 		_rendF2<_Id, 100>(npars, in0, inG0, in1, inG1, out0, outG);
// 	}
// 	else {
// 		_rendF2<_Id, 1000>(npars, in0, inG0, in1, inG1, out0, outG);
// 	}
// }
// 



template<int _Id>
void InnerAdFuncX(int npars
	, const std::vector<TMat>& ins
	, const std::vector<TMat>& inGs
	, TMat out0, TMat outG)
{
#ifdef _DEBUG
	if (npars < 300) {
		_InnerAdFuncX<_Id, 300>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 2000) {
		_InnerAdFuncX<_Id, 2000>(npars, ins, inGs, out0, outG);
	}
	else {
		std::cout << "unsupport"<<std::endl;
	}
#else
	if (npars < 10) {
		_InnerAdFuncX<_Id, 10>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 20) {
		_InnerAdFuncX<_Id, 20>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 50) {
		_InnerAdFuncX<_Id, 50>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 100) {
		_InnerAdFuncX<_Id, 100>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 200) {
		_InnerAdFuncX<_Id, 200>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 300) {
		_InnerAdFuncX<_Id, 300>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 500) {
		_InnerAdFuncX<_Id, 500>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 800) {
		_InnerAdFuncX<_Id, 800>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 1000) {
		_InnerAdFuncX<_Id, 1000>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 2000) {
		_InnerAdFuncX<_Id, 2000>(npars, ins, inGs, out0, outG);
	}
	else if (npars < 3000) {
		_InnerAdFuncX<_Id, 3000>(npars, ins, inGs, out0, outG);
	}
	else {
		//LG_FT << "unsupport";
	}
#endif

}



void _GradBackCompute(const TMat& bkGd, const TMat& outGd, TMat& inGd)
{
#ifdef _DEBUG
	EnsureSameDev(bkGd, outGd, inGd);
#endif

	_cx_materialBack(checkIsGPU(bkGd), bkGd.size(0)
		, bkGd.data_ptr<Ad_Ftype>(), bkGd.size(1)
		, outGd.data_ptr<Ad_Ftype>(), outGd.size(1)
		, inGd.data_ptr<Ad_Ftype>(), inGd.size(1));
}


//-----

template<int _Id>
class _InerLayerForward
{
public:

	TMat _createGIn(int r, int pars_dim, int in_dim, int start_dim, bool gpu)
	{
		std::vector<double> vs(in_dim * pars_dim, 0);

		for (int i = 0; i < in_dim; i++)
		{
			vs[i * pars_dim + start_dim + i] = 1;
		}

		TMat ret = createTMat<double>({ 1, in_dim * pars_dim }, vs, Ad_KF);
		if (gpu)
			to_gpu_(ret);

		ret = ret.repeat({ r,1 });

		return ret;
	}


	std::vector<TMat> _createInRowSizeLike(const std::vector<TMat>& ins)
	{
		std::vector<TMat> szs(ins.size());
		for (int i = 0; i < ins.size(); i++)
		{
			szs[i] = createZeroTMat({ 1, ins[i].size(1) }, Ad_KF);
			if (checkIsGPU(ins[i])) {
				to_gpu_(szs[i]);
			}
		}
		return szs;
	}

	void forward(const std::vector<TMat>& ins
		, std::vector<TMat>& inRowSizeLike
		, TMat& out, TMat& outG)
	{
		const int n_out = AdFReturnEDef<_Id>::out_dim;
		int dim_in = 0;
		for (auto& in : ins) {
			dim_in += (int)in.size(1);
		}

		// 		if (inRowSizeLike_.empty())
		// 		{
		// 			inRowSizeLike_ = _createInRowSizeLike(ins);
		// 		}
		inRowSizeLike = _createInRowSizeLike(ins);

		auto createInGs = [&]()->std::vector<TMat>
		{
			std::vector<TMat> inGs(ins.size());
			int n_start = 0;
			for (int i = 0; i < ins.size(); i++)
			{

				inGs[i] = _createGIn(ins[i].size(0), dim_in, ins[i].size(1), n_start, checkIsGPU(ins[i]));
				n_start += ins[i].size(1);
				//inGs[i] = zm::rowLike(ins[0], ins[0].size(1) * dim_in, Ad_KF);
			}
			return inGs;
		};

		// 		if (inGs_.empty()) {
		// 			inGs_ = createInGs();
		// 		}

		std::vector<TMat> inGs = createInGs();


		out = rowLike(ins[0], n_out, Ad_KF);
		outG = rowLike(ins[0], n_out * dim_in, Ad_KF);

		InnerAdFuncX<_Id>(dim_in, ins, inGs, out, outG);

	}

	//std::vector<TMat> inRowSizeLike_;
	//std::vector<TMat> inGs_;
};


inline std::vector<TMat> GradBakwareCompute(TMat _bkGd
	, const std::vector<TMat>& inRowSizeLike
	, TMat outgd)
{
	TMat bkGd = _bkGd.clone();

	int nPars = 0;

	for (int i = 0; i < inRowSizeLike.size(); i++)
	{
		nPars += inRowSizeLike[i].size(1);

	}

	TMat inGd = rowLike(bkGd, nPars, Ad_KF);


	//  	LG << "outgd: " << outgd;
	// // 	LG << "inGd: " << inGd;
	// // 
	//  	LG << "bkGd: " << bkGd;
	// 	Ad_Ftype* pdata = bkGd.data_ptr<Ad_Ftype>();
	// 	LG << "data[0]: " << pdata[0];
	// 	LG << "data[1]: " << pdata[1];

	_GradBackCompute(bkGd, outgd, inGd);

	std::vector<TMat> inGds(inRowSizeLike.size());

	int n_start = 0;
	for (int i = 0; i < inRowSizeLike.size(); i++)
	{
		inGds[i] = inGd.index({ "...", tr::indexing::Slice(n_start, n_start + inRowSizeLike[i].size(1)) });

		n_start += inRowSizeLike[i].size(1);
	}

	// 	LG << "rowlike: " << inRowSizeLike;
	// 	LG << "inGd: " << inGd;
	// 	LG << "inGds: " << inGds;



		//LG << "inGd: " << inGd;
	return inGds;

}


template<int _Id>
class _InnerAdLayer
{
public:
	TMat forward(std::vector<TMat> ins, torch::autograd::AutogradContext* ctx)
	{
		std::vector<TMat> inRowSizeLike_;
		TMat outG_;

		_InerLayerForward<_Id> ly_;
		TMat out;
		ly_.forward(ins, inRowSizeLike_, out, outG_);

		
		std::vector<TMat> save_datas = inRowSizeLike_;
		save_datas.push_back(outG_);
		ctx->save_for_backward(save_datas);

		return out;
	}
	std::vector<TMat> backward(TMat gBk, torch::autograd::AutogradContext* ctx)
	{
		//LG << "gBk: " << gBk;

		std::vector<TMat> save_datas = ctx->get_saved_variables();
		TMat outG_ = save_datas.back();

		save_datas.pop_back();
		std::vector<TMat> inRowSizeLike_ = save_datas;

		std::vector<TMat> gIns;

		gIns = GradBakwareCompute(gBk, inRowSizeLike_, outG_);

		//LG << "gIns: " << gIns;

		return gIns;
	}

	
	
};

