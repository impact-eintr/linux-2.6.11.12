#ifndef SOUNDCARD_H
#define SOUNDCARD_H
/*
 * Copyright by Hannu Savolainen 1993-1997
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer. 2.
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


/*
 * OSS interface version. With versions earlier than 3.6 this value is
 * an integer with value less than 361. In versions 3.6 and later
 * it's a six digit hexadecimal value. For example value
 * of 0x030600 represents OSS version 3.6.0.
 * Use ioctl(fd, OSS_GETVERSION, &int) to get the version number of
 * the currently active driver.
 */
#define SOUND_VERSION	0x030802
#define OPEN_SOUND_SYSTEM

/* In Linux we need to be prepared for cross compiling */
#include <linux/ioctl.h>

/*
 *	Supported card ID numbers (Should be somewhere else?)
 */

#define SNDCARD_ADLIB		1
#define SNDCARD_SB		2
#define SNDCARD_PAS		3
#define SNDCARD_GUS		4
#define SNDCARD_MPU401		5
#define SNDCARD_SB16		6
#define SNDCARD_SB16MIDI	7
#define SNDCARD_UART6850	8
#define SNDCARD_GUS16		9
#define SNDCARD_MSS		10
#define SNDCARD_PSS     	11
#define SNDCARD_SSCAPE		12
#define SNDCARD_PSS_MPU     	13
#define SNDCARD_PSS_MSS     	14
#define SNDCARD_SSCAPE_MSS	15
#define SNDCARD_TRXPRO		16
#define SNDCARD_TRXPRO_SB	17
#define SNDCARD_TRXPRO_MPU	18
#define SNDCARD_MAD16		19
#define SNDCARD_MAD16_MPU	20
#define SNDCARD_CS4232		21
#define SNDCARD_CS4232_MPU	22
#define SNDCARD_MAUI		23
#define SNDCARD_PSEUDO_MSS	24
#define SNDCARD_GUSPNP		25
#define SNDCARD_UART401		26
/* Sound card numbers 27 to N are reserved. Don't add more numbers here. */

/***********************************
 * IOCTL Commands for /dev/sequencer
 */

#ifndef _SIOWR
#if defined(_IOWR) && (defined(_AIX) || (!defined(sun) && !defined(sparc) && !defined(__sparc__) && !defined(__INCioctlh) && !defined(__Lynx__)))
/* Use already defined ioctl defines if they exist (except with Sun or Sparc) */
#define	SIOCPARM_MASK	IOCPARM_MASK
#define	SIOC_VOID	IOC_VOID
#define	SIOC_OUT	IOC_OUT
#define	SIOC_IN		IOC_IN
#define	SIOC_INOUT	IOC_INOUT
#define _SIOC_SIZE	_IOC_SIZE
#define _SIOC_DIR	_IOC_DIR
#define _SIOC_NONE	_IOC_NONE
#define _SIOC_READ	_IOC_READ
#define _SIOC_WRITE	_IOC_WRITE
#define	_SIO		_IO
#define	_SIOR		_IOR
#define	_SIOW		_IOW
#define	_SIOWR		_IOWR
#else

/* Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 8191 bytes.
 */
/* #define	SIOCTYPE		(0xff<<8) */
#define	SIOCPARM_MASK	0x1fff		/* parameters must be < 8192 bytes */
#define	SIOC_VOID	0x00000000	/* no parameters */
#define	SIOC_OUT	0x20000000	/* copy out parameters */
#define	SIOC_IN		0x40000000	/* copy in parameters */
#define	SIOC_INOUT	(SIOC_IN|SIOC_OUT)
/* the 0x20000000 is so we can distinguish new ioctl's from old */
#define	_SIO(x,y)	((int)(SIOC_VOID|(x<<8)|y))
#define	_SIOR(x,y,t)	((int)(SIOC_OUT|((sizeof(t)&SIOCPARM_MASK)<<16)|(x<<8)|y))
#define	_SIOW(x,y,t)	((int)(SIOC_IN|((sizeof(t)&SIOCPARM_MASK)<<16)|(x<<8)|y))
/* this should be _SIORW, but stdio got there first */
#define	_SIOWR(x,y,t)	((int)(SIOC_INOUT|((sizeof(t)&SIOCPARM_MASK)<<16)|(x<<8)|y))
#define _SIOC_SIZE(x)	((x>>16)&SIOCPARM_MASK)	
#define _SIOC_DIR(x)	(x & 0xf0000000)
#define _SIOC_NONE	SIOC_VOID
#define _SIOC_READ	SIOC_OUT
#define _SIOC_WRITE	SIOC_IN
#  endif /* _IOWR */
#endif  /* !_SIOWR */

