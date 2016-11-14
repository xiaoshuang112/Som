#define feature   5
#define outputnum 2
#define traintime 100
#define somnode   2 //somnode==output
#define alpha 0.6

float v_node[somnode*feature] = {0};

void  transformToUnit(int* Array ,int num,float* dst) 
{
	for (int i = 0; i < num; i++) 
	{
		double sum = 0;
		for (int j = 0; j < feature; j++) 
		{
			sum += Array[i*feature+j] * Array[i*feature+j];
		}
		double factor = sqrt(sum);
		for (int j = 0; j < feature; j++) 
		{
			 dst[i*feature+j] =  (float)Array[i*feature+j] /(float)factor;
		}
	}
}

void Sominit(int* Array ,int num)
{
	 
}
