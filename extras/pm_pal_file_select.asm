; Paper Mario (PAL) file menu text disassembly
; Compatible with armips (https://github.com/Kingcom/armips)

.definelabel FM_ROM_ADDR, 0x0016F4D0
.definelabel FM_RAM_ADDR, 0x80246AB0
.headersize (FM_RAM_ADDR - FM_ROM_ADDR)

.org 0x8024E864
lui  at, hi(fm_str_banks)
addu at, at, v0
lw   v0, lo(fm_str_banks) (at)

.org 0x8024F100
.dw fm_keyboard

.org 0x8025096C
.area 0x89C, 0

fm_00:
.strn "?"
end_dlg_seq

fm_01:
.strn "Select file to start:"
end_dlg_seq

fm_02:
.strn "Wähle eine Datei:"
end_dlg_seq

fm_03:
.strn "Choisir fichier:"
end_dlg_seq

fm_04:
.strn "Elige fichero:"
end_dlg_seq

fm_05:
.strn "Select file to delete:"
end_dlg_seq

fm_06:
.strn "Wähle zu löschende Datei:"
end_dlg_seq

fm_07:
.strn "Choisir fichier à effacer:"
end_dlg_seq

fm_08:
.strn "Elige el fichero a borrar:"
end_dlg_seq

fm_09:
.strn "Copy which file?"
end_dlg_seq

fm_0A:
.strn "Welche Datei kopieren?"
end_dlg_seq

fm_0B:
.strn "Fichier source?"
end_dlg_seq

fm_0C:
.strn "¿Qué fichero copias?"
end_dlg_seq

fm_0D:
.strn "Copy to which file?"
end_dlg_seq

fm_0E:
.strn "In welche Datei kopieren?"
end_dlg_seq

fm_0F:
.strn "Fichier destination?"
end_dlg_seq

fm_10:
.strn "¿Dónde lo copias?"
end_dlg_seq

fm_11:
.strn "NEW"
end_dlg_seq

fm_12:
.strn "Neu"
end_dlg_seq

fm_13:
.strn "Nouveau"
end_dlg_seq

fm_14:
.strn "Nuevo"
end_dlg_seq

fm_15:
.strn "Level"
end_dlg_seq

fm_16:
.strn "Niveau"
end_dlg_seq

fm_17:
.strn "Nivel"
end_dlg_seq

fm_18:
.strn "Play Time"
end_dlg_seq

fm_19:
.strn "Spielzeit"
end_dlg_seq

fm_1A:
.strn "Temps"
end_dlg_seq

fm_1B:
.strn "Tiempo"
end_dlg_seq

fm_1C:
.strn "Delete File"
end_dlg_seq

fm_1D:
.strn "Löschen"
end_dlg_seq

fm_1E:
.strn "Effacer"
end_dlg_seq

fm_1F:
.strn "Borrar"
end_dlg_seq

fm_20:
.strn "Cancel"
end_dlg_seq

fm_21:
.strn "Abbrechen"
end_dlg_seq

fm_22:
.strn "Annuler"
end_dlg_seq

fm_23:
.strn "Salir"
end_dlg_seq

fm_24:
.strn "Copy File"
end_dlg_seq

fm_25:
.strn "Kopieren"
end_dlg_seq

fm_26:
.strn "Copier"
end_dlg_seq

fm_27:
.strn "Copiar"
end_dlg_seq

fm_28:
.strn "First Play"
end_dlg_seq

fm_29:
.strn "Neues Spiel"
end_dlg_seq

fm_2A:
.strn "Première partie"
end_dlg_seq

fm_2B:
.strn "Primera Vez"
end_dlg_seq

fm_2C:
.strn "."
end_dlg_seq

fm_2D:
.strn "Yes"
end_dlg_seq

fm_2E:
.strn "Ja"
end_dlg_seq

fm_2F:
.strn "Oui"
end_dlg_seq

fm_30:
.strn "Sí"
end_dlg_seq

fm_31:
.strn "No"
end_dlg_seq

fm_32:
.strn "Nein"
end_dlg_seq

fm_33:
.strn "Non"
end_dlg_seq

fm_34:
.strn "No"
end_dlg_seq

fm_35:
.strn "Delete"
end_dlg_seq

fm_36:
.strn "löschen"
end_dlg_seq

fm_37:
.strn "Effacer"
end_dlg_seq

fm_38:
.strn "¿Borro el"
end_dlg_seq

fm_39:
.strn "File name is :"
end_dlg_seq

fm_3A:
.strn "Der Name lautet :"
end_dlg_seq

fm_3B:
.strn "Nom du fichier :"
end_dlg_seq

fm_3C:
.strn "Nombre del fichero :"
end_dlg_seq

fm_3D:
.strn "OK?"
end_dlg_seq

fm_3E:
.strn "¿Vale?"
end_dlg_seq

fm_3F:
.strn "File"
end_dlg_seq

fm_40:
.strn "Datei"
end_dlg_seq

fm_41:
.strn "Fichier"
end_dlg_seq

fm_42:
.strn "Fichero"
end_dlg_seq

fm_43:
.strn "Dat."
end_dlg_seq

fm_44:
.strn "Fich."
end_dlg_seq

fm_45:
.strn "will be deleted."
end_dlg_seq

fm_46:
.strn "wird gelöscht."
end_dlg_seq

fm_47:
.strn "sera effacé."
end_dlg_seq

fm_48:
.strn "será borrado."
end_dlg_seq

fm_49:
.strn "OK to copy to this file?"
end_dlg_seq

fm_4A:
.strn "Soll auf diese Datei kopiert werden?"
end_dlg_seq

fm_4B:
.strn "Confirmer la copie?"
end_dlg_seq

fm_4C:
.strn "¿Quieres copiarlo aquí ?"
end_dlg_seq

fm_4D:
.strn "Start game with"
end_dlg_seq

fm_4E:
.strn "Spiel mit"
end_dlg_seq

fm_4F:
.strn "Commencer une partie avec le"
end_dlg_seq

fm_50:
.strn "¿Quieres este fichero?"
end_dlg_seq

fm_51:
.strn "beginnen?"
end_dlg_seq

fm_52:
.strn "has been deleted."
end_dlg_seq

fm_53:
.strn "wurde gelöscht."
end_dlg_seq

fm_54:
.strn "a été effacé."
end_dlg_seq

fm_55:
.strn "ha sido borrado."
end_dlg_seq

fm_56:
end_dlg_seq

fm_57:
.strn "Le"
end_dlg_seq

fm_58:
.strn "El"
end_dlg_seq

fm_59:
.strn "Copy from"
end_dlg_seq

fm_5A:
.strn "Von"
end_dlg_seq

fm_5B:
.strn "Copier du"
end_dlg_seq

fm_5C:
.strn "Copia del"
end_dlg_seq

fm_5D:
.strn "to"
end_dlg_seq

fm_5E:
.strn "nach"
end_dlg_seq

fm_5F:
.strn "au"
end_dlg_seq

fm_60:
.strn "al"
end_dlg_seq

fm_61:
.strn "kopieren."
end_dlg_seq

fm_62:
.strn "has been created."
end_dlg_seq

fm_63:
.strn "wurde erstellt."
end_dlg_seq

fm_64:
.strn "a été créé."
end_dlg_seq

fm_65:
.strn "ha sido creado."
end_dlg_seq

fm_66:
.strn "Enter a file name!"
end_dlg_seq

fm_67:
.strn "Gib einen Namen ein!"
end_dlg_seq

fm_68:
.strn "Entrer le nom du Fichier!"
end_dlg_seq

fm_69:
.strn "¡Introduce nombre!"
end_dlg_seq

fm_6A:
.strn "1"
end_dlg_seq

fm_6B:
.strn "2"
end_dlg_seq

fm_6C:
.strn "3"
end_dlg_seq

fm_6D:
.strn "4"
end_dlg_seq

.align 4

fm_keyboard:
.strn "ABCDEFGHIJKLM"
.strn "NOPQRSTUVWXYZ"
.strn "abcdefghijklm"
.strn "nopqrstuvwxyz"
.strn "ÁÉÍÑÓÚßàáâäçè"
.strn "éêëíîñóôöùúûü"
.strn "1234567890.- "
.strn CHR_MUSIC_NOTE, CHR_HEART, CHR_STAR, "@   "
.strn 0xC9, "  " // Backspace
.strn 0xCA, "  " // END

.align 4

fm_bank_en:
.dw 0, fm_01, fm_05, fm_09, fm_0D, fm_11, fm_15, fm_18, fm_1C, fm_20, fm_24, fm_28, fm_2C, fm_2D, fm_31, fm_35, fm_39, fm_2C, fm_3D, fm_3F, fm_3F, fm_45, fm_49, fm_4D, fm_00, fm_3F, fm_52, fm_56, fm_59, fm_5D, fm_2C, fm_62, fm_56, fm_66, fm_00, fm_2C, fm_6A, fm_6B, fm_6C, fm_6D

fm_bank_de:
.dw 0, fm_02, fm_06, fm_0A, fm_0E, fm_12, fm_15, fm_19, fm_1D, fm_21, fm_25, fm_29, fm_2C, fm_2E, fm_32, fm_36, fm_3A, fm_2C, fm_3D, fm_40, fm_43, fm_46, fm_4A, fm_4E, fm_51, fm_40, fm_53, fm_56, fm_5A, fm_5E, fm_61, fm_63, fm_56, fm_67, fm_00, fm_2C, fm_6A, fm_6B, fm_6C, fm_6D

fm_bank_fr:
.dw 0, fm_03, fm_07, fm_0B, fm_0F, fm_13, fm_16, fm_1A, fm_1E, fm_22, fm_26, fm_2A, fm_2C, fm_2F, fm_33, fm_37, fm_3B, fm_2C, fm_3D, fm_41, fm_44, fm_47, fm_4B, fm_4F, fm_00, fm_41, fm_54, fm_57, fm_5B, fm_5F, fm_2C, fm_64, fm_56, fm_68, fm_00, fm_2C, fm_6A, fm_6B, fm_6C, fm_6D

fm_bank_es:
.dw 0, fm_04, fm_08, fm_0C, fm_10, fm_14, fm_17, fm_1B, fm_1F, fm_23, fm_27, fm_2B, fm_2C, fm_30, fm_34, fm_38, fm_3C, fm_2C, fm_3E, fm_42, fm_44, fm_48, fm_4C, fm_50, fm_00, fm_42, fm_55, fm_58, fm_5C, fm_60, fm_2C, fm_65, fm_58, fm_69, fm_00, fm_2C, fm_6A, fm_6B, fm_6C, fm_6D

fm_str_banks:
.dw fm_bank_en, fm_bank_de, fm_bank_fr, fm_bank_es

.endarea