#define SNDCTL_SEQ_RESET		_SIO  ('Q', 0)
#define SNDCTL_SEQ_SYNC			_SIO  ('Q', 1)
#define SNDCTL_SYNTH_INFO		_SIOWR('Q', 2, struct synth_info)
#define SNDCTL_SEQ_CTRLRATE		_SIOWR('Q', 3, int)	/* Set/get timer resolution (HZ) */
#define SNDCTL_SEQ_GETOUTCOUNT		_SIOR ('Q', 4, int)
#define SNDCTL_SEQ_GETINCOUNT		_SIOR ('Q', 5, int)
#define SNDCTL_SEQ_PERCMODE		_SIOW ('Q', 6, int)
#define SNDCTL_FM_LOAD_INSTR		_SIOW ('Q', 7, struct sbi_instrument)	/* Obsolete. Don't use!!!!!! */
#define SNDCTL_SEQ_TESTMIDI		_SIOW ('Q', 8, int)
#define SNDCTL_SEQ_RESETSAMPLES		_SIOW ('Q', 9, int)
#define SNDCTL_SEQ_NRSYNTHS		_SIOR ('Q',10, int)
#define SNDCTL_SEQ_NRMIDIS		_SIOR ('Q',11, int)
#define SNDCTL_MIDI_INFO		_SIOWR('Q',12, struct midi_info)
#define SNDCTL_SEQ_THRESHOLD		_SIOW ('Q',13, int)
#define SNDCTL_SYNTH_MEMAVL		_SIOWR('Q',14, int)	/* in=dev#, out=memsize */
#define SNDCTL_FM_4OP_ENABLE		_SIOW ('Q',15, int)	/* in=dev# */
#define SNDCTL_SEQ_PANIC		_SIO  ('Q',17)
#define SNDCTL_SEQ_OUTOFBAND		_SIOW ('Q',18, struct seq_event_rec)
#define SNDCTL_SEQ_GETTIME		_SIOR ('Q',19, int)
#define SNDCTL_SYNTH_ID			_SIOWR('Q',20, struct synth_info)
#define SNDCTL_SYNTH_CONTROL		_SIOWR('Q',21, struct synth_control)
#define SNDCTL_SYNTH_REMOVESAMPLE	_SIOWR('Q',22, struct remove_sample)

typedef struct synth_control
{
	int devno;	/* Synthesizer # */
	char data[4000]; /* Device spesific command/data record */
}synth_control;

typedef struct remove_sample
{
	int devno;	/* Synthesizer # */
	int bankno;	/* MIDI bank # (0=General MIDI) */
	int instrno;	/* MIDI instrument number */
} remove_sample;

typedef struct seq_event_rec {
		unsigned char arr[8];
} seq_event_rec;

#define SNDCTL_TMR_TIMEBASE		_SIOWR('T', 1, int)
#define SNDCTL_TMR_START		_SIO  ('T', 2)
#define SNDCTL_TMR_STOP			_SIO  ('T', 3)
#define SNDCTL_TMR_CONTINUE		_SIO  ('T', 4)
#define SNDCTL_TMR_TEMPO		_SIOWR('T', 5, int)
#define SNDCTL_TMR_SOURCE		_SIOWR('T', 6, int)
#	define TMR_INTERNAL		0x00000001
#	define TMR_EXTERNAL		0x00000002
#		define TMR_MODE_MIDI	0x00000010
#		define TMR_MODE_FSK	0x00000020
#		define TMR_MODE_CLS	0x00000040
#		define TMR_MODE_SMPTE	0x00000080
#define SNDCTL_TMR_METRONOME		_SIOW ('T', 7, int)
#define SNDCTL_TMR_SELECT		_SIOW ('T', 8, int)

/*
 * Some big endian/little endian handling macros
 */

#if defined(_AIX) || defined(AIX) || defined(sparc) || defined(__sparc__) || defined(HPPA) || defined(PPC) || defined(__mc68000__)
/* Big endian machines */
#  define _PATCHKEY(id) (0xfd00|id)
#  define AFMT_S16_NE AFMT_S16_BE
#else
#  define _PATCHKEY(id) ((id<<8)|0xfd)
#  define AFMT_S16_NE AFMT_S16_LE
#endif

/*
 *	Sample loading mechanism for internal synthesizers (/dev/sequencer)
 *	The following patch_info structure has been designed to support
 *	Gravis UltraSound. It tries to be universal format for uploading
 *	sample based patches but is probably too limited.
 *
 *      (PBD) As Hannu guessed, the GUS structure is too limited for 
 *      the WaveFront, but this is the right place for a constant definition.
 */

struct patch_info {
		unsigned short key;		/* Use WAVE_PATCH here */
#define WAVE_PATCH	   _PATCHKEY(0x04)
#define GUS_PATCH	   WAVE_PATCH
#define WAVEFRONT_PATCH    _PATCHKEY(0x06)

		short device_no;	/* Synthesizer number */
		short instr_no;		/* Midi pgm# */

		unsigned int mode;
/*
 * The least significant byte has the same format than the GUS .PAT
 * files
 */
#define WAVE_16_BITS	0x01	/* bit 0 = 8 or 16 bit wave data. */
#define WAVE_UNSIGNED	0x02	/* bit 1 = Signed - Unsigned data. */
#define WAVE_LOOPING	0x04	/* bit 2 = looping enabled-1. */
#define WAVE_BIDIR_LOOP	0x08	/* bit 3 = Set is bidirectional looping. */
#define WAVE_LOOP_BACK	0x10	/* bit 4 = Set is looping backward. */
#define WAVE_SUSTAIN_ON	0x20	/* bit 5 = Turn sustaining on. (Env. pts. 3)*/
#define WAVE_ENVELOPES	0x40	/* bit 6 = Enable envelopes - 1 */
#define WAVE_FAST_RELEASE 0x80	/* bit 7 = Shut off immediately after note off */
				/* 	(use the env_rate/env_offs fields). */
/* Linux specific bits */
#define WAVE_VIBRATO	0x00010000	/* The vibrato info is valid */
#define WAVE_TREMOLO	0x00020000	/* The tremolo info is valid */
#define WAVE_SCALE	0x00040000	/* The scaling info is valid */
#define WAVE_FRACTIONS	0x00080000	/* Fraction information is valid */
/* Reserved bits */
#define WAVE_ROM	0x40000000	/* For future use */
#define WAVE_MULAW	0x20000000	/* For future use */
/* Other bits must be zeroed */

