#define feature   5
#define outputnum 2
#define traintime 100
#define somnode   2 //somnode==output
#define alpha 0.6

float v_node[somnode*feature] = {0};
float*Trainsample = NULL; 
int Num = 0;//训练向量个数； 

void  TransformToUnit(float* Array ,int num,float* dst) 
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

void Sominit(float* Array ,int num)//Array是训练数据，最好包含各类数据 
{
	// 1 训练数据归一化 
	Trainsample = new float[feature*num];
	TransformToUnit(Array, num, Trainsample);
	 
	 // 2 节点初始归一化
	float*Node = new float[somnode*feature];
	for (int i = 0; i < somnode; i++) 
	{
	 	for(int j = 0; j < feature; j++)
		{
		 	Node[i*feature+j] = (float)(i*feature+j);
		}	
	}
	TransformToUnit(Node, somnode, v_node);	 
	
	//3
	Num = num; 
}

void Somcalresult(float*Input,int &Index)
{
	double*sum = new double[somnode];
	int i ,j;
	for(i = 0; i < somnode; i++)
	{
		double Temp = 0;
		for(j =0; j < feature; j++ )
		{
			Temp+= Input[j]*v_node[i*feature + j];
		}
		sum[i] = Temp;
	}
	
	double Max = sum[0];
	for(i = 0; i < somnode; i++)
	{
		if(Max < sum[i])
		{
			Max   = sum[i];
			Index = i;
		}
	}	
}

void Somadjust(float*TrainData, float*Node)
{
	for(int j = 0; j < feature; j++)
	{
		Node[j] = Node[j] + alpha*(TrainData[j] - Node[j]);//向训练向量靠拢； 
	}
	
	TransformToUnit(Node, 1, Node) ;//再次归一化； 
}

void SomTrain()
{
	for(int i = 0; i < traintime; i++)
	{
		for(int j = 0; j < Num; j++)
		{
			int index = 0;
			Somcalresult((Trainsample + j*feature), index);
			Somadjust((Trainsample + j*feature),v_node + index ); 
		}
	}
} 

int Sompredict(float*Data) 
{
	int index = 0;
	Somcalresult(Data, index);
	
	return index;
}
