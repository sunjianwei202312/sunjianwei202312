//`include "timescale.v"
`include "nfc_defines.v"
module nfc_top(
//wishbone side
clk_i,
rst_i,
adr_i,
dat_o,
dat_i,
cyc_i,
stb_i,
sel_i,
we_i,
ack_o,
rty_o,
err_o,
//nandflash side
nf_data_io,
nf_cen,
nf_ale,
nf_cle,
nf_ren,
nf_wen,
nf_rb);

input clk_i,rst_i,cyc_i,stb_i,we_i;
input [3:0] sel_i;
input [31:0] adr_i;
input [31:0] dat_i;
output reg [31:0] dat_o;
output ack_o,rty_o,err_o;
inout [7:0] nf_data_io;
output reg nf_cen;
output reg nf_cle;
output reg nf_ale;
output reg nf_ren;
output reg nf_wen;
input nf_rb;
reg ack_o;
assign rty_o=1'b0;
assign err_o=1'b0;
/*
always @(posedge clk_i or posedge rst_i) begin
    if(rst_i) begin
        
    end
    else begin
        
    end
end
`define      NFCMD_ADR      16'h0004
`define      NFADDR_ADR     16'h0008
`define      NFDATA_ADR     16'h000C
`define      NFSTAT_ADR     16'h0010
`define      NFENDADDR_ADR  16'h0014