		int len;	/* Size of the wave data in bytes */
		int loop_start, loop_end; /* Byte offsets from the beginning */

/* 
 * The base_freq and base_note fields are used when computing the
 * playback speed for a note. The base_note defines the tone frequency
 * which is heard if the sample is played using the base_freq as the
 * playback speed.
 *
 * The low_note and high_note fields define the minimum and maximum note
 * frequencies for which this sample is valid. It is possible to define
 * more than one samples for an instrument number at the same time. The
 * low_note and high_note fields are used to select the most suitable one.
 *
 * The fields base_note, high_note and low_note should contain
 * the note frequency multiplied by 1000. For example value for the
 * middle A is 440*1000.
 */

		unsigned int base_freq;
		unsigned int base_note;
		unsigned int high_note;
		unsigned int low_note;
		int panning;	/* -128=left, 127=right */
		int detuning;

/*	New fields introduced in version 1.99.5	*/

       /* Envelope. Enabled by mode bit WAVE_ENVELOPES	*/
		unsigned char	env_rate[ 6 ];	 /* GUS HW ramping rate */
		unsigned char	env_offset[ 6 ]; /* 255 == 100% */

	/* 
	 * The tremolo, vibrato and scale info are not supported yet.
	 * Enable by setting the mode bits WAVE_TREMOLO, WAVE_VIBRATO or
	 * WAVE_SCALE
	 */

		unsigned char	tremolo_sweep;
		unsigned char	tremolo_rate;
		unsigned char	tremolo_depth;
	
		unsigned char	vibrato_sweep;
		unsigned char	vibrato_rate;
		unsigned char	vibrato_depth;

		int		scale_frequency;
		unsigned int	scale_factor;		/* from 0 to 2048 or 0 to 2 */
	
	        int		volume;
		int		fractions;
		int		reserved1;
	        int		spare[2];
		char data[1];	/* The waveform data starts here */
	};

struct sysex_info {
		short key;		/* Use SYSEX_PATCH or MAUI_PATCH here */
#define SYSEX_PATCH	_PATCHKEY(0x05)
#define MAUI_PATCH	_PATCHKEY(0x06)
		short device_no;	/* Synthesizer number */
		int len;	/* Size of the sysex data in bytes */
		unsigned char data[1];	/* Sysex data starts here */
	};

/*
 * /dev/sequencer input events.
 *
 * The data written to the /dev/sequencer is a stream of events. Events
 * are records of 4 or 8 bytes. The first byte defines the size. 
 * Any number of events can be written with a write call. There
 * is a set of macros for sending these events. Use these macros if you
 * want to maximize portability of your program.
 *
 * Events SEQ_WAIT, SEQ_MIDIPUTC and SEQ_ECHO. Are also input events.
 * (All input events are currently 4 bytes long. Be prepared to support
 * 8 byte events also. If you receive any event having first byte >= 128,
 * it's a 8 byte event.
 *
 * The events are documented at the end of this file.
 *
 * Normal events (4 bytes)
 * There is also a 8 byte version of most of the 4 byte events. The
 * 8 byte one is recommended.
 */
#define SEQ_NOTEOFF		0
#define SEQ_FMNOTEOFF		SEQ_NOTEOFF	/* Just old name */
#define SEQ_NOTEON		1
#define	SEQ_FMNOTEON		SEQ_NOTEON
#define SEQ_WAIT		TMR_WAIT_ABS
#define SEQ_PGMCHANGE		3
#define SEQ_FMPGMCHANGE		SEQ_PGMCHANGE
#define SEQ_SYNCTIMER		TMR_START
#define SEQ_MIDIPUTC		5
#define SEQ_DRUMON		6	/*** OBSOLETE ***/
#define SEQ_DRUMOFF		7	/*** OBSOLETE ***/
#define SEQ_ECHO		TMR_ECHO	/* For synching programs with output */
#define SEQ_AFTERTOUCH		9
#define SEQ_CONTROLLER		10

/*******************************************
 *	Midi controller numbers
 *******************************************
 * Controllers 0 to 31 (0x00 to 0x1f) and
 * 32 to 63 (0x20 to 0x3f) are continuous
 * controllers.
 * In the MIDI 1.0 these controllers are sent using
 * two messages. Controller numbers 0 to 31 are used
 * to send the MSB and the controller numbers 32 to 63
 * are for the LSB. Note that just 7 bits are used in MIDI bytes.
 */

#define	   CTL_BANK_SELECT		0x00
#define	   CTL_MODWHEEL			0x01
#define    CTL_BREATH			0x02
/*		undefined		0x03 */
#define    CTL_FOOT			0x04
#define    CTL_PORTAMENTO_TIME		0x05
#define    CTL_DATA_ENTRY		0x06
#define    CTL_MAIN_VOLUME		0x07
#define    CTL_BALANCE			0x08
/*		undefined		0x09 */
#define    CTL_PAN			0x0a
#define    CTL_EXPRESSION		0x0b
/*		undefined		0x0c */
/*		undefined		0x0d */
/*		undefined		0x0e */
/*		undefined		0x0f */
#define    CTL_GENERAL_PURPOSE1	0x10
#define    CTL_GENERAL_PURPOSE2	0x11
#define    CTL_GENERAL_PURPOSE3	0x12
#define    CTL_GENERAL_PURPOSE4	0x13
/*		undefined		0x14 - 0x1f */

/*		undefined		0x20 */
/* The controller numbers 0x21 to 0x3f are reserved for the */
/* least significant bytes of the controllers 0x00 to 0x1f. */
/* These controllers are not recognised by the driver. */

