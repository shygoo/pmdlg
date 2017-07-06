/*

	pmdlg

	Paper Mario 64 dialog bank decoder
	
	shygoo 2017
	
	License: MIT
	
	Thanks to Justin Aquandro for dialog system documentation:
	http://hocuspocus.taloncrossing.com/rii/pmdiag/pm1docs.txt

*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include "n64rom.h"
#include "pmdlg.h"

// Names and argument decoder dispatch

const pm_dlg_element_t* pm_dlg_get_special_char(uint8_t chr)
{
	static const pm_dlg_element_t map[] = {
		{ CHR_MUSIC_NOTE,   "CHR_MUSIC_NOTE",   0, NULL },
		{ CHR_HEART,        "CHR_HEART",        0, NULL },
		{ CHR_STAR,         "CHR_STAR",         0, NULL },
		{ CHR_UP_ARROW,     "CHR_UP_ARROW",     0, NULL },
		{ CHR_DN_ARROW,     "CHR_DN_ARROW",     0, NULL },
		{ CHR_LT_ARROW,     "CHR_LT_ARROW",     0, NULL },
		{ CHR_RT_ARROW,     "CHR_RT_ARROW",     0, NULL },
		{ CHR_O_NOUGHT,     "CHR_O_NOUGHT",     0, NULL },
		{ CHR_X_CROSS,      "CHR_X_CROSS",      0, NULL },
		{ CHR_A_BUTTON,     "CHR_A_BUTTON",     0, NULL },
		{ CHR_B_BUTTON,     "CHR_B_BUTTON",     0, NULL },
		{ CHR_L_BUTTON,     "CHR_L_BUTTON",     0, NULL },
		{ CHR_R_BUTTON,     "CHR_R_BUTTON",     0, NULL },
		{ CHR_Z_BUTTON,     "CHR_Z_BUTTON",     0, NULL },
		{ CHR_C_UP_BUTTON,  "CHR_C_UP_BUTTON",  0, NULL },
		{ CHR_C_DN_BUTTON,  "CHR_C_DN_BUTTON",  0, NULL },
		{ CHR_C_LT_BUTTON,  "CHR_C_LT_BUTTON",  0, NULL },
		{ CHR_C_RT_BUTTON,  "CHR_C_RT_BUTTON",  0, NULL },
		{ CHR_START_BUTTON, "CHR_START_BUTTON", 0, NULL },
		{ CHR_NULL_0,       "CHR_NULL_0",       0, NULL },
		{ CHR_NULL_1,       "CHR_NULL_1",       0, NULL },
		{ CHR_NULL_2,       "CHR_NULL_2",       0, NULL },
		{ CHR_NULL_3,       "CHR_NULL_3",       0, NULL },
		{ CHR_NULL_4,       "CHR_NULL_4",       0, NULL },
		{ CHR_TAB_16,       "CHR_TAB_16",       0, NULL },
		{ CHR_TAB_6,        "CHR_TAB_6",        0, NULL },
		{ CHR_LINE_BREAK,   "CHR_LINE_BREAK",   0, NULL },
		{ CHR_BELL,         "CHR_BELL",         0, NULL },
		{ CHR_DELAY,        "CHR_DELAY",        1, NULL },
		{ CHR_NEXT_BUBBLE,  "CHR_NEXT_BUBBLE",  0, NULL },
		{ CHR_STYLE,        "CHR_STYLE",        1, pm_decode_chr_style_args },
		{ CHR_END,          "CHR_END",          0, NULL },
		{ CHR_CMD,          "CHR_CMD",          1, pm_decode_chr_cmd_args },
		{ 0, NULL, 0, NULL}
	};
	
	return pm_map_get(map, chr);
}

const pm_dlg_element_t* pm_dlg_get_command(uint8_t command_id)
{
	static const pm_dlg_element_t map[] = {
		{ CMD_UNK_00,          "CMD_UNK_00",         -1,  pm_decode_cmd_00_args }, // 00 changes encoding in last dialog section??
		// 01, 02, 03 unused ?                        
		{ CMD_UNK_04,          "CMD_UNK_04",          0,  NULL }, // 04
		{ CMD_TEXT_COLOR,      "CMD_TEXT_COLOR",      1,  NULL }, // 05
		// 06 unused ?                                
		{ CMD_UNK_07,          "CMD_UNK_07",          0,  NULL },
		{ CMD_UNK_08,          "CMD_UNK_08",          0,  NULL }, // 08
		{ CMD_PRINT_INSTANT,   "CMD_PRINT_INSTANT",   0,  NULL }, // 09
		{ CMD_CANCEL_WRITING,  "CMD_CANCEL_WRITING",  0,  NULL }, // 0A
		{ CMD_FONT_KERNING,    "CMD_FONT_KERNING",    1,  NULL }, // 0B
		{ CMD_AUTO_SCROLL,     "CMD_AUTO_SCROLL",     1,  NULL }, // 0C
		{ CMD_FONT_SIZE,       "CMD_FONT_SIZE",       2,  NULL }, // 0D
		{ CMD_FONT_SIZE_RESET, "CMD_FONT_SIZE_RESET", 0,  NULL }, // 0E
		{ CMD_PRINT_SPEED,     "CMD_PRINT_SPEED",     2,  NULL }, // 0F
		{ CMD_MARGIN,          "CMD_MARGIN",          2,  NULL }, // 10
		{ CMD_UNK_11,          "CMD_UNK_11",          1,  NULL }, // 11
		{ CMD_UNK_12,          "CMD_UNK_12",          1,  NULL }, // 12
		{ CMD_UNK_13,          "CMD_UNK_13",          1,  NULL }, // 13
		{ CMD_UNK_14,          "CMD_UNK_14",          1,  NULL }, // 14
		{ CMD_GRAPHIC_A,       "CMD_GRAPHIC_A",       1,  NULL }, // 15
		// 16 possibly unused                         
		{ CMD_ICON,            "CMD_ICON",            2,  NULL }, // 17
		{ CMD_GRAPHIC_B,       "CMD_GRAPHIC_B",       7,  NULL }, // 18
		// 19 unused?                                 
		{ CMD_UNK_1A,          "CMD_UNK_1A",          8,  NULL }, // 1A // need to check ASM
		{ CMD_UNK_1B,          "CMD_UNK_1B",          7,  NULL }, // 1B // need to check ASM
		// 1c possibly unused                         
		// 1e through 21 selection related            
		{ CMD_UNK_1E,          "CMD_UNK_1E",          1,  NULL }, // 1E
		{ CMD_UNK_1F,          "CMD_UNK_1F",          1,  NULL }, // 1F
		{ CMD_UNK_20,          "CMD_UNK_20",          1,  NULL }, // 20
		{ CMD_UNK_21,          "CMD_UNK_21",          1,  NULL }, // 21
		{ CMD_UNK_22,          "CMD_UNK_22",          0,  NULL }, // 21
		{ CMD_UNK_23,          "CMD_UNK_23",          0,  NULL }, // 23
		{ CMD_SAVE_TEXT_COLOR, "CMD_SAVE_TEXT_COLOR", 0,  NULL }, // 24
		{ CMD_LOAD_TEXT_COLOR, "CMD_LOAD_TEXT_COLOR", 0,  NULL }, // 25
		{ CMD_START_EFFECT,    "CMD_START_EFFECT",    1,  pm_decode_cmd_effect_args }, // 26
		{ CMD_CANCEL_EFFECT,   "CMD_CANCEL_EFFECT",   1,  pm_decode_cmd_effect_args }, // 27
		{ CMD_UNK_28,          "CMD_UNK_28",          1,  NULL }, // 28
		{ CMD_UNK_29,          "CMD_UNK_29",          1,  NULL }, // 29
		// 2a unused?                                 
		{ CMD_UNK_2B,          "CMD_UNK_2B",          0,  NULL }, // 2B
		// 2C, 2d unused ?                            
		{ CMD_VOLUME,          "CMD_VOLUME",          1,  NULL }, // 2E
		{ CMD_VOICE,           "CMD_VOICE" ,          1,  NULL }, // 2F
		{ 0, NULL, 0, NULL}		                                     
	};                                                                   

	return pm_map_get(map, command_id);
}

const pm_dlg_element_t* pm_dlg_get_effect(uint8_t effect_id)
{
	static const pm_dlg_element_t map[] = {
		{ EFFECT_JITTER,            "EFFECT_JITTER",            0, NULL },
		{ EFFECT_WAVE,              "EFFECT_WAVE",              0, NULL },
		{ EFFECT_DARK_STATIC,       "EFFECT_DARK_STATIC",       0, NULL },
		{ EFFECT_LIGHT_STATIC,      "EFFECT_LIGHT_STATIC",      1, NULL },
		{ EFFECT_UNKNOWN,           "EFFECT_UNKNOWN",           0, NULL },
		{ EFFECT_GHOST_JITTER,      "EFFECT_GHOST_JITTER",      1, NULL },
		{ EFFECT_CHASING_RAINBOW_A, "EFFECT_CHASING_RAINBOW_A", 0, NULL },
		{ EFFECT_GRAYED_OUT,        "EFFECT_GRAYED_OUT",        1, NULL },
		{ EFFECT_WAVE_B,            "EFFECT_WAVE_B",            0, NULL },
		{ EFFECT_CHASING_RAINBOW_B, "EFFECT_CHASING_RAINBOW_B", 0, NULL },
		{ EFFECT_SHRINK_PLACEMENT,  "EFFECT_SHRINK_PLACEMENT",  0, NULL },
		{ EFFECT_GROWTH_PLACEMENT,  "EFFECT_GROWTH_PLACEMENT",  0, NULL },
		{ EFFECT_SIZE_JITTER,       "EFFECT_SIZE_JITTER",       0, NULL },
		{ EFFECT_SIZE_WAVE,         "EFFECT_SIZE_WAVE",         0, NULL },
		{ EFFECT_DROP_SHADOW,       "EFFECT_DROP_SHADOW",       0, NULL },
		{ 0, NULL, 0, NULL}
	};
	
	return pm_map_get(map, effect_id);
}

const pm_dlg_element_t* pm_dlg_get_style(uint8_t style_id)
{
	static const pm_dlg_element_t map[] = {
		{ STYLE_INVALID,             "STYLE_INVALID",             0, NULL },
		{ STYLE_BUBBLE_RIGHT,        "STYLE_BUBBLE_RIGHT",        0, NULL },
		{ STYLE_BUBBLE_LEFT,         "STYLE_BUBBLE_LEFT",         0, NULL },
		{ STYLE_BUBBLE_A,            "STYLE_BUBBLE_A",            0, NULL },
		{ STYLE_BUBBLE_B,            "STYLE_BUBBLE_B",            0, NULL },
		{ STYLE_WHITE_BORDER,        "STYLE_WHITE_BORDER",        4, NULL },
		{ STYLE_NARRATION_A,         "STYLE_NARRATION_A",         0, NULL },
		{ STYLE_SIGN_POST,           "STYLE_SIGN_POST",           0, NULL },
		{ STYLE_BLUE_MESSAGE,        "STYLE_BLUE_MESSAGE",        1, NULL },
		{ STYLE_INVALID_2,           "STYLE_INVALID_2",           0, NULL },
		{ STYLE_WHITE_BUBBLE,        "STYLE_WHITE_BUBBLE",        0, NULL },
		{ STYLE_WHITE_BUBBLE_B,      "STYLE_WHITE_BUBBLE_B",      0, NULL },
		{ STYLE_NO_DISPLAY,          "STYLE_NO_DISPLAY",          4, NULL },
		{ STYLE_NARRATION_SILENT,    "STYLE_NARRATION_SILENT",    0, NULL },
		{ STYLE_NO_DISPLAY_V_CENTER, "STYLE_NO_DISPLAY_V_CENTER", 0, NULL },
		{ STYLE_NARRATION_B,         "STYLE_NARRATION_B",         0, NULL },
		{ 0, NULL, 0, NULL}
	};
	
	return pm_map_get(map, style_id);
}

const pm_dlg_element_t* pm_map_get(const pm_dlg_element_t* map, uint8_t value)
{
	for(int i = 0; map[i].name != NULL; i++)
	{
		if(map[i].value == value)
		{
			return &map[i];
		}
	}
	return NULL;
}

// Argument Decoders

// CHR_CMD, CMD_UNK_00
void pm_decode_cmd_00_args(n64rom_t* rom)
{
	while(true)
	{
		uint8_t c = n64rom_stream_read_u8(rom);
		
		if(c == CHR_END)
		{
			n64rom_stream_set_pos(rom, n64rom_stream_get_pos(rom) - 1);
			break;
		}
		
		pm_dlg_output(", 0x%02X", c);
	}
}

// CHR_CMD, CMD_START/CANCEL_EFFECT
void pm_decode_cmd_effect_args(n64rom_t* rom)
{
	int effect_id = n64rom_stream_read_u8(rom);
	const pm_dlg_element_t* effect = pm_dlg_get_effect(effect_id);
	
	if(!effect)
	{
		pm_dlg_output(", 0x%02X", effect_id);
		return;
	}

	pm_dlg_output(", %s", effect->name);
	
	for(int i = 0; i < effect->nargs; i++)
	{
		uint8_t arg = n64rom_stream_read_u8(rom);
		pm_dlg_output(", 0x%02X", arg);
	}
	
	return;
}

// CHR_CMD
void pm_decode_chr_cmd_args(n64rom_t* rom)
{
	int command_id = n64rom_stream_read_u8(rom);
	const pm_dlg_element_t* command = pm_dlg_get_command(command_id);
	
	if(command == NULL)
	{
		pm_dlg_output(", 0x%02X ; unknown command", command_id);
		return;
	}
	else
	{
		pm_dlg_output(", %s", command->name);
	}
	
	if(command->decode_args != NULL)
	{
		command->decode_args(rom);
	}
	else
	{
		for(int j = 0; j < command->nargs; j++)
		{
			pm_dlg_output(", 0x%02X", n64rom_stream_read_u8(rom));
		}
	}
}

// CHR_STYLE
void pm_decode_chr_style_args(n64rom_t* rom)
{
	int style_id = n64rom_stream_read_u8(rom);
	const pm_dlg_element_t* style = pm_dlg_get_style(style_id);
	
	if(style == NULL)
	{
		pm_dlg_output(", 0x%02X", style_id);
		return;
	}
	else
	{
		pm_dlg_output(", %s", style->name);
	}
	
	for(int j = 0; j < style->nargs; j++)
	{
		pm_dlg_output(", 0x%02X", n64rom_stream_read_u8(rom));
	}
}

/////////

char pm_dlg_char_to_ascii(unsigned char c)
{
	if(c >= 0x01 && c <= 0x5E)
	{
		c += 0x20;
		return c;
	}
	
	switch(c)
	{
		case 0x5F: return '°';
		case 0x60: return 'À';
		case 0x61: return 'Á';
		case 0x62: return 'Â';
		case 0x63: return 'Ä';
		case 0x64: return 'Ç';
		case 0x65: return 'È';
		case 0x66: return 'É';
		case 0x67: return 'Ê';
		case 0x68: return 'Ë';
		case 0x69: return 'Ì';
		case 0x6A: return 'Í';
		case 0x6B: return 'Î';
		case 0x6C: return 'Ï';
		case 0x6D: return 'Ñ';
		case 0x6E: return 'Ò';
		case 0x6F: return 'Ó';
		case 0x70: return 'Ô';
		case 0x71: return 'Ö';
		case 0x72: return 'Ù';
		case 0x73: return 'Ú';
		case 0x74: return 'Û';
		case 0x75: return 'Ü';
		case 0x76: return 'ß';
		case 0x77: return 'à';
		case 0x78: return 'á';
		case 0x79: return 'â';
		case 0x7A: return 'ä';
		case 0x7B: return 'ç';
		case 0x7C: return 'è';
		case 0x7D: return 'é';
		case 0x7E: return 'ê';
		case 0x7F: return 'ë';
		case 0x80: return 'ì';
		case 0x81: return 'í';
		case 0x82: return 'î';
		case 0x83: return 'ï';
		case 0x84: return 'ñ';
		case 0x85: return 'ò';
		case 0x86: return 'ó';
		case 0x87: return 'ô';
		case 0x88: return 'ö';
		case 0x89: return 'ù';
		case 0x8A: return 'ú';
		case 0x8B: return 'û';
		case 0x8C: return 'ü';
		case 0x8D: return '¡';
		case 0x8E: return '¿';
		case 0x8F: return 'ª';
		case 0xF7: return ' ';
	}
	
	return SPECIAL_CHAR; // unhandled, must use pm_dlg_char_to_ascii_special
}

// decode until CHR_END is met
void pm_dlg_decode_sequence(n64rom_t* rom)
{
	bool after_element = false;
	bool in_quotes = false;
	
	while(true)
	{
		uint8_t chr = n64rom_stream_read_u8(rom);
		char chr_asc = pm_dlg_char_to_ascii(chr);
		
		if(after_element)
		{
			pm_dlg_output("\r\n");
			after_element = false;
		}
		
		if(chr_asc != SPECIAL_CHAR)
		{
			// Regular character
		
			if(!in_quotes)
			{
				// Start new quoted string
				in_quotes = true;
				pm_dlg_output(".strn \"");
			}
			
			// Add character to quoted string
			if(chr_asc == '"')
			{
				pm_dlg_output("\\\"");
			}
			else
			{
				pm_dlg_output("%c", chr_asc);
			}
			continue;
		}
		
		// Special character
		
		if(in_quotes)
		{
			// end the quotes
			in_quotes = false;
			after_element = true;
		
			if(chr == CHR_LINE_BREAK)
			{
				pm_dlg_output("\\n\"");
				continue;
			}
			else
			{
				pm_dlg_output("\"\r\n");
			}
		}
		
		if(chr == CHR_END)
		{
			pm_dlg_output("end_dlg_seq");
			break;
		}
		
		pm_dlg_output(".strn ");
		
		const pm_dlg_element_t* special = pm_dlg_get_special_char(chr);
		
		if(special == NULL)
		{
			pm_dlg_output("Unhandled special character\r\n");
			exit(EXIT_FAILURE);
		}
		
		after_element = true;
		
		// Print special char name
		
		if(special->name == NULL)
		{
			pm_dlg_output("CHR_UNK_%02X", (uint8_t)chr);
			continue;
		}

		pm_dlg_output("%s", special->name);
		
		// Decode special char arguments
		
		if(special->decode_args == NULL)
		{
			// Default, print out nargs bytes
			for(int i = 0; i < special->nargs; i++)
			{
				pm_dlg_output(", 0x%02X", n64rom_stream_read_u8(rom));
			}
		}
		else
		{
			// Use special character's argument decoder
			special->decode_args(rom);
		}
	}
}

int pm_dlg_decode_section(n64rom_t* rom, int bank_pos, int section_num)
{
	char output_path[PATH_MAX];
	sprintf(output_path, "pm_dialog/dlg_%02X.asm", section_num);
	pm_dlg_open_output(output_path);
	
	pm_dlg_output_auto_msg();
	
	uint32_t section_offset = n64rom_get_u32(rom, bank_pos + section_num * sizeof(uint32_t));
	
	if(section_offset == 0)
	{
		return 0;
	}
	
	pm_dlg_output("; Dialog Section %02X:\r\n\r\n", section_num);
	
	int section_pos = bank_pos + section_offset;
	int section_end_pos = 0;
	
	// Output each string in the section
	
	int string_num = 0;
	
	while(1)
	{
		uint32_t string_offset = n64rom_get_u32(rom, section_pos + string_num * sizeof(uint32_t));
		uint32_t string_end_offset = n64rom_get_u32(rom, section_pos + (string_num + 1) * sizeof(uint32_t));
		
		if(string_offset == 0)
		{
			break;
		}
		
		pm_dlg_output("dlg_%02X_%04X:\r\n", section_num, string_num);
		
		int string_pos = bank_pos + string_offset;
		
		n64rom_stream_set_pos(rom, string_pos);
		
		pm_dlg_decode_sequence(rom);
		
		pm_dlg_output("\r\n\r\n");
		
		if(string_end_offset == section_offset)
		{
			section_end_pos =  section_pos + (string_num + 2) * sizeof(uint32_t);
			break;
		}
		
		string_num++;
	}
	
	// Output string offset list
	
	pm_dlg_output(".align 4\r\n\r\n");
	pm_dlg_output("dlg_%02X:\r\n", section_num);
	
	for(int i = 0;; i++)
	{
		uint32_t string_offset = n64rom_get_u32(rom, section_pos + i * sizeof(uint32_t));
		uint32_t string_end_offset = n64rom_get_u32(rom, section_pos + (i + 1) * sizeof(uint32_t));
		
		if(i % 8 == 0)
		{
			pm_dlg_output(".dw ");
		}
		
		pm_dlg_output("dlg_%02X_%04X", section_num, i);
		
		if((i+1)%8 == 0)
		{
			pm_dlg_output("\r\n");
		}
		else
		{
			pm_dlg_output(", ");
		}
		
		if(string_end_offset == section_offset)
		{
			if((i+1) % 8 == 0 && i > 0)
			{
				pm_dlg_output(".dw ");
			}
			pm_dlg_output("dlg_%02X", section_num);
			break;
		}
	}
	
	pm_dlg_output("\r\n\r\n");
	pm_dlg_output("end_dlg_section\r\n");
	
	pm_dlg_close_output();
	
	return section_end_pos;
}

void pm_decode_dialog(n64rom_t* rom)
{
	int bank_pos;
	
	char country_code = n64rom_get_country_code(rom);
	
	switch(country_code)
	{
		case 'J':
			bank_pos = 0x01D40000;
			break;
		case 'P':
			bank_pos = 0x021B0000;
			// 02030000 en
			// 021B0000 de
			// 02330000 fr
			// 024B0000 es
			break;
		default:
		case 'E':
			bank_pos = 0x01B83000;
			break;
	}
	
	// Decode all sections
	
	int section_num = 0;
	int bank_end_pos = 0;
	
	while(1)
	{
		int end_pos = pm_dlg_decode_section(rom, bank_pos, section_num);
		
		if(end_pos == 0)
		{
			break;
		}
		
		bank_end_pos = end_pos;
		section_num++;
	}
	
	int bank_size = bank_end_pos - bank_pos;
	
	// Output main file
	
	pm_dlg_open_output("pm_dialog.asm");
	
	pm_dlg_output_auto_msg();
	
	pm_dlg_output(".include \"pm_dialog_header.asm\"\r\n\r\n");
	
	pm_dlg_output(".definelabel DIALOG_BANK_POS,  0x%08X\r\n", bank_pos);
	pm_dlg_output(".definelabel DIALOG_BANK_SIZE, 0x%08X\r\n\r\n", bank_size);
	
	pm_dlg_output(".orga DIALOG_BANK_POS\r\n");
	pm_dlg_output(".headersize -DIALOG_BANK_POS\r\n", bank_pos);
	pm_dlg_output(".area DIALOG_BANK_SIZE, 0\r\n\r\n", bank_size);
	
	// Output labels
	// These point to each section's sequence offset list
	
	for(int i = 0;; i++)
	{
		int section_offset = n64rom_get_u32(rom, bank_pos + i*4);
		
		if(i % 8 == 0)
		{
			pm_dlg_output(".dw ");
		}
		else
		{
			pm_dlg_output(", ");
		}
		
		if(section_offset == 0)
		{
			pm_dlg_output("0\r\n");
			break;
		}
		else
		{
			pm_dlg_output("dlg_%02X", i);
		}
		
		if((i+1)%8 == 0)
		{
			pm_dlg_output("\r\n");
		}
		
	}
	pm_dlg_output("\r\n");
	
	for(int i = 0;; i++)
	{
		int section_offset = n64rom_get_u32(rom, bank_pos + i*4);
		
		if(section_offset == 0)
		{
			break;
		}
		
		pm_dlg_output(".include \"pm_dialog/dlg_%02X.asm\"\r\n", i);
	}
	pm_dlg_output("\r\n");
	
	pm_dlg_output(".endarea\r\n");
	
	pm_dlg_close_output();
}

// print to files

static FILE* pm_dlg_output_file;

void pm_dlg_open_output(const char* path)
{
	pm_dlg_output_file = fopen(path, "wb");
}

void pm_dlg_close_output()
{
	fclose(pm_dlg_output_file);
}

void pm_dlg_output(const char* format, ...)
{
	va_list vl;
	va_start(vl, format);
	vfprintf(pm_dlg_output_file, format, vl);
	va_end(vl);
}

void pm_dlg_output_auto_msg()
{
	pm_dlg_output(
		"; Paper Mario Dialog Disassembly v0.1\r\n"
		"; Generated with pmdlg (https://github.com/shygoo/pmdlg)\r\n"
		"; Compatible with armips (https://github.com/Kingcom/armips)\r\n\r\n"
	);
}

void pm_dlg_make_asm_dir()
{
	#ifdef _WIN32
	mkdir("pm_dialog");
	#else
	mkdir("pm_dialog", 0777);
	#endif
}

int main(int argc, const char* argv[])
{
	if(argc < 3)
	{
		printf("Usage: pmgld <rom_path> <out_dir>\n");
		exit(EXIT_FAILURE);
	}
	
	const char* rom_path = argv[1];
	const char* out_dir = argv[2];
	
	n64rom_t* rom = n64rom_create(rom_path);
	
	chdir(out_dir);
	mkdir("pm_dialog");
	
	pm_decode_dialog(rom);
	
	n64rom_destroy(rom);
}
