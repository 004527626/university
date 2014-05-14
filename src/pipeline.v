`include "src/fetch/i_fetch.v"
`include "src/decode/i_decode.v"
`include "src/execute/i_execute.v"

module pipeline ();
    wire [31:0] IF_ID_instrout;
    wire [31:0] IF_ID_npcout;
    wire        EX_MEM_PCSrc;
    wire [31:0] EX_MEM_NPC;
    reg  [4:0]  regwrite;
    wire [1:0]  wb_ctlout;
    wire [2:0]  m_ctlout;
    wire        regdst,
                alusrc;
    wire [1:0]  aluop;
    wire [31:0] npcout,
                rdata1out,
                rdata2out,
                s_extendout;
    wire [4:0]  instrout_2016,
                instrout_1511;
    wire        memwrite,
                zero;

    initial begin
        regwrite     <= 5'b0;
    end

    assign EX_MEM_PCSrc = zero & memwrite;

    i_fetch i_fetch1 (.EX_MEM_PCSrc(EX_MEM_PCSrc),
                      .EX_MEM_NPC(EX_MEM_NPC),
                      .IF_ID_instr(IF_ID_instrout),
                      .IF_ID_npc(IF_ID_npcout));

    i_decode i_decode1 (.IF_ID_instrout(IF_ID_instrout),
                        .IF_ID_npcout(IF_ID_npcout),
                        .MEM_WB_rd(regwrite),
                        .MEM_WB_regwrite(EX_MEM_PCSrc),
                        .WB_mux5_writedata(EX_MEM_NPC),
                        .wb_ctlout(wb_ctlout),
                        .m_ctlout(m_ctlout),
                        .regdst(regdst),
                        .alusrc(alusrc),
                        .aluop(aluop),
                        .npcout(npcout),
                        .rdata1out(rdata1out),
                        .rdata2out(rdata2out),
                        .s_extendout(s_extendout),
                        .instrout_2016(instrout_2016),
                        .instrout_1511(instrout_1511));

    i_execute i_execute1(.wb_ctl(wb_ctlout),
                         .m_ctl(m_ctlout),
                         .regdst(regdst),
                         .alusrc(alusrc),
                         .aluop(aluop),
                         .npcout(npcout),
                         .rdata1(rdata1out),
                         .rdata2(rdata2out),
                         .s_extendout(s_extendout),
                         .instrout_2016(instrout_2016),
                         .instrout_1511(instrout_1511),
                         .memwrite(memwrite),
                         .EX_MEM_NPC(EX_MEM_NPC),
                         .zero(zero));

endmodule
