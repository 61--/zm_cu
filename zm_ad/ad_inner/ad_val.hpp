#pragma once


#define AD_TYPE double
#define GAD_TYPE double


template<int _N>
class _AdVal
{
public:
	AD_TYPE val{0};
	GAD_TYPE gd[_N] = {0};

	AD_API _AdVal(){}
	AD_API _AdVal(double v) {
		val = v;
	}

	AD_API _AdVal& operator=(double v) {
		val = v;
		for (int i = 0; i < _N; i++)
		{
			gd[i] = 0;
		}
		return *this;
	}
	AD_API _AdVal& operator=(const _AdVal<_N> v) {
		val = v.val;
		for (int i = 0; i < _N; i++)
		{
			gd[i] = v.gd[i];
		}
		return *this;
	}

	AD_TYPE Val() { return val; }
};



//-------------------------------------
template<int _N>
AD_API _AdVal<_N> operator+(const _AdVal<_N>& a, const _AdVal<_N>& b)
{
	_AdVal<_N> c;
	c.val = a.val + b.val;

	for (int i = 0; i < _N; i++)
	{
		c.gd[i] = a.gd[i] + b.gd[i];
	}

	return c;
}
template<int _N>
AD_API _AdVal<_N> operator+(const _AdVal<_N>& a, double b)
{
	_AdVal<_N> c;
	c.val = a.val + b;

	for (int i = 0; i < _N; i++)
	{
		c.gd[i] = a.gd[i];
	}

	return c;
}
template<int _N>
AD_API _AdVal<_N> operator+(double b, const _AdVal<_N>& a)
{
	return a + b;
}

//-----------------------------------
template<int _N>
AD_API _AdVal<_N> operator*(const _AdVal<_N>& a, double b)
{
	_AdVal<_N> c;
	c.val = a.val * b;

	for (int i = 0; i < _N; i++)
	{
		c.gd[i] = a.gd[i] * b;
	}

	return c;
}
template<int _N>
AD_API _AdVal<_N> operator*(double b, const _AdVal<_N>& a)
{
	return a * b;
}

template<int _N>
AD_API _AdVal<_N> operator*(const _AdVal<_N>& a, const _AdVal<_N>& b)
{
	_AdVal<_N> c;
	c.val = a.val * b.val;

	for (int i = 0; i < _N; i++)
	{
		c.gd[i] = a.gd[i] * b.val + b.gd[i] * a.val;
	}

	return c;
}

//----------------------------
template<int _N>
AD_API _AdVal<_N> operator-(const _AdVal<_N>& a, double b)
{
	return a + (-1) * b;
}
template<int _N>
AD_API _AdVal<_N> operator-(double b, const _AdVal<_N>& a)
{
	return b + (-1) * a;
}

template<int _N>
AD_API _AdVal<_N> operator-(const _AdVal<_N>& a, const _AdVal<_N>& b)
{
	return a + (-1) * b;
}
//----------------------------------------------
template<int _N>
AD_API _AdVal<_N> operator/(const _AdVal<_N>& a, double b)
{
	return a * (1.0/b);
}

template<int _N>
AD_API _AdVal<_N> operator/(const _AdVal<_N>& a, const _AdVal<_N>& b)
{
	_AdVal<_N> c;
	c.val = a.val / b.val;

	double b2 = b.val * b.val;
	for (int i = 0; i < _N; i++)
	{
		c.gd[i] = (a.gd[i] * b.val - b.gd[i] * a.val)/b2;
	}

	return c;
}
template<int _N>
AD_API _AdVal<_N> operator/(double a, const _AdVal<_N>& b)
{
	_AdVal<_N> c;
	c.val = a / b.val;

	double b2 = b.val * b.val;
	for (int i = 0; i < _N; i++)
	{
		c.gd[i] = (- b.gd[i] * a) / b2;
	}

	return c;
}

//------------------
template<int _N>
AD_API _AdVal<_N> pow(const _AdVal<_N>& a, double n)
{
	//assert(n > 1);

	_AdVal<_N> c;
	c.val = ::pow(a.val,n);

	for (int i = 0; i < _N; i++)
	{
		c.gd[i] = a.gd[i] *n * ::pow(a.val,n-1);
	}

	return c;
}

template<int _N>
AD_API _AdVal<_N> exp(const _AdVal<_N>& a)
{
	_AdVal<_N> c;
	c.val = ::exp(a.val);

	for (int i = 0; i < _N; i++)
	{
		c.gd[i] = a.gd[i] * c.val;
	}

	return c;
}

template<int _N>
AD_API _AdVal<_N> sqrt(const _AdVal<_N>& a)
{
	return exp(a, 0.5);
}

template<int _N>
AD_API _AdVal<_N> abs(const _AdVal<_N>& a)
{
	if (a.val >= 0)
		return a;

	return -1 * a;
}




#define AdVal _AdVal<_GdDim_>






