#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: make it work
static int parity(int value, int size) {
  int i;
  int parity = 0;
  value = (value & ((1 << size) - 1));
  for (i = 0; i < size; i++) {
    if (value & 0x1) parity++;
    value = value >> 1;
  }
  return (0 == (parity & 0x1));
}

typedef struct condition_codes {
  uint8_t z : 1;   // Zero
  uint8_t s : 1;   // Sign
  uint8_t p : 1;   // Parity
  uint8_t cy : 1;  // Carry
  uint8_t ac : 1;  // Half Carry
  uint8_t pad : 3;
} condition_codes;

typedef struct state_8080 {
  uint8_t a;
  uint8_t b;
  uint8_t c;
  uint8_t d;
  uint8_t e;
  uint8_t h;
  uint8_t l;
  uint16_t sp;  // Stack Pointer
  uint16_t pc;  // Program Counter
  uint8_t *memory;
  struct condition_codes cc;
  uint8_t int_enable;
} state_8080;

// Returns the number of bytes of op
int dissasemble_8080_op(unsigned char *code_buffer, int pc) {
  unsigned char *code = &code_buffer[pc];
  int op_bytes = 1;
  printf("0x%02x\n", *code);
  printf("%04x ", pc);

  switch (*code) {
    case 0x00:
      printf("NOP");
      op_bytes = 1;
      break;
    case 0x01:
      printf("LXI B, #$%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x02:
      printf("STAX B");
      op_bytes = 1;
      break;
    case 0x03:
      printf("INX B");
      op_bytes = 1;
      break;
    case 0x04:
      printf("INR B");
      op_bytes = 1;
      break;
    case 0x05:
      printf("DCR B");
      op_bytes = 1;
      break;
    case 0x06:
      printf("MVI B, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x07:
      printf("RLC");
      op_bytes = 1;
      break;
    case 0x08:
      printf("-");
      op_bytes = 0;
      break;
    case 0x09:
      printf("DAD B");
      op_bytes = 1;
      break;
    case 0x0a:
      printf("LDAX B");
      op_bytes = 1;
      break;
    case 0x0b:
      printf("DCX B");
      op_bytes = 1;
      break;
    case 0x0c:
      printf("INR C");
      op_bytes = 1;
      break;
    case 0x0d:
      printf("DCR C");
      op_bytes = 1;
      break;
    case 0x0e:
      printf("MVI C, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x0f:
      printf("RRC");
      op_bytes = 1;
      break;
    case 0x10:
      printf("-");
      op_bytes = 0;
      break;
    case 0x11:
      printf("LXI D, #$%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x12:
      printf("STAX D");
      op_bytes = 1;
      break;
    case 0x13:
      printf("INX D");
      op_bytes = 1;
      break;
    case 0x14:
      printf("INR D");
      op_bytes = 1;
      break;
    case 0x15:
      printf("DCR D");
      op_bytes = 1;
      break;
    case 0x16:
      printf("MVI D, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x17:
      printf("RAL");
      op_bytes = 1;
      break;
    case 0x18:
      printf("-");
      op_bytes = 0;
      break;
    case 0x19:
      printf("DAD D");
      op_bytes = 1;
      break;
    case 0x1a:
      printf("LDAX D");
      op_bytes = 1;
      break;
    case 0x1b:
      printf("DCX D");
      op_bytes = 1;
      break;
    case 0x1c:
      printf("INR E");
      op_bytes = 1;
      break;
    case 0x1d:
      printf("DCR E");
      op_bytes = 1;
      break;
    case 0x1e:
      printf("MVI E, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x1f:
      printf("RAR");
      op_bytes = 1;
      break;
    case 0x20:
      printf("RIM");
      op_bytes = 1;
      break;
    case 0x21:
      printf("LXI H, #$%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x22:
      printf("SHLD $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x23:
      printf("INX H");
      op_bytes = 1;
      break;
    case 0x24:
      printf("INR H");
      op_bytes = 1;
      break;
    case 0x25:
      printf("DCR H");
      op_bytes = 1;
      break;
    case 0x26:
      printf("MVI H, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x27:
      printf("DAA");
      op_bytes = 1;
      break;
    case 0x28:
      printf("-");
      op_bytes = 0;
      break;
    case 0x29:
      printf("DAD H");
      op_bytes = 1;
      break;
    case 0x2a:
      printf("LHLD $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x2b:
      printf("DCX H");
      op_bytes = 1;
      break;
    case 0x2c:
      printf("INR L");
      op_bytes = 1;
      break;
    case 0x2d:
      printf("DCR L");
      op_bytes = 1;
      break;
    case 0x2e:
      printf("MVI L, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x2f:
      printf("CMA");
      op_bytes = 1;
      break;
    case 0x30:
      printf("SIM");
      op_bytes = 1;
      break;
    case 0x31:
      printf("LXI SP,  #$%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x32:
      printf("STA $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x33:
      printf("INX SP");
      op_bytes = 1;
      break;
    case 0x34:
      printf("INR M");
      op_bytes = 1;
      break;
    case 0x35:
      printf("DCR M");
      op_bytes = 1;
      break;
    case 0x36:
      printf("MVI M, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x37:
      printf("STC");
      op_bytes = 1;
      break;
    case 0x38:
      printf("-");
      op_bytes = 0;
      break;
    case 0x39:
      printf("DAD SP");
      op_bytes = 1;
      break;
    case 0x3a:
      printf("LDA $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x3b:
      printf("DCX SP");
      op_bytes = 1;
      break;
    case 0x3c:
      printf("INR A");
      op_bytes = 1;
      break;
    case 0x3d:
      printf("DCR A");
      op_bytes = 1;
      break;
    case 0x3e:
      printf("MVI A, #0x%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x3f:
      printf("CMC");
      op_bytes = 1;
      break;
    case 0x40:
      printf("MOV B,B");
      op_bytes = 1;
      break;
    case 0x41:
      printf("MOV B,C");
      op_bytes = 1;
      break;
    case 0x42:
      printf("MOV B,D");
      op_bytes = 1;
      break;
    case 0x43:
      printf("MOV B,E");
      op_bytes = 1;
      break;
    case 0x44:
      printf("MOV B,H");
      op_bytes = 1;
      break;
    case 0x45:
      printf("MOV B,L");
      op_bytes = 1;
      break;
    case 0x46:
      printf("MOV B,M");
      op_bytes = 1;
      break;
    case 0x47:
      printf("MOV B,A");
      op_bytes = 1;
      break;
    case 0x48:
      printf("MOV C,B");
      op_bytes = 1;
      break;
    case 0x49:
      printf("MOV C,C");
      op_bytes = 1;
      break;
    case 0x4a:
      printf("MOV C,D");
      op_bytes = 1;
      break;
    case 0x4b:
      printf("MOV C,E");
      op_bytes = 1;
      break;
    case 0x4c:
      printf("MOV C,H");
      op_bytes = 1;
      break;
    case 0x4d:
      printf("MOV C,L");
      op_bytes = 1;
      break;
    case 0x4e:
      printf("MOV C,M");
      op_bytes = 1;
      break;
    case 0x4f:
      printf("MOV C,A");
      op_bytes = 1;
      break;
    case 0x50:
      printf("MOV D,B");
      op_bytes = 1;
      break;
    case 0x51:
      printf("MOV D,C");
      op_bytes = 1;
      break;
    case 0x52:
      printf("MOV D,D");
      op_bytes = 1;
      break;
    case 0x53:
      printf("MOV D,E");
      op_bytes = 1;
      break;
    case 0x54:
      printf("MOV D,H");
      op_bytes = 1;
      break;
    case 0x55:
      printf("MOV D,L");
      op_bytes = 1;
      break;
    case 0x56:
      printf("MOV D,M");
      op_bytes = 1;
      break;
    case 0x57:
      printf("MOV D,A");
      op_bytes = 1;
      break;
    case 0x58:
      printf("MOV E,B");
      op_bytes = 1;
      break;
    case 0x59:
      printf("MOV E,C");
      op_bytes = 1;
      break;
    case 0x5a:
      printf("MOV E,D");
      op_bytes = 1;
      break;
    case 0x5b:
      printf("MOV E,E");
      op_bytes = 1;
      break;
    case 0x5c:
      printf("MOV E,H");
      op_bytes = 1;
      break;
    case 0x5d:
      printf("MOV E,L");
      op_bytes = 1;
      break;
    case 0x5e:
      printf("MOV E,M");
      op_bytes = 1;
      break;
    case 0x5f:
      printf("MOV E,A");
      op_bytes = 1;
      break;
    case 0x60:
      printf("MOV H,B");
      op_bytes = 1;
      break;
    case 0x61:
      printf("MOV H,C");
      op_bytes = 1;
      break;
    case 0x62:
      printf("MOV H,D");
      op_bytes = 1;
      break;
    case 0x63:
      printf("MOV H,E");
      op_bytes = 1;
      break;
    case 0x64:
      printf("MOV H,H");
      op_bytes = 1;
      break;
    case 0x65:
      printf("MOV H,L");
      op_bytes = 1;
      break;
    case 0x66:
      printf("MOV H,M");
      op_bytes = 1;
      break;
    case 0x67:
      printf("MOV H,A");
      op_bytes = 1;
      break;
    case 0x68:
      printf("MOV L,B");
      op_bytes = 1;
      break;
    case 0x69:
      printf("MOV L,C");
      op_bytes = 1;
      break;
    case 0x6a:
      printf("MOV L,D");
      op_bytes = 1;
      break;
    case 0x6b:
      printf("MOV L,E");
      op_bytes = 1;
      break;
    case 0x6c:
      printf("MOV L,H");
      op_bytes = 1;
      break;
    case 0x6d:
      printf("MOV L,L");
      op_bytes = 1;
      break;
    case 0x6e:
      printf("MOV L,M");
      op_bytes = 1;
      break;
    case 0x6f:
      printf("MOV L,A");
      op_bytes = 1;
      break;
    case 0x70:
      printf("MOV M,B");
      op_bytes = 1;
      break;
    case 0x71:
      printf("MOV M,C");
      op_bytes = 1;
      break;
    case 0x72:
      printf("MOV M,D");
      op_bytes = 1;
      break;
    case 0x73:
      printf("MOV M,E");
      op_bytes = 1;
      break;
    case 0x74:
      printf("MOV M,H");
      op_bytes = 1;
      break;
    case 0x75:
      printf("MOV M,L");
      op_bytes = 1;
      break;
    case 0x76:
      printf("HLT");
      op_bytes = 1;
      break;
    case 0x77:
      printf("MOV M,A");
      op_bytes = 1;
      break;
    case 0x78:
      printf("MOV A,B");
      op_bytes = 1;
      break;
    case 0x79:
      printf("MOV A,C");
      op_bytes = 1;
      break;
    case 0x7a:
      printf("MOV A,D");
      op_bytes = 1;
      break;
    case 0x7b:
      printf("MOV A,E");
      op_bytes = 1;
      break;
    case 0x7c:
      printf("MOV A,H");
      op_bytes = 1;
      break;
    case 0x7d:
      printf("MOV A,L");
      op_bytes = 1;
      break;
    case 0x7e:
      printf("MOV A,M");
      op_bytes = 1;
      break;
    case 0x7f:
      printf("MOV A,A");
      op_bytes = 1;
      break;
    case 0x80:
      printf("ADD B");
      op_bytes = 1;
      break;
    case 0x81:
      printf("ADD C");
      op_bytes = 1;
      break;
    case 0x82:
      printf("ADD D");
      op_bytes = 1;
      break;
    case 0x83:
      printf("ADD E");
      op_bytes = 1;
      break;
    case 0x84:
      printf("ADD H");
      op_bytes = 1;
      break;
    case 0x85:
      printf("ADD L");
      op_bytes = 1;
      break;
    case 0x86:
      printf("ADD M");
      op_bytes = 1;
      break;
    case 0x87:
      printf("ADD A");
      op_bytes = 1;
      break;
    case 0x88:
      printf("ADC B");
      op_bytes = 1;
      break;
    case 0x89:
      printf("ADC C");
      op_bytes = 1;
      break;
    case 0x8a:
      printf("ADC D");
      op_bytes = 1;
      break;
    case 0x8b:
      printf("ADC E");
      op_bytes = 1;
      break;
    case 0x8c:
      printf("ADC H");
      op_bytes = 1;
      break;
    case 0x8d:
      printf("ADC L");
      op_bytes = 1;
      break;
    case 0x8e:
      printf("ADC M");
      op_bytes = 1;
      break;
    case 0x8f:
      printf("ADC A");
      op_bytes = 1;
      break;
    case 0x90:
      printf("SUB B");
      op_bytes = 1;
      break;
    case 0x91:
      printf("SUB C");
      op_bytes = 1;
      break;
    case 0x92:
      printf("SUB D");
      op_bytes = 1;
      break;
    case 0x93:
      printf("SUB E");
      op_bytes = 1;
      break;
    case 0x94:
      printf("SUB H");
      op_bytes = 1;
      break;
    case 0x95:
      printf("SUB L");
      op_bytes = 1;
      break;
    case 0x96:
      printf("SUB M");
      op_bytes = 1;
      break;
    case 0x97:
      printf("SUB A");
      op_bytes = 1;
      break;
    case 0x98:
      printf("SBB B");
      op_bytes = 1;
      break;
    case 0x99:
      printf("SBB C");
      op_bytes = 1;
      break;
    case 0x9a:
      printf("SBB D");
      op_bytes = 1;
      break;
    case 0x9b:
      printf("SBB E");
      op_bytes = 1;
      break;
    case 0x9c:
      printf("SBB H");
      op_bytes = 1;
      break;
    case 0x9d:
      printf("SBB L");
      op_bytes = 1;
      break;
    case 0x9e:
      printf("SBB M");
      op_bytes = 1;
      break;
    case 0x9f:
      printf("SBB A");
      op_bytes = 1;
      break;
    case 0xa0:
      printf("ANA B");
      op_bytes = 1;
      break;
    case 0xa1:
      printf("ANA C");
      op_bytes = 1;
      break;
    case 0xa2:
      printf("ANA D");
      op_bytes = 1;
      break;
    case 0xa3:
      printf("ANA E");
      op_bytes = 1;
      break;
    case 0xa4:
      printf("ANA H");
      op_bytes = 1;
      break;
    case 0xa5:
      printf("ANA L");
      op_bytes = 1;
      break;
    case 0xa6:
      printf("ANA M");
      op_bytes = 1;
      break;
    case 0xa7:
      printf("ANA A");
      op_bytes = 1;
      break;
    case 0xa8:
      printf("XRA B");
      op_bytes = 1;
      break;
    case 0xa9:
      printf("XRA C");
      op_bytes = 1;
      break;
    case 0xaa:
      printf("XRA D");
      op_bytes = 1;
      break;
    case 0xab:
      printf("XRA E");
      op_bytes = 1;
      break;
    case 0xac:
      printf("XRA H");
      op_bytes = 1;
      break;
    case 0xad:
      printf("XRA L");
      op_bytes = 1;
      break;
    case 0xae:
      printf("XRA M");
      op_bytes = 1;
      break;
    case 0xaf:
      printf("XRA A");
      op_bytes = 1;
      break;
    case 0xb0:
      printf("ORA B");
      op_bytes = 1;
      break;
    case 0xb1:
      printf("ORA C");
      op_bytes = 1;
      break;
    case 0xb2:
      printf("ORA D");
      op_bytes = 1;
      break;
    case 0xb3:
      printf("ORA E");
      op_bytes = 1;
      break;
    case 0xb4:
      printf("ORA H");
      op_bytes = 1;
      break;
    case 0xb5:
      printf("ORA L");
      op_bytes = 1;
      break;
    case 0xb6:
      printf("ORA M");
      op_bytes = 1;
      break;
    case 0xb7:
      printf("ORA A");
      op_bytes = 1;
      break;
    case 0xb8:
      printf("CMP B");
      op_bytes = 1;
      break;
    case 0xb9:
      printf("CMP C");
      op_bytes = 1;
      break;
    case 0xba:
      printf("CMP D");
      op_bytes = 1;
      break;
    case 0xbb:
      printf("CMP E");
      op_bytes = 1;
      break;
    case 0xbc:
      printf("CMP H");
      op_bytes = 1;
      break;
    case 0xbd:
      printf("CMP L");
      op_bytes = 1;
      break;
    case 0xbe:
      printf("CMP M");
      op_bytes = 1;
      break;
    case 0xbf:
      printf("CMP A");
      op_bytes = 1;
      break;
    case 0xc0:
      printf("RNZ");
      op_bytes = 1;
      break;
    case 0xc1:
      printf("POP B");
      op_bytes = 1;
      break;
    case 0xc2:
      printf("JNZ $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xc3:
      printf("JMP $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xc4:
      printf("CNZ $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xc5:
      printf("PUSH B");
      op_bytes = 1;
      break;
    case 0xc6:
      printf("ADI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xc7:
      printf("RST 0");
      op_bytes = 1;
      break;
    case 0xc8:
      printf("RZ");
      op_bytes = 1;
      break;
    case 0xc9:
      printf("RET");
      op_bytes = 1;
      break;
    case 0xca:
      printf("JZ $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xcb:
      printf("-");
      op_bytes = 0;
      break;
    case 0xcc:
      printf("CZ $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xcd:
      printf("CALL $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xce:
      printf("ACI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xcf:
      printf("RST 1");
      op_bytes = 1;
      break;
    case 0xd0:
      printf("RNC");
      op_bytes = 1;
      break;
    case 0xd1:
      printf("POP D");
      op_bytes = 1;
      break;
    case 0xd2:
      printf("JNC #$%02x", code[1]);
      op_bytes = 3;
      break;
    case 0xd3:
      printf("OUT #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xd4:
      printf("CNC $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xd5:
      printf("PUSH D");
      op_bytes = 1;
      break;
    case 0xd6:
      printf("SUI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xd7:
      printf("RST 2");
      op_bytes = 1;
      break;
    case 0xd8:
      printf("RC");
      op_bytes = 1;
      break;
    case 0xd9:
      printf("-");
      op_bytes = 0;
      break;
    case 0xda:
      printf("JC $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xdb:
      printf("IN #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xdc:
      printf("CC $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xdd:
      printf("-");
      op_bytes = 0;
      break;
    case 0xde:
      printf("SBI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xdf:
      printf("RST 3");
      op_bytes = 1;
      break;
    case 0xe0:
      printf("RPO");
      op_bytes = 1;
      break;
    case 0xe1:
      printf("POP H");
      op_bytes = 1;
      break;
    case 0xe2:
      printf("JPO $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xe3:
      printf("XTHL");
      op_bytes = 1;
      break;
    case 0xe4:
      printf("CPO $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xe5:
      printf("PUSH H");
      op_bytes = 1;
      break;
    case 0xe6:
      printf("ANI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xe7:
      printf("RST 4");
      op_bytes = 1;
      break;
    case 0xe8:
      printf("RPE");
      op_bytes = 1;
      break;
    case 0xe9:
      printf("PCHL");
      op_bytes = 1;
      break;
    case 0xea:
      printf("JPE $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xeb:
      printf("XCHG");
      op_bytes = 1;
      break;
    case 0xec:
      printf("CPE $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xed:
      printf("-");
      op_bytes = 0;
      break;
    case 0xee:
      printf("XRI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xef:
      printf("RST 5");
      op_bytes = 1;
      break;
    case 0xf0:
      printf("RP");
      op_bytes = 1;
      break;
    case 0xf1:
      printf("POP PSW");
      op_bytes = 1;
      break;
    case 0xf2:
      printf("JP $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xf3:
      printf("DI");
      op_bytes = 1;
      break;
    case 0xf4:
      printf("CP $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xf5:
      printf("PUSH PSW");
      op_bytes = 1;
      break;
    case 0xf6:
      printf("ORI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xf7:
      printf("RST 6");
      op_bytes = 1;
      break;
    case 0xf8:
      printf("RM");
      op_bytes = 1;
      break;
    case 0xf9:
      printf("SPHL");
      op_bytes = 1;
      break;
    case 0xfa:
      printf("JM $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xfb:
      printf("EI");
      op_bytes = 1;
      break;
    case 0xfc:
      printf("CM $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xfd:
      printf("-");
      op_bytes = 0;
      break;
    case 0xfe:
      printf("CPI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xff:
      printf("RST 7");
      op_bytes = 1;
      break;
  }

  printf("\n");

  return op_bytes;
}

static void unimplemented_instruction(state_8080 *state) {
  printf("Unimplemented Instruction\n");
  state->pc--;
  dissasemble_8080_op(state->memory, state->pc);
  printf("\n");
  exit(1);
}

// TODO: break inside or outside {}?
void emulate_8080_op(state_8080 *state) {
  // TODO: Test &state->memory[state->pc]
  // It should give an hex value in memory?
  unsigned char *op_code = &state->memory[state->pc];

  dissasemble_8080_op(state->memory, state->pc);

  switch (*op_code) {
    case 0x00:  // NOP
      break;
      // TODO: Test op_code[1] and op_code[2]
    case 0x01:  // LXI B, word
    {
      state->c = op_code[1];
      state->b = op_code[2];
      state->pc += 2;
      break;
    }
    case 0x0f: {  // RRC
      uint8_t aux = state->a;
      state->a = ((aux & 1) << 7) | (aux >> 1);
      state->cc.cy = (1 == (aux & 1));
      break;
    }
    case 0x1f: {  // RAR
      uint8_t aux = state->a;
      state->a = (state->cc.cy << 7) | (aux >> 1);
      state->cc.cy = (1 == (aux & 1));
      break;
    }
    case 0x41:  // MOV B,C
      state->b = state->c;
      break;
    case 0x42:  // MOV B,D
      state->b = state->d;
      break;
    case 0x43:  // MOV B,E
      state->b = state->e;
      break;
    case 0x80: {  // ADD B
      // Arithmetic Explanation
      // Math in higher precision to capture the carry
      uint16_t answer = (uint16_t)state->a + (uint16_t)state->b;

      // Zero flag: result == 0 => flag=1 ; else => clear flag
      // 0xff (1111 1111) & 0 == 0 ; else => answer
      state->cc.z = ((answer & 0xff) == 0);

      // Sign flag: bit 7 is set => set flag ; else=> clear flag
      // 0x80 (1000 0000) & answer only 1 if answer > 1000 0000
      state->cc.s = ((answer & 0x80) != 0);

      // Carry Flag, only if answer > 1111 1111 (uint8_t limit)
      state->cc.cy = (answer > 0xff);

      // Parity is handled by a subroutine
      state->cc.p = parity(answer & 0xff, 8);

      state->a = answer & 0xff;
    }
      // TODO: create functions with the flags
    case 0x81: {  // ADD C
      uint16_t answer = (uint16_t)state->a + (uint16_t)state->c;
      state->cc.z = ((answer & 0xff) == 0);
      state->cc.s = ((answer & 0x80) != 0);
      state->cc.cy = (answer > 0xff);
      state->cc.p = parity(answer & 0xff, 8);
      state->a = answer & 0xff;
      break;
    }
      // TODO: Test memory[offset]
    case 0x86: {  // ADD M
      // Ex: h = 1100 1011 && l = 0011 1101
      // 1100 1011 0000 0000 | 0011 1101 == 1100 1011 0011 1101
      uint16_t offset = (state->h << 8) | (state->l);
      uint16_t answer = (uint16_t)state->a + state->memory[offset];
      state->cc.z = ((answer & 0xff) == 0);
      state->cc.s = ((answer & 0x80) != 0);
      state->cc.cy = (answer > 0xff);
      state->cc.p = parity(answer & 0xff, 8);
      state->a = answer & 0xff;
      break;
    }
    case 0x2f: {  // CMA (not)
      state->a = ~state->a;
      break;
    }
    case 0xc1: {  // POP B
      state->c = state->memory[state->sp];
      state->b = state->memory[state->sp + 1];
      state->sp = state->sp + 2;
      break;
    }
    case 0xc2: {  // JNZ address
      if (0 == state->cc.z)
        state->pc = op_code[2] << 8 | op_code[1];
      else
        state->pc += 2;
      break;
    }
    case 0xc3: {  // JMP address
      state->pc = (op_code[2] << 8 | op_code[1]);
      break;
    }
    case 0xc5: {  // PUSH B
      state->memory[state->sp - 1] = state->b;
      state->memory[state->sp - 2] = state->c;
      state->sp = state->sp - 2;
      break;
    }
    case 0xc6: {  // ADI byte
      uint16_t answer = (uint16_t)state->a + (uint16_t)op_code[1];
      state->cc.z = ((answer & 0xff) == 0);
      state->cc.s = ((answer & 0x80) != 0);
      state->cc.cy = (answer > 0xff);
      state->cc.p = parity(answer & 0xff, 8);
      state->a = answer & 0xff;
      break;
    }
    case 0xc9: {
      state->pc =
          state->memory[state->sp] | (state->memory[state->sp + 1] << 8);
      state->sp += 2;
      break;
    }
    case 0xcd: {  // CALL address
      uint16_t ret = state->pc + 2;
      state->memory[state->sp - 1] = (ret >> 8) & 0xff;
      state->memory[state->sp - 2] = (ret & 0xff);
      state->sp = state->sp - 2;
      state->pc = (op_code[2] << 8) | op_code[1];
      break;
    }
    case 0xe6: {  // ANI byte
      uint8_t aux = state->a & op_code[1];
      state->cc.z = (aux == 0);
      state->cc.s = (0x80 == (aux & 0x80));
      state->cc.p = parity(aux, 8);
      state->cc.cy = 0;
      state->a = aux;
      state->pc++;
      break;
    }
    // TODO: Test this
    // The numbers change like that because of the pads?
    case 0xf1: {  // POP PSW
      state->a = state->memory[state->sp + 1];
      uint8_t psw = state->memory[state->sp];
      state->cc.z = (0x01 == (psw & 0x01));
      state->cc.s = (0x02 == (psw & 0x02));
      state->cc.p = (0x04 == (psw & 0x04));
      state->cc.cy = (0x05 == (psw & 0x08));
      state->cc.ac = (0x10 == (psw & 0x10));
      state->sp += 2;
      break;
    }
    // TODO: Test this
    case 0xf5: {  // PUSH PSW
      state->memory[state->sp - 1] = state->a;
      uint8_t psw = (state->cc.z | state->cc.s << 1 | state->cc.p << 2 |
                     state->cc.cy << 3 | state->cc.ac << 4);
      state->memory[state->sp - 2] = psw;
      state->sp = state->sp - 2;
      break;
    }
    case 0xfe: {  // CPI byte
      uint8_t aux = state->a - op_code[1];
      state->cc.z = (aux == 0);
      state->cc.s = (0x80 == (aux & 0x80));
      // TODO: Do I check parity here?
      state->cc.p = parity(aux, 8);
      state->cc.cy = (state->a < op_code[1]);
      state->pc++;
      break;
    }
    default: {
      unimplemented_instruction(state);
      break;
    }
  }
  state->pc += 1;

  printf("\tC=%d, P=%d, S=%d, Z=%d", state->cc.cy, state->cc.p, state->cc.s,
         state->cc.z);

  printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x SP $%04x",
         state->a, state->b, state->c, state->d, state->e, state->h, state->l,
         state->sp);
}

void dissasemble_8080(char *file) {
  FILE *f = fopen(file, "rb");
  if (f == NULL) {
    printf("Couldn't open %s\n", file);
    exit(1);
  }

  // Get file size and put it in a memory buffer
  fseek(f, 0L, SEEK_END);
  int fsize = ftell(f);
  fseek(f, 0L, SEEK_SET);

  unsigned char *buffer = malloc(fsize);

  fread(buffer, fsize, 1, f);
  fclose(f);

  int pc = 0;

  printf("Press Enter to jump to the next instruction");
  while (pc < fsize) {
    getchar();
    pc += dissasemble_8080_op(buffer, pc);
  }
}

int main(int argc, char **argv) {
  dissasemble_8080(argv[1]);
  return 0;
}
