#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: make it work
static int parity(int value, int size) { return 0x00; }

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
int disassemble_8080_op(unsigned char *code_buffer, int pc) {
  unsigned char *code = &code_buffer[pc];
  int op_bytes = 1;
  printf("OP: 0x%02x\t", *code);
  printf("PC: $%04x\t", pc);

  switch (*code) {
    case 0x00:
      printf("I: NOP");
      op_bytes = 1;
      break;
    case 0x01:
      printf("I: LXI B, #$%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x02:
      printf("I: STAX B");
      op_bytes = 1;
      break;
    case 0x03:
      printf("I: INX B");
      op_bytes = 1;
      break;
    case 0x04:
      printf("I: INR B");
      op_bytes = 1;
      break;
    case 0x05:
      printf("I: DCR B");
      op_bytes = 1;
      break;
    case 0x06:
      printf("I: MVI B, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x07:
      printf("I: RLC");
      op_bytes = 1;
      break;
    case 0x08:
      printf("I: -");
      op_bytes = 0;
      break;
    case 0x09:
      printf("I: DAD B");
      op_bytes = 1;
      break;
    case 0x0a:
      printf("I: LDAX B");
      op_bytes = 1;
      break;
    case 0x0b:
      printf("I: DCX B");
      op_bytes = 1;
      break;
    case 0x0c:
      printf("I: INR C");
      op_bytes = 1;
      break;
    case 0x0d:
      printf("I: DCR C");
      op_bytes = 1;
      break;
    case 0x0e:
      printf("I: MVI C, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x0f:
      printf("I: RRC");
      op_bytes = 1;
      break;
    case 0x10:
      printf("I: -");
      op_bytes = 0;
      break;
    case 0x11:
      printf("I: LXI D, #$%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x12:
      printf("I: STAX D");
      op_bytes = 1;
      break;
    case 0x13:
      printf("I: INX D");
      op_bytes = 1;
      break;
    case 0x14:
      printf("I: INR D");
      op_bytes = 1;
      break;
    case 0x15:
      printf("I: DCR D");
      op_bytes = 1;
      break;
    case 0x16:
      printf("I: MVI D, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x17:
      printf("I: RAL");
      op_bytes = 1;
      break;
    case 0x18:
      printf("I: -");
      op_bytes = 0;
      break;
    case 0x19:
      printf("I: DAD D");
      op_bytes = 1;
      break;
    case 0x1a:
      printf("I: LDAX D");
      op_bytes = 1;
      break;
    case 0x1b:
      printf("I: DCX D");
      op_bytes = 1;
      break;
    case 0x1c:
      printf("I: INR E");
      op_bytes = 1;
      break;
    case 0x1d:
      printf("I: DCR E");
      op_bytes = 1;
      break;
    case 0x1e:
      printf("I: MVI E, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x1f:
      printf("I: RAR");
      op_bytes = 1;
      break;
    case 0x20:
      printf("I: RIM");
      op_bytes = 1;
      break;
    case 0x21:
      printf("I: LXI H, #$%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x22:
      printf("I: SHLD $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x23:
      printf("I: INX H");
      op_bytes = 1;
      break;
    case 0x24:
      printf("I: INR H");
      op_bytes = 1;
      break;
    case 0x25:
      printf("I: DCR H");
      op_bytes = 1;
      break;
    case 0x26:
      printf("I: MVI H, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x27:
      printf("I: DAA");
      op_bytes = 1;
      break;
    case 0x28:
      printf("I: -");
      op_bytes = 0;
      break;
    case 0x29:
      printf("I: DAD H");
      op_bytes = 1;
      break;
    case 0x2a:
      printf("I: LHLD $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x2b:
      printf("I: DCX H");
      op_bytes = 1;
      break;
    case 0x2c:
      printf("I: INR L");
      op_bytes = 1;
      break;
    case 0x2d:
      printf("I: DCR L");
      op_bytes = 1;
      break;
    case 0x2e:
      printf("I: MVI L, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x2f:
      printf("I: CMA");
      op_bytes = 1;
      break;
    case 0x30:
      printf("I: SIM");
      op_bytes = 1;
      break;
    case 0x31:
      printf("I: LXI SP, #$%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x32:
      printf("I: STA $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x33:
      printf("I: INX SP");
      op_bytes = 1;
      break;
    case 0x34:
      printf("I: INR M");
      op_bytes = 1;
      break;
    case 0x35:
      printf("I: DCR M");
      op_bytes = 1;
      break;
    case 0x36:
      printf("I: MVI M, #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x37:
      printf("I: STC");
      op_bytes = 1;
      break;
    case 0x38:
      printf("I: -");
      op_bytes = 0;
      break;
    case 0x39:
      printf("I: DAD SP");
      op_bytes = 1;
      break;
    case 0x3a:
      printf("I: LDA $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0x3b:
      printf("I: DCX SP");
      op_bytes = 1;
      break;
    case 0x3c:
      printf("I: INR A");
      op_bytes = 1;
      break;
    case 0x3d:
      printf("I: DCR A");
      op_bytes = 1;
      break;
    case 0x3e:
      printf("I: MVI A, #0x%02x", code[1]);
      op_bytes = 2;
      break;
    case 0x3f:
      printf("I: CMC");
      op_bytes = 1;
      break;
    case 0x40:
      printf("I: MOV B,B");
      op_bytes = 1;
      break;
    case 0x41:
      printf("I: MOV B,C");
      op_bytes = 1;
      break;
    case 0x42:
      printf("I: MOV B,D");
      op_bytes = 1;
      break;
    case 0x43:
      printf("I: MOV B,E");
      op_bytes = 1;
      break;
    case 0x44:
      printf("I: MOV B,H");
      op_bytes = 1;
      break;
    case 0x45:
      printf("I: MOV B,L");
      op_bytes = 1;
      break;
    case 0x46:
      printf("I: MOV B,M");
      op_bytes = 1;
      break;
    case 0x47:
      printf("I: MOV B,A");
      op_bytes = 1;
      break;
    case 0x48:
      printf("I: MOV C,B");
      op_bytes = 1;
      break;
    case 0x49:
      printf("I: MOV C,C");
      op_bytes = 1;
      break;
    case 0x4a:
      printf("I: MOV C,D");
      op_bytes = 1;
      break;
    case 0x4b:
      printf("I: MOV C,E");
      op_bytes = 1;
      break;
    case 0x4c:
      printf("I: MOV C,H");
      op_bytes = 1;
      break;
    case 0x4d:
      printf("I: MOV C,L");
      op_bytes = 1;
      break;
    case 0x4e:
      printf("I: MOV C,M");
      op_bytes = 1;
      break;
    case 0x4f:
      printf("I: MOV C,A");
      op_bytes = 1;
      break;
    case 0x50:
      printf("I: MOV D,B");
      op_bytes = 1;
      break;
    case 0x51:
      printf("I: MOV D,C");
      op_bytes = 1;
      break;
    case 0x52:
      printf("I: MOV D,D");
      op_bytes = 1;
      break;
    case 0x53:
      printf("I: MOV D,E");
      op_bytes = 1;
      break;
    case 0x54:
      printf("I: MOV D,H");
      op_bytes = 1;
      break;
    case 0x55:
      printf("I: MOV D,L");
      op_bytes = 1;
      break;
    case 0x56:
      printf("I: MOV D,M");
      op_bytes = 1;
      break;
    case 0x57:
      printf("I: MOV D,A");
      op_bytes = 1;
      break;
    case 0x58:
      printf("I: MOV E,B");
      op_bytes = 1;
      break;
    case 0x59:
      printf("I: MOV E,C");
      op_bytes = 1;
      break;
    case 0x5a:
      printf("I: MOV E,D");
      op_bytes = 1;
      break;
    case 0x5b:
      printf("I: MOV E,E");
      op_bytes = 1;
      break;
    case 0x5c:
      printf("I: MOV E,H");
      op_bytes = 1;
      break;
    case 0x5d:
      printf("I: MOV E,L");
      op_bytes = 1;
      break;
    case 0x5e:
      printf("I: MOV E,M");
      op_bytes = 1;
      break;
    case 0x5f:
      printf("I: MOV E,A");
      op_bytes = 1;
      break;
    case 0x60:
      printf("I: MOV H,B");
      op_bytes = 1;
      break;
    case 0x61:
      printf("I: MOV H,C");
      op_bytes = 1;
      break;
    case 0x62:
      printf("I: MOV H,D");
      op_bytes = 1;
      break;
    case 0x63:
      printf("I: MOV H,E");
      op_bytes = 1;
      break;
    case 0x64:
      printf("I: MOV H,H");
      op_bytes = 1;
      break;
    case 0x65:
      printf("I: MOV H,L");
      op_bytes = 1;
      break;
    case 0x66:
      printf("I: MOV H,M");
      op_bytes = 1;
      break;
    case 0x67:
      printf("I: MOV H,A");
      op_bytes = 1;
      break;
    case 0x68:
      printf("I: MOV L,B");
      op_bytes = 1;
      break;
    case 0x69:
      printf("I: MOV L,C");
      op_bytes = 1;
      break;
    case 0x6a:
      printf("I: MOV L,D");
      op_bytes = 1;
      break;
    case 0x6b:
      printf("I: MOV L,E");
      op_bytes = 1;
      break;
    case 0x6c:
      printf("I: MOV L,H");
      op_bytes = 1;
      break;
    case 0x6d:
      printf("I: MOV L,L");
      op_bytes = 1;
      break;
    case 0x6e:
      printf("I: MOV L,M");
      op_bytes = 1;
      break;
    case 0x6f:
      printf("I: MOV L,A");
      op_bytes = 1;
      break;
    case 0x70:
      printf("I: MOV M,B");
      op_bytes = 1;
      break;
    case 0x71:
      printf("I: MOV M,C");
      op_bytes = 1;
      break;
    case 0x72:
      printf("I: MOV M,D");
      op_bytes = 1;
      break;
    case 0x73:
      printf("I: MOV M,E");
      op_bytes = 1;
      break;
    case 0x74:
      printf("I: MOV M,H");
      op_bytes = 1;
      break;
    case 0x75:
      printf("I: MOV M,L");
      op_bytes = 1;
      break;
    case 0x76:
      printf("I: HLT");
      op_bytes = 1;
      break;
    case 0x77:
      printf("I: MOV M,A");
      op_bytes = 1;
      break;
    case 0x78:
      printf("I: MOV A,B");
      op_bytes = 1;
      break;
    case 0x79:
      printf("I: MOV A,C");
      op_bytes = 1;
      break;
    case 0x7a:
      printf("I: MOV A,D");
      op_bytes = 1;
      break;
    case 0x7b:
      printf("I: MOV A,E");
      op_bytes = 1;
      break;
    case 0x7c:
      printf("I: MOV A,H");
      op_bytes = 1;
      break;
    case 0x7d:
      printf("I: MOV A,L");
      op_bytes = 1;
      break;
    case 0x7e:
      printf("I: MOV A,M");
      op_bytes = 1;
      break;
    case 0x7f:
      printf("I: MOV A,A");
      op_bytes = 1;
      break;
    case 0x80:
      printf("I: ADD B");
      op_bytes = 1;
      break;
    case 0x81:
      printf("I: ADD C");
      op_bytes = 1;
      break;
    case 0x82:
      printf("I: ADD D");
      op_bytes = 1;
      break;
    case 0x83:
      printf("I: ADD E");
      op_bytes = 1;
      break;
    case 0x84:
      printf("I: ADD H");
      op_bytes = 1;
      break;
    case 0x85:
      printf("I: ADD L");
      op_bytes = 1;
      break;
    case 0x86:
      printf("I: ADD M");
      op_bytes = 1;
      break;
    case 0x87:
      printf("I: ADD A");
      op_bytes = 1;
      break;
    case 0x88:
      printf("I: ADC B");
      op_bytes = 1;
      break;
    case 0x89:
      printf("I: ADC C");
      op_bytes = 1;
      break;
    case 0x8a:
      printf("I: ADC D");
      op_bytes = 1;
      break;
    case 0x8b:
      printf("I: ADC E");
      op_bytes = 1;
      break;
    case 0x8c:
      printf("I: ADC H");
      op_bytes = 1;
      break;
    case 0x8d:
      printf("I: ADC L");
      op_bytes = 1;
      break;
    case 0x8e:
      printf("I: ADC M");
      op_bytes = 1;
      break;
    case 0x8f:
      printf("I: ADC A");
      op_bytes = 1;
      break;
    case 0x90:
      printf("I: SUB B");
      op_bytes = 1;
      break;
    case 0x91:
      printf("I: SUB C");
      op_bytes = 1;
      break;
    case 0x92:
      printf("I: SUB D");
      op_bytes = 1;
      break;
    case 0x93:
      printf("I: SUB E");
      op_bytes = 1;
      break;
    case 0x94:
      printf("I: SUB H");
      op_bytes = 1;
      break;
    case 0x95:
      printf("I: SUB L");
      op_bytes = 1;
      break;
    case 0x96:
      printf("I: SUB M");
      op_bytes = 1;
      break;
    case 0x97:
      printf("I: SUB A");
      op_bytes = 1;
      break;
    case 0x98:
      printf("I: SBB B");
      op_bytes = 1;
      break;
    case 0x99:
      printf("I: SBB C");
      op_bytes = 1;
      break;
    case 0x9a:
      printf("I: SBB D");
      op_bytes = 1;
      break;
    case 0x9b:
      printf("I: SBB E");
      op_bytes = 1;
      break;
    case 0x9c:
      printf("I: SBB H");
      op_bytes = 1;
      break;
    case 0x9d:
      printf("I: SBB L");
      op_bytes = 1;
      break;
    case 0x9e:
      printf("I: SBB M");
      op_bytes = 1;
      break;
    case 0x9f:
      printf("I: SBB A");
      op_bytes = 1;
      break;
    case 0xa0:
      printf("I: ANA B");
      op_bytes = 1;
      break;
    case 0xa1:
      printf("I: ANA C");
      op_bytes = 1;
      break;
    case 0xa2:
      printf("I: ANA D");
      op_bytes = 1;
      break;
    case 0xa3:
      printf("I: ANA E");
      op_bytes = 1;
      break;
    case 0xa4:
      printf("I: ANA H");
      op_bytes = 1;
      break;
    case 0xa5:
      printf("I: ANA L");
      op_bytes = 1;
      break;
    case 0xa6:
      printf("I: ANA M");
      op_bytes = 1;
      break;
    case 0xa7:
      printf("I: ANA A");
      op_bytes = 1;
      break;
    case 0xa8:
      printf("I: XRA B");
      op_bytes = 1;
      break;
    case 0xa9:
      printf("I: XRA C");
      op_bytes = 1;
      break;
    case 0xaa:
      printf("I: XRA D");
      op_bytes = 1;
      break;
    case 0xab:
      printf("I: XRA E");
      op_bytes = 1;
      break;
    case 0xac:
      printf("I: XRA H");
      op_bytes = 1;
      break;
    case 0xad:
      printf("I: XRA L");
      op_bytes = 1;
      break;
    case 0xae:
      printf("I: XRA M");
      op_bytes = 1;
      break;
    case 0xaf:
      printf("I: XRA A");
      op_bytes = 1;
      break;
    case 0xb0:
      printf("I: ORA B");
      op_bytes = 1;
      break;
    case 0xb1:
      printf("I: ORA C");
      op_bytes = 1;
      break;
    case 0xb2:
      printf("I: ORA D");
      op_bytes = 1;
      break;
    case 0xb3:
      printf("I: ORA E");
      op_bytes = 1;
      break;
    case 0xb4:
      printf("I: ORA H");
      op_bytes = 1;
      break;
    case 0xb5:
      printf("I: ORA L");
      op_bytes = 1;
      break;
    case 0xb6:
      printf("I: ORA M");
      op_bytes = 1;
      break;
    case 0xb7:
      printf("I: ORA A");
      op_bytes = 1;
      break;
    case 0xb8:
      printf("I: CMP B");
      op_bytes = 1;
      break;
    case 0xb9:
      printf("I: CMP C");
      op_bytes = 1;
      break;
    case 0xba:
      printf("I: CMP D");
      op_bytes = 1;
      break;
    case 0xbb:
      printf("I: CMP E");
      op_bytes = 1;
      break;
    case 0xbc:
      printf("I: CMP H");
      op_bytes = 1;
      break;
    case 0xbd:
      printf("I: CMP L");
      op_bytes = 1;
      break;
    case 0xbe:
      printf("I: CMP M");
      op_bytes = 1;
      break;
    case 0xbf:
      printf("I: CMP A");
      op_bytes = 1;
      break;
    case 0xc0:
      printf("I: RNZ");
      op_bytes = 1;
      break;
    case 0xc1:
      printf("I: POP B");
      op_bytes = 1;
      break;
    case 0xc2:
      printf("I: JNZ $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xc3:
      printf("I: JMP $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xc4:
      printf("I: CNZ $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xc5:
      printf("I: PUSH B");
      op_bytes = 1;
      break;
    case 0xc6:
      printf("I: ADI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xc7:
      printf("I: RST 0");
      op_bytes = 1;
      break;
    case 0xc8:
      printf("I: RZ");
      op_bytes = 1;
      break;
    case 0xc9:
      printf("I: RET");
      op_bytes = 1;
      break;
    case 0xca:
      printf("I: JZ $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xcb:
      printf("I: -");
      op_bytes = 0;
      break;
    case 0xcc:
      printf("I: CZ $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xcd:
      printf("I: CALL $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xce:
      printf("I: ACI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xcf:
      printf("I: RST 1");
      op_bytes = 1;
      break;
    case 0xd0:
      printf("I: RNC");
      op_bytes = 1;
      break;
    case 0xd1:
      printf("I: POP D");
      op_bytes = 1;
      break;
    case 0xd2:
      printf("I: JNC #$%02x", code[1]);
      op_bytes = 3;
      break;
    case 0xd3:
      printf("I: OUT #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xd4:
      printf("I: CNC $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xd5:
      printf("I: PUSH D");
      op_bytes = 1;
      break;
    case 0xd6:
      printf("I: SUI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xd7:
      printf("I: RST 2");
      op_bytes = 1;
      break;
    case 0xd8:
      printf("I: RC");
      op_bytes = 1;
      break;
    case 0xd9:
      printf("I: -");
      op_bytes = 0;
      break;
    case 0xda:
      printf("I: JC $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xdb:
      printf("I: IN #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xdc:
      printf("I: CC $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xdd:
      printf("I: -");
      op_bytes = 0;
      break;
    case 0xde:
      printf("I: SBI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xdf:
      printf("I: RST 3");
      op_bytes = 1;
      break;
    case 0xe0:
      printf("I: RPO");
      op_bytes = 1;
      break;
    case 0xe1:
      printf("I: POP H");
      op_bytes = 1;
      break;
    case 0xe2:
      printf("I: JPO $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xe3:
      printf("I: XTHL");
      op_bytes = 1;
      break;
    case 0xe4:
      printf("I: CPO $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xe5:
      printf("I: PUSH H");
      op_bytes = 1;
      break;
    case 0xe6:
      printf("I: ANI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xe7:
      printf("I: RST 4");
      op_bytes = 1;
      break;
    case 0xe8:
      printf("I: RPE");
      op_bytes = 1;
      break;
    case 0xe9:
      printf("I: PCHL");
      op_bytes = 1;
      break;
    case 0xea:
      printf("I: JPE $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xeb:
      printf("I: XCHG");
      op_bytes = 1;
      break;
    case 0xec:
      printf("I: CPE $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xed:
      printf("I: -");
      op_bytes = 0;
      break;
    case 0xee:
      printf("I: XRI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xef:
      printf("I: RST 5");
      op_bytes = 1;
      break;
    case 0xf0:
      printf("I: RP");
      op_bytes = 1;
      break;
    case 0xf1:
      printf("I: POP PSW");
      op_bytes = 1;
      break;
    case 0xf2:
      printf("I: JP $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xf3:
      printf("I: DI");
      op_bytes = 1;
      break;
    case 0xf4:
      printf("I: CP $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xf5:
      printf("I: PUSH PSW");
      op_bytes = 1;
      break;
    case 0xf6:
      printf("I: ORI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xf7:
      printf("I: RST 6");
      op_bytes = 1;
      break;
    case 0xf8:
      printf("I: RM");
      op_bytes = 1;
      break;
    case 0xf9:
      printf("I: SPHL");
      op_bytes = 1;
      break;
    case 0xfa:
      printf("I: JM $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xfb:
      printf("I: EI");
      op_bytes = 1;
      break;
    case 0xfc:
      printf("I: CM $%02x%02x", code[2], code[1]);
      op_bytes = 3;
      break;
    case 0xfd:
      printf("I: -");
      op_bytes = 0;
      break;
    case 0xfe:
      printf("I: CPI #$%02x", code[1]);
      op_bytes = 2;
      break;
    case 0xff:
      printf("I: RST 7");
      op_bytes = 1;
      break;
  }

  printf("\n");

  return op_bytes;
}

static void unimplemented_instruction(state_8080 *state) {
  printf("Unimplemented Instruction\t");
  disassemble_8080_op(state->memory, state->pc);
  state->pc--;
  printf("\n");
  exit(1);
}

// TODO: Create functions for arith-logic-etc
// TODO: break inside or outside {}?
int emulate_8080_op(state_8080 *state) {
  // TODO: Test &state->memory[state->pc]
  // It should give an hex value in memory?
  unsigned char *op_code = &state->memory[state->pc];

  disassemble_8080_op(state->memory, state->pc);

  state->pc += 1;

  switch (*op_code) {
    case 0x00: {  // NOP
      break;
    }
      // TODO: Test op_code[1] and op_code[2]
    case 0x01:  // LXI B, word
    {
      state->c = op_code[1];
      state->b = op_code[2];
      state->pc += 2;
      break;
    }
    case 0x05: {  // DCR B
      uint8_t result = state->b - 1;
      state->cc.z = (result == 0);
      state->cc.s = (0x80 == (result & 0x80));
      state->cc.p = parity(result, 8);
      state->b = result;
      break;
    }
    case 0x06: {  // MVI B byte
      state->b = op_code[1];
      state->pc++;
      break;
    }
    // TODO: Test this case
    case 0x09: {  // DAD B
      uint32_t hl = (state->h << 8) | state->l;
      uint32_t bc = (state->b << 8) | state->c;
      uint32_t result = hl + bc;
      state->h = (result & 0xff00) >> 8;
      state->l = (result & 0xff);
      state->cc.cy = ((result & 0xffff0000) > 0);
      break;
    }
    case 0x0d: {  // DCR C
      uint8_t result = state->c - 1;
      state->cc.z = (result == 0);
      state->cc.s = (0x80 == (result & 0x80));
      state->cc.p = parity(result, 8);
      state->c = result;
      break;
    }
    case 0x0e: {  // MVI C byte
      state->c = op_code[1];
      state->pc++;
      break;
    }
    case 0x0f: {  // RRC
      uint8_t result = state->a;
      state->a = ((result & 1) << 7) | (result >> 1);
      state->cc.cy = (1 == (result & 1));
      break;
    }
    case 0x11: {  // LXI D word
      state->e = op_code[1];
      state->d = op_code[2];
      state->pc += 2;
      break;
    }
    case 0x13: {  // INX D
      state->e++;
      if (state->e == 0) {
        state->d++;
      }
      break;
    }
    case 0x19: {  // DAD D
      uint32_t hl = (state->h << 8) | state->l;
      uint32_t de = (state->d << 8) | state->e;
      uint32_t result = hl + de;
      state->h = (result & 0xff00) >> 8;
      state->l = (result & 0xff);
      state->cc.cy = ((result & 0xffff0000) > 0);
      break;
    }
    case 0x1a: {  // LDAX D
      uint16_t offset = (state->d << 8) | state->e;
      state->a = state->memory[offset];
      break;
    }
    case 0x1f: {  // RAR
      uint8_t result = state->a;
      state->a = (state->cc.cy << 7) | (result >> 1);
      state->cc.cy = (1 == (result & 1));
      break;
    }
    case 0x21: {  //	LXI H word
      state->l = op_code[1];
      state->h = op_code[2];
      state->pc += 2;
      break;
    }
    case 0x23: {  // INX H
      state->l++;
      if (state->l == 0) {
        state->h++;
      }
      break;
    }
    case 0x26: {  // MVI H byte
      state->h = op_code[1];
      state->pc++;
      break;
    }
    case 0x29: {  // DAD H
      uint32_t hl = (state->h << 8) | state->l;
      uint32_t result = hl + hl;
      state->h = (result & 0xff00) >> 8;
      state->l = (result & 0xff);
      state->cc.cy = ((result & 0xffff0000) > 0);
      break;
    }
    case 0x31: {  // LXI SP word
                  // SP.hi <- byte 3, SP.lo <- byte 2
      state->sp = (op_code[2] << 8) | op_code[1];
      state->pc += 2;
      break;
    }
    case 0x32: {  // STA address
      uint16_t offset = (op_code[2] << 8) | (op_code[1]);
      state->memory[offset] = state->a;
      state->pc += 2;
      break;
    }
    case 0x36: {  // MVI M byte
      uint16_t offset = (state->h << 8) | state->l;
      state->memory[offset] = op_code[1];
      state->pc++;
      break;
    }
    case 0x3a: {  // LDA address
      uint16_t offset = (op_code[2] << 8) | (op_code[1]);
      state->a = state->memory[offset];
      state->pc += 2;
      break;
    }
    case 0x3e: {  // MVI A byte
      state->a = op_code[1];
      state->pc++;
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
    case 0x56: {  // MOV D,M
      uint16_t offset = (state->h << 8) | (state->l);
      state->d = state->memory[offset];
      break;
    }
    case 0x5e: {  // MOV E,M
      uint16_t offset = (state->h << 8) | (state->l);
      state->e = state->memory[offset];
      break;
    }
    case 0x66: {  // MOV H,M
      uint16_t offset = (state->h << 8) | (state->l);
      state->h = state->memory[offset];
      break;
    }
    case 0x6f:  // MOV L,A
      state->l = state->a;
      break;
    case 0x77: {  // MOV M,A
      uint16_t offset = (state->h << 8) | (state->l);
      state->memory[offset] = state->a;
      break;
    }
    case 0x7a:  // MOV A,D
      state->a = state->d;
      break;
    case 0x7b:  // MOV A,E
      state->a = state->e;
      break;
    case 0x7c:  // MOV A,H
      state->a = state->h;
      break;
    case 0x7e: {  //	MOV A,M
      uint16_t offset = (state->h << 8) | (state->l);
      state->a = state->memory[offset];
      break;
    }
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
    case 0xa7: {  //	ANA A
      uint8_t result = state->a & state->a;
      state->cc.z = (result == 0);
      state->cc.s = (0x80 == (result & 0x80));
      state->cc.p = parity(result, 8);
      state->cc.cy = (state->a < op_code[1]);
      state->a = result;
      break;
    }
    case 0xaf: {  //	XRA A
      uint8_t result = state->a ^ state->a;
      state->cc.z = (result == 0);
      state->cc.s = (0x80 == (result & 0x80));
      state->cc.p = parity(result, 8);
      state->cc.cy = (state->a < op_code[1]);
      state->a = result;
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
    case 0xd1: {  // POP D
      state->e = state->memory[state->sp];
      state->d = state->memory[state->sp + 1];
      state->sp = state->sp + 2;
      break;
    }
    case 0xd3: {  // OUT byte
      // TODO: Learn what to do here
      state->pc++;
      break;
    }
    case 0xd5: {  // PUSH D
      state->memory[state->sp - 1] = state->d;
      state->memory[state->sp - 2] = state->e;
      state->sp = state->sp - 2;
      break;
    }
    case 0xe1: {  // POP H
      state->l = state->memory[state->sp];
      state->h = state->memory[state->sp + 1];
      state->sp = state->sp + 2;
      break;
    }
    case 0xe5: {  // PUSH H
      state->memory[state->sp - 1] = state->h;
      state->memory[state->sp - 2] = state->l;
      state->sp = state->sp - 2;
      break;
    }
    case 0xe6: {  // ANI byte
      uint8_t result = state->a & op_code[1];
      state->cc.z = (result == 0);
      state->cc.s = (0x80 == (result & 0x80));
      state->cc.p = parity(result, 8);
      state->cc.cy = 0;
      state->a = result;
      state->pc++;
      break;
    }
    case 0xeb: {  // XCHG
      uint8_t temporal1 = state->d;
      uint8_t temporal2 = state->e;
      state->d = state->h;
      state->e = state->l;
      state->h = temporal1;
      state->l = temporal2;
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
    case 0xfb: {  // EI
      state->int_enable = 1;
      break;
    }
    case 0xfe: {  // CPI byte
      uint8_t result = state->a - op_code[1];
      state->cc.z = (result == 0);
      state->cc.s = (0x80 == (result & 0x80));
      // TODO: Do I check parity here?
      state->cc.p = parity(result, 8);
      state->cc.cy = (state->a < op_code[1]);
      state->pc++;
      break;
    }
    default: {
      state->pc -= 1;
      unimplemented_instruction(state);
      break;
    }
  }

  printf("\t");
  printf("%c", state->cc.s ? 's' : '.');
  printf("%c", state->cc.z ? 'z' : '.');
  printf("%c", '.');
  printf("%c", state->cc.ac ? 'a' : '.');
  printf("%c", '.');
  printf("%c", state->cc.p ? 'p' : '.');
  printf("%c", '.');
  printf("%c", state->cc.cy ? 'c' : '.');

  printf(
      "\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x SP $%04x\n\n",
      state->a, state->b, state->c, state->d, state->e, state->h, state->l,
      state->sp);

  return 0;
}

void disassemble_8080(char *file) {
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
    pc += disassemble_8080_op(buffer, pc);
  }
}

state_8080 *init_8080() {
  state_8080 *state = calloc(1, sizeof(state_8080));
  state->memory = malloc(0x10000);  // 16K
  return state;
}

void read_file_into_memory_at(char *filename, state_8080 *state,
                              uint32_t offset) {
  FILE *f = fopen(filename, "rb");
  if (f == NULL) {
    printf("ERROR: Couldn't open %s\n", filename);
    exit(1);
  }

  fseek(f, 0L, SEEK_END);
  int fsize = ftell(f);
  fseek(f, 0L, SEEK_SET);

  uint8_t *buffer = &state->memory[offset];
  fread(buffer, fsize, 1, f);
  fclose(f);
}

void emulate_8080(char *file) {
  state_8080 *state = init_8080();
  read_file_into_memory_at("Invaders/invaders", state, 0);

  int done = 0;

  while (done == 0) {
    done = emulate_8080_op(state);
  }
}

int main(int argc, char **argv) {
  emulate_8080(argv[1]);
  // disassemble_8080(argv[1]);
  return 0;
}