/* Controllers 64 to 69 (0x40 to 0x45) are on/off switches. */
/* 0=OFF and 127=ON (intermediate values are possible) */
#define    CTL_DAMPER_PEDAL		0x40
#define    CTL_SUSTAIN			0x40	/* Alias */
#define    CTL_HOLD			0x40	/* Alias */
#define    CTL_PORTAMENTO		0x41
#define    CTL_SOSTENUTO		0x42
#define    CTL_SOFT_PEDAL		0x43
/*		undefined		0x44 */
#define    CTL_HOLD2			0x45
/*		undefined		0x46 - 0x4f */

#define    CTL_GENERAL_PURPOSE5	0x50
#define    CTL_GENERAL_PURPOSE6	0x51
#define    CTL_GENERAL_PURPOSE7	0x52
#define    CTL_GENERAL_PURPOSE8	0x53
/*		undefined		0x54 - 0x5a */
#define    CTL_EXT_EFF_DEPTH		0x5b
#define    CTL_TREMOLO_DEPTH		0x5c
#define    CTL_CHORUS_DEPTH		0x5d
#define    CTL_DETUNE_DEPTH		0x5e
#define    CTL_CELESTE_DEPTH		0x5e	/* Alias for the above one */
#define    CTL_PHASER_DEPTH		0x5f
#define    CTL_DATA_INCREMENT		0x60
#define    CTL_DATA_DECREMENT		0x61
#define    CTL_NONREG_PARM_NUM_LSB	0x62
#define    CTL_NONREG_PARM_NUM_MSB	0x63
#define    CTL_REGIST_PARM_NUM_LSB	0x64
#define    CTL_REGIST_PARM_NUM_MSB	0x65
/*		undefined		0x66 - 0x78 */
/*		reserved		0x79 - 0x7f */

/* Pseudo controllers (not midi compatible) */
#define    CTRL_PITCH_BENDER		255
#define    CTRL_PITCH_BENDER_RANGE	254
#define    CTRL_EXPRESSION		253	/* Obsolete */
#define    CTRL_MAIN_VOLUME		252	/* Obsolete */
#define SEQ_BALANCE		11
#define SEQ_VOLMODE             12

/*
 * Volume mode decides how volumes are used
 */

#define VOL_METHOD_ADAGIO	1
#define VOL_METHOD_LINEAR	2

/*
 * Note! SEQ_WAIT, SEQ_MIDIPUTC and SEQ_ECHO are used also as
 *	 input events.
 */

/*
 * Event codes 0xf0 to 0xfc are reserved for future extensions.
 */

#define SEQ_FULLSIZE		0xfd	/* Long events */
/*
 *	SEQ_FULLSIZE events are used for loading patches/samples to the
 *	synthesizer devices. These events are passed directly to the driver
 *	of the associated synthesizer device. There is no limit to the size
 *	of the extended events. These events are not queued but executed
 *	immediately when the write() is called (execution can take several
 *	seconds of time). 
 *
 *	When a SEQ_FULLSIZE message is written to the device, it must
 *	be written using exactly one write() call. Other events cannot
 *	be mixed to the same write.
 *	
 *	For FM synths (YM3812/OPL3) use struct sbi_instrument and write it to the 
 *	/dev/sequencer. Don't write other data together with the instrument structure
 *	Set the key field of the structure to FM_PATCH. The device field is used to
 *	route the patch to the corresponding device.
 *
 *	For wave table use struct patch_info. Initialize the key field
 *      to WAVE_PATCH.
 */
#define SEQ_PRIVATE		0xfe	/* Low level HW dependent events (8 bytes) */
#define SEQ_EXTENDED		0xff	/* Extended events (8 bytes) OBSOLETE */

/*
 * Record for FM patches
 */

typedef unsigned char sbi_instr_data[32];

struct sbi_instrument {
		unsigned short	key;	/* FM_PATCH or OPL3_PATCH */
#define FM_PATCH	_PATCHKEY(0x01)
#define OPL3_PATCH	_PATCHKEY(0x03)
		short		device;		/*	Synth# (0-4)	*/
		int 		channel;	/*	Program# to be initialized 	*/
		sbi_instr_data	operators;	/*	Register settings for operator cells (.SBI format)	*/
	};

struct synth_info {	/* Read only */
		char	name[30];
		int	device;		/* 0-N. INITIALIZE BEFORE CALLING */
		int	synth_type;
#define SYNTH_TYPE_FM			0
#define SYNTH_TYPE_SAMPLE		1
#define SYNTH_TYPE_MIDI			2	/* Midi interface */

		int	synth_subtype;
#define FM_TYPE_ADLIB			0x00
#define FM_TYPE_OPL3			0x01
#define MIDI_TYPE_MPU401		0x401

#define SAMPLE_TYPE_BASIC		0x10
#define SAMPLE_TYPE_GUS			SAMPLE_TYPE_BASIC
#define SAMPLE_TYPE_WAVEFRONT           0x11

		int	perc_mode;	/* No longer supported */
		int	nr_voices;
		int	nr_drums;	/* Obsolete field */
		int	instr_bank_size;
		unsigned int	capabilities;	
#define SYNTH_CAP_PERCMODE		0x00000001 /* No longer used */
#define SYNTH_CAP_OPL3			0x00000002 /* Set if OPL3 supported */
#define SYNTH_CAP_INPUT			0x00000004 /* Input (MIDI) device */
		int	dummies[19];	/* Reserve space */
	};

struct sound_timer_info {
		char name[32];
		int caps;
	};

#define MIDI_CAP_MPU401		1		/* MPU-401 intelligent mode */

struct midi_info {
		char		name[30];
		int		device;		/* 0-N. INITIALIZE BEFORE CALLING */
		unsigned int	capabilities;	/* To be defined later */
		int		dev_type;
		int		dummies[18];	/* Reserve space */
	};