*/
wire access=cyc_i&stb_i&(!ack_o);
wire cmd_write=(adr_i[15:0]==16'h0004)&we_i&access;
wire addr_write=(adr_i[15:0]==16'h0008)&we_i&access;
wire status_read=(adr_i[15:0]==16'h0010)&(!we_i)&access;
wire data_read=(adr_i[15:0]==16'h000C)& (!we_i)&access;
wire data_write=(adr_i[15:0]==16'h000C)& (we_i)&access;
wire end_addr=(adr_i[15:0]==16'h0014)&we_i&access;
reg drive_data;
reg [7:0] data_out;
assign nf_data_io=drive_data?data_out:8'bzzzz_zzzz;
`define NFSIGNAL {nf_cen,nf_cle,nf_ale,nf_ren,nf_wen}
`define NFSIGNAL_IDLE 5'b00011
`define NFSIGNAL_CMDWR  5'b01010
`define NFSIGNAL_CMDHOLD 5'b01011
`define NFSIGNAL_ADDR_IDLE 5'b00111
`define NFSIGNAL_ADDR_WR 5'b00110
`define NFSIGNAL_DATAWR 5'b00010
`define NFSIGNAL_DATARD 5'b00001
reg [3:0] wait_cnt;
reg block_erase,read_id;
reg [12:0] state;
reg [15:0] length;
reg fast_mode;
parameter 	NF_IDLE=1,
			NF_CMD=2,
			NF_CMD_HOLD=3,
			NF_WAIT_ADDR=4,
			NF_ADDR1=5,
			NF_ADDR2=6,
			NF_ADDR3=7,
			NF_ADDR4=8,
			NF_ADDR5=9,
			NF_ADDR6=10,
			NF_ADDR7=11,
			NF_ADDR8=12,
			NF_ADDR9=13,
			NF_ADDR10=14,
			NF_END_ADDR=15,
			NF_STATUS=16,			
			NF_WRITE_DATA1=17,
			NF_WRITE_DATA2=18,
			NF_WRITE_DATA3=19,
			NF_WRITE_DATA4=20,
			NF_WRITE_DATA5=21,
			NF_WRITE_DATA6=22,
			NF_WRITE_DATA7=23,
			NF_WRITE_DATA8=24,									
			NF_READ_DATA1=25,
			NF_READ_DATA2=26,
			NF_READ_DATA3=27,
			NF_READ_DATA4=28,
			NF_READ_DATA5=29,
			NF_READ_DATA6=30,
			NF_READ_DATA7=31,
			NF_READ_DATA8=32,									
			NF_TWR=33;
reg [7:0] watchdog;			
reg int_rst;
always @(posedge clk_i or posedge rst_i) begin
    if(rst_i) begin watchdog<=8'h0; int_rst<=1;end
    else  begin
        if(cyc_i&stb_i&nf_rb) watchdog<=watchdog+1; 
        else watchdog<=8'h0;     
        if(watchdog>8'h40 && watchdog<8'h50) int_rst<=1;else int_rst<=0;
	end
end
always @(posedge clk_i or posedge int_rst) begin
    if(int_rst) begin
        state<=NF_IDLE;
        data_out<=8'b0;
        drive_data<=1'b0;
        `NFSIGNAL<=`NFSIGNAL_IDLE;
        wait_cnt<=0;
        ack_o<=0;
        length<=0;
        fast_mode<=0;
        {block_erase,read_id}<=2'b00;
    end
    else begin
       case(state)
           NF_IDLE:begin 
              {nf_cen,nf_cle,nf_ren,nf_wen}<=4'b0011;
              wait_cnt<=2; 
              drive_data<=1'b0;                     
              if(cmd_write & (nf_rb)) begin
                   state<=NF_CMD;                  
              end
              else if(addr_write &(nf_rb)) begin
                   state<=NF_WAIT_ADDR;                 
              end 
              else if(end_addr &(nf_rb)) begin
                  state<=NF_END_ADDR;
              end
              else if(data_write &(nf_rb)) begin
                  state<=NF_WRITE_DATA1;
              end
              else if(data_read&(nf_rb)) begin
                  state<=NF_READ_DATA1;
              end
              else if (status_read&(nf_rb)) begin
                  state<=NF_STATUS;
              end
	      else if(access) begin
		ack_o<=1'b1;
	      end
	      else ack_o<=1'b0;
           end
           NF_CMD:begin 
             `NFSIGNAL<=`NFSIGNAL_CMDWR;
              drive_data<=1'b1;
              data_out<=dat_i[7:0];
              if(dat_i[9]) length<=dat_i[31:16];
              fast_mode<=dat_i[8];
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_CMD_HOLD;                    
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end
           end
           NF_CMD_HOLD: begin 
              `NFSIGNAL<=`NFSIGNAL_CMDHOLD;
              if(wait_cnt==0) begin
                 wait_cnt<=6; 
                 state<=NF_TWR;
                 ack_o<=1;
                 drive_data<=1'b0;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end
           end           
           NF_WAIT_ADDR: begin
              `NFSIGNAL<=`NFSIGNAL_ADDR_IDLE;
               if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_ADDR1;
                 drive_data<=1'b0;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end    
           end
           NF_ADDR1:begin
             `NFSIGNAL<=`NFSIGNAL_ADDR_WR;
             drive_data<=1'b1;  
             data_out<=dat_i[7:0];
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_ADDR2;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end
           end           
           NF_ADDR2:begin
             `NFSIGNAL<=`NFSIGNAL_ADDR_IDLE;       
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 
                 if(fast_mode) state<=NF_ADDR3;                 
                 else begin state<=NF_IDLE;ack_o<=1'b1;end
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end 
           end
/////////////////////////
            NF_ADDR3:begin
             `NFSIGNAL<=`NFSIGNAL_ADDR_WR;
             drive_data<=1'b1;  
             data_out<={4'b0,dat_i[11:8]};
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_ADDR4;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end
           end           
           NF_ADDR4:begin
             `NFSIGNAL<=`NFSIGNAL_ADDR_IDLE;       
              if(wait_cnt==0) begin
                 wait_cnt<=2;                 
                 state<=NF_ADDR5;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end 
           end
           NF_ADDR5:begin
             `NFSIGNAL<=`NFSIGNAL_ADDR_WR;
             drive_data<=1'b1;  
             data_out<={dat_i[19:12]};
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_ADDR6;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end
           end           
           NF_ADDR6:begin
             `NFSIGNAL<=`NFSIGNAL_ADDR_IDLE;       
              if(wait_cnt==0) begin
                 wait_cnt<=2;               
                 state<=NF_ADDR7;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end 
           end
           NF_ADDR7:begin
             `NFSIGNAL<=`NFSIGNAL_ADDR_WR;
             drive_data<=1'b1;  
             data_out<=dat_i[27:20];
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_ADDR8;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end
           end           
           NF_ADDR8:begin
             `NFSIGNAL<=`NFSIGNAL_ADDR_IDLE;       
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 //ack_o<=1'b1;
                 state<=NF_ADDR9;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end 
           end
           NF_ADDR9:begin
             `NFSIGNAL<=`NFSIGNAL_ADDR_WR;
             drive_data<=1'b1;  
             data_out<={4'b0,dat_i[31:28]};
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_ADDR10;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end
           end           
           NF_ADDR10:begin
             `NFSIGNAL<=`NFSIGNAL_ADDR_IDLE;       
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 ack_o<=1'b0;
                 state<=NF_END_ADDR;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end 
           end
/////////////////////////           
           NF_END_ADDR:begin
              `NFSIGNAL<=`NFSIGNAL_IDLE;
              state<=NF_IDLE; 
              ack_o<=1;
              drive_data<=1'b0; 
			     wait_cnt<=2; 
           end 
          NF_TWR:begin
			 `NFSIGNAL<=`NFSIGNAL_IDLE;
              ack_o<=0;
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_IDLE;                    
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end
			end 
          NF_WRITE_DATA1:begin
              `NFSIGNAL<=`NFSIGNAL_DATAWR;
             drive_data<=1'b1;  
             data_out<=dat_i[7:0];
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_WRITE_DATA2;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end              
          end
          NF_WRITE_DATA2:begin
             `NFSIGNAL<=`NFSIGNAL_IDLE;
             drive_data<=1'b1;               
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 if(fast_mode) state<= NF_WRITE_DATA3;                
                 else begin 
                 state<=NF_IDLE;                 
                 ack_o<=1'b1;
                 end
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end    
          end
          /////////////////////
          NF_WRITE_DATA3:begin
              `NFSIGNAL<=`NFSIGNAL_DATAWR;
             drive_data<=1'b1;  
             data_out<=dat_i[15:8];
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_WRITE_DATA4;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end              
          end
          NF_WRITE_DATA4:begin
             `NFSIGNAL<=`NFSIGNAL_IDLE;
             drive_data<=1'b1;               
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_WRITE_DATA5;                                  
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end    
          end
          NF_WRITE_DATA5:begin
              `NFSIGNAL<=`NFSIGNAL_DATAWR;
             drive_data<=1'b1;  
             data_out<=dat_i[23:16];
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_WRITE_DATA6;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end              
          end
          NF_WRITE_DATA6:begin
             `NFSIGNAL<=`NFSIGNAL_IDLE;
             drive_data<=1'b1;               
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_WRITE_DATA7;                       
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end    
          end
          NF_WRITE_DATA7:begin
              `NFSIGNAL<=`NFSIGNAL_DATAWR;
             drive_data<=1'b1;  
             data_out<=dat_i[31:24];
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_WRITE_DATA8;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end              
          end
          NF_WRITE_DATA8:begin
             `NFSIGNAL<=`NFSIGNAL_IDLE;
             drive_data<=1'b1;               
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_IDLE;                 
                 ack_o<=1'b1;
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end    
          end
          /////////////////////
          NF_READ_DATA1:begin
              `NFSIGNAL<=`NFSIGNAL_DATARD;
              drive_data<=1'b0;               
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_READ_DATA2;
                 dat_o<={24'b0,nf_data_io};                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end              
          end
          NF_READ_DATA2:begin
             `NFSIGNAL<=`NFSIGNAL_IDLE;
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 if(fast_mode) state<=NF_READ_DATA3;
                 else begin 
                 	state<=NF_IDLE;                 
                 	ack_o<=1'b1;
                 end
                 //
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end    
          end
          /////////////////////////////
           NF_READ_DATA3:begin
              `NFSIGNAL<=`NFSIGNAL_DATARD;
              drive_data<=1'b0;               
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_READ_DATA4;
                 dat_o<={16'b0,nf_data_io,dat_o[7:0]};                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end              
          end
          NF_READ_DATA4:begin
             `NFSIGNAL<=`NFSIGNAL_IDLE;
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_READ_DATA5;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end    
          end
           NF_READ_DATA5:begin
              `NFSIGNAL<=`NFSIGNAL_DATARD;
              drive_data<=1'b0;               
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_READ_DATA6;
                 dat_o<={8'b0,nf_data_io,dat_o[15:0]};                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end              
          end
          NF_READ_DATA6:begin
             `NFSIGNAL<=`NFSIGNAL_IDLE;
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_READ_DATA7;                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end    
          end
           NF_READ_DATA7:begin
              `NFSIGNAL<=`NFSIGNAL_DATARD;
              drive_data<=1'b0;               
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_READ_DATA8;
                 dat_o<={nf_data_io,dat_o[23:0]};                 
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end              
          end
          NF_READ_DATA8:begin
             `NFSIGNAL<=`NFSIGNAL_IDLE;
              if(wait_cnt==0) begin
                 wait_cnt<=2; 
                 state<=NF_IDLE;                 
                 ack_o<=1'b1;
              end
              else begin
                 wait_cnt<=wait_cnt-1; 
              end    
          end
          /////////////////////////////
          NF_STATUS:begin
              dat_o<={1'b0,nf_cen,nf_cle,nf_ale,nf_ren,nf_wen,nf_rb};
              ack_o<=1'b1;
              state<=NF_IDLE;
          end
          default:begin 
			 	state<=NF_IDLE;
	        	data_out<=8'b0;
		        drive_data<=1'b0;
		        `NFSIGNAL<=`NFSIGNAL_IDLE;
		        wait_cnt<=0;
		        ack_o<=0;
		        {block_erase,read_id}<=2'b00;
		  end
       endcase
    end
end

endmodule