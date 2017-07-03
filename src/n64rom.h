/*

	n64rom.h
	
	Basic N64 ROM data interface
	
	shygoo 2017
	
	License: MIT
	
*/

#ifndef N64ROM_H
#define N64ROM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef bswap32
	#ifdef __GNUC__
		#define bswap32 __builtin_bswap32
	#elif _MSC_VER
		#define bswap32 _byteswap_ulong
	#else
		#define bswap32(n) (((unsigned)n & 0xFF000000) >> 24 | (n & 0xFF00) << 8 | (n & 0xFF0000) >> 8 | n << 24)
	#endif
#endif

#ifndef bswap16
	#ifdef __GNUC__
		#define bswap16 __builtin_bswap16
	#elif _MSC_VER
		#define bswap16 _byteswap_ushort
	#else
		#define bswap16(n) (((unsigned)n & 0xFF00) >> 8 | n << 8)
	#endif
#endif

#define N64ROM_POS_STACK_SIZE 16

#define N64ROM_OFFSET_COUNTRY_CODE 0x3E
#define N64ROM_OFFSET_VERSION      0x3F
#define N64ROM_OFFSET_NAME         0x20

#define N64ROM_NAME_SIZE   20
#define N64ROM_NAME_SIZE_Z 21

typedef struct {
	uint8_t* data;
	uint32_t size;
	uint32_t pos;
	char name[N64ROM_NAME_SIZE_Z];
} n64rom_t;

n64rom_t* n64rom_create    (const char* path);
void      n64rom_destroy   (n64rom_t* rom);

void      n64rom_fix_order (n64rom_t* rom);

uint8_t   n64rom_get_u8    (n64rom_t* rom, uint32_t pos);
uint32_t  n64rom_get_u16   (n64rom_t* rom, uint32_t pos);
uint32_t  n64rom_get_u32   (n64rom_t* rom, uint32_t pos);

void      n64rom_stream_set_pos   (n64rom_t* rom, uint32_t pos);
uint32_t  n64rom_stream_get_pos   (n64rom_t* rom);

uint8_t   n64rom_stream_read_u8   (n64rom_t* rom);
uint16_t  n64rom_stream_read_u16  (n64rom_t* rom);
uint32_t  n64rom_stream_read_u32  (n64rom_t* rom);

char*     n64rom_get_name(n64rom_t* rom);
char      n64rom_get_country_code (n64rom_t* rom);
uint8_t   n64rom_get_version (n64rom_t* rom);


n64rom_t* n64rom_create(const char* path)
{
	n64rom_t* rom = (n64rom_t*) malloc(sizeof(n64rom_t));
	
	FILE* pfile = fopen(path, "rb");
	
	fseek(pfile, 0, SEEK_END);
	
	rom->size = ftell(pfile);
	rewind(pfile);
	
	rom->data = malloc(rom->size);
	fread(rom->data, rom->size, 1, pfile);
	
	rom->pos = 0;
	
	fclose(pfile);
	
	n64rom_fix_order(rom);
	
	return rom;
}

void n64rom_destroy(n64rom_t* rom)
{
	free(rom->data);
	free(rom);
}

// Make big endian
void n64rom_fix_order(n64rom_t* rom)
{
	if(rom->data[0] != 0x80)
	{
		if(rom->data[1] == 0x80)
		{
			// Middle endian
			for(int i = 0; i < rom->size; i += sizeof(uint16_t))
			{
				*(uint16_t*)&rom->data[i] = bswap16(*(uint16_t*)&rom->data[i]);
			}
		}
		else if(rom->data[3] == 0x80)
		{
			// Little endian
			for(int i = 0; i < rom->size; i += sizeof(uint32_t))
			{
				*(uint32_t*)&rom->data[i] = bswap32(*(uint32_t*)&rom->data[i]);
			}
		}
	}
}

uint8_t n64rom_get_u8(n64rom_t* rom, uint32_t pos)
{
	return rom->data[pos];
}

uint32_t n64rom_get_u16(n64rom_t* rom, uint32_t pos)
{
	return bswap16(*(uint16_t*)&rom->data[pos]);
}

uint32_t n64rom_get_u32(n64rom_t* rom, uint32_t pos)
{
	return bswap32(*(uint32_t*)&rom->data[pos]);
}

// for stream-like reading

void n64rom_stream_set_pos(n64rom_t* rom, uint32_t pos)
{
	rom->pos = pos;
}

uint32_t n64rom_stream_get_pos(n64rom_t* rom)
{
	return rom->pos;
}

uint8_t n64rom_stream_read_u8(n64rom_t* rom)
{
	uint8_t value = n64rom_get_u8(rom, rom->pos);
	rom->pos += sizeof(uint8_t);
	return value;
}

uint16_t n64rom_stream_read_u16(n64rom_t* rom)
{
	uint16_t value = n64rom_get_u16(rom, rom->pos);
	rom->pos += sizeof(uint16_t);
	return value;
}

uint32_t n64rom_stream_read_u32(n64rom_t* rom)
{
	uint32_t value = n64rom_get_u32(rom, rom->pos);
	rom->pos += sizeof(uint32_t);
	return value;
}

// header values

char* n64rom_get_name(n64rom_t* rom)
{
	for(int i = 0; i < N64ROM_NAME_SIZE; i++)
	{
		rom->name[i] = n64rom_get_u8(rom, N64ROM_OFFSET_NAME + i);
	}
	
	rom->name[N64ROM_NAME_SIZE] = '\0';
}

char n64rom_get_country_code(n64rom_t* rom)
{
	return n64rom_get_u8(rom, N64ROM_OFFSET_COUNTRY_CODE);
}

uint8_t n64rom_get_version(n64rom_t* rom)
{
	return n64rom_get_u32(rom, N64ROM_OFFSET_VERSION);
}

#endif // N64ROM_H