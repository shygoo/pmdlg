; Paper Mario Dialog Disassembly Header v0.4
; Compatible with armips (https://github.com/Kingcom/armips)

; CONFIG_SHRINK:
;  Set to 0 to use original boundary padding
;  Set to 1 to use minimized boundary padding (recommended)
.definelabel CONFIG_SHRINK, 1

; Load character encoding

.table "pm_dialog_encoding.tbl"

; Special characters

.definelabel CHR_MUSIC_NOTE,            0x00
.definelabel CHR_HEART,                 0x90
.definelabel CHR_STAR,                  0x91
.definelabel CHR_UP_ARROW,              0x92
.definelabel CHR_DN_ARROW,              0x93
.definelabel CHR_LT_ARROW,              0x94
.definelabel CHR_RT_ARROW,              0x95
.definelabel CHR_O_NOUGHT,              0x96
.definelabel CHR_X_CROSS,               0x97
.definelabel CHR_A_BUTTON,              0x98
.definelabel CHR_B_BUTTON,              0x99
.definelabel CHR_L_BUTTON,              0x9A
.definelabel CHR_R_BUTTON,              0x9B
.definelabel CHR_Z_BUTTON,              0x9C
.definelabel CHR_C_UP_BUTTON,           0x9D
.definelabel CHR_C_DN_BUTTON,           0x9E
.definelabel CHR_C_LT_BUTTON,           0x9F
.definelabel CHR_C_RT_BUTTON,           0xA0
.definelabel CHR_START_BUTTON,          0xA1
.definelabel CHR_NULL_0,                0xA2
.definelabel CHR_NULL_1,                0xA3
.definelabel CHR_NULL_2,                0xA4
.definelabel CHR_NULL_3,                0xA5
.definelabel CHR_NULL_4,                0xA6
.definelabel CHR_TAB_16,                0xA8
.definelabel CHR_TAB_6,                 0xA9
.definelabel CHR_LINE_BREAK,            0xF0
.definelabel CHR_BELL,                  0xF1
.definelabel CHR_DELAY,                 0xF2
.definelabel CHR_UNK_F3,                0xF3
.definelabel CHR_NEXT_BUBBLE,           0xFB
.definelabel CHR_STYLE,                 0xFC
.definelabel CHR_END,                   0xFD
.definelabel CHR_CMD,                   0xFF

; DLG_CMD argument

.definelabel CMD_UNK_00,                0x00
.definelabel CMD_UNK_04,                0x04
.definelabel CMD_TEXT_COLOR,            0x05
.definelabel CMD_UNK_07,                0x07
.definelabel CMD_UNK_08,                0x08
.definelabel CMD_PRINT_INSTANT,         0x09
.definelabel CMD_CANCEL_WRITING,        0x0A
.definelabel CMD_FONT_KERNING,          0x0B
.definelabel CMD_AUTO_SCROLL,           0x0C
.definelabel CMD_FONT_SIZE,             0x0D
.definelabel CMD_FONT_SIZE_RESET,       0x0E
.definelabel CMD_PRINT_SPEED,           0x0F
.definelabel CMD_MARGIN,                0x10
.definelabel CMD_UNK_11,                0x11
.definelabel CMD_UNK_12,                0x12
.definelabel CMD_UNK_13,                0x13
.definelabel CMD_UNK_14,                0x14
.definelabel CMD_GRAPHIC_A,             0x15
.definelabel CMD_ICON,                  0x17
.definelabel CMD_GRAPHIC_B,             0x18
.definelabel CMD_UNK_1A,                0x1A
.definelabel CMD_UNK_1B,                0x1B
.definelabel CMD_UNK_1E,                0x1E
.definelabel CMD_UNK_1F,                0x1F
.definelabel CMD_UNK_20,                0x20
.definelabel CMD_UNK_21,                0x21
.definelabel CMD_UNK_22,                0x22
.definelabel CMD_UNK_23,                0x23
.definelabel CMD_SAVE_TEXT_COLOR,       0x24
.definelabel CMD_LOAD_TEXT_COLOR,       0x25
.definelabel CMD_START_EFFECT,          0x26
.definelabel CMD_CANCEL_EFFECT,         0x27
.definelabel CMD_UNK_28,                0x28
.definelabel CMD_UNK_29,                0x29
.definelabel CMD_UNK_2B,                0x2B
.definelabel CMD_VOLUME,                0x2E
.definelabel CMD_VOICE,                 0x2F

; DLG_STYLE argument

.definelabel STYLE_INVALID,             0x00
.definelabel STYLE_BUBBLE_RIGHT,        0x01
.definelabel STYLE_BUBBLE_LEFT,         0x02
.definelabel STYLE_BUBBLE_A,            0x03
.definelabel STYLE_BUBBLE_B,            0x04
.definelabel STYLE_WHITE_BORDER,        0x05
.definelabel STYLE_NARRATION_A,         0x06
.definelabel STYLE_SIGN_POST,           0x07
.definelabel STYLE_BLUE_MESSAGE,        0x08
.definelabel STYLE_INVALID_2,           0x09
.definelabel STYLE_WHITE_BUBBLE,        0x0A
.definelabel STYLE_WHITE_BUBBLE_B,      0x0B
.definelabel STYLE_NO_DISPLAY,          0x0C
.definelabel STYLE_NARRATION_SILENT,    0x0D
.definelabel STYLE_NO_DISPLAY_V_CENTER, 0x0E
.definelabel STYLE_NARRATION_B,         0x0F

; DLG_CALL CMD_START/CANCEL_EFFECT argument

.definelabel EFFECT_JITTER,             0x00
.definelabel EFFECT_WAVE,               0x01
.definelabel EFFECT_DARK_STATIC,        0x02
.definelabel EFFECT_LIGHT_STATIC,       0x03
.definelabel EFFECT_UNKNOWN,            0x04
.definelabel EFFECT_GHOST_JITTER,       0x05
.definelabel EFFECT_CHASING_RAINBOW_A,  0x06
.definelabel EFFECT_GRAYED_OUT,         0x07
.definelabel EFFECT_WAVE_B,             0x08
.definelabel EFFECT_CHASING_RAINBOW_B,  0x09
.definelabel EFFECT_SHRINK_PLACEMENT,   0x0A
.definelabel EFFECT_GROWTH_PLACEMENT,   0x0B
.definelabel EFFECT_SIZE_JITTER,        0x0C
.definelabel EFFECT_SIZE_WAVE,          0x0D
.definelabel EFFECT_DROP_SHADOW,        0x0E

; Termination & boundary padding

.macro end_dlg_seq
	.db CHR_END
	.if (CONFIG_SHRINK == 0)
		.align 4
	.else
		.align 2
	.endif
.endmacro

.macro end_dlg_section
	.if (CONFIG_SHRINK == 0)
		.align 16
	.else
		.align 2
	.endif
.endmacro
