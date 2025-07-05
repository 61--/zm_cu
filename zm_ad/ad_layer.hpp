#pragma once

#include "ad_inner/ad_core.hpp"


template<int _Id>
class CusLayer : public tr::autograd::Function<CusLayer<_Id>>
{
public:

	static at::Tensor forward(
		tr::autograd::AutogradContext* ctx
		, at::Tensor t0)
	{
		_InnerAdLayer<_Id> inner_;
		return inner_.forward({ t0 }, ctx);
	}

	static at::Tensor forward(
		tr::autograd::AutogradContext* ctx
		, at::Tensor t0
		, at::Tensor t1)
	{
		_InnerAdLayer<_Id> inner_;
		return inner_.forward({ t0, t1 }, ctx);
	}
	static at::Tensor forward(
		tr::autograd::AutogradContext* ctx
		, at::Tensor t0
		, at::Tensor t1
		, at::Tensor t2)
	{
		_InnerAdLayer<_Id> inner_;
		return inner_.forward({ t0, t1,t2 }, ctx);
	}
	static at::Tensor forward(
		tr::autograd::AutogradContext* ctx
		, at::Tensor t0
		, at::Tensor t1
		, at::Tensor t2
		, at::Tensor t3)
	{
		_InnerAdLayer<_Id> inner_;
		return inner_.forward({ t0, t1,t2,t3 }, ctx);
	}
	static at::Tensor forward(
		tr::autograd::AutogradContext* ctx
		, at::Tensor t0
		, at::Tensor t1
		, at::Tensor t2
		, at::Tensor t3
		, at::Tensor t4)
	{
		_InnerAdLayer<_Id> inner_;
		return inner_.forward({ t0, t1,t2,t3,t4 }, ctx);
	}
	static at::Tensor forward(
		tr::autograd::AutogradContext* ctx
		, at::Tensor t0
		, at::Tensor t1
		, at::Tensor t2
		, at::Tensor t3
		, at::Tensor t4
		, at::Tensor t5)
	{
		_InnerAdLayer<_Id> inner_;
		return inner_.forward({ t0, t1,t2,t3,t4,t5 }, ctx);
	}

	static torch::autograd::tensor_list backward(
		torch::autograd::AutogradContext* ctx
		, torch::autograd::tensor_list grad_outputs)
	{
		_InnerAdLayer<_Id> inner_;
		return inner_.backward(grad_outputs[0], ctx);
	}

//private:
//	static texelFetchLy<_Id> inner_;
};


//template<int _Id>
//texelFetchLy<_Id> CusLayer<_Id>::inner_;
