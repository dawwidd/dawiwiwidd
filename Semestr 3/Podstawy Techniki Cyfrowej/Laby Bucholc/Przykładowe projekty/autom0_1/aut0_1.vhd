library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity aut2 is
port (X, CLK100: in std_logic;
Z: out std_logic_vector (3 downto 0));
end aut2;
architecture Behavioral of aut2 is
component ck_divider
    Port (
		CK_IN : in  STD_LOGIC;
		CK_OUT : out  STD_LOGIC);
end component;
type state_t is (S0, S1, S2, S3);
signal state, nextstate: state_t;
signal CLK1 : std_logic; -- output of clock divider
begin
clock : ck_divider port map (
		CK_IN => CLK100,
		CK_OUT => CLK1);	
--combinational circuit
process (state, x, CLK1)
begin
case state is
when S0 =>
if X='0' then Z<= "0010"; nextstate <= S1;
else Z<="1000"; nextstate <= S3; end if;
when S1 =>
if X='0' then Z<= "0100"; nextstate <= S2;
else Z<= "0001"; nextstate <= S0; end if;
when S2 =>
if X='0' then Z<= "1000"; nextstate <= S3;
else Z<= "0010"; nextstate <= S1; end if;
when S3 =>
if X='0' then Z<="0001"; nextstate <= S0;
else Z<="0100"; nextstate <= S2; end if;
end case;
if  rising_edge (CLK1) then
			state <= nextstate; 
			end if;
end process;


end Behavioral;
