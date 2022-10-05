-- two_bit_counter.vhd
-- This is a simple 2-bit (Ripple) binary counter made up
-- of two T flip-flops. It also includes a clock divider
-- to bring down the input CK signal from 100 MHz to about 1 Hz.
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity twobit_counter is
    Port ( CK : in  STD_LOGIC;
           Q : out  STD_LOGIC_VECTOR (7 downto 0));
end twobit_counter;

architecture Structural of twobit_counter is

component tff
	Port ( T 	: in  STD_LOGIC;
			CK 	: in  STD_LOGIC;
			Q, QN : out STD_LOGIC);
end component;

component ck_divider
    Port ( CK_IN : in  STD_LOGIC;
           CK_OUT : out  STD_LOGIC);
end component;

signal all_T, S0, S1, S2, S3, S4, S5, S6, S7, internal_ck : STD_LOGIC;
begin

-- We use signal all_T set to logic '1' to drive
-- input T of all T flip-flops to logic '1'.
all_T <= '1';
 
CLOCK: ck_divider port map (CK, internal_ck);

TFF0: tff port map (all_T, internal_ck, Q(0), S0);
TFF1: tff port map (all_T, S0, Q(1), S1);
TFF2: tff port map (all_T, S1, Q(2), S2);
TFF3: tff port map (all_T, S2, Q(3), S3);
TFF4: tff port map (all_T, S3, Q(4), S4);
TFF5: tff port map (all_T, S4, Q(5), S5);
TFF6: tff port map (all_T, S5, Q(6), S6);
TFF7: tff port map (all_T, S6, Q(7), S7);


end Structural;

