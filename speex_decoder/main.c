#include <speex/speex.h>
#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
SpeexBits bits;/* Holds bits so they can be read and written by the Speex routines */
void *enc_state, *dec_state;/* Holds the states of the encoder & the decoder */
int quality = 4, complexity = 1, vbr = 0, enh = 1;/* SPEEX PARAMETERS, MUST REMAINED UNCHANGED */
int frame_size;
void Speex_Init(void)
{
	/* Speex encoding initializations */
	speex_bits_init(&bits);
	enc_state = speex_encoder_init(&speex_nb_mode);
	speex_encoder_ctl(enc_state, SPEEX_SET_VBR, &vbr);
	speex_encoder_ctl(enc_state, SPEEX_SET_QUALITY, &quality);
	speex_encoder_ctl(enc_state, SPEEX_SET_COMPLEXITY, &complexity);

	speex_encoder_ctl(enc_state, SPEEX_GET_SAMPLING_RATE, &frame_size);

	/* speex decoding intilalization */
	dec_state = speex_decoder_init(&speex_nb_mode);
	speex_decoder_ctl(dec_state, SPEEX_SET_ENH, &enh);
}
void recoder_wav_init(__WaveHeader* wavhead, unsigned int fs);

__WaveHeader wavhead;
char in_path[100];
int i;
char *str[] = {"34","G:\\12345.wzr"};
int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;

	i = 0;
	while (argv[1][i] != '.' && argv[1][i])
		in_path[i++] = argv[1][i];
	if (argv[1][i + 1] != 'w' || argv[1][i + 2] != 'z' || argv[1][i + 3] != 'r')
		return 0;



	if (argv[1][i] == 0)
	{
		in_path[i++] = '.';
		in_path[i++] = 'w';
		in_path[i++] = 'a';
		in_path[i++] = 'v';
		in_path[i++] =  0;
	}
	else if (argv[1][i] == '.')
	{
		in_path[i++] = '.';
		in_path[i++] = 'w';
		in_path[i++] = 'a';
		in_path[i++] = 'v';
		in_path[i++] = 0;
	}
	else
		return 0;

	FILE *fin = fopen(argv[1], "rb");
	FILE *fout = fopen(in_path, "wb+");

	if (fin == 0 || fout == 0)
		return 0;

	fseek(fin, 0, SEEK_END); //定位到文件末 
	int nFileLen = ftell(fin); //文件长度

	fseek(fin, 0, SEEK_SET); //定位到文件末 

	unsigned char * fin_ptr = malloc(nFileLen);

	fread(fin_ptr, sizeof(unsigned char), nFileLen, fin);


	int read_loc = 0;

	unsigned short out[160];



	recoder_wav_init(&wavhead,8000);

	recoder_wav_update(&wavhead, (nFileLen / 20) * 320 );

	fwrite(&wavhead, sizeof(char), sizeof(__WaveHeader), fout);

	Speex_Init();
	while ((nFileLen - read_loc) / 20 > 0)
	{
		/* Copy the encoded data into the bit-stream struct */
		speex_bits_read_from(&bits, (char*)&fin_ptr[read_loc], 20);
		/* Decode the data */
		speex_decode_int(dec_state, &bits, (spx_int16_t *)out);

		fwrite(out, sizeof(unsigned short), 160, fout);

		read_loc += 20;
	}
	fclose(fin);
	fclose(fout);
	//while (1);
}