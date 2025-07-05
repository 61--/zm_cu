#pragma once



#include <torch/torch.h>


namespace tr = torch;
typedef  at::Tensor TMat;


inline void to_gpu_(TMat& tm) {
	tm = tm.to(torch::kCUDA);
}

inline TMat to_gpu(TMat tm) {
	return tm.to(torch::kCUDA);
}

inline bool checkIsGPU(const TMat& m) {
	if (m.device().is_cuda())
		return true;
	return false;
}

struct IntArray
{
	IntArray() {}

	template<typename _T>
	IntArray(std::initializer_list<_T> vs) {
		std::vector<_T> v_vs(vs.begin(), vs.end());
		datas.resize(v_vs.size());
		for (int i = 0; i < v_vs.size(); i++) {
			datas[i] = (int)v_vs[i];
		}
	}

	IntArray(std::initializer_list<int64_t> vs) {
		std::vector<int64_t> v_vs(vs.begin(), vs.end());
		datas.resize(v_vs.size());
		for (int i = 0; i < v_vs.size(); i++) {
			datas[i] = (int)v_vs[i];
		}
	}

	template<typename _T>
	IntArray(const std::vector<_T>& vs) {
		datas.resize(vs.size());
		for (int i = 0; i < vs.size(); i++) {
			datas[i] = vs[i];
		}
	}

	IntArray(c10::IntArrayRef sz_ay)
	{
		datas.resize(sz_ay.size());
		for (int i = 0; i < sz_ay.size(); i++)
		{
			datas[i] = sz_ay[i];
		}
	}

	IntArray(int v0) {
		datas = { v0 };
	}
	IntArray(int v0, int v1) {
		datas = { v0, v1 };
	}
	IntArray(int v0, int v1, int v2) {
		datas = { v0, v1 , v2 };
	}
	IntArray(int v0, int v1, int v2, int v3) {
		datas = { v0, v1 , v2, v3 };
	}

	int len() {
		return datas.size();
	}
	int len() const {
		return datas.size();
	}

	int getVal(int idx) {
		return datas[idx];
	}
	int getVal(int idx) const {
		if (idx <0 || idx> datas.size()) {
			//LG_FT << "invalid idx: " << idx;
			return 0;
		}
		return datas[idx];
	}

	void setVal(int idx, int v) {
		datas.at(idx) = v;
	}

	std::vector<int64_t> to_vector_int64_t() const {
		std::vector<int64_t> ret(datas.size());
		for (int i = 0; i < datas.size(); i++)
		{
			ret[i] = datas[i];
		}
		return ret;
	}

	int volume() const {
		if (len() == 0)
			return 0;

		int n = 1;
		for (int i = 0; i < len(); i++)
		{
			n *= getVal(i);
		}
		return n;
	}

private:
	std::vector<int> datas;
};


inline bool operator==(const IntArray& i1, const IntArray& i2)
{
	if (i1.len() != i2.len())
		return false;

	int n1 = i1.len();
	for (int i = 0; i < n1; i++)
	{
		if (i1.getVal(i) != i2.getVal(i))
			return false;
	}
	return true;
}

inline bool operator!=(const IntArray& i1, const IntArray& i2)
{
	if (i1 == i2)
		return false;
	return true;
}



template<typename _T>
at::Tensor createTMat(const IntArray& sz
	, const std::vector<_T>& data
	, c10::ScalarType ty)
{
// 	FT_IF(sz.volume() > data.size())
// 		<< "crateTMat invalid:  sz:" << sz
// 		<< " - dataLen:" << data.size();
// 	FT_IF(sz.getVal(0) <= 0);

	std::vector<int64_t> ay = sz.to_vector_int64_t();
	c10::IntArrayRef c10_sz(ay);

	at::Tensor ret;
	if (typeid(_T) == typeid(double))
	{
		at::Tensor t = torch::from_blob((void*)data.data(), c10_sz, at::kDouble);
		ret = t.clone().to(ty);
	}
	else if (typeid(_T) == typeid(float))
	{
		at::Tensor t = torch::from_blob((void*)data.data(), c10_sz, at::kFloat);
		ret = t.clone().to(ty);
	}
	else if (typeid(_T) == typeid(int64_t))
	{
		at::Tensor t = torch::from_blob((void*)data.data(), c10_sz, at::kLong);
		ret = t.clone().to(ty);
	}
	else if (typeid(_T) == typeid(int32_t))
	{
		at::Tensor t = torch::from_blob((void*)data.data(), c10_sz, at::kInt);
		ret = t.clone().to(ty);
	}
	else {
		//LG_FT << "invalid type";
	}
	return ret;
}

