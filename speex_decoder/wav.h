




//RIFF��
typedef struct __packed1
{
    unsigned int ChunkID;		   	//chunk id;����̶�Ϊ"RIFF",��0X46464952
    unsigned int ChunkSize ;		   	//���ϴ�С;�ļ��ܴ�С-8
    unsigned int Format;	   			//��ʽ;WAVE,��0X45564157
}ChunkRIFF ;
//fmt��
typedef struct __packed2
{
    unsigned int ChunkID;		   	//chunk id;����̶�Ϊ"fmt ",��0X20746D66
    unsigned int ChunkSize ;		   	//�Ӽ��ϴ�С(������ID��Size);����Ϊ:20.
    unsigned short AudioFormat;	  	//��Ƶ��ʽ;0X01,��ʾ����PCM;0X11��ʾIMA ADPCM
	unsigned short NumOfChannels;		//ͨ������;1,��ʾ������;2,��ʾ˫����;
	unsigned int SampleRate;			//������;0X1F40,��ʾ8Khz
	unsigned int ByteRate;			//�ֽ�����; 
	unsigned short BlockAlign;			//�����(�ֽ�); 
	unsigned short BitsPerSample;		//�����������ݴ�С;4λADPCM,����Ϊ4
//	unsigned short ByteExtraData;		//���ӵ������ֽ�;2��; ����PCM,û���������
}ChunkFMT;	   
//fact�� 
typedef struct __packed3
{
    unsigned int ChunkID;		   	//chunk id;����̶�Ϊ"fact",��0X74636166;
    unsigned int ChunkSize ;		   	//�Ӽ��ϴ�С(������ID��Size);����Ϊ:4.
    unsigned int NumOfSamples;	  	//����������; 
}ChunkFACT;
//LIST�� 
typedef struct __packed4
{
    unsigned int ChunkID;		   	//chunk id;����̶�Ϊ"LIST",��0X74636166;
    unsigned int ChunkSize ;		   	//�Ӽ��ϴ�С(������ID��Size);����Ϊ:4. 
}ChunkLIST;

//data�� 
typedef struct __packed5
{
    unsigned int ChunkID;		   	//chunk id;����̶�Ϊ"data",��0X5453494C
    unsigned int ChunkSize ;		   	//�Ӽ��ϴ�С(������ID��Size) 
}ChunkDATA;

//wavͷ
typedef struct __packed6
{ 
	ChunkRIFF riff;	//riff��
	ChunkFMT fmt;  	//fmt��
//	ChunkFACT fact;	//fact�� ����PCM,û������ṹ��	 
	ChunkDATA data;	//data��		 
}__WaveHeader; 

//wav ���ſ��ƽṹ��
typedef struct __packed7
{ 
    unsigned short audioformat;			//��Ƶ��ʽ;0X01,��ʾ����PCM;0X11��ʾIMA ADPCM
	unsigned short nchannels;				//ͨ������;1,��ʾ������;2,��ʾ˫����; 
	unsigned short blockalign;				//�����(�ֽ�);  
	unsigned int datasize;				//WAV���ݴ�С 

    unsigned int totsec ;				//���׸�ʱ��,��λ:��
    unsigned int cursec ;				//��ǰ����ʱ��
	
    unsigned int bitrate;	   			//������(λ��)
	unsigned int samplerate;				//������ 
	unsigned short bps;					//λ��,����16bit,24bit,32bit
	
	unsigned int datastart;				//����֡��ʼ��λ��(���ļ������ƫ��)
}__wavctrl; 
void recoder_wav_init(__WaveHeader* wavhead , unsigned int fs) ;
void recoder_wav_update(__WaveHeader* wavhead , unsigned int datalen);


