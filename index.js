const fs = require('fs');
const elf_tools = require('elf-tools');

const header: ELFHeader = {
    elfsig: <Buffer 7f 45 4c 46>,
    class: '64',
    endian: 'lsb',
    osabi: 'unix-sysv',
    abiversion: 'none',
    type: 'exec',
    machine: 'amd64',
    version: 1,
    entry: 4198400,
    phoff: 64,
    shoff: 8688,
    flags: 0,
    ehsize: 64,
    phentsize: 56,
    phnum: 3,
    shentsize: 64,
    shnum: 7,
    shstrndx: 6,
    padding: <Buffer 00 00 00 00 00 00 00 00>
 }

console.log(process.argc);
console.log(process.argv);

if (process.argc <= 2) {
	return -1;
}

const elf_path = process.argv[2];
const file = fs.readFileSync(elf_path);
const elf = elf_tools.parse(file);


console.log(elf);