inline at::Tensor createZeroTMat(const IntArray& idx
	, c10::ScalarType ty
	, bool use_gpu = false)
{
	std::vector<int64_t> ay = idx.to_vector_int64_t();
	c10::IntArrayRef ret(ay);

	at::Tensor t = at::zeros(ret, tr::dtype(ty));
	if (use_gpu) {
		to_gpu_(t);
	}
	return t;
}

inline at::Tensor createOneTMat(const IntArray& idx
	, c10::ScalarType ty)
{
	std::vector<int64_t> ay = idx.to_vector_int64_t();
	c10::IntArrayRef ret(ay);

	at::Tensor t = at::ones(ret, tr::dtype(ty));
	return t;
}


inline TMat rowLike(TMat tm, int n, c10::ScalarType tp)
{
	TMat m = createZeroTMat({ tm.size(0),n }, tp);

	if (checkIsGPU(tm)) {
		//LG << "m: " << m;
		m = to_gpu(m);
	}
	return m;
}

inline TMat rowLike(TMat tm, int n, double v, c10::ScalarType tp)
{
	TMat m = createOneTMat({ tm.size(0),n }, tp) * v;

	if (checkIsGPU(tm)) {
		//LG << "m: " << m;
		m = to_gpu(m);
	}
	return m;
}

inline TMat to_cpu(TMat tm) {
	return tm.to(torch::kCPU);
}

inline double to_double(TMat _v)
{
	TMat v = _v.reshape({ 1 });
	v = v.to(tr::kF64);
	v = to_cpu(v);
	return *v.data_ptr<double>();
}

inline void EnsureSameDim0(const TMat& m0, const TMat& m1) {
// 	FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars1: " << m1.size(0);
}

inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2) {
// 	FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars1: " << m1.size(0);
// 
// 	FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars2: " << m2.size(0);
}

inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3) {
// 	FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars1: " << m1.size(0);
// 
// 	FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars2: " << m2.size(0);
// 
// 	FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars3: " << m3.size(0);
}

inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3, const TMat& m4) {
// 	FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars1: " << m1.size(0);
// 
// 	FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars2: " << m2.size(0);
// 
// 	FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars3: " << m3.size(0);
// 
// 	FT_IF(m0.size(0) != m4.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars4: " << m4.size(0);

}

inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3, const TMat& m4, const TMat& m5) {
// 	FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars1: " << m1.size(0);
// 
// 	FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars2: " << m2.size(0);
// 
// 	FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars3: " << m3.size(0);
// 
// 	FT_IF(m0.size(0) != m4.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars4: " << m4.size(0);
// 
// 	FT_IF(m0.size(0) != m5.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars5: " << m5.size(0);
}

inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6) {
// 	FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars1: " << m1.size(0);
// 
// 	FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars2: " << m2.size(0);
// 
// 	FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars3: " << m3.size(0);
// 
// 	FT_IF(m0.size(0) != m4.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars4: " << m4.size(0);
// 
// 	FT_IF(m0.size(0) != m5.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars5: " << m5.size(0);
// 
// 	FT_IF(m0.size(0) != m6.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars6: " << m6.size(0);
}

inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6, const TMat& m7) {
// 	FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars1: " << m1.size(0);
// 
// 	FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars2: " << m2.size(0);
// 
// 	FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars3: " << m3.size(0);
// 
// 	FT_IF(m0.size(0) != m4.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars4: " << m4.size(0);
// 
// 	FT_IF(m0.size(0) != m5.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars5: " << m5.size(0);
// 
// 	FT_IF(m0.size(0) != m6.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars6: " << m6.size(0);
// 
// 	FT_IF(m0.size(0) != m7.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars7: " << m7.size(0);
}

inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6
	, const TMat& m7, const TMat& m8) {
// 	FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars1: " << m1.size(0);
// 
// 	FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars2: " << m2.size(0);
// 
// 	FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars3: " << m3.size(0);
// 
// 	FT_IF(m0.size(0) != m4.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars4: " << m4.size(0);
// 
// 	FT_IF(m0.size(0) != m5.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars5: " << m5.size(0);
// 
// 	FT_IF(m0.size(0) != m6.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars6: " << m6.size(0);
// 
// 	FT_IF(m0.size(0) != m7.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars7: " << m7.size(0);
// 
// 	FT_IF(m0.size(0) != m8.size(0)) << "invalid dim0: "
// 		<< " pars0: " << m0.size(0)
// 		<< " pars8: " << m8.size(0);
}


inline void EnsureSameDev(const TMat& m0, const TMat& m1) {
// 	FT_IF(m0.device() != m1.device()) << "invalid dim0: "
// 		<< " pars0: " << m0.device()
// 		<< " pars1: " << m1.device();
}

inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2) {
// 	FT_IF(m0.device() != m1.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars1: " << m1.device();
// 	FT_IF(m0.device() != m2.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars2: " << m2.device();
}

inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3) {
// 	FT_IF(m0.device() != m1.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars1: " << m1.device();
// 	FT_IF(m0.device() != m2.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars2: " << m2.device();
// 	FT_IF(m0.device() != m3.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars3: " << m3.device();
}

inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3, const TMat& m4) {
// 	FT_IF(m0.device() != m1.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars1: " << m1.device();
// 	FT_IF(m0.device() != m2.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars2: " << m2.device();
// 	FT_IF(m0.device() != m3.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars3: " << m3.device();
// 	FT_IF(m0.device() != m4.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars4: " << m4.device();
}

inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3, const TMat& m4, const TMat& m5) {
// 	FT_IF(m0.device() != m1.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars1: " << m1.device();
// 	FT_IF(m0.device() != m2.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars2: " << m2.device();
// 	FT_IF(m0.device() != m3.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars3: " << m3.device();
// 	FT_IF(m0.device() != m4.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars4: " << m4.device();
// 	FT_IF(m0.device() != m5.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars5: " << m5.device();
}

inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6) {
// 	FT_IF(m0.device() != m1.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars1: " << m1.device();
// 	FT_IF(m0.device() != m2.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars2: " << m2.device();
// 	FT_IF(m0.device() != m3.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars3: " << m3.device();
// 	FT_IF(m0.device() != m4.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars4: " << m4.device();
// 	FT_IF(m0.device() != m5.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars5: " << m5.device();
// 
// 	FT_IF(m0.device() != m6.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars6: " << m6.device();
}

inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6, const TMat& m7) {
// 	FT_IF(m0.device() != m1.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars1: " << m1.device();
// 	FT_IF(m0.device() != m2.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars2: " << m2.device();
// 	FT_IF(m0.device() != m3.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars3: " << m3.device();
// 	FT_IF(m0.device() != m4.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars4: " << m4.device();
// 	FT_IF(m0.device() != m5.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars5: " << m5.device();
// 
// 	FT_IF(m0.device() != m6.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars6: " << m6.device();
// 	FT_IF(m0.device() != m7.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars7: " << m7.device();
}

inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
	, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6
	, const TMat& m7, const TMat& m8) {
// 	FT_IF(m0.device() != m1.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars1: " << m1.device();
// 	FT_IF(m0.device() != m2.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars2: " << m2.device();
// 	FT_IF(m0.device() != m3.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars3: " << m3.device();
// 	FT_IF(m0.device() != m4.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars4: " << m4.device();
// 	FT_IF(m0.device() != m5.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars5: " << m5.device();
// 
// 	FT_IF(m0.device() != m6.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars6: " << m6.device();
// 	FT_IF(m0.device() != m7.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars7: " << m7.device();
// 
// 	FT_IF(m0.device() != m8.device()) << "invalid dev: "
// 		<< " pars0: " << m0.device()
// 		<< " pars8: " << m8.device();
}