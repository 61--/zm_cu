#pragma once


#include "ad_val.hpp"



class AdBf
{
public:
	AD_API AdBf() {

	}

	AD_API AdBf(int r, int s1, void* data, void* gData, int gDm) {
		r_ = r;
		s1_ = s1;
		data_ = (Ad_Ftype*)data;
		gData_ = (Ad_Ftype*)gData;
		gDm_ = gDm;
	}

	template<int _N>
	AD_API _AdVal<_N> getAD(int i) const
	{
		assert(_N >= gDm_);

		_AdVal<_N> val;
		val.val = data_[i + r_ * s1_];
		
		double* start_p = gData_ + (i + r_ * s1_) * gDm_;
		memcpy(&val.gd[0], start_p, gDm_ * sizeof(Ad_Ftype));

		return val;
	}

	template<int _N>
	AD_API _AdVal<_N> operator[](int i) const {
		return this->getAD<_N>(i);
	}

	template<int _N>
	AD_API void setAD(int i, const _AdVal<_N>& val)
	{
		assert(_N >= gDm_);
		data_[i + r_ * s1_] = val.val;

		double* start_p = gData_ + (i + r_ * s1_) * gDm_;
		memcpy(start_p , &val.gd[0], gDm_ * sizeof(Ad_Ftype));
	}



private:
	Ad_Ftype* data_{nullptr};
	Ad_Ftype* gData_{ nullptr };
	int gDm_{ 0 };
	int r_{ 0 };
	int s1_{ 0 };
};



class InAdBf : public AdBf
{
public:

private:


};


class _RawBf
{
public:
	AD_API _RawBf(int row, Ad_Ftype* data, int s1) :
		data_(data), s1_(s1), row_(row) {}

	AD_API Ad_Ftype& _ref(int i1) {
		assert(i1 < s1_);
		assert(i1 >= 0);

		int idx = s1_ * row_ + i1;
		return data_[idx];
	}

	AD_API Ad_Ftype _val(int i1) const{
		assert(i1 < s1_);
		assert(i1 >= 0);

		return data_[s1_ * row_ + i1];
	}

	AD_API Ad_Ftype& operator[](int i1) {
		return this->_ref(i1);
	}
	AD_API Ad_Ftype operator[](int i1) const {
		return this->_val(i1);
	}


private:
	Ad_Ftype* data_{nullptr};
	int s1_{ 0 };
	int row_{ 0 };
};


