-- tff.vhd
-- Toggle Flip-Flop with behavioral description
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tff is
	Port ( T 	: in  STD_LOGIC;
			CK 	: in  STD_LOGIC;
			Q, QN : out STD_LOGIC);
end tff;

architecture My_behavioral of tff is
signal mem : std_logic := '0';
begin

process (CK, T, mem) -- execute this process only when the clock changes
begin
	if T = '0' then null; -- no toggle, so do nothing
	elsif (CK'event and CK = '1') then
		mem <= not mem; -- rising edge of clock and T = 1, toggle stored value
	end if;
end process;

Q  <= mem;
QN <= not mem;
	
end;