/********************************************
 * ioctl commands for the /dev/midi##
 */
typedef struct {
		unsigned char cmd;
		char nr_args, nr_returns;
		unsigned char data[30];
	} mpu_command_rec;

#define SNDCTL_MIDI_PRETIME		_SIOWR('m', 0, int)
#define SNDCTL_MIDI_MPUMODE		_SIOWR('m', 1, int)
#define SNDCTL_MIDI_MPUCMD		_SIOWR('m', 2, mpu_command_rec)

/********************************************
 * IOCTL commands for /dev/dsp and /dev/audio
 */

#define SNDCTL_DSP_RESET		_SIO  ('P', 0)
#define SNDCTL_DSP_SYNC			_SIO  ('P', 1)
#define SNDCTL_DSP_SPEED		_SIOWR('P', 2, int)
#define SNDCTL_DSP_STEREO		_SIOWR('P', 3, int)
#define SNDCTL_DSP_GETBLKSIZE		_SIOWR('P', 4, int)
#define SNDCTL_DSP_SAMPLESIZE		SNDCTL_DSP_SETFMT
#define SNDCTL_DSP_CHANNELS		_SIOWR('P', 6, int)
#define SOUND_PCM_WRITE_CHANNELS	SNDCTL_DSP_CHANNELS
#define SOUND_PCM_WRITE_FILTER		_SIOWR('P', 7, int)
#define SNDCTL_DSP_POST			_SIO  ('P', 8)
#define SNDCTL_DSP_SUBDIVIDE		_SIOWR('P', 9, int)
#define SNDCTL_DSP_SETFRAGMENT		_SIOWR('P',10, int)

/*	Audio data formats (Note! U8=8 and S16_LE=16 for compatibility) */
#define SNDCTL_DSP_GETFMTS		_SIOR ('P',11, int) /* Returns a mask */
#define SNDCTL_DSP_SETFMT		_SIOWR('P',5, int) /* Selects ONE fmt*/
#	define AFMT_QUERY		0x00000000	/* Return current fmt */
#	define AFMT_MU_LAW		0x00000001
#	define AFMT_A_LAW		0x00000002
#	define AFMT_IMA_ADPCM		0x00000004
#	define AFMT_U8			0x00000008
#	define AFMT_S16_LE		0x00000010	/* Little endian signed 16*/
#	define AFMT_S16_BE		0x00000020	/* Big endian signed 16 */
#	define AFMT_S8			0x00000040
#	define AFMT_U16_LE		0x00000080	/* Little endian U16 */
#	define AFMT_U16_BE		0x00000100	/* Big endian U16 */
#	define AFMT_MPEG		0x00000200	/* MPEG (2) audio */
#	define AFMT_AC3		0x00000400	/* Dolby Digital AC3 */

/*
 * Buffer status queries.
 */
typedef struct audio_buf_info {
			int fragments;	/* # of available fragments (partially usend ones not counted) */
			int fragstotal;	/* Total # of fragments allocated */
			int fragsize;	/* Size of a fragment in bytes */

			int bytes;	/* Available space in bytes (includes partially used fragments) */
			/* Note! 'bytes' could be more than fragments*fragsize */
		} audio_buf_info;

#define SNDCTL_DSP_GETOSPACE		_SIOR ('P',12, audio_buf_info)
#define SNDCTL_DSP_GETISPACE		_SIOR ('P',13, audio_buf_info)
#define SNDCTL_DSP_NONBLOCK		_SIO  ('P',14)
#define SNDCTL_DSP_GETCAPS		_SIOR ('P',15, int)
#	define DSP_CAP_REVISION		0x000000ff	/* Bits for revision level (0 to 255) */
#	define DSP_CAP_DUPLEX		0x00000100	/* Full duplex record/playback */
#	define DSP_CAP_REALTIME		0x00000200	/* Real time capability */
#	define DSP_CAP_BATCH		0x00000400	/* Device has some kind of */
							/* internal buffers which may */
							/* cause some delays and */
							/* decrease precision of timing */
#	define DSP_CAP_COPROC		0x00000800	/* Has a coprocessor */
							/* Sometimes it's a DSP */
							/* but usually not */
#	define DSP_CAP_TRIGGER		0x00001000	/* Supports SETTRIGGER */
#	define DSP_CAP_MMAP		0x00002000	/* Supports mmap() */
#	define DSP_CAP_MULTI		0x00004000	/* support multiple open */
#	define DSP_CAP_BIND		0x00008000	/* channel binding to front/rear/cneter/lfe */


#define SNDCTL_DSP_GETTRIGGER		_SIOR ('P',16, int)
#define SNDCTL_DSP_SETTRIGGER		_SIOW ('P',16, int)
#	define PCM_ENABLE_INPUT		0x00000001
#	define PCM_ENABLE_OUTPUT		0x00000002

typedef struct count_info {
		int bytes;	/* Total # of bytes processed */
		int blocks;	/* # of fragment transitions since last time */
		int ptr;	/* Current DMA pointer value */
	} count_info;

#define SNDCTL_DSP_GETIPTR		_SIOR ('P',17, count_info)
#define SNDCTL_DSP_GETOPTR		_SIOR ('P',18, count_info)

typedef struct buffmem_desc {
		unsigned *buffer;
		int size;
	} buffmem_desc;
#define SNDCTL_DSP_MAPINBUF		_SIOR ('P', 19, buffmem_desc)
#define SNDCTL_DSP_MAPOUTBUF		_SIOR ('P', 20, buffmem_desc)
#define SNDCTL_DSP_SETSYNCRO		_SIO  ('P', 21)
#define SNDCTL_DSP_SETDUPLEX		_SIO  ('P', 22)
#define SNDCTL_DSP_GETODELAY		_SIOR ('P', 23, int)

