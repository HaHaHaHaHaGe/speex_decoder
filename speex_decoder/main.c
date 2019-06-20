#include <speex/speex.h>
#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
SpeexBits bits;/* Holds bits so they can be read and written by the Speex routines */
void *enc_state, *dec_state;/* Holds the states of the encoder & the decoder */
int quality = 4, complexity = 1, vbr = 0, enh = 1;/* SPEEX PARAMETERS, MUST REMAINED UNCHANGED */
int frame_size;

	void _declspec(dllexport) Speex_Init(void)
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

	void _declspec(dllexport) decode(unsigned char*data, unsigned char*out)
	{

		/* Copy the encoded data into the bit-stream struct */
		speex_bits_read_from(&bits, (char*)data, 20);
		/* Decode the data */
		speex_decode_int(dec_state, &bits, (spx_int16_t *)out);

	}


