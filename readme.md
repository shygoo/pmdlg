# Paper Mario Dialog
Utilities for editing Paper Mario's dialog

## Building

### Build pmdlg:
	make pmdlg
- Builds the dialog bank disassembler utility.
	
### Generate fresh dialog disassembly:
	make newpatch
- Generates an `armips`-compatible disassembly of the dialog bank to the `patch` directory using `pmdlg`.
- Requires a `Paper_Mario_(U)_[!].z64` in the `roms` directory.

### Generate patched ROM:
	make rom
- Reassembles ASM files in the `patch` directory onto `roms/Paper_Mario_(U)_[!].z64`
- Outputs to `roms/Paper_Mario_(U)_[!].mod.z64`
- Requires `armips`