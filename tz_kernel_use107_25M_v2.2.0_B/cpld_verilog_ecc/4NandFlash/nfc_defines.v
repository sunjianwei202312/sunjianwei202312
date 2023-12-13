 //1.command define
`define      READ_FST       8'h00
`define      READ_SEC       8'h30////wait Ttr

`define      CBREAD_FST     8'h00 
`define      CBREAD_SEC     8'h35 

`define      READ_ID        8'h90 
`define      RESET          8'hff 

`define      PPRAM_FST      8'h80 
`define      PPRAM_SEC      8'h10 

`define      CPRAM_FST      8'h80 
`define      CPRAM_SEC      8'h15 

`define      CBPRAM_FST     8'h85 
`define      CBPRAM_SEC     8'h10 

`define      BERASE_FST     8'h60 
`define      BERASE_SEC     8'hd0 

`define      RDATI          8'h85 

`define      RDATO_FST      8'h05 
`define      RDATO_SEC      8'he0 

`define      RSTATUS        8'h70 
  
`define      BYTE_EOF       8'h21 
  
//2.register address define

`define      NFCMD_ADR      16'h0004
`define      NFADDR_ADR     16'h0008
`define      NFDATA_ADR     16'h000C
`define      NFSTAT_ADR     16'h0010
`define      NFENDADDR_ADR  16'h0014
