CC=gcc
CFLAGS=-static -O3 -s

pmdlg: src/pmdlg.c src/pmdlg.h src/n64rom.h
	$(CC) $(CFLAGS) src/pmdlg.c -o $@

##########
# make newpatch
#  Runs pmdlg to disassemble dialog bank(s) from Paper Mario ROM
#  "roms/Paper_Mario_(U)_[!].z64" required

ROM_IN=roms/Paper_Mario_(U)_[!].z64
PATCH_SRC_DIR=patch_src
PATCH_DIR=patch
PATCH=$(PATCH_DIR)/pm_dialog.asm
PATCH_HEADER_FILE=pm_dialog_header.asm
PATCH_ENCODE_FILE=pm_dialog_encoding.tbl
PATCH_SRC_HEADER=$(PATCH_SRC_DIR)/$(PATCH_HEADER_FILE)
PATCH_SRC_ENCODE=$(PATCH_SRC_DIR)/$(PATCH_ENCODE_FILE)
PATCH_HEADER=$(PATCH_DIR)/$(PATCH_HEADER_FILE)
PATCH_ENCODE=$(PATCH_DIR)/$(PATCH_ENCODE_FILE)

# Generated ASM
PATCH_DISASM_MAIN=$(PATCH_DIR)/pm_dialog.asm
PATCH_DISASM_INCS=$(PATCH_DIR)/pm_dialog/*.*

# Handwritten ASM header and character table
PATCH_INCS=$(PATCH_HEADER) $(PATCH_ENCODE)

# All patch files
PATCH=$(PATCH_DISASM_MAIN) $(PATCH_DISASM_INCS) $(PATCH_INCS)

.PHONY: newpatch
newpatch: $(PATCH)

$(PATCH_DISASM_MAIN): pmdlg $(ROM_IN) | $(PATCH_DIR)
	./pmdlg "$(ROM_IN)" $(PATCH_DIR)
	
$(PATCH_DISASM_INCS):
# assume we have it

$(PATCH_HEADER): $(PATCH_SRC_HEADER) | $(PATCH_DIR)
	cp -p $(PATCH_SRC_HEADER) $(PATCH_HEADER)
	
$(PATCH_ENCODE): $(PATCH_SRC_ENCODE) | $(PATCH_DIR)
	cp -p $(PATCH_SRC_ENCODE) $(PATCH_ENCODE)
	
$(PATCH_DIR):
	mkdir $@
	
##########
# make rom
#  Generates a modified ROM with armips
#  "roms/Paper_Mario_(U)_[!].z64" required

N64_WRAP=armips_n64_wrapper.asm
ROM_OUT=roms/Paper_Mario_(U)_[!].mod.z64

.PHONY: rom
rom: $(ROM_OUT)

$(ROM_OUT): $(N64_WRAP) $(ROM_IN) $(PATCH) | $(PATCH_DIR)
	armips ../$(N64_WRAP) -root $(PATCH_DIR)
	
$(N64_WRAP):
	echo ".n64" > $(N64_WRAP)
	echo ".open \"../$(ROM_IN)\", \"../$(ROM_OUT)\", 0" >> $(N64_WRAP)
	echo ".include \"../$(PATCH_DISASM_MAIN)\"" >> $(N64_WRAP)
	echo ".close" >> $(N64_WRAP)
	
##########
	
.PHONY: clean clean_patch

clean_patch:
	rm -rf $(PATCH_DIR)

clean: clean_patch
	rm -f  pmdlg
	rm -f  $(N64_WRAP)
	rm -f  "$(ROM_OUT)"
