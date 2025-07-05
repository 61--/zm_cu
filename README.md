# pytorch custom op library



本开源库提供了一种快速实现pytorch自定义算子的方式  
并且自定义算子同时支持cuda和cpu，自带梯度反向传播  
This open-source library provides a fast way to implement custom operators in PyTorch.  
It supports both CUDA and CPU, and includes automatic gradient propagation.
<br />

举个例子  自定义一个算子  
Give an example of creating a custom operator.  
$`y0=x0+x1`$  
$`y1=x1^2-x0^3`$  


在工程项目中加入 my_cus_func.hpp文件  在文件中添加如下代码  
Add the my_cus_func.hpp file to the project and include the following code in the file.
```
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

```
define_ab_func1(1, 2）中的 1 代表函数的id， 2代表返回值的维数  
 the 1 represents the function's ID, and 2 represents the number of dimensions of the return value.  
好了，你就成功完成了算子的自定义
Great! You've successfully completed the custom operator definition.  
<br />


使用更简单
use is more simple

```
TMat y = CusLayer<1>::apply(x);
```
CusLayer<1>::apply 中的 1 就是之前定义的函数 id
the 1 is the function ID that was defined earlier.  
<br />

<br />
full example code can be find in example1 

```

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

```

<br />
这种实现方式，主要是为了便利性，在性能和显存使用上有很大的问题。大点的项目推荐JAX <br />
This implementation method is mainly for convenience, but it has significant issues with performance and memory usage. For larger projects, JAX is recommended.

  

