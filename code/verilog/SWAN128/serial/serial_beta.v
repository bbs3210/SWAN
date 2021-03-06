/*
 *  beta module of table's version
 *  Author: Guojun Tang 
 */
module  serial_beta( x, y);

parameter       BLOCK_SIZE = 128;
parameter       SIDE_SIZE = BLOCK_SIZE/2;
parameter       COLUMN_SIZE  = SIDE_SIZE/4;
parameter       SBOX_SIZE  = 4;

input   [0:(SIDE_SIZE-1)]   x;
output  [0:(SIDE_SIZE-1)]   y;


wire  [0:(SIDE_SIZE-1)]   y;

//input 
reg [0:SBOX_SIZE-1] s0;
reg [0:SBOX_SIZE-1] s1;
reg [0:SBOX_SIZE-1] s2;
reg [0:SBOX_SIZE-1] s3;
reg [0:SBOX_SIZE-1] s4;
reg [0:SBOX_SIZE-1] s5;
reg [0:SBOX_SIZE-1] s6;
reg [0:SBOX_SIZE-1] s7;
reg [0:SBOX_SIZE-1] s8;
reg [0:SBOX_SIZE-1] s9;
reg [0:SBOX_SIZE-1] s10;
reg [0:SBOX_SIZE-1] s11;
reg [0:SBOX_SIZE-1] s12;
reg [0:SBOX_SIZE-1] s13;
reg [0:SBOX_SIZE-1] s14;
reg [0:SBOX_SIZE-1] s15;


sbox a0(s0,   {y[0],  y[16], y[32], y[48]});
sbox a1(s1,   {y[1],  y[17], y[33], y[49]});
sbox a2(s2,   {y[2],  y[18], y[34], y[50]});
sbox a3(s3,   {y[3],  y[19], y[35], y[51]});
sbox a4(s4,   {y[4],  y[20], y[36], y[52]});
sbox a5(s5,   {y[5],  y[21], y[37], y[53]});
sbox a6(s6,   {y[6],  y[22], y[38], y[54]});
sbox a7(s7,   {y[7],  y[23], y[39], y[55]});
sbox a8(s8,   {y[8],  y[24], y[40], y[56]});
sbox a9(s9,   {y[9],  y[25], y[41], y[57]});
sbox a10(s10, {y[10], y[26], y[42], y[58]});
sbox a11(s11, {y[11], y[27], y[43], y[59]});
sbox a12(s12, {y[12], y[28], y[44], y[60]});
sbox a13(s13, {y[13], y[29], y[45], y[61]});
sbox a14(s14, {y[14], y[30], y[46], y[62]});
sbox a15(s15, {y[15], y[31], y[47], y[63]});

always@(x)
    fork
        s0 <=  {x[0], x[16], x[32],  x[48]};
        s1 <=  {x[1], x[17], x[33],  x[49]};
        s2 <=  {x[2], x[18], x[34],  x[50]};
        s3 <=  {x[3], x[19], x[35],  x[51]}; 
        s4 <=  {x[4], x[20], x[36],  x[52]};
        s5 <=  {x[5], x[21], x[37],  x[53]};
        s6 <=  {x[6], x[22], x[38],  x[54]};  
        s7 <=  {x[7], x[23], x[39],  x[55]};  
        s8 <=  {x[8], x[24], x[40],  x[56]};
        s9 <=  {x[9], x[25], x[41],  x[57]};
        s10<= {x[10], x[26], x[42], x[58]};
        s11<= {x[11], x[27], x[43], x[59]}; 
        s12<= {x[12], x[28], x[44], x[60]};
        s13<= {x[13], x[29], x[45], x[61]};
        s14<= {x[14], x[30], x[46], x[62]};  
        s15<= {x[15], x[31], x[47], x[63]};  
    join





endmodule