#define SNDCTL_DSP_GETCHANNELMASK		_SIOWR('P', 64, int)
#define SNDCTL_DSP_BIND_CHANNEL		_SIOWR('P', 65, int)
#	define DSP_BIND_QUERY		0x00000000
#	define DSP_BIND_FRONT		0x00000001
#	define DSP_BIND_SURR		0x00000002
#	define DSP_BIND_CENTER_LFE	0x00000004
#	define DSP_BIND_HANDSET		0x00000008
#	define DSP_BIND_MIC		0x00000010
#	define DSP_BIND_MODEM1		0x00000020
#	define DSP_BIND_MODEM2		0x00000040
#	define DSP_BIND_I2S		0x00000080
#	define DSP_BIND_SPDIF		0x00000100

#define SNDCTL_DSP_SETSPDIF		_SIOW ('P', 66, int)
#define SNDCTL_DSP_GETSPDIF		_SIOR ('P', 67, int)
#	define SPDIF_PRO	0x0001
#	define SPDIF_N_AUD	0x0002
#	define SPDIF_COPY	0x0004
#	define SPDIF_PRE	0x0008
#	define SPDIF_CC		0x07f0
#	define SPDIF_L		0x0800
#	define SPDIF_DRS	0x4000
#	define SPDIF_V		0x8000

/*
 * Application's profile defines the way how playback underrun situations should be handled.
 * 
 *	APF_NORMAL (the default) and APF_NETWORK make the driver to cleanup the
 *	playback buffer whenever an underrun occurs. This consumes some time
 *	prevents looping the existing buffer.
 *	APF_CPUINTENS is intended to be set by CPU intensive applications which
 *	are likely to run out of time occasionally. In this mode the buffer cleanup is
 *	disabled which saves CPU time but also let's the previous buffer content to
 *	be played during the "pause" after the underrun.
 */
#define SNDCTL_DSP_PROFILE		_SIOW ('P', 23, int)
#define	  APF_NORMAL	0	/* Normal applications */
#define	  APF_NETWORK	1	/* Underruns probably caused by an "external" delay */
#define   APF_CPUINTENS 2	/* Underruns probably caused by "overheating" the CPU */

#define SOUND_PCM_READ_RATE		_SIOR ('P', 2, int)
#define SOUND_PCM_READ_CHANNELS		_SIOR ('P', 6, int)
#define SOUND_PCM_READ_BITS		_SIOR ('P', 5, int)
#define SOUND_PCM_READ_FILTER		_SIOR ('P', 7, int)

/* Some alias names */
#define SOUND_PCM_WRITE_BITS		SNDCTL_DSP_SETFMT
#define SOUND_PCM_WRITE_RATE		SNDCTL_DSP_SPEED
#define SOUND_PCM_POST			SNDCTL_DSP_POST
#define SOUND_PCM_RESET			SNDCTL_DSP_RESET
#define SOUND_PCM_SYNC			SNDCTL_DSP_SYNC
#define SOUND_PCM_SUBDIVIDE		SNDCTL_DSP_SUBDIVIDE
#define SOUND_PCM_SETFRAGMENT		SNDCTL_DSP_SETFRAGMENT
#define SOUND_PCM_GETFMTS		SNDCTL_DSP_GETFMTS
#define SOUND_PCM_SETFMT		SNDCTL_DSP_SETFMT
#define SOUND_PCM_GETOSPACE		SNDCTL_DSP_GETOSPACE
#define SOUND_PCM_GETISPACE		SNDCTL_DSP_GETISPACE
#define SOUND_PCM_NONBLOCK		SNDCTL_DSP_NONBLOCK
#define SOUND_PCM_GETCAPS		SNDCTL_DSP_GETCAPS
#define SOUND_PCM_GETTRIGGER		SNDCTL_DSP_GETTRIGGER
#define SOUND_PCM_SETTRIGGER		SNDCTL_DSP_SETTRIGGER
#define SOUND_PCM_SETSYNCRO		SNDCTL_DSP_SETSYNCRO
#define SOUND_PCM_GETIPTR		SNDCTL_DSP_GETIPTR
#define SOUND_PCM_GETOPTR		SNDCTL_DSP_GETOPTR
#define SOUND_PCM_MAPINBUF		SNDCTL_DSP_MAPINBUF
#define SOUND_PCM_MAPOUTBUF		SNDCTL_DSP_MAPOUTBUF

/*
 * ioctl calls to be used in communication with coprocessors and
 * DSP chips.
 */

typedef struct copr_buffer {
		int command;	/* Set to 0 if not used */
		int flags;
#define CPF_NONE		0x0000
#define CPF_FIRST		0x0001	/* First block */
#define CPF_LAST		0x0002	/* Last block */
		int len;
		int offs;	/* If required by the device (0 if not used) */

		unsigned char data[4000]; /* NOTE! 4000 is not 4k */
	} copr_buffer;

typedef struct copr_debug_buf {
		int command;	/* Used internally. Set to 0 */
		int parm1;
		int parm2;
		int flags;	
		int len;	/* Length of data in bytes */
	} copr_debug_buf;

typedef struct copr_msg {
		int len;
		unsigned char data[4000];
	} copr_msg;

