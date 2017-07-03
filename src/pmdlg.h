/*

	pmdlg

	Paper Mario 64 dialog bank decoder
	
	shygoo 2017
	
	License: MIT
	
	Thanks to Justin Aquandro for dialog system documentation:
	http://hocuspocus.taloncrossing.com/rii/pmdiag/pm1docs.txt

*/

#ifndef PMDLG_H
#define PMDLG_H

#include <stdint.h>
#include <stdarg.h>

#include "n64rom.h"

#define CHR_MUSIC_NOTE            0x00
#define CHR_HEART                 0x90
#define CHR_STAR                  0x91
#define CHR_UP_ARROW              0x92
#define CHR_DN_ARROW              0x93
#define CHR_LT_ARROW              0x94
#define CHR_RT_ARROW              0x95
#define CHR_O_NOUGHT              0x96
#define CHR_X_CROSS               0x97
#define CHR_A_BUTTON              0x98
#define CHR_B_BUTTON              0x99
#define CHR_L_BUTTON              0x9A
#define CHR_R_BUTTON              0x9B
#define CHR_Z_BUTTON              0x9C
#define CHR_C_UP_BUTTON           0x9D
#define CHR_C_DN_BUTTON           0x9E
#define CHR_C_LT_BUTTON           0x9F
#define CHR_C_RT_BUTTON           0xA0
#define CHR_START_BUTTON          0xA1
#define CHR_NULL_0                0xA2
#define CHR_NULL_1                0xA3
#define CHR_NULL_2                0xA4
#define CHR_NULL_3                0xA5
#define CHR_NULL_4                0xA6
#define CHR_TAB_16                0xA8
#define CHR_TAB_6                 0xA9
#define CHR_LINE_BREAK            0xF0
#define CHR_BELL                  0xF1
#define CHR_DELAY                 0xF2
#define CHR_NEXT_BUBBLE           0xFB
#define CHR_STYLE                 0xFC
#define CHR_END                   0xFD
#define CHR_CMD                   0xFF

#define STYLE_INVALID             0x00
#define STYLE_BUBBLE_RIGHT        0x01
#define STYLE_BUBBLE_LEFT         0x02
#define STYLE_BUBBLE_A            0x03
#define STYLE_BUBBLE_B            0x04
#define STYLE_WHITE_BORDER        0x05
#define STYLE_NARRATION_A         0x06
#define STYLE_SIGN_POST           0x07
#define STYLE_BLUE_MESSAGE        0x08
#define STYLE_INVALID_2           0x09
#define STYLE_WHITE_BUBBLE        0x0A
#define STYLE_WHITE_BUBBLE_B      0x0B
#define STYLE_NO_DISPLAY          0x0C
#define STYLE_NARRATION_SILENT    0x0D
#define STYLE_NO_DISPLAY_V_CENTER 0x0E
#define STYLE_NARRATION_B         0x0F

#define EFFECT_JITTER             0x00
#define EFFECT_WAVE               0x01
#define EFFECT_DARK_STATIC        0x02
#define EFFECT_LIGHT_STATIC       0x03 // [1] Intensity
#define EFFECT_UNKNOWN            0x04
#define EFFECT_GHOST_JITTER       0x05 // [1] [Unknown]
#define EFFECT_CHASING_RAINBOW_A  0x06
#define EFFECT_GRAYED_OUT         0x07 // [1] Darkness
#define EFFECT_WAVE_B             0x08
#define EFFECT_CHASING_RAINBOW_B  0x09
#define EFFECT_SHRINK_PLACEMENT   0x0A
#define EFFECT_GROWTH_PLACEMENT   0x0B
#define EFFECT_SIZE_JITTER        0x0C
#define EFFECT_SIZE_WAVE          0x0D
#define EFFECT_DROP_SHADOW        0x0E

// 01, 02, 03 unused ?
#define CMD_UNK_00                0x00
#define CMD_UNK_04                0x04
#define CMD_TEXT_COLOR            0x05
#define CMD_UNK_07                0x07
#define CMD_UNK_08                0x08
#define CMD_PRINT_INSTANT         0x09
#define CMD_CANCEL_WRITING        0x0A
#define CMD_FONT_KERNING          0x0B
#define CMD_AUTO_SCROLL           0x0C
#define CMD_FONT_SIZE             0x0D
#define CMD_FONT_SIZE_RESET       0x0E
#define CMD_PRINT_SPEED           0x0F
#define CMD_MARGIN                0x10
#define CMD_UNK_11                0x11
#define CMD_UNK_12                0x12
#define CMD_UNK_13                0x13
#define CMD_UNK_14                0x14
#define CMD_GRAPHIC_A             0x15
#define CMD_ICON                  0x17
#define CMD_GRAPHIC_B             0x18
#define CMD_UNK_1A                0x1A
#define CMD_UNK_1B                0x1B
#define CMD_UNK_1E                0x1E
#define CMD_UNK_1F                0x1F
#define CMD_UNK_20                0x20
#define CMD_UNK_21                0x21
#define CMD_UNK_22                0x22
#define CMD_UNK_23                0x23
#define CMD_SAVE_TEXT_COLOR       0x24
#define CMD_LOAD_TEXT_COLOR       0x25
#define CMD_START_EFFECT          0x26
#define CMD_CANCEL_EFFECT         0x27
#define CMD_UNK_28                0x28
#define CMD_UNK_29                0x29
#define CMD_UNK_2B                0x2B
#define CMD_VOLUME                0x2E
#define CMD_VOICE                 0x2F

#define SPECIAL_CHAR (-1)

struct _pm_dlg_element;

typedef void (*pm_dlg_arg_decoder_t)(n64rom_t* rom);

typedef struct _pm_dlg_element {
	const uint8_t value;
	const char* name;
	const int nargs;
	pm_dlg_arg_decoder_t decode_args;
} pm_dlg_element_t;

void pm_decode_dialog(n64rom_t* rom);

const pm_dlg_element_t* pm_map_get(const pm_dlg_element_t* map, uint8_t value);
const pm_dlg_element_t* pm_dlg_get_special_char(uint8_t chr);
const pm_dlg_element_t* pm_dlg_get_style(uint8_t style_id);
const pm_dlg_element_t* pm_dlg_get_command(uint8_t command_id);
const pm_dlg_element_t* pm_dlg_get_effect(uint8_t effect_id);

char pm_dlg_char_to_ascii(uint8_t c);
void pm_dlg_decode_sequence(n64rom_t* rom);
int pm_dlg_decode_section(n64rom_t* rom, int bank_pos, int section_num);

void pm_decode_cmd_00_args(n64rom_t* rom);
void pm_decode_cmd_effect_args(n64rom_t* rom);
void pm_decode_chr_cmd_args(n64rom_t* rom);
void pm_decode_chr_style_args(n64rom_t* rom);

// const int* pm_dlg_bank_list_e();
// const int* pm_dlg_bank_list_j();
// const int* pm_dlg_bank_list_p();

void pm_dlg_open_output(const char* path);
void pm_dlg_close_output();
void pm_dlg_output(const char* format, ...);
void pm_dlg_output_auto_msg();
void pm_dlg_make_asm_dir();

#endif // PMDLG_H
