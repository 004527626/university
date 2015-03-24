module mod3counter(
        input wire [1:0] num,
        output reg [1:0] mod3num
    );

    always @ * begin
        if (num == 2'b11) begin
            num <= 2'b00;
        end
        mod3num <= (num + 1) % 3;
    end
endmodule
