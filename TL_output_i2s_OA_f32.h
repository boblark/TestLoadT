/* TL_output_i2s_OA_f32.h
 * 
 * This is Teensy Audio output_i2s.h altered to support OpenAudio float (F32)
 * to allow direct output of F32 blocks to the codec. It is the Teensy Audio output
 * class with a conversion of float to int16 at the beginning.   Bob Larkin
 * June 2020
 * 
 * This is basic: 128 word blocks, 16-bit integer word to the codec.  It
 * needs to be revisited for variable word block.
 * 
 * Tested: Using TestOutput_float.ino, Runs T3.6 and T4.0 w/o error.
 * 
 * Additions under MIT license, and all the original is:
 * Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// **********************************************************************
// NOT FOR GENERAL USE  -  TO TEST Teensy Loading  -  NOT FOR GENERAL USE 
// **********************************************************************

#ifndef TL_output_i2s_OA_F32_h_
#define TL_output_i2s_OA_F32_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "AudioStream_F32.h"
#include "DMAChannel.h"

class TL_AudioOutputI2S_OA_F32 : public AudioStream_F32
{
//GUI: inputs:2, outputs:0  //this line used for automatic generation of GUI node
public:
	// WAS AudioOutputI2S_OA_F32(void) : AudioStream_F32(2, inputQueueArray) {
	TL_AudioOutputI2S_OA_F32(int includeBegin) : AudioStream_F32(2, inputQueueArray) {
          if(includeBegin) begin(); // ONLY difference from standard Class.  Temporary for testing. <<<
    }

	virtual void update(void);
	void begin(void);
  	friend class AudioInputI2S_OA_F32; 

protected:
    // Next fcn to be used only inside AudioOutputI2S_OA_F32slave !!
//	AudioOutputI2S_OA_F32(int dummy): AudioStream_F32(2, inputQueueArray) {}
	static void config_i2s(void);
	static audio_block_t *block_left_1st;
	static audio_block_t *block_right_1st;
	static bool update_responsibility;
	static DMAChannel dma;
	static void isr(void);
private:
	static audio_block_t *block_left_2nd;
	static audio_block_t *block_right_2nd;
	static uint16_t block_left_offset;
	static uint16_t block_right_offset;
	audio_block_f32_t *inputQueueArray[2];
};

#if 0
class AudioOutputI2Sslave_OA_F32 : public AudioOutputI2S_OA_F32
{
public:
	AudioOutputI2Sslave_OA_F32(void) : AudioOutputI2S_OA_F32(0) { begin(); } ;
	void begin(void);
    friend class AudioInputI2Sslave_OA_F32;
	friend void dma_ch0_isr(void);
protected:
	static void config_i2s(void);
};
#endif

#endif
