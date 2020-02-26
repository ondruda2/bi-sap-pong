library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity main is 
    generic (
--Units: pixels * 2 (50 MHz pixel clock on 100 MHz system)
        hvis :integer:= 800*2;
        hfporch :integer:= 56*2;
        hsync :integer:= 120*2;
        hbporch :integer:= 64*2;
--Units: lines
        vvis :integer:= 600;
        vfporch :integer:= 37;
        vsync :integer:= 6;
        vbporch :integer:= 23);
    port(
        clk : in std_logic;
        r, g, b : out std_logic_vector(0 to 3);
        hsyncout : out std_logic;
        vsyncout : out std_logic
    );
end main;

architecture synth of main is
    signal x, y: unsigned(0 to 15) := (others => '0');
begin
    pixel_output :process(clk)
        variable tx : unsigned := x + 1;
        variable ty : unsigned := y + 1;
    begin if rising_edge(clk) then
        x <= tx;
        r <= (others => '0');
        g <= (others => '0');
        b <= (others => '0');
        hsyncout <= '0';
        vsyncout <= '0';
            
        if tx < hvis then
            if y < vvis then
                r <= std_logic_vector(x(1 to 4));
                g <= std_logic_vector(y(0 to 3));
                b <= std_logic_vector(y(2 to 5));
            end if;
        elsif tx < hvis + hfporch then
        elsif tx < hvis + hfporch + hsync then
            hsyncout <= '1';
        elsif tx < hvis + hfporch + hsync  + hbporch then
        else
            x <= (others => '0');
            y <= ty;
            
            if ty < vvis then
            elsif ty < vvis + vfporch then
            elsif ty < vvis + vfporch + vsync then
                vsyncout <= '1';
            elsif ty < vvis + vfporch + vsync then
            else
                y <= (others => '0');
            end if;
        end if;
    end if;
    end process;
end synth;