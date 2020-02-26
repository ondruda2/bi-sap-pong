library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity main is 
    generic (
--Units: pixels * 2 (50 MHz pixel clock on 100 MHz system)
        hvis :integer:= 800*2;
--        hvis :integer:= 50*2;
        hfporch :integer:= 56*2;
        hsync :integer:= 120*2;
        hbporch :integer:= 64*2;
--Units: lines
        vvis :integer:= 600;
--        vvis :integer:= 50;
        vfporch :integer:= 37;
        vsync :integer:= 6;
        vbporch :integer:= 23);
    port(
        clk : in std_logic;
        r, g, b : out std_logic_vector(3 downto 0);
        hsyncout, vsyncout: out std_logic := '0'
    );
end main;

architecture synth of main is
    signal x, y, frame: unsigned(15 downto 0) := (others => '0');
begin
    pixel_output :process(clk)
        variable tx, ty : unsigned(15 downto 0);
    begin if rising_edge(clk) then
        tx := x + 1;
        ty := y + 1;
        x <= tx;
        r <= (others => '0');
        g <= (others => '0');
        b <= (others => '0');
        hsyncout <= '0';
                    
        if tx < hvis then
            if y < vvis then
                r <= std_logic_vector(x(6 downto 3));
                g <= std_logic_vector(y(3 downto 0));
                b <= std_logic_vector(frame(6 downto 3));
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
            elsif ty < vvis + vfporch + vsync + vbporch then
                vsyncout <= '0';
            else
                y <= (others => '0');
                frame <= frame + 1;
            end if;
        end if;
    end if;
    end process;
end synth;


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity sim is
end sim;

architecture sim of sim is
signal clk : std_logic := '1';
begin
    dut : entity work.main(synth) port map (clk => clk);
    process begin
    clk <= not clk;
    wait for 5 ns;
    end process;
end sim;