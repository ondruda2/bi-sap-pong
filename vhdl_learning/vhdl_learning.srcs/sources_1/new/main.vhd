library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity main is 
    port(
        clk : in std_logic;
        r, g, b : out std_logic_vector(3 downto 0);
        hsyncout, vsyncout: out std_logic;
        switches : in std_logic_vector(15 downto 0) := (4 => '1', others => '0')
    );
    
-- Pixel clock is estimated as 65 MHz
    
--Pixels to clock cycles on Basys 3
    function mult(p : integer) return integer is
    begin
        return p * 100 / 65;
    end mult;
--Clocks to pixels on Basys 3
    function div(x : unsigned(15 downto 0)) return unsigned is
    variable tmp : unsigned(31 downto 0);
    begin
        -- GCD(65,100)
        tmp := x * 13 / 20;
        return tmp(15 downto 0);
    end div;

--Units: pixels
    constant hvis :integer:= 1024;
--    constant hvis :integer:= 64;
    constant hfporch :integer:= 24;
    constant hsync :integer:= 136;
    constant hbporch :integer:= 160;
--Units: lines
    constant vvis :integer:= 768;
--    constant vvis :integer:= 64;
    constant vfporch :integer:= 3;
    constant vsync :integer:= 6;
    constant vbporch :integer:= 29;
    
end main;

architecture synth of main is
    signal griddiv : unsigned(15 downto 0) := unsigned(switches);
    signal x, y, frame, divx: unsigned(15 downto 0) := (others => '0');
    signal thblank, tvblank : std_logic;
begin
    pixel_output :process(clk)
        variable tx, ty, realx, gx, gy : unsigned(15 downto 0);
        variable visible, output : std_logic;
        variable hblank, vblank : std_logic;
    begin if rising_edge(clk) then
        hblank := thblank;
        vblank := tvblank;
        tx := x + 1;
        ty := y;
        
        if tx = mult(hvis) then
            hblank := '1';            
        elsif tx = mult(hvis + hfporch) then
            hsyncout <= '1';
        elsif tx = mult(hvis + hfporch + hsync) then
            hsyncout <= '0';
        elsif tx = mult(hvis + hfporch + hsync  + hbporch) then
            hblank := '0';
            tx := (others => '0');
            ty := y + 1;
            
            if ty = vvis then
                vblank := '1';
            elsif ty = vvis + vfporch then 
                vsyncout <= '1';
            elsif ty = vvis + vfporch + vsync then
                vsyncout <= '0';
            elsif ty = vvis + vfporch + vsync + vbporch then
                vblank := '0';
                ty := (others => '0');
                frame <= frame + 1;
                -- per-frame logic
            end if;
            y <= ty;
        end if;
        if not hblank and not vblank then
            visible := '1';
        end if;
        x <= tx;
        thblank <= hblank;
        tvblank <= vblank;
        
        -- per-pixel logic
--        realx := div(tx);
        realx := tx;
                
--        gx := realx / griddiv;
--        gy := ty / griddiv;
        gx := shift_right(realx, 4);
        gy := shift_right(ty, 4);
        
        divx <= gx;
        
--        output := '1';        
        output := gx(0) xor gy(0);
--        output := '1' when gy = 0 or gy = shift_right(to_unsigned(vvis, 16), griddiv) else '0';       

        r <= (others => visible and output);
        g <= (others => visible and output);
        b <= (others => visible and output);
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