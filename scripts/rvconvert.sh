#!/bin/bash
if (($# < 2))
then
	eval /pkgs/riscv-gnu-toolchain/riscv-gnu-toolchain/bin/riscv64-unknown-linux-gnu-objdump -d $1 | grep -o '^[[:blank:]]*[[:xdigit:]]*:[[:blank:]][[:xdigit:]]*' > prog.mem
else
	eval /pkgs/riscv-gnu-toolchain/riscv-gnu-toolchain/bin/riscv64-unknown-linux-gnu-objdump -d $1 | grep -o '^[[:blank:]]*[[:xdigit:]]*:[[:blank:]][[:xdigit:]]*' > $2
fi

