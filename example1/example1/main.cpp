
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

#include "ad_layer.hpp"


#pragma comment(lib, "torch.lib")
#pragma comment(lib, "torch_cpu.lib")
#pragma comment(lib, "torch_cuda.lib")
#pragma comment(lib, "c10.lib")

#ifdef _WIN32
#include <windows.h>
#endif


#ifdef _WIN32

inline void ini_torch_cuda()
{

	LoadLibraryA("ATen_cuda.dll");
	LoadLibraryA("c10_cuda.dll");
	LoadLibraryA("torch_cuda.dll");
	LoadLibraryA("torchvision.dll");

	if (!torch::cuda::is_available()) {
		std::cout << "cuda is_available is no avb"<<std::endl;
	}
	if (!torch::cuda::cudnn_is_available()) {
		std::cout << "cudnn is_available is no avb"<<std::endl;
	}

	if (torch::cuda::device_count() == 0) {
		std::cout << "device_count is zero"<<std::endl;
	}
}
#else
inline void ini_torch_cuda()
{
}

#endif




int main()
{
	const bool use_cuda = true;

	if(use_cuda)
		ini_torch_cuda();

	std::cout << "+++ start" << std::endl;

	c10::IntArrayRef ret({1,2});
	at::Tensor x = createTMat<double>({ 1,2 }, { 1.0, 2.0 }, tr::kF64);
	if(use_cuda)
		x = x.to(torch::kCUDA);
	x.requires_grad_(true);
	

	at::Tensor y_dst = createTMat<double>({ 1,2 }, { 5,1 }, tr::kF64);
	if (use_cuda)
		y_dst = y_dst.to(torch::kCUDA);

	std::cout << "ini x: " << x << std::endl;
	std::cout << "y_dst: " << y_dst << std::endl;

	std::cout << "" << std::endl;

	double lrate = 1e-4;
	tr::optim::Adam opt({x}, tr::optim::AdamOptions(lrate));

	for (int i = 0; true; i++)
	{
		opt.zero_grad();

		TMat y = CusLayer<1>::apply(x);


		TMat er = (y - y_dst).norm();

		er.backward();
		opt.step();

		

		if (i % 1000 == 0) {
			std::cout << "----------------: " << i << std::endl;
			std::cout << "x: " << x << std::endl;
			std::cout << "y: " << y << std::endl;
			std::cout << "er: " << er << std::endl;
			std::cout << ""<<std::endl;
		}

		if (to_double(er) < 1e-4) {
			std::cout << "+++ opt finish ++" << std::endl;
			break;
		}

	}


 	

    return 0;
}




// 
// 	zuFunc2<1>(x, y);