#define SNDCTL_COPR_RESET             _SIO  ('C',  0)
#define SNDCTL_COPR_LOAD	      _SIOWR('C',  1, copr_buffer)
#define SNDCTL_COPR_RDATA	      _SIOWR('C',  2, copr_debug_buf)
#define SNDCTL_COPR_RCODE	      _SIOWR('C',  3, copr_debug_buf)
#define SNDCTL_COPR_WDATA	      _SIOW ('C',  4, copr_debug_buf)
#define SNDCTL_COPR_WCODE	      _SIOW ('C',  5, copr_debug_buf)
#define SNDCTL_COPR_RUN		      _SIOWR('C',  6, copr_debug_buf)
#define SNDCTL_COPR_HALT	      _SIOWR('C',  7, copr_debug_buf)
#define SNDCTL_COPR_SENDMSG	      _SIOWR('C',  8, copr_msg)
#define SNDCTL_COPR_RCVMSG	      _SIOR ('C',  9, copr_msg)

/*********************************************
 * IOCTL commands for /dev/mixer
 */
	
/* 
 * Mixer devices
 *
 * There can be up to 20 different analog mixer channels. The
 * SOUND_MIXER_NRDEVICES gives the currently supported maximum. 
 * The SOUND_MIXER_READ_DEVMASK returns a bitmask which tells
 * the devices supported by the particular mixer.
 */

#define SOUND_MIXER_NRDEVICES	25
#define SOUND_MIXER_VOLUME	0
#define SOUND_MIXER_BASS	1
#define SOUND_MIXER_TREBLE	2
#define SOUND_MIXER_SYNTH	3
#define SOUND_MIXER_PCM		4
#define SOUND_MIXER_SPEAKER	5
#define SOUND_MIXER_LINE	6
#define SOUND_MIXER_MIC		7
#define SOUND_MIXER_CD		8
#define SOUND_MIXER_IMIX	9	/*  Recording monitor  */
#define SOUND_MIXER_ALTPCM	10
#define SOUND_MIXER_RECLEV	11	/* Recording level */
#define SOUND_MIXER_IGAIN	12	/* Input gain */
#define SOUND_MIXER_OGAIN	13	/* Output gain */
/* 
 * The AD1848 codec and compatibles have three line level inputs
 * (line, aux1 and aux2). Since each card manufacturer have assigned
 * different meanings to these inputs, it's inpractical to assign
 * specific meanings (line, cd, synth etc.) to them.
 */
#define SOUND_MIXER_LINE1	14	/* Input source 1  (aux1) */
#define SOUND_MIXER_LINE2	15	/* Input source 2  (aux2) */
#define SOUND_MIXER_LINE3	16	/* Input source 3  (line) */
#define SOUND_MIXER_DIGITAL1	17	/* Digital (input) 1 */
#define SOUND_MIXER_DIGITAL2	18	/* Digital (input) 2 */
#define SOUND_MIXER_DIGITAL3	19	/* Digital (input) 3 */
#define SOUND_MIXER_PHONEIN	20	/* Phone input */
#define SOUND_MIXER_PHONEOUT	21	/* Phone output */
#define SOUND_MIXER_VIDEO	22	/* Video/TV (audio) in */
#define SOUND_MIXER_RADIO	23	/* Radio in */
#define SOUND_MIXER_MONITOR	24	/* Monitor (usually mic) volume */

/* Some on/off settings (SOUND_SPECIAL_MIN - SOUND_SPECIAL_MAX) */
/* Not counted to SOUND_MIXER_NRDEVICES, but use the same number space */
#define SOUND_ONOFF_MIN		28
#define SOUND_ONOFF_MAX		30

/* Note!	Number 31 cannot be used since the sign bit is reserved */
#define SOUND_MIXER_NONE	31

/*
 * The following unsupported macros are no longer functional.
 * Use SOUND_MIXER_PRIVATE# macros in future.
 */
#define SOUND_MIXER_ENHANCE	SOUND_MIXER_NONE
#define SOUND_MIXER_MUTE	SOUND_MIXER_NONE
#define SOUND_MIXER_LOUD	SOUND_MIXER_NONE


#define SOUND_DEVICE_LABELS	{"Vol  ", "Bass ", "Trebl", "Synth", "Pcm  ", "Spkr ", "Line ", \
				 "Mic  ", "CD   ", "Mix  ", "Pcm2 ", "Rec  ", "IGain", "OGain", \
				 "Line1", "Line2", "Line3", "Digital1", "Digital2", "Digital3", \
				 "PhoneIn", "PhoneOut", "Video", "Radio", "Monitor"}

#define SOUND_DEVICE_NAMES	{"vol", "bass", "treble", "synth", "pcm", "speaker", "line", \
				 "mic", "cd", "mix", "pcm2", "rec", "igain", "ogain", \
				 "line1", "line2", "line3", "dig1", "dig2", "dig3", \
				 "phin", "phout", "video", "radio", "monitor"}

/*	Device bitmask identifiers	*/

#define SOUND_MIXER_RECSRC	0xff	/* Arg contains a bit for each recording source */
#define SOUND_MIXER_DEVMASK	0xfe	/* Arg contains a bit for each supported device */
#define SOUND_MIXER_RECMASK	0xfd	/* Arg contains a bit for each supported recording source */
#define SOUND_MIXER_CAPS	0xfc
#	define SOUND_CAP_EXCL_INPUT	0x00000001	/* Only one recording source at a time */
#define SOUND_MIXER_STEREODEVS	0xfb	/* Mixer channels supporting stereo */
#define SOUND_MIXER_OUTSRC	0xfa	/* Arg contains a bit for each input source to output */
#define SOUND_MIXER_OUTMASK	0xf9	/* Arg contains a bit for each supported input source to output */

/*	Device mask bits	*/

