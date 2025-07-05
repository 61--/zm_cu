#pragma once



define_ab_func1(1, 2)(AdBf in0, AdBf out)
{
	AdVal v0_0 = getAd(in0, 0);
	AdVal v0_1 = getAd(in0, 1);

	AdVal v0 = v0_0 + v0_1;
	AdVal v1 = pow(v0_1,2) - pow(v0_0,3);

	out.setAD(0, v0);
	out.setAD(1, v1);
}
end_define_ab_func1(1)