#define SOUND_MASK_VOLUME	(1 << SOUND_MIXER_VOLUME)
#define SOUND_MASK_BASS		(1 << SOUND_MIXER_BASS)
#define SOUND_MASK_TREBLE	(1 << SOUND_MIXER_TREBLE)
#define SOUND_MASK_SYNTH	(1 << SOUND_MIXER_SYNTH)
#define SOUND_MASK_PCM		(1 << SOUND_MIXER_PCM)
#define SOUND_MASK_SPEAKER	(1 << SOUND_MIXER_SPEAKER)
#define SOUND_MASK_LINE		(1 << SOUND_MIXER_LINE)
#define SOUND_MASK_MIC		(1 << SOUND_MIXER_MIC)
#define SOUND_MASK_CD		(1 << SOUND_MIXER_CD)
#define SOUND_MASK_IMIX		(1 << SOUND_MIXER_IMIX)
#define SOUND_MASK_ALTPCM	(1 << SOUND_MIXER_ALTPCM)
#define SOUND_MASK_RECLEV	(1 << SOUND_MIXER_RECLEV)
#define SOUND_MASK_IGAIN	(1 << SOUND_MIXER_IGAIN)
#define SOUND_MASK_OGAIN	(1 << SOUND_MIXER_OGAIN)
#define SOUND_MASK_LINE1	(1 << SOUND_MIXER_LINE1)
#define SOUND_MASK_LINE2	(1 << SOUND_MIXER_LINE2)
#define SOUND_MASK_LINE3	(1 << SOUND_MIXER_LINE3)
#define SOUND_MASK_DIGITAL1	(1 << SOUND_MIXER_DIGITAL1)
#define SOUND_MASK_DIGITAL2	(1 << SOUND_MIXER_DIGITAL2)
#define SOUND_MASK_DIGITAL3	(1 << SOUND_MIXER_DIGITAL3)
#define SOUND_MASK_PHONEIN	(1 << SOUND_MIXER_PHONEIN)
#define SOUND_MASK_PHONEOUT	(1 << SOUND_MIXER_PHONEOUT)
#define SOUND_MASK_RADIO	(1 << SOUND_MIXER_RADIO)
#define SOUND_MASK_VIDEO	(1 << SOUND_MIXER_VIDEO)
#define SOUND_MASK_MONITOR	(1 << SOUND_MIXER_MONITOR)

/* Obsolete macros */
#define SOUND_MASK_MUTE		(1 << SOUND_MIXER_MUTE)
#define SOUND_MASK_ENHANCE	(1 << SOUND_MIXER_ENHANCE)
#define SOUND_MASK_LOUD		(1 << SOUND_MIXER_LOUD)

#define MIXER_READ(dev)		_SIOR('M', dev, int)
#define SOUND_MIXER_READ_VOLUME		MIXER_READ(SOUND_MIXER_VOLUME)
#define SOUND_MIXER_READ_BASS		MIXER_READ(SOUND_MIXER_BASS)
#define SOUND_MIXER_READ_TREBLE		MIXER_READ(SOUND_MIXER_TREBLE)
#define SOUND_MIXER_READ_SYNTH		MIXER_READ(SOUND_MIXER_SYNTH)
#define SOUND_MIXER_READ_PCM		MIXER_READ(SOUND_MIXER_PCM)
#define SOUND_MIXER_READ_SPEAKER	MIXER_READ(SOUND_MIXER_SPEAKER)
#define SOUND_MIXER_READ_LINE		MIXER_READ(SOUND_MIXER_LINE)
#define SOUND_MIXER_READ_MIC		MIXER_READ(SOUND_MIXER_MIC)
#define SOUND_MIXER_READ_CD		MIXER_READ(SOUND_MIXER_CD)
#define SOUND_MIXER_READ_IMIX		MIXER_READ(SOUND_MIXER_IMIX)
#define SOUND_MIXER_READ_ALTPCM		MIXER_READ(SOUND_MIXER_ALTPCM)
#define SOUND_MIXER_READ_RECLEV		MIXER_READ(SOUND_MIXER_RECLEV)
#define SOUND_MIXER_READ_IGAIN		MIXER_READ(SOUND_MIXER_IGAIN)
#define SOUND_MIXER_READ_OGAIN		MIXER_READ(SOUND_MIXER_OGAIN)
#define SOUND_MIXER_READ_LINE1		MIXER_READ(SOUND_MIXER_LINE1)
#define SOUND_MIXER_READ_LINE2		MIXER_READ(SOUND_MIXER_LINE2)
#define SOUND_MIXER_READ_LINE3		MIXER_READ(SOUND_MIXER_LINE3)

/* Obsolete macros */
#define SOUND_MIXER_READ_MUTE		MIXER_READ(SOUND_MIXER_MUTE)
#define SOUND_MIXER_READ_ENHANCE	MIXER_READ(SOUND_MIXER_ENHANCE)
#define SOUND_MIXER_READ_LOUD		MIXER_READ(SOUND_MIXER_LOUD)

#define SOUND_MIXER_READ_RECSRC		MIXER_READ(SOUND_MIXER_RECSRC)
#define SOUND_MIXER_READ_DEVMASK	MIXER_READ(SOUND_MIXER_DEVMASK)
#define SOUND_MIXER_READ_RECMASK	MIXER_READ(SOUND_MIXER_RECMASK)
#define SOUND_MIXER_READ_STEREODEVS	MIXER_READ(SOUND_MIXER_STEREODEVS)
#define SOUND_MIXER_READ_CAPS		MIXER_READ(SOUND_MIXER_CAPS)

#define MIXER_WRITE(dev)		_SIOWR('M', dev, int